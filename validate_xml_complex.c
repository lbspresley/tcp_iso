#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <regex.h>

#include "parson.h" // parson 라이브러리 헤더

// --- 오류 정보 구조체 정의 ---
typedef struct {
    char* rule_description;
    char* error_message;
    char* xpath;
    char* expected_value;
    char* actual_value;
    int rule_index;
} ValidationError;

typedef struct {
    ValidationError* errors;
    size_t count;
    size_t capacity;
} ErrorCollection;

// --- 전방 선언 ---
char* extract_xpath_value(xmlDocPtr doc, const xmlChar* xpathExpr, xmlNodePtr context_node);
int check_element_presence(xmlDocPtr doc, const char* xpathExpr, xmlNodePtr context_node);
int validate_by_exact_value(const char* extracted_value, const char* expected_value);
int validate_by_regex(const char* extracted_value, const char* regex_pattern);
int validate_cross_element_match(xmlDocPtr doc, const char* xpath1, const char* xpath2, xmlNodePtr context_node);
// int check_value_in_list(const char* extracted_value, JSON_Array* values_array, int is_not_in_list);
int check_value_in_list(const char* extracted_value, char** values_array, size_t num_values, int is_not_in_list);

// 오류 관리 함수들
void init_error_collection(ErrorCollection* errors);
void add_validation_error(ErrorCollection* errors, const char* rule_desc, const char* error_msg, 
                         const char* xpath, const char* expected, const char* actual, int rule_idx);
void free_error_collection(ErrorCollection* errors);
void output_errors_as_json(const ErrorCollection* errors, int overall_status);

// --- 규칙 구조체 정의 ---

// 조건의 유형
typedef enum {
    COND_TYPE_NONE,
    COND_TYPE_PRESENCE,         // 요소가 존재하는지
    COND_TYPE_ABSENCE,          // 요소가 존재하지 않는지
    COND_TYPE_VALUE_IN_LIST,    // 값이 리스트에 포함되는지
    COND_TYPE_VALUE_NOT_IN_LIST,// 값이 리스트에 포함되지 않는지
    COND_TYPE_REGEX_MATCH       // 값이 정규 표현식에 매치되는지
} ConditionType;

// 액션의 유형 (검증 방식)
typedef enum {
    ACT_TYPE_NONE,
    ACT_TYPE_EXACT_VALUE,       // 정확한 값 일치
    ACT_TYPE_REGEX,             // 정규 표현식 매치
    ACT_TYPE_PRESENCE,          // 요소가 존재하는지
    ACT_TYPE_ABSENCE,           // 요소가 존재하지 않는지
    ACT_TYPE_CROSS_ELEMENT_MATCH,// 두 요소의 값 일치
    ACT_TYPE_ONE_OF_PRESENT,    // 여러 요소 중 하나 이상 존재하는지
    ACT_TYPE_ALL_PRESENT        // 여러 요소 모두 존재하는지
} ActionType;

// 일반적인 XPath 기반 검증 규칙
typedef struct {
    char* description;
    char* xpath; // 주요 XPath
    char* value; // 검증 값 (exact_value, regex)
    char* xpath1; // cross_element_match용
    char* xpath2; // cross_element_match용
    // C에서 JSON_Array를 직접 저장하기는 비효율적이므로, 별도의 StringList 또는 파싱 시 처리
} SimpleRuleData;

// 조건부 규칙 데이터
typedef struct {
    char* description; // 조건부 규칙에 대한 설명 (예: "if value is X then...")
    ConditionType type;
    char** xpaths; // 조건 요소의 XPath들 (다중 지원)
    size_t num_xpaths;
    char** values; // value_in_list / value_not_in_list 용 문자열 배열
    size_t num_values;
    char* regex_pattern; // regex_match 용
} ConditionData;

// 조건부 규칙의 액션 데이터
typedef struct {
    char* description; // 액션에 대한 설명 (예: "then element Y must be present")
    ActionType type;
    char** xpaths; // 다중 XPath 지원 (presence, absence, regex, exact_value, one_of_present, all_present)
    size_t num_xpaths;
    char* xpath1; // cross_element_match 용
    char* xpath2; // cross_element_match 용
    char* value; // exact_value, regex 용
} ActionData;

// 메인 규칙 유형
typedef enum {
    RULE_TYPE_NONE,             // None
    RULE_TYPE_SIMPLE,             // exact_value, regex
    RULE_TYPE_CROSS_ELEMENT_MATCH, // 두 XPath 값 일치
    RULE_TYPE_MUTUALLY_EXCLUSIVE_PRESENCE, // 상호 배타적 존재
    RULE_TYPE_CONDITIONAL         // 조건부 규칙 (IF-THEN)
} RuleType;

// 전체 규칙 구조체 (가장 복잡한 규칙을 포괄)
typedef struct {
    char* description;
    RuleType rule_type;
    char* context_xpath; // Conditional rules의 경우, XPath 평가의 기준 노드

    // SIMPLE, CROSS_ELEMENT_MATCH 규칙용 필드 (다중 XPath 지원)
    char** xpaths_main; // multiple xpaths for SIMPLE rules
    size_t num_xpaths_main;
    char* xpath_compare1; // xpath1 for cross_element_match
    char* xpath_compare2; // xpath2 for cross_element_match
    char* value_expected; // for exact_value or regex patterns (SIMPLE rule)
    int simple_rule_sub_type; // ACT_TYPE_EXACT_VALUE or ACT_TYPE_REGEX

    // MUTUALLY_EXCLUSIVE_PRESENCE 규칙용 필드
    char** xpaths_mutual;
    size_t num_xpaths_mutual;
    int allow_absent;

    // CONDITIONAL 규칙용 필드
    ConditionData condition;
    ActionData action;
} ValidationRule;

// --- 오류 관리 함수 구현 ---

// 오류 컬렉션 초기화
void init_error_collection(ErrorCollection* errors) {
    errors->errors = NULL;
    errors->count = 0;
    errors->capacity = 0;
}

// 검증 오류 추가
void add_validation_error(ErrorCollection* errors, const char* rule_desc, const char* error_msg, 
                         const char* xpath, const char* expected, const char* actual, int rule_idx) {
    if (errors->count >= errors->capacity) {
        size_t new_capacity = errors->capacity == 0 ? 10 : errors->capacity * 2;
        ValidationError* new_errors = (ValidationError*)realloc(errors->errors, 
                                                               sizeof(ValidationError) * new_capacity);
        if (new_errors == NULL) {
            fprintf(stderr, "Error: Failed to allocate memory for validation errors.\n");
            return;
        }
        errors->errors = new_errors;
        errors->capacity = new_capacity;
    }
    
    ValidationError* err = &errors->errors[errors->count];
    err->rule_description = rule_desc ? strdup(rule_desc) : NULL;
    err->error_message = error_msg ? strdup(error_msg) : NULL;
    err->xpath = xpath ? strdup(xpath) : NULL;
    err->expected_value = expected ? strdup(expected) : NULL;
    err->actual_value = actual ? strdup(actual) : NULL;
    err->rule_index = rule_idx;
    
    errors->count++;
}

