#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <regex.h>

#include "parson.h" // parson 라이브러리 헤더

// --- 규칙 구조체 정의 ---
typedef enum {
    RULE_TYPE_NONE,
    RULE_TYPE_EXACT_VALUE,
    RULE_TYPE_REGEX
} ValidationRuleType;

typedef struct {
    char* description;
    char* xpath;
    ValidationRuleType type;
    char* value;
} ValidationRule;

// 동적으로 할당된 ValidationRule 구조체 배열을 해제하는 함수
void free_validation_rules(ValidationRule* rules, size_t count) {
    size_t i;
    for (i = 0; i < count; i++) {
        if (rules[i].description) free(rules[i].description);
        if (rules[i].xpath) free(rules[i].xpath);
        if (rules[i].value) free(rules[i].value);
    }
    if (rules) free(rules);
}

// --- JSON config 파싱 함수 ---
// config_file_path: JSON 규칙 파일 경로
// out_rules: 파싱된 규칙들을 저장할 ValidationRule 배열 포인터
// out_count: 파싱된 규칙의 개수를 저장할 포인터
// 반환: 성공 시 0, 실패 시 -1
int load_validation_rules_from_json(const char* config_file_path, ValidationRule** out_rules, size_t* out_count) {
    JSON_Value* root_value = NULL;
    JSON_Array* rules_array = NULL;
    ValidationRule* rules = NULL;
    size_t i, count = 0;

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
    rules = (ValidationRule*)malloc(sizeof(ValidationRule) * count);
    if (rules == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for validation rules.\n");
        json_value_free(root_value);
        return -1;
    }

    for (i = 0; i < count; i++) {
        JSON_Object* rule_obj = json_array_get_object(rules_array, i);
        if (rule_obj == NULL) {
            fprintf(stderr, "Warning: Skipping invalid rule object at index %zu.\n", i);
            // 메모리 누수를 피하기 위해 현재까지 할당된 규칙 해제
            free_validation_rules(rules, i);
            json_value_free(root_value);
            *out_rules = NULL;
            *out_count = 0;
            return -1; // Or just skip and continue, depending on error policy
        }

        const char* description = json_object_get_string(rule_obj, "description");
        const char* xpath = json_object_get_string(rule_obj, "xpath");
        const char* type_str = json_object_get_string(rule_obj, "type");
        const char* value = json_object_get_string(rule_obj, "value");

        if (xpath == NULL || type_str == NULL || value == NULL) {
            fprintf(stderr, "Warning: Rule at index %zu is missing required fields (xpath, type, or value). Skipping.\n", i);
            rules[i].description = NULL; // Mark as empty/invalid to be safely skipped or freed
            rules[i].xpath = NULL;
            rules[i].type = RULE_TYPE_NONE;
            rules[i].value = NULL;
            continue; // Skip this rule, but continue parsing others
        }

        rules[i].description = description ? strdup(description) : NULL;
        rules[i].xpath = strdup(xpath);
        rules[i].value = strdup(value);

        if (strcmp(type_str, "exact_value") == 0) {
            rules[i].type = RULE_TYPE_EXACT_VALUE;
        } else if (strcmp(type_str, "regex") == 0) {
            rules[i].type = RULE_TYPE_REGEX;
        } else {
            fprintf(stderr, "Warning: Unknown rule type '%s' for rule at index %zu. Skipping.\n", type_str, i);
            rules[i].type = RULE_TYPE_NONE; // Unknown type, mark as invalid
            // Free the memory just allocated for this skipped rule
            if (rules[i].description) { free(rules[i].description); rules[i].description = NULL; }
            if (rules[i].xpath) { free(rules[i].xpath); rules[i].xpath = NULL; }
            if (rules[i].value) { free(rules[i].value); rules[i].value = NULL; }
        }

        // Check for strdup errors
        if ((rules[i].description && !description) || !rules[i].xpath || !rules[i].value) {
            fprintf(stderr, "Error: Memory allocation failed for rule at index %zu.\n", i);
            free_validation_rules(rules, i + 1); // Free all rules up to current
            json_value_free(root_value);
            *out_rules = NULL;
            *out_count = 0;
            return -1;
        }
    }

    json_value_free(root_value);
    *out_rules = rules;
    *out_count = count;
    return 0;
}

// --- 이전 코드에서 재사용할 함수들 (변화 없음) ---

