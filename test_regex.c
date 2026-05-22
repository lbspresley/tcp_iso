#include <stdio.h>
#include <regex.h>
#include <string.h>

int test_regex(const char* pattern, const char* text) {
    regex_t regex;
    int result;
    
    // 정규표현식 컴파일
    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        printf("Failed to compile regex: %s\n", pattern);
        return -1;
    }
    
    // 매칭 테스트
    result = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);
    
    return (result == 0) ? 1 : 0; // 1 = 매치, 0 = 매치 안됨
}

int main() {
    const char* pattern1 = "^[0-9]{10}$";        // 정확히 10개 숫자
    const char* pattern2 = "^[0-9]{10,10}$";     // 최소10개, 최대10개 숫자
    
    const char* test_cases[] = {
        "1234567890",      // 10자리 - 매치되어야 함
        "12345678901",     // 11자리 - 매치되지 않아야 함  
        "123456789",       // 9자리 - 매치되지 않아야 함
        "123456789a",      // 9숫자+1문자 - 매치되지 않아야 함
        "0000000000",      // 10자리 0 - 매치되어야 함
        "9876543210"       // 10자리 - 매치되어야 함
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    printf("정규표현식 테스트: [0-9]{10} vs [0-9]{10,10}\n");
    printf("=================================================\n");
    
    int i;
    for (i = 0; i < num_tests; i++) {
        int result1 = test_regex(pattern1, test_cases[i]);
        int result2 = test_regex(pattern2, test_cases[i]);
        
        printf("테스트 문자열: %-12s | {10}: %s | {10,10}: %s | 결과: %s\n", 
               test_cases[i],
               result1 ? "매치" : "안됨",
               result2 ? "매치" : "안됨", 
               (result1 == result2) ? "✅ 동일" : "❌ 다름");
    }
    
    printf("\n💡 결론: [0-9]{10}과 [0-9]{10,10}은 완전히 같은 의미입니다!\n");
    
    return 0;
} 