// 오류 컬렉션 메모리 해제
void free_error_collection(ErrorCollection* errors) {
    for (size_t i = 0; i < errors->count; i++) {
        if (errors->errors[i].rule_description) free(errors->errors[i].rule_description);
        if (errors->errors[i].error_message) free(errors->errors[i].error_message);
        if (errors->errors[i].xpath) free(errors->errors[i].xpath);
        if (errors->errors[i].expected_value) free(errors->errors[i].expected_value);
        if (errors->errors[i].actual_value) free(errors->errors[i].actual_value);
    }
    if (errors->errors) free(errors->errors);
    errors->errors = NULL;
    errors->count = 0;
    errors->capacity = 0;
}

// JSON 형태로 오류 출력
void output_errors_as_json(const ErrorCollection* errors, int overall_status) {
    JSON_Value* root_value = json_value_init_object();
    JSON_Object* root_object = json_value_get_object(root_value);
    
    // 전체 검증 상태
    json_object_set_string(root_object, "validation_status", overall_status == 0 ? "PASS" : "FAIL");
    json_object_set_number(root_object, "total_errors", (double)errors->count);
    
    // 오류 배열 생성
    JSON_Value* errors_array_value = json_value_init_array();
    JSON_Array* errors_array = json_value_get_array(errors_array_value);
    
    for (size_t i = 0; i < errors->count; i++) {
        JSON_Value* error_value = json_value_init_object();
        JSON_Object* error_object = json_value_get_object(error_value);
        
        json_object_set_number(error_object, "rule_index", (double)(errors->errors[i].rule_index + 1));
        
        if (errors->errors[i].rule_description) {
            json_object_set_string(error_object, "rule_description", errors->errors[i].rule_description);
        }
        
        if (errors->errors[i].error_message) {
            json_object_set_string(error_object, "error_message", errors->errors[i].error_message);
        }
        
        if (errors->errors[i].xpath) {
            json_object_set_string(error_object, "xpath", errors->errors[i].xpath);
        }
        
        if (errors->errors[i].expected_value) {
            json_object_set_string(error_object, "expected_value", errors->errors[i].expected_value);
        }
        
        if (errors->errors[i].actual_value) {
            json_object_set_string(error_object, "actual_value", errors->errors[i].actual_value);
        }
        
        json_array_append_value(errors_array, error_value);
    }
    
    json_object_set_value(root_object, "errors", errors_array_value);
    
    // JSON 문자열로 변환 및 출력
    char* json_string = json_serialize_to_string_pretty(root_value);
    if (json_string) {
        printf("\n--- Validation Results (JSON) ---\n");
        printf("%s\n", json_string);
        json_free_serialized_string(json_string);
    }
    
    json_value_free(root_value);
}

// 동적으로 할당된 ValidationRule 구조체 배열을 해제하는 함수
void free_validation_rules(ValidationRule* rules, size_t count) {
    for (size_t i = 0; i < count; i++) {
        if (rules[i].description) free(rules[i].description);
        if (rules[i].context_xpath) free(rules[i].context_xpath);

        // Simple/Cross-element rule fields
        if (rules[i].xpaths_main) {
            for (size_t j = 0; j < rules[i].num_xpaths_main; j++) {
                if (rules[i].xpaths_main[j]) free(rules[i].xpaths_main[j]);
            }
            free(rules[i].xpaths_main);
        }
        if (rules[i].xpath_compare1) free(rules[i].xpath_compare1);
        if (rules[i].xpath_compare2) free(rules[i].xpath_compare2);
        if (rules[i].value_expected) free(rules[i].value_expected);

        // Mutually exclusive fields
        if (rules[i].xpaths_mutual) {
            for (size_t j = 0; j < rules[i].num_xpaths_mutual; j++) {
                if (rules[i].xpaths_mutual[j]) free(rules[i].xpaths_mutual[j]);
            }
            free(rules[i].xpaths_mutual);
        }

        // Conditional rule fields
        if (rules[i].condition.description) free(rules[i].condition.description);
        if (rules[i].condition.xpaths) {
            for (size_t j = 0; j < rules[i].condition.num_xpaths; j++) {
                if (rules[i].condition.xpaths[j]) free(rules[i].condition.xpaths[j]);
            }
            free(rules[i].condition.xpaths);
        }
        if (rules[i].condition.values) {
            for (size_t j = 0; j < rules[i].condition.num_values; j++) {
                if (rules[i].condition.values[j]) free(rules[i].condition.values[j]);
            }
            free(rules[i].condition.values);
        }
        if (rules[i].condition.regex_pattern) free(rules[i].condition.regex_pattern);

        if (rules[i].action.description) free(rules[i].action.description);
        if (rules[i].action.xpaths) {
            for (size_t j = 0; j < rules[i].action.num_xpaths; j++) {
                if (rules[i].action.xpaths[j]) free(rules[i].action.xpaths[j]);
            }
            free(rules[i].action.xpaths);
        }
        if (rules[i].action.xpath1) free(rules[i].action.xpath1);
        if (rules[i].action.xpath2) free(rules[i].action.xpath2);
        if (rules[i].action.value) free(rules[i].action.value);
    }
    if (rules) free(rules);
}

// JSON 문자열 배열을 C 문자열 배열로 변환하는 헬퍼 함수
char** json_array_to_string_array(JSON_Array* json_arr, size_t* num_elements) {
    *num_elements = json_array_get_count(json_arr);
    char** str_arr = (char**)malloc(sizeof(char*) * (*num_elements));
    if (str_arr == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for string array.\n");
        return NULL;
    }
    for (size_t i = 0; i < *num_elements; i++) {
        const char* s = json_array_get_string(json_arr, i);
        if (s == NULL) {
            fprintf(stderr, "Warning: Non-string element found in JSON array at index %zu. Skipping.\n", i);
            str_arr[i] = NULL; // Or handle as error
        } else {
            str_arr[i] = strdup(s);
            if (str_arr[i] == NULL) {
                fprintf(stderr, "Error: Failed to strdup string from JSON array.\n");
                // Clean up already allocated strings
                for (size_t j = 0; j < i; j++) {
                    if (str_arr[j]) free(str_arr[j]);
                }
                free(str_arr);
                return NULL;
            }
        }
    }
    return str_arr;
}