// 특정 XPath에서 값을 추출하는 헬퍼 함수
char* extract_xpath_value(xmlDocPtr doc, const xmlChar* xpathExpr) {
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    char* value = NULL;

    xpathCtx = xmlXPathNewContext(doc);
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
        }
    } else if (xpathObj->type == XPATH_STRING) {
        value = (char*)xmlStrdup(xpathObj->stringval);
    }

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);

    return value;
}

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


int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <xml_file> <config_file>\n", argv[0]);
        return 1;
    }

    const char* xml_file = argv[1];
    const char* config_file = argv[2];
    xmlDocPtr doc = NULL;
    char* extracted_value = NULL;
    int overall_validation_status = 0; // 0 = all passed, 1 = at least one failed

    ValidationRule* rules = NULL;
    size_t i, num_rules = 0;

    // XML 파서 초기화
    LIBXML_TEST_VERSION

    // XML 파일 파싱
    doc = xmlReadFile(xml_file, NULL, 0);
    if (doc == NULL) {
        fprintf(stderr, "Error: Could not parse XML file %s\n", xml_file);
        return 1;
    }

    // JSON config 파일에서 규칙 로드
    printf("Loading validation rules from '%s'...\n", config_file);
    if (load_validation_rules_from_json(config_file, &rules, &num_rules) != 0) {
        fprintf(stderr, "Error: Failed to load validation rules.\n");
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return 1;
    }

    printf("Successfully loaded %zu rules.\n", num_rules);
    printf("\n--- Starting XML Validation based on Configured Rules ---\n");

    // 로드된 각 규칙에 대해 유효성 검증 수행
    for (i = 0; i < num_rules; i++) {
        // Skip invalid/incomplete rules that might have been marked as NONE during parsing
        if (rules[i].type == RULE_TYPE_NONE || rules[i].xpath == NULL || rules[i].value == NULL) {
            fprintf(stderr, "Skipping rule %zu due to parsing errors or missing fields.\n", i + 1);
            overall_validation_status = 1; // Consider it a failure if rules are malformed
            continue;
        }
        
        printf("\nRule %zu: '%s'\n", i + 1, rules[i].description ? rules[i].description : "No description");
        printf("  XPath: %s\n", rules[i].xpath);
        printf("  Type: %s\n", rules[i].type == RULE_TYPE_EXACT_VALUE ? "Exact Value" : "Regex");
        printf("  Expected/Pattern: '%s'\n", rules[i].value);

        extracted_value = extract_xpath_value(doc, (const xmlChar*)rules[i].xpath);

        if (extracted_value) {
            printf("  Extracted value: '%s'\n", extracted_value);
            int current_rule_status = 0;
            if (rules[i].type == RULE_TYPE_EXACT_VALUE) {
                current_rule_status = validate_by_exact_value(extracted_value, rules[i].value);
            } else if (rules[i].type == RULE_TYPE_REGEX) {
                current_rule_status = validate_by_regex(extracted_value, rules[i].value);
            }

            if (current_rule_status) {
                printf("  Result: PASS\n");
            } else {
                printf("  Result: FAIL\n");
                overall_validation_status = 1; // 하나라도 실패하면 최종 결과 실패
            }
            xmlFree(extracted_value);
        } else {
            printf("  Extracted value: NOT FOUND or EMPTY (for XPath '%s')\n", rules[i].xpath);
            // XPath가 없거나 비어있는 것이 항상 실패를 의미하지는 않을 수 있습니다.
            // 여기서는 규칙에 따라 "any_value"로 검증하려고 했으므로,
            // 값이 없는 경우 유효성 검증은 (해당 값을 찾지 못했으니) 실패로 간주합니다.
            // 필요에 따라 'required' 플래그 등을 규칙에 추가하여 처리 로직을 더 정교하게 만들 수 있습니다.
            printf("  Result: FAIL (Value not found for XPath)\n");
            overall_validation_status = 1;
        }
    }

    printf("\n--- XML Validation Summary ---\n");
    if (overall_validation_status == 0) {
        printf("All rules passed successfully!\n");
    } else {
        printf("One or more rules failed validation.\n");
    }

    // 할당된 모든 리소스 해제
    free_validation_rules(rules, num_rules); // 규칙 메모리 해제
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return overall_validation_status; // 0 for success, 1 for failure
}