// --- JSON config 파싱 함수 ---
int load_validation_rules_from_json(const char* config_file_path, ValidationRule** out_rules, size_t* out_count) {
    JSON_Value* root_value = NULL;
    JSON_Array* rules_array = NULL;
    ValidationRule* rules = NULL;
    size_t count = 0;

    root_value = json_parse_file(config_file_path);
    if (root_value == NULL) {
        fprintf(stderr, "Error: Could not parse JSON config file '%s'.\n", config_file_path);
        return -1;
    }

    rules_array = json_value_get_array(root_value);
    if (rules_array == NULL) {
        fprintf(stderr, "Error: JSON config root is not an array.\n");
        json_value_free(root_value);
        return -1;
    }

    count = json_array_get_count(rules_array);
    rules = (ValidationRule*)calloc(count, sizeof(ValidationRule)); // Use calloc to zero-initialize
    if (rules == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for validation rules.\n");
        json_value_free(root_value);
        return -1;
    }

    for (size_t i = 0; i < count; i++) {
        JSON_Object* rule_obj = json_array_get_object(rules_array, i);
        if (rule_obj == NULL) {
            fprintf(stderr, "Warning: Skipping invalid rule object at index %zu.\n", i);
            continue;
        }

        const char* description = json_object_get_string(rule_obj, "description");
        if (description) rules[i].description = strdup(description);

        const char* type_str = json_object_get_string(rule_obj, "type");
        if (type_str == NULL) {
            fprintf(stderr, "Error: Rule at index %zu is missing 'type' field. Skipping.\n", i);
            continue;
        }

        if (strcmp(type_str, "exact_value") == 0) {
            rules[i].rule_type = RULE_TYPE_SIMPLE;
            rules[i].simple_rule_sub_type = ACT_TYPE_EXACT_VALUE;
            const char* value = json_object_get_string(rule_obj, "value");
            
            // xpath 필드가 배열인지 문자열인지 확인
            JSON_Array* xpath_array = json_object_get_array(rule_obj, "xpath");
            if (xpath_array) {
                rules[i].xpaths_main = json_array_to_string_array(xpath_array, &rules[i].num_xpaths_main);
                if (rules[i].xpaths_main == NULL) { fprintf(stderr, "Error: Failed to parse xpath array for exact_value rule %zu.\n", i); continue; }
            } else {
                const char* xpath = json_object_get_string(rule_obj, "xpath");
                if (xpath) {
                    rules[i].xpaths_main = (char**)malloc(sizeof(char*));
                    rules[i].xpaths_main[0] = strdup(xpath);
                    rules[i].num_xpaths_main = 1;
                } else { fprintf(stderr, "Error: Missing xpath for exact_value rule %zu.\n", i); continue; }
            }
            
            if (value) {
                rules[i].value_expected = strdup(value);
            } else { fprintf(stderr, "Error: Missing value for exact_value rule %zu.\n", i); continue; }
        } else if (strcmp(type_str, "regex") == 0) {
            rules[i].rule_type = RULE_TYPE_SIMPLE;
            rules[i].simple_rule_sub_type = ACT_TYPE_REGEX;
            const char* value = json_object_get_string(rule_obj, "value");
            
            // xpath 필드가 배열인지 문자열인지 확인
            JSON_Array* xpath_array = json_object_get_array(rule_obj, "xpath");
            if (xpath_array) {
                rules[i].xpaths_main = json_array_to_string_array(xpath_array, &rules[i].num_xpaths_main);
                if (rules[i].xpaths_main == NULL) { fprintf(stderr, "Error: Failed to parse xpath array for regex rule %zu.\n", i); continue; }
            } else {
                const char* xpath = json_object_get_string(rule_obj, "xpath");
                if (xpath) {
                    rules[i].xpaths_main = (char**)malloc(sizeof(char*));
                    rules[i].xpaths_main[0] = strdup(xpath);
                    rules[i].num_xpaths_main = 1;
                } else { fprintf(stderr, "Error: Missing xpath for regex rule %zu.\n", i); continue; }
            }
            
            if (value) {
                rules[i].value_expected = strdup(value);
            } else { fprintf(stderr, "Error: Missing value for regex rule %zu.\n", i); continue; }
        } else if (strcmp(type_str, "cross_element_match") == 0) {
            rules[i].rule_type = RULE_TYPE_CROSS_ELEMENT_MATCH;
            const char* xpath1 = json_object_get_string(rule_obj, "xpath1");
            const char* xpath2 = json_object_get_string(rule_obj, "xpath2");
            if (xpath1 && xpath2) {
                rules[i].xpath_compare1 = strdup(xpath1);
                rules[i].xpath_compare2 = strdup(xpath2);
            } else { fprintf(stderr, "Error: Missing xpath1/xpath2 for cross_element_match rule %zu.\n", i); continue; }
        } else if (strcmp(type_str, "mutually_exclusive_presence") == 0) {
            rules[i].rule_type = RULE_TYPE_MUTUALLY_EXCLUSIVE_PRESENCE;
            JSON_Array* xpaths_json_arr = json_object_get_array(rule_obj, "xpaths");
            if (xpaths_json_arr) {
                rules[i].xpaths_mutual = json_array_to_string_array(xpaths_json_arr, &rules[i].num_xpaths_mutual);
                if (rules[i].xpaths_mutual == NULL) { fprintf(stderr, "Error: Failed to parse xpaths for mutually_exclusive_presence rule %zu.\n", i); continue; }
            } else { fprintf(stderr, "Error: Missing 'xpaths' array for mutually_exclusive_presence rule %zu.\n", i); continue; }
            rules[i].allow_absent = (int)json_object_get_boolean(rule_obj, "allow_absent");
        } else if (strcmp(type_str, "conditional") == 0) {
            rules[i].rule_type = RULE_TYPE_CONDITIONAL;
            const char* context_xpath = json_object_get_string(rule_obj, "context_xpath");
            if (context_xpath) rules[i].context_xpath = strdup(context_xpath);

            JSON_Object* cond_obj = json_object_get_object(rule_obj, "condition");
            JSON_Object* act_obj = json_object_get_object(rule_obj, "action");

            if (cond_obj == NULL || act_obj == NULL) {
                fprintf(stderr, "Error: Conditional rule %zu is missing 'condition' or 'action' object.\n", i);
                continue;
            }

            // Parse Condition
            const char* cond_desc = json_object_get_string(cond_obj, "description");
            if (cond_desc) rules[i].condition.description = strdup(cond_desc);
            const char* cond_type_str = json_object_get_string(cond_obj, "type");
            
            // xpath 필드가 배열인지 문자열인지 확인
            JSON_Array* cond_xpath_array = json_object_get_array(cond_obj, "xpath");
            if (cond_xpath_array) {
                rules[i].condition.xpaths = json_array_to_string_array(cond_xpath_array, &rules[i].condition.num_xpaths);
                if (rules[i].condition.xpaths == NULL) { fprintf(stderr, "Error: Failed to parse condition xpath array for rule %zu.\n", i); continue; }
            } else {
                const char* cond_xpath = json_object_get_string(cond_obj, "xpath");
                if (cond_xpath) {
                    rules[i].condition.xpaths = (char**)malloc(sizeof(char*));
                    rules[i].condition.xpaths[0] = strdup(cond_xpath);
                    rules[i].condition.num_xpaths = 1;
                } else { fprintf(stderr, "Error: Missing xpath for condition in rule %zu.\n", i); continue; }
            }
            
            if (cond_type_str) {
                if (strcmp(cond_type_str, "presence") == 0) rules[i].condition.type = COND_TYPE_PRESENCE;
                else if (strcmp(cond_type_str, "absence") == 0) rules[i].condition.type = COND_TYPE_ABSENCE;
                else if (strcmp(cond_type_str, "value_in_list") == 0) {
                    rules[i].condition.type = COND_TYPE_VALUE_IN_LIST;
                    JSON_Array* values_json_arr = json_object_get_array(cond_obj, "values");
                    if (values_json_arr) {
                        rules[i].condition.values = json_array_to_string_array(values_json_arr, &rules[i].condition.num_values);
                        if (rules[i].condition.values == NULL) { fprintf(stderr, "Error: Failed to parse condition values for rule %zu.\n", i); continue; }
                    } else { fprintf(stderr, "Error: Missing 'values' array for conditional rule %zu.\n", i); continue; }
                }
                else if (strcmp(cond_type_str, "value_not_in_list") == 0) {
                    rules[i].condition.type = COND_TYPE_VALUE_NOT_IN_LIST;
                    JSON_Array* values_json_arr = json_object_get_array(cond_obj, "values");
                    if (values_json_arr) {
                        rules[i].condition.values = json_array_to_string_array(values_json_arr, &rules[i].condition.num_values);
                        if (rules[i].condition.values == NULL) { fprintf(stderr, "Error: Failed to parse condition values for rule %zu.\n", i); continue; }
                    } else { fprintf(stderr, "Error: Missing 'values' array for conditional rule %zu.\n", i); continue; }
                }
                else if (strcmp(cond_type_str, "regex_match") == 0) {
                    rules[i].condition.type = COND_TYPE_REGEX_MATCH;
                    const char* regex_pattern = json_object_get_string(cond_obj, "value");
                    if (regex_pattern) rules[i].condition.regex_pattern = strdup(regex_pattern);
                    else { fprintf(stderr, "Error: Missing regex pattern for conditional rule %zu.\n", i); continue; }
                }
                else { fprintf(stderr, "Error: Unknown condition type '%s' for rule %zu.\n", cond_type_str, i); continue; }
            } else { fprintf(stderr, "Error: Missing type/xpath for condition in rule %zu.\n", i); continue; }

            // Parse Action
            const char* act_desc = json_object_get_string(act_obj, "description");
            if (act_desc) rules[i].action.description = strdup(act_desc);
            const char* act_type_str = json_object_get_string(act_obj, "type");
            if (act_type_str == NULL) {
                fprintf(stderr, "Error: Action for conditional rule %zu is missing 'type' field.\n", i);
                continue;
            }

            if (strcmp(act_type_str, "presence") == 0) {
                rules[i].action.type = ACT_TYPE_PRESENCE;
                // xpath 필드가 배열인지 문자열인지 확인
                JSON_Array* xpath_array = json_object_get_array(act_obj, "xpath");
                if (xpath_array) {
                    rules[i].action.xpaths = json_array_to_string_array(xpath_array, &rules[i].action.num_xpaths);
                    if (rules[i].action.xpaths == NULL) { fprintf(stderr, "Error: Failed to parse action xpath array for rule %zu.\n", i); continue; }
                } else {
                    const char* xpath = json_object_get_string(act_obj, "xpath");
                    if (xpath) {
                        rules[i].action.xpaths = (char**)malloc(sizeof(char*));
                        rules[i].action.xpaths[0] = strdup(xpath);
                        rules[i].action.num_xpaths = 1;
                    } else { fprintf(stderr, "Error: Missing xpath for action type presence in rule %zu.\n", i); continue; }
                }
            } else if (strcmp(act_type_str, "absence") == 0) {
                rules[i].action.type = ACT_TYPE_ABSENCE;
                // xpath 필드가 배열인지 문자열인지 확인
                JSON_Array* xpath_array = json_object_get_array(act_obj, "xpath");
                if (xpath_array) {
                    rules[i].action.xpaths = json_array_to_string_array(xpath_array, &rules[i].action.num_xpaths);
                    if (rules[i].action.xpaths == NULL) { fprintf(stderr, "Error: Failed to parse action xpath array for rule %zu.\n", i); continue; }
                } else {
                    const char* xpath = json_object_get_string(act_obj, "xpath");
                    if (xpath) {
                        rules[i].action.xpaths = (char**)malloc(sizeof(char*));
                        rules[i].action.xpaths[0] = strdup(xpath);
                        rules[i].action.num_xpaths = 1;
                    } else { fprintf(stderr, "Error: Missing xpath for action type absence in rule %zu.\n", i); continue; }
                }
            } else if (strcmp(act_type_str, "exact_value") == 0) {
                rules[i].action.type = ACT_TYPE_EXACT_VALUE;
                const char* value = json_object_get_string(act_obj, "value");
                // xpath 필드가 배열인지 문자열인지 확인
                JSON_Array* xpath_array = json_object_get_array(act_obj, "xpath");
                if (xpath_array) {
                    rules[i].action.xpaths = json_array_to_string_array(xpath_array, &rules[i].action.num_xpaths);
                    if (rules[i].action.xpaths == NULL) { fprintf(stderr, "Error: Failed to parse action xpath array for rule %zu.\n", i); continue; }
                } else {
                    const char* xpath = json_object_get_string(act_obj, "xpath");
                    if (xpath) {
                        rules[i].action.xpaths = (char**)malloc(sizeof(char*));
                        rules[i].action.xpaths[0] = strdup(xpath);
                        rules[i].action.num_xpaths = 1;
                    } else { fprintf(stderr, "Error: Missing xpath for action type exact_value in rule %zu.\n", i); continue; }
                }
                if (value) {
                    rules[i].action.value = strdup(value);
                } else { fprintf(stderr, "Error: Missing value for action type exact_value in rule %zu.\n", i); continue; }
            } else if (strcmp(act_type_str, "regex") == 0) {
                rules[i].action.type = ACT_TYPE_REGEX;
                const char* value = json_object_get_string(act_obj, "value");
                // xpath 필드가 배열인지 문자열인지 확인
                JSON_Array* xpath_array = json_object_get_array(act_obj, "xpath");
                if (xpath_array) {
                    rules[i].action.xpaths = json_array_to_string_array(xpath_array, &rules[i].action.num_xpaths);
                    if (rules[i].action.xpaths == NULL) { fprintf(stderr, "Error: Failed to parse action xpath array for rule %zu.\n", i); continue; }
                } else {
                    const char* xpath = json_object_get_string(act_obj, "xpath");
                    if (xpath) {
                        rules[i].action.xpaths = (char**)malloc(sizeof(char*));
                        rules[i].action.xpaths[0] = strdup(xpath);
                        rules[i].action.num_xpaths = 1;
                    } else { fprintf(stderr, "Error: Missing xpath for action type regex in rule %zu.\n", i); continue; }
                }
                if (value) {
                    rules[i].action.value = strdup(value);
                } else { fprintf(stderr, "Error: Missing value for action type regex in rule %zu.\n", i); continue; }
            } else if (strcmp(act_type_str, "cross_element_match") == 0) {
                rules[i].action.type = ACT_TYPE_CROSS_ELEMENT_MATCH;
                const char* xpath1 = json_object_get_string(act_obj, "xpath1");
                const char* xpath2 = json_object_get_string(act_obj, "xpath2");
                if (xpath1 && xpath2) {
                    rules[i].action.xpath1 = strdup(xpath1);
                    rules[i].action.xpath2 = strdup(xpath2);
                } else { fprintf(stderr, "Error: Missing xpath1/xpath2 for action type cross_element_match in rule %zu.\n", i); continue; }
            } else if (strcmp(act_type_str, "one_of_present") == 0 || strcmp(act_type_str, "all_present") == 0) {
                rules[i].action.type = (strcmp(act_type_str, "one_of_present") == 0) ? ACT_TYPE_ONE_OF_PRESENT : ACT_TYPE_ALL_PRESENT;
                // xpaths 또는 xpath 필드 처리
                JSON_Array* xpaths_json_arr = json_object_get_array(act_obj, "xpaths");
                if (xpaths_json_arr) {
                    rules[i].action.xpaths = json_array_to_string_array(xpaths_json_arr, &rules[i].action.num_xpaths);
                    if (rules[i].action.xpaths == NULL) { fprintf(stderr, "Error: Failed to parse action xpaths for rule %zu.\n", i); continue; }
                } else {
                    // xpath 필드로 시도
                    JSON_Array* xpath_array = json_object_get_array(act_obj, "xpath");
                    if (xpath_array) {
                        rules[i].action.xpaths = json_array_to_string_array(xpath_array, &rules[i].action.num_xpaths);
                        if (rules[i].action.xpaths == NULL) { fprintf(stderr, "Error: Failed to parse action xpath array for rule %zu.\n", i); continue; }
                    } else { fprintf(stderr, "Error: Missing 'xpaths' or 'xpath' array for action type %s in rule %zu.\n", act_type_str, i); continue; }
                }
            } else {
                fprintf(stderr, "Error: Unknown action type '%s' for rule %zu.\n", act_type_str, i);
                continue;
            }
        } else {
            fprintf(stderr, "Error: Unknown rule type '%s' for rule %zu. Skipping.\n", type_str, i);
            continue;
        }
    }

    json_value_free(root_value);
    *out_rules = rules;
    *out_count = count;
    return 0;
}

// --- XML 파싱 및 XPath 헬퍼 함수 ---

// XPath를 평가할 XML 노드 컨텍스트를 찾아 반환
xmlNodePtr get_xpath_context_node(xmlDocPtr doc, const char* context_xpath_str) {
    if (context_xpath_str == NULL) {
        return (xmlNodePtr)doc; // 문서 루트를 컨텍스트로 사용
    }

    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        fprintf(stderr, "Error: Could not create XPath context for context_node lookup.\n");
        return NULL;
    }

    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar*)context_xpath_str, xpathCtx);
    if (xpathObj == NULL) {
        fprintf(stderr, "Error: Could not evaluate context XPath expression '%s'.\n", context_xpath_str);
        xmlXPathFreeContext(xpathCtx);
        return NULL;
    }

    xmlNodePtr context_node = NULL;
    if (xpathObj->type == XPATH_NODESET && !xmlXPathNodeSetIsEmpty(xpathObj->nodesetval)) {
        context_node = xpathObj->nodesetval->nodeTab[0]; // 첫 번째 노드를 컨텍스트로 사용
    } else {
        fprintf(stderr, "Warning: Context XPath '%s' did not resolve to a node. Using document root.\n", context_xpath_str);
        context_node = (xmlNodePtr)doc;
    }

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    return context_node;
}


// 특정 XPath에서 값을 추출하는 헬퍼 함수 (컨텍스트 노드 지원 추가)
char* extract_xpath_value(xmlDocPtr doc, const xmlChar* xpathExpr, xmlNodePtr context_node) {
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    char* value = NULL;

    if (context_node == NULL) { // No specific context, use document root
        xpathCtx = xmlXPathNewContext(doc);
    } else { // Use specific context node
        xpathCtx = xmlXPathNewContext(doc);
        xpathCtx->node = context_node; // Set the evaluation context node
    }
    
    if (xpathCtx == NULL) {
        fprintf(stderr, "Error: Could not create XPath context.\n");
        return NULL;
    }

    xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
    if (xpathObj == NULL) {
        fprintf(stderr, "Error: Could not evaluate XPath expression '%s'.\n", xpathExpr);
        xmlXPathFreeContext(xpathCtx);
        return NULL;
    }

    if (xpathObj->type == XPATH_NODESET && !xmlXPathNodeSetIsEmpty(xpathObj->nodesetval)) {
        xmlNodePtr node = xpathObj->nodesetval->nodeTab[0];
        if (node != NULL && node->type == XML_TEXT_NODE) {
             value = (char*)xmlStrdup(node->content);
        } else if (node != NULL && node->type == XML_ELEMENT_NODE) {
            xmlNodePtr child = node->children;
            while (child != NULL) {
                if (child->type == XML_TEXT_NODE) {
                    value = (char*)xmlStrdup(child->content);
                    break;
                }
                child = child->next;
            }
             if (value == NULL) { // Element node might have no text child but still be considered "present"
                 // If the element itself is the target and we just need presence, this is fine.
                 // If we strictly need text content and it's missing, NULL is correct.
             }
        }
    } else if (xpathObj->type == XPATH_STRING) {
        value = (char*)xmlStrdup(xpathObj->stringval);
    } else if (xpathObj->type == XPATH_BOOLEAN) {
        // XPath might return a boolean (e.g., boolean(xpath))
        value = (char*)xmlStrdup(xpathObj->boolval ? (const xmlChar*)"true" : (const xmlChar*)"false");
    } else if (xpathObj->type == XPATH_NUMBER) {
        char buf[64];
        snprintf(buf, sizeof(buf), "%.0f", xpathObj->floatval); // Or use %f for float values
        value = (char*)xmlStrdup((const xmlChar*)buf);
    }


    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);

    return value;
}

// 요소의 존재 여부를 확인하는 헬퍼 함수
int check_element_presence(xmlDocPtr doc, const char* xpathExpr, xmlNodePtr context_node) {
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    int is_present = 0;

    if (context_node == NULL) {
        xpathCtx = xmlXPathNewContext(doc);
    } else {
        xpathCtx = xmlXPathNewContext(doc);
        xpathCtx->node = context_node;
    }
    
    if (xpathCtx == NULL) {
        fprintf(stderr, "Error: Could not create XPath context for presence check.\n");
        return 0;
    }

    // XPath 표현식을 평가하여 노드 집합을 얻음
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpathExpr, xpathCtx);
    if (xpathObj == NULL) {
        // fprintf(stderr, "Error: Could not evaluate XPath expression '%s' for presence check.\n", xpathExpr);
        xmlXPathFreeContext(xpathCtx);
        return 0;
    }

    if (xpathObj->type == XPATH_NODESET && !xmlXPathNodeSetIsEmpty(xpathObj->nodesetval)) {
        is_present = 1; // 노드가 하나 이상 존재함
    }

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    return is_present;
}


// --- 유효성 검증 로직 함수들 ---

// 추출된 값이 특정 문자열과 일치하는지 검증하는 함수
int validate_by_exact_value(const char* extracted_value, const char* expected_value) {
    if (extracted_value == NULL || expected_value == NULL) {
        return 0;
    }
    return strcmp(extracted_value, expected_value) == 0;
}

// 추출된 값이 정규 표현식에 매치되는지 검증하는 함수
int validate_by_regex(const char* extracted_value, const char* regex_pattern) {
    if (extracted_value == NULL || regex_pattern == NULL) {
        return 0;
    }

    regex_t regex;
    int reti;
    int result = 0;

    reti = regcomp(&regex, regex_pattern, REG_EXTENDED | REG_NOSUB);
    if (reti) {
        fprintf(stderr, "Error: Could not compile regex '%s'\n", regex_pattern);
        return 0;
    }

    reti = regexec(&regex, extracted_value, 0, NULL, 0);
    if (!reti) {
        result = 1;
    } else if (reti == REG_NOMATCH) {
        result = 0;
    } else {
        char errbuf[100];
        regerror(reti, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex match failed: %s\n", errbuf);
        result = 0;
    }

    regfree(&regex);
    return result;
}

// 두 추출된 값이 일치하는지 검증하는 함수 (XML 컨텍스트에서 직접 추출)
int validate_cross_element_match(xmlDocPtr doc, const char* xpath1, const char* xpath2, xmlNodePtr context_node) {
    char* value1 = extract_xpath_value(doc, (const xmlChar*)xpath1, context_node);
    char* value2 = extract_xpath_value(doc, (const xmlChar*)xpath2, context_node);

    int result = validate_by_exact_value(value1, value2);

    if (value1) xmlFree(value1);
    if (value2) xmlFree(value2);
    return result;
}

// 값이 주어진 문자열 리스트에 포함되는지/포함되지 않는지 확인
int check_value_in_list(const char* extracted_value, char** values_array, size_t num_values, int is_not_in_list) {
    if (extracted_value == NULL || values_array == NULL || num_values == 0) {
        return is_not_in_list ? 1 : 0; // if not in list, and no values, then true for 'not in list'
    }

    int found = 0;
    for (size_t i = 0; i < num_values; i++) {
        if (values_array[i] && strcmp(extracted_value, values_array[i]) == 0) {
            found = 1;
            break;
        }
    }

    return is_not_in_list ? !found : found;
}

// 상호 배타적 존재 규칙 검증
int validate_mutually_exclusive_presence(xmlDocPtr doc, char** xpaths, size_t num_xpaths, int allow_absent) {
    int present_count = 0;
    for (size_t i = 0; i < num_xpaths; i++) {
        if (check_element_presence(doc, xpaths[i], NULL)) { // Assume top-level XPath for mutual exclusivity
            present_count++;
        }
    }

    if (present_count == 0) {
        return allow_absent; // 모두 부재하는 경우 allow_absent에 따름
    } else if (present_count == 1) {
        return 1; // 하나만 존재하는 경우 유효
    } else {
        return 0; // 두 개 이상 존재하는 경우 유효하지 않음
    }
}

// 조건 평가 함수 (다중 XPath 지원)
int evaluate_condition(xmlDocPtr doc, const ConditionData* condition, xmlNodePtr context_node) {
    char* extracted_val = NULL;
    int result = 0;

    // 다중 XPath의 경우 모든 XPath에 대해 조건이 만족되어야 함 (AND 로직)
    for (size_t xpath_idx = 0; xpath_idx < condition->num_xpaths; xpath_idx++) {
        const char* current_xpath = condition->xpaths[xpath_idx];
        int current_result = 0;
        
        switch (condition->type) {
            case COND_TYPE_PRESENCE:
                current_result = check_element_presence(doc, current_xpath, context_node);
                break;
            case COND_TYPE_ABSENCE:
                current_result = !check_element_presence(doc, current_xpath, context_node);
                break;
            case COND_TYPE_VALUE_IN_LIST:
                extracted_val = extract_xpath_value(doc, (const xmlChar*)current_xpath, context_node);
                current_result = check_value_in_list(extracted_val, condition->values, condition->num_values, 0);
                if (extracted_val) xmlFree(extracted_val);
                break;
            case COND_TYPE_VALUE_NOT_IN_LIST:
                extracted_val = extract_xpath_value(doc, (const xmlChar*)current_xpath, context_node);
                current_result = check_value_in_list(extracted_val, condition->values, condition->num_values, 1);
                if (extracted_val) xmlFree(extracted_val);
                break;
            case COND_TYPE_REGEX_MATCH:
                extracted_val = extract_xpath_value(doc, (const xmlChar*)current_xpath, context_node);
                current_result = validate_by_regex(extracted_val, condition->regex_pattern);
                if (extracted_val) xmlFree(extracted_val);
                break;
            case COND_TYPE_NONE:
            default:
                fprintf(stderr, "Error: Unknown condition type in rule.\n");
                return 0;
        }
        
        if (xpath_idx == 0) {
            result = current_result;
        } else {
            result = result && current_result; // AND 로직
        }
        
        // 하나라도 실패하면 조기 종료
        if (!result) break;
    }
    
    return result;
}

// 액션 실행 함수 (다중 XPath 지원)
int execute_action(xmlDocPtr doc, const ActionData* action, xmlNodePtr context_node) {
    char* extracted_val = NULL;
    int result = 0;

    switch (action->type) {
        case ACT_TYPE_PRESENCE: {
            // 모든 XPath가 존재해야 함 (AND 로직)
            result = 1;
            for (size_t i = 0; i < action->num_xpaths; i++) {
                if (!check_element_presence(doc, action->xpaths[i], context_node)) {
                    result = 0;
                    break;
                }
            }
            break;
        }
        case ACT_TYPE_ABSENCE: {
            // 모든 XPath가 존재하지 않아야 함 (AND 로직)
            result = 1;
            for (size_t i = 0; i < action->num_xpaths; i++) {
                if (check_element_presence(doc, action->xpaths[i], context_node)) {
                    result = 0;
                    break;
                }
            }
            break;
        }
        case ACT_TYPE_EXACT_VALUE: {
            // 모든 XPath의 값이 예상 값과 일치해야 함 (AND 로직)
            result = 1;
            for (size_t i = 0; i < action->num_xpaths; i++) {
                extracted_val = extract_xpath_value(doc, (const xmlChar*)action->xpaths[i], context_node);
                if (!validate_by_exact_value(extracted_val, action->value)) {
                    result = 0;
                    if (extracted_val) xmlFree(extracted_val);
                    break;
                }
                if (extracted_val) xmlFree(extracted_val);
            }
            break;
        }
        case ACT_TYPE_REGEX: {
            // 모든 XPath의 값이 정규식과 일치해야 함 (AND 로직)
            result = 1;
            for (size_t i = 0; i < action->num_xpaths; i++) {
                extracted_val = extract_xpath_value(doc, (const xmlChar*)action->xpaths[i], context_node);
                if (!validate_by_regex(extracted_val, action->value)) {
                    result = 0;
                    if (extracted_val) xmlFree(extracted_val);
                    break;
                }
                if (extracted_val) xmlFree(extracted_val);
            }
            break;
        }
        case ACT_TYPE_CROSS_ELEMENT_MATCH:
            result = validate_cross_element_match(doc, action->xpath1, action->xpath2, context_node);
            break;
        case ACT_TYPE_ONE_OF_PRESENT: {
            int found_one = 0;
            for (size_t i = 0; i < action->num_xpaths; i++) {
                if (check_element_presence(doc, action->xpaths[i], context_node)) {
                    found_one = 1;
                    break;
                }
            }
            result = found_one;
            break;
        }
        case ACT_TYPE_ALL_PRESENT: {
            int all_found = 1;
            for (size_t i = 0; i < action->num_xpaths; i++) {
                if (!check_element_presence(doc, action->xpaths[i], context_node)) {
                    all_found = 0;
                    break;
                }
            }
            result = all_found;
            break;
        }
        case ACT_TYPE_NONE:
        default:
            fprintf(stderr, "Error: Unknown action type in rule.\n");
            return 0;
    }
    return result;
}


// --- 메인 함수 ---
int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <xml_file> <config_file>\n", argv[0]);
        return 1;
    }

    const char* xml_file = argv[1];
    const char* config_file = argv[2];
    xmlDocPtr doc = NULL;
    int overall_validation_status = 0; // 0 = all passed, 1 = at least one failed

    ValidationRule* rules = NULL;
    size_t num_rules = 0;
    
    // 오류 컬렉션 초기화
    ErrorCollection validation_errors;
    init_error_collection(&validation_errors);

    LIBXML_TEST_VERSION

    doc = xmlReadFile(xml_file, NULL, 0);
    if (doc == NULL) {
        fprintf(stderr, "Error: Could not parse XML file %s\n", xml_file);
        return 1;
    }

    printf("Loading validation rules from '%s'...\n", config_file);
    if (load_validation_rules_from_json(config_file, &rules, &num_rules) != 0) {
        fprintf(stderr, "Error: Failed to load validation rules.\n");
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return 1;
    }

    printf("Successfully loaded %zu rules.\n", num_rules);
    printf("\n--- Starting XML Validation based on Configured Rules ---\n");

    for (size_t i = 0; i < num_rules; i++) {
        printf("\nRule %zu: '%s'\n", i + 1, rules[i].description ? rules[i].description : "No description");
        int current_rule_status = 0;

        // Determine the context node for the current rule
        xmlNodePtr rule_context_node = NULL;
        if (rules[i].context_xpath) {
            rule_context_node = get_xpath_context_node(doc, rules[i].context_xpath);
            if (rule_context_node == NULL) {
                fprintf(stderr, "Warning: Context XPath '%s' for Rule %zu not found. Rule may not be evaluated correctly.\n",
                        rules[i].context_xpath, i + 1);
                // Decide how to handle: skip rule, or evaluate against document root
                // For now, if context not found, we will fail the rule
                printf("  Result: FAIL (Context XPath not found or invalid)\n");
                
                add_validation_error(&validation_errors, 
                                    rules[i].description,
                                    "Context XPath not found or invalid",
                                    rules[i].context_xpath,
                                    "Valid context node",
                                    "Context XPath evaluation failed",
                                    i);
                
                overall_validation_status = 1;
                continue;
            }
        } else {
            rule_context_node = (xmlNodePtr)doc; // Default to document root
        }


        switch (rules[i].rule_type) {
            case RULE_TYPE_SIMPLE: {
                printf("  Type: Simple Rule (%s)\n", 
                       rules[i].simple_rule_sub_type == ACT_TYPE_EXACT_VALUE ? "Exact Value" : "Regex");
                printf("  Expected: '%s'\n", rules[i].value_expected);
                printf("  XPaths to check: %zu\n", rules[i].num_xpaths_main);
                
                current_rule_status = 1; // 기본적으로 성공으로 시작
                
                // 모든 XPath에 대해 검증 수행
                for (size_t xpath_idx = 0; xpath_idx < rules[i].num_xpaths_main; xpath_idx++) {
                    char* extracted_value = extract_xpath_value(doc, (const xmlChar*)rules[i].xpaths_main[xpath_idx], rule_context_node);
                    printf("    XPath[%zu]: %s\n", xpath_idx + 1, rules[i].xpaths_main[xpath_idx]);
                    
                    if (extracted_value) {
                        printf("    Extracted value: '%s'\n", extracted_value);
                        int xpath_result = 0;
                        
                        if (rules[i].simple_rule_sub_type == ACT_TYPE_EXACT_VALUE) {
                            xpath_result = validate_by_exact_value(extracted_value, rules[i].value_expected);
                        } else if (rules[i].simple_rule_sub_type == ACT_TYPE_REGEX) {
                            xpath_result = validate_by_regex(extracted_value, rules[i].value_expected);
                        }
                        
                        if (!xpath_result) {
                            current_rule_status = 0; // 하나라도 실패하면 전체 실패
                            add_validation_error(&validation_errors, 
                                                rules[i].description,
                                                rules[i].simple_rule_sub_type == ACT_TYPE_EXACT_VALUE ? 
                                                    "Value does not match expected exact value" : 
                                                    "Value does not match regex pattern",
                                                rules[i].xpaths_main[xpath_idx],
                                                rules[i].value_expected,
                                                extracted_value,
                                                i);
                        }
                        xmlFree(extracted_value);
                    } else {
                        printf("    Extracted value: NOT FOUND or EMPTY\n");
                        current_rule_status = 0; // Value not found, so simple validation fails
                        add_validation_error(&validation_errors, 
                                            rules[i].description,
                                            "XPath element not found or empty",
                                            rules[i].xpaths_main[xpath_idx],
                                            rules[i].value_expected,
                                            "NOT FOUND",
                                            i);
                    }
                }
                break;
            }
            case RULE_TYPE_CROSS_ELEMENT_MATCH: {
                printf("  Type: Cross-Element Match\n");
                printf("  XPath1: %s\n", rules[i].xpath_compare1);
                printf("  XPath2: %s\n", rules[i].xpath_compare2);
                current_rule_status = validate_cross_element_match(doc, rules[i].xpath_compare1, rules[i].xpath_compare2, rule_context_node);
                
                if (current_rule_status) {
                    printf("  Values match.\n");
                } else {
                    printf("  Values do NOT match.\n");
                    // 실제 값들을 추출해서 오류 정보에 포함
                    char* value1 = extract_xpath_value(doc, (const xmlChar*)rules[i].xpath_compare1, rule_context_node);
                    char* value2 = extract_xpath_value(doc, (const xmlChar*)rules[i].xpath_compare2, rule_context_node);
                    
                    char xpath_info[1024];
                    snprintf(xpath_info, sizeof(xpath_info), "XPath1: %s, XPath2: %s", 
                            rules[i].xpath_compare1, rules[i].xpath_compare2);
                    
                    char actual_info[1024];
                    snprintf(actual_info, sizeof(actual_info), "Value1: %s, Value2: %s", 
                            value1 ? value1 : "NOT FOUND", value2 ? value2 : "NOT FOUND");
                    
                    add_validation_error(&validation_errors, 
                                        rules[i].description,
                                        "Cross-element values do not match",
                                        xpath_info,
                                        "Values should match",
                                        actual_info,
                                        i);
                    
                    if (value1) xmlFree(value1);
                    if (value2) xmlFree(value2);
                }
                break;
            }
            case RULE_TYPE_MUTUALLY_EXCLUSIVE_PRESENCE: {
                printf("  Type: Mutually Exclusive Presence\n");
                printf("  Xpaths to check: [");
                for(size_t j=0; j<rules[i].num_xpaths_mutual; ++j) {
                    printf("'%s'%s", rules[i].xpaths_mutual[j], (j == rules[i].num_xpaths_mutual - 1) ? "" : ", ");
                }
                printf("]\n");
                printf("  Allow Absent: %s\n", rules[i].allow_absent ? "True" : "False");
                current_rule_status = validate_mutually_exclusive_presence(doc, rules[i].xpaths_mutual, rules[i].num_xpaths_mutual, rules[i].allow_absent);
                
                if (!current_rule_status) {
                    // 어떤 요소들이 존재하는지 확인하여 상세 정보 제공
                    char present_elements[2048] = "";
                    int present_count = 0;
                    for (size_t j = 0; j < rules[i].num_xpaths_mutual; j++) {
                        if (check_element_presence(doc, rules[i].xpaths_mutual[j], NULL)) {
                            if (present_count > 0) strcat(present_elements, ", ");
                            strcat(present_elements, rules[i].xpaths_mutual[j]);
                            present_count++;
                        }
                    }
                    
                    char all_xpaths[2048] = "";
                    for (size_t j = 0; j < rules[i].num_xpaths_mutual; j++) {
                        if (j > 0) strcat(all_xpaths, ", ");
                        strcat(all_xpaths, rules[i].xpaths_mutual[j]);
                    }
                    
                    char error_msg[512];
                    if (present_count == 0 && !rules[i].allow_absent) {
                        snprintf(error_msg, sizeof(error_msg), "All elements are absent but at least one should be present");
                    } else if (present_count > 1) {
                        snprintf(error_msg, sizeof(error_msg), "Multiple elements are present (%d found) but only one should exist", present_count);
                    } else {
                        snprintf(error_msg, sizeof(error_msg), "Mutually exclusive presence validation failed");
                    }
                    
                    add_validation_error(&validation_errors, 
                                        rules[i].description,
                                        error_msg,
                                        all_xpaths,
                                        "Only one element should be present",
                                        present_count > 0 ? present_elements : "No elements present",
                                        i);
                }
                break;
            }
            case RULE_TYPE_CONDITIONAL: {
                printf("  Type: Conditional Rule\n");
                printf("  Context XPath: %s\n", rules[i].context_xpath ? rules[i].context_xpath : "/ (document root)");
                printf("  Condition: '%s' (XPaths: %zu)\n", rules[i].condition.description, rules[i].condition.num_xpaths);

                int condition_met = evaluate_condition(doc, &rules[i].condition, rule_context_node);
                if (condition_met) {
                    printf("  Condition MET. Executing action: '%s'\n", rules[i].action.description);
                    current_rule_status = execute_action(doc, &rules[i].action, rule_context_node);
                    
                    if (!current_rule_status) {
                        // 액션 실행 실패 시 상세 오류 정보 수집
                        char context_info[2048] = "Condition XPaths: ";
                        for (size_t j = 0; j < rules[i].condition.num_xpaths; j++) {
                            if (j > 0) strcat(context_info, ", ");
                            strcat(context_info, rules[i].condition.xpaths[j]);
                        }
                        strcat(context_info, "; Action XPaths: ");
                        for (size_t j = 0; j < rules[i].action.num_xpaths; j++) {
                            if (j > 0) strcat(context_info, ", ");
                            strcat(context_info, rules[i].action.xpaths[j]);
                        }
                        
                        add_validation_error(&validation_errors, 
                                            rules[i].description,
                                            "Conditional rule action failed",
                                            context_info,
                                            rules[i].action.value ? rules[i].action.value : "Action should succeed",
                                            "Action validation failed",
                                            i);
                    }
                } else {
                    printf("  Condition NOT MET. Action skipped.\n");
                    current_rule_status = 1; // Condition not met, so rule passes (action not required)
                }
                break;
            }
            case RULE_TYPE_NONE:
            default:
                fprintf(stderr, "Skipping invalid/unsupported rule type for rule %zu.\n", i + 1);
                current_rule_status = 0; // Treat as failed if rule type is unknown/invalid
                
                add_validation_error(&validation_errors, 
                                    rules[i].description,
                                    "Invalid or unsupported rule type",
                                    "N/A",
                                    "Valid rule type",
                                    "Unknown rule type",
                                    i);
                break;
        }

        if (current_rule_status) {
            printf("  Result: PASS\n");
        } else {
            printf("  Result: FAIL\n");
            overall_validation_status = 1;
        }
    }

    printf("\n--- XML Validation Summary ---\n");
    if (overall_validation_status == 0) {
        printf("All rules passed successfully!\n");
    } else {
        printf("One or more rules failed validation.\n");
    }

    // JSON 형태로 검증 결과 출력
    output_errors_as_json(&validation_errors, overall_validation_status);

    // 메모리 정리
    free_error_collection(&validation_errors);
    free_validation_rules(rules, num_rules);
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return overall_validation_status;
}