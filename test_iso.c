#include "tcp_iso.h"

void test_parse_bokwire_envelope() 
{
    // 테스트용 XML 문자열
    const char* test_xml = 
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<bwh:BokwireEnvelope xmlns:bwh=\"urn:bok:std:iso:20022:xsd:001\">"
        "    <bwh:BokwireHeader>"
        "            <TrCd>falseValue</TrCd>"
        "        <SecurityHandshake>"
        "            <TrCd>000000001</TrCd>"
        "            <Key>0084MTEwMXZlcgAAAAAENTAwMXJhbjEAAAAUvz4%2FD4lM3ZdUmhZQQMRlC0deSNxjdHlwAAAABENFUlQ%3D</Key>"
        "        </SecurityHandshake>"
        "    </bwh:BokwireHeader>"
        "</bwh:BokwireEnvelope>";

    printf("Testing parse_bokwire_envelope...\n");
    
    char ret_value[4096] = {0};
    int ret;

    // XPath를 사용한 테스트
    ret = parse_xml_xpath((char*)test_xml, "//TrCd", ret_value);
    printf("\nFALSE Value Test : XPath test result: %d\n", ret);
    printf("TrCd: %s\n", ret_value);

    ret = parse_xml_xpath((char*)test_xml, "//bwh:BokwireHeader/SecurityHandshake/TrCd", ret_value);
    // ret = parse_xml_xpath((char*)test_xml, "//SecurityHandshake/TrCd", ret_value);
    printf("\nXPath full path result: %d\n", ret);
    printf("TrCd: %s\n", ret_value);

    // 다른 XPath 테스트
    ret = parse_xml_xpath((char*)test_xml, "//Key", ret_value);
    printf("\nXPath test result: %d\n", ret);
    printf("Key: %s\n", ret_value);

    // 잘못된 XML 테스트
    // const char* invalid_xml = "<InvalidXML>";
    // ret = parse_xml_xpath((char*)invalid_xml, "//TrCd", ret_value);
    // printf("Invalid XML case result: %d\n", ret);

    // 빈 문자열 테스트
    // ret = parse_xml_xpath("", "//TrCd", ret_value);
    // printf("Empty string case result: %d\n", ret);

	// strip XML test
	printf("Original xml : \n%s\n", test_xml);
	char* strip_msg = (char*)strip_xml_message((char*)test_xml);
	printf("Strip xml : \n%s\n", strip_msg);

	// XML escape test
	char* test_escape = "XML Escape Test : & < > \" ' characters";
	printf("\nOriginal text: %s\n", test_escape);
	char* rst = (char*)make_escaped_value((char*)test_escape);
	printf(" Escaped text: %s\n", (char*)rst);
	printf(" Unescaped text: %s\n", (char*)make_unescaped_value((char*)rst));

}

void test_build_SecurityHandshake() 
{
    // 새로운 XML 문서 생성
    xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
    if (doc == NULL) {
        printf("Failed to create new XML document\n");
        return;
    }

    char* namespace = "urn:bok:std:iso:20022:xsd:001";
    char namespace_prefix[12] = "bwh";
    char nodeName[512] = "BokwireEnvelope";
    char parentNode[512] = "";

    // change_local_name(nodeName, parentNode);
    // printf("parent node: %s\n", parentNode);

    // 루트 노드 추가
    doc = add_root_node(doc, nodeName, namespace, namespace_prefix);
    if (doc == NULL) {
        printf("1. Failed to add root node\n");
        xmlFreeDoc(doc);
        return;
    }

    // XPath를 사용하여 노드 추가
    strcpy(parentNode, "/BokwireEnvelope");
    doc = add_node_with_value(doc, parentNode, "bwh:BokwireHeader", NULL, namespace, namespace_prefix, 1);
    if (doc == NULL) {
        printf("2. Failed to add BokwireHeader\n");
        xmlFreeDoc(doc);
        return;
    }

    strcat(parentNode, "/bwh:BokwireHeader");
    doc = add_node_with_value(doc, parentNode, "SecurityHandshake", NULL, namespace, namespace_prefix, 1);
    if (doc == NULL) {
        printf("3. Failed to add SecurityHandshake\n");
        xmlFreeDoc(doc);
        return;
    }
    printf("parent node: %s\n", parentNode);

    strcat(parentNode, "/SecurityHandshake");
    doc = add_node_with_value(doc, parentNode, "TrCd", "000000001", namespace, namespace_prefix, 1);
    if (doc == NULL) {
        printf("4. Failed to add TrCd\n");
        xmlFreeDoc(doc);
        return;
    }
    printf("parent node: %s\n", parentNode);

    doc = add_node_with_value(doc, parentNode, "Key", 
        "0084MTEwMXZlcgAAAAAENTAwMXJhbjEAAAAUvz4%2FD4lM3ZdUmhZQQMRlC0deSNxjdHlwAAAABENFUlQ%3D", namespace, namespace_prefix, 1);
    if (doc == NULL) {
        printf("5. Failed to add Key\n");
        xmlFreeDoc(doc);
        return;
    }

    // 생성된 XML 출력
    char* xml = build_xml(doc);
    if (xml != NULL) {
        printf("6. Generated XML:\n%s\n", xml);
        xmlFree(xml);
    }

    // 메모리 해제
    xmlFreeDoc(doc);
}

void test_build_ACK(char* respcd, char* msgtpcd, char* bizsvc, char* bizmsgidr) 
{
    // parameters
    // char *respcd="SUCCESS";
    // char *msgtpcd="pacs.009_CORE";
    // char *bizsvc="bok.rtgs.gtr.01";
    // char * bizmsgidr="202506131518S000000001";

    // 새로운 XML 문서 생성
    xmlDocPtr doc = xmlNewDoc((const xmlChar*)"1.0");
    if (doc == NULL) {
        printf("Failed to create new XML document\n");
        return;
    }

    char* namespace = "urn:bok:std:iso:20022:xsd:001";
    char namespace_prefix[12] = "bwh";
    char nodeName[512] = "BokwireEnvelope";
    char parentNode[512] = "";

    // 루트 노드 추가
    doc = add_root_node(doc, nodeName, namespace, namespace_prefix);
    if (doc == NULL) {
        printf("1. Failed to add root node\n");
        xmlFreeDoc(doc);
        return;
    }

    // XPath를 사용하여 노드 추가
    strcpy(parentNode, "/BokwireEnvelope");
    doc = add_node_with_value(doc, parentNode, "bwh:BokwireHeader", NULL, namespace, namespace_prefix, 1);
    if (doc == NULL) {
        printf("2. Failed to add BokwireHeader\n");
        xmlFreeDoc(doc);
        return;
    }

    strcat(parentNode, "/bwh:BokwireHeader");
    doc = add_node_with_value(doc, parentNode, "Response", NULL, namespace, namespace_prefix, 1);
    if (doc == NULL) {
        printf("3. Failed to add Response\n");
        xmlFreeDoc(doc);
        return;
    }
    printf("parent node: %s\n", parentNode);

    strcat(parentNode, "/Response");
    doc = add_node_with_value(doc, parentNode, "RespCd", respcd, namespace, namespace_prefix, 1);
    if (doc == NULL) {
        printf("4. Failed to add RespCd\n");
        xmlFreeDoc(doc);
        return;
    }

    doc = add_node_with_value(doc, parentNode, "MsgTpCd", msgtpcd, namespace, namespace_prefix, 1);
    if (doc == NULL) {
        printf("5. Failed to add MsgTpCd\n");
        xmlFreeDoc(doc);
        return;
    }

    doc = add_node_with_value(doc, parentNode, "BizSvc", bizsvc, namespace, namespace_prefix, 1);
    if (doc == NULL) {
        printf("5. Failed to add BizSvc\n");
        xmlFreeDoc(doc);
        return;
    }

    doc = add_node_with_value(doc, parentNode, "BizMsgIdr", bizmsgidr, namespace, namespace_prefix, 1);
    if (doc == NULL) {
        printf("6. Failed to add BizMsgIdr\n");
        xmlFreeDoc(doc);
        return;
    }

    // 생성된 XML 출력
    char* xml = build_xml(doc);
    if (xml != NULL) {
        printf("7. Generated XML:\n%s\n", xml);
        xmlFree(xml);
    }

    // 메모리 해제
    xmlFreeDoc(doc);
}

char* read_file(const char* filename)
{
    FILE* file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);
    return buffer;
}   

void test_response_ACK() 
{
    const char* xmlfile = "xml/pacs.009_GTR.xml";
    char* request_xml = read_file(xmlfile);
    // printf("request_xml: %s\n", request_xml);

    // parse request xml
    char respcd[36] = "SUCCESS";
    char msgtpcd[36] = {0};
    char bizsvc[36] = {0};
    char bizmsgidr[36] = {0};

    parse_xml_xpath(request_xml, "//Request/MsgTpCd", msgtpcd);
    parse_xml_xpath(request_xml, "//h:BizSvc", bizsvc);
    parse_xml_xpath(request_xml, "//h:BizMsgIdr", bizmsgidr);

    printf("msgtpcd: %s\n", msgtpcd);
    printf("bizsvc: %s\n", bizsvc);
    printf("bizmsgidr: %s\n", bizmsgidr);

    test_build_ACK(respcd, msgtpcd, bizsvc, bizmsgidr);

    return;
}

void test_dynamic_namespace() 
{
    printf("\n=== Testing Dynamic Namespace Extraction ===\n");
    
    // 테스트 1: pacs.009_GTR.xml (기본 namespace 사용)
    printf("\n1. Testing pacs.009_GTR.xml (default namespace):\n");
    const char* xmlfile1 = "xml/pacs.009_GTR.xml";
    char* request_xml1 = read_file(xmlfile1);
    
    char msgtpcd[36] = {0};
    char bizsvc[36] = {0};
    char bizmsgidr[36] = {0};
    char evtcd[36] = {0};

    parse_xml_xpath(request_xml1, "//bwh:MsgTpCd", msgtpcd);
    parse_xml_xpath(request_xml1, "//h:BizSvc", bizsvc);
    parse_xml_xpath(request_xml1, "//h:BizMsgIdr", bizmsgidr);
    
    printf("msgtpcd: %s\n", msgtpcd);
    printf("bizsvc: %s\n", bizsvc);
    printf("bizmsgidr: %s\n", bizmsgidr);
    
    free(request_xml1);
    
    // 테스트 2: admi.004.001.01.xml (다른 namespace)
    printf("\n2. Testing admi.004.001.01.xml (different namespace):\n");
    const char* xmlfile2 = "xml/admi.004.001.01.xml";
    char* request_xml2 = read_file(xmlfile2);

    memset(msgtpcd, 0, sizeof(msgtpcd));
    memset(bizsvc, 0, sizeof(bizsvc));
    memset(bizmsgidr, 0, sizeof(bizmsgidr));
    memset(evtcd, 0, sizeof(evtcd));
    
    // admi.004.001.01.xml은 기본 namespace를 사용하므로 prefix 없이 접근
    parse_xml_xpath(request_xml2, "//bwh:MsgTpCd", msgtpcd);
    parse_xml_xpath(request_xml2, "//bwh:BokwireBody/h:AppHdr/h:BizSvc", bizsvc);
    parse_xml_xpath(request_xml2, "//bwh:BokwireBody/h:AppHdr/h:BizMsgIdr", bizmsgidr);
    
    // 방법 1: 네임스페이스를 명시적으로 지정
    parse_xml_xpath(request_xml2, "//*[local-name()='EvtCd']", evtcd);
    printf("1 evtcd: %s\n", evtcd);
    
    // 방법 2: 더 구체적인 경로 사용
    parse_xml_xpath(request_xml2, "//bwh:BokwireBody/Document/*[local-name()='admi.004.001.01']/*[local-name()='EvtInf']/*[local-name()='EvtCd']", evtcd);
    printf("2 evtcd: %s\n", evtcd);

    // 방법 3: 다른 namespace 사용
    parse_xml_xpath(request_xml2, "//*[local-name()='BizMsgIdr']", evtcd);
    printf("3 evtcd: %s\n", evtcd);
    
    char* val = (char*)get_tag_value(request_xml2, "EvtCd");
    printf("evtcd: %s\n", val);
    val = (char*)get_tag_value(request_xml2, "EvtInf/EvtCd");
    printf("multi level evtcd: %s\n", val);
    val = (char*)get_tag_value(request_xml2, "bwh:BokwireBody/Document/admi.004.001.01/EvtInf");
    printf("multi level evtcd: %s\n", val);
    
    printf("msgtpcd: %s\n", msgtpcd);
    printf("bizsvc: %s\n", bizsvc);
    printf("bizmsgidr: %s\n", bizmsgidr);
    
    
    free(request_xml2);
}

void remove_empty_child_node(xmlNodePtr child)
{
    if (child == NULL) {
        return;
    }

    // 자식 노드들을 먼저 재귀적으로 처리
    xmlNodePtr grandChild = child->xmlChildrenNode;
    while (grandChild != NULL) {
        xmlNodePtr next = grandChild->next; // 다음 노드를 미리 저장 (삭제될 수 있으므로)
        remove_empty_child_node(grandChild);
        grandChild = next;
    }

    // 현재 노드가 삭제되었는지 확인
    if (child->parent == NULL) {
        return; // 이미 삭제된 노드
    }

    // 현재 노드의 content 확인
    xmlChar* content = xmlNodeGetContent(child);
    int has_content = 0;
    
    if (content != NULL) {
        // 공백이 아닌 실제 내용이 있는지 확인
        char* trimmed = (char*)content;
        while (*trimmed && (*trimmed == ' ' || *trimmed == '\t' || *trimmed == '\n' || *trimmed == '\r')) {
            trimmed++;
        }
        if (*trimmed != '\0') {
            has_content = 1;
        }
        xmlFree(content);
    }

    // 자식 노드가 있는지 확인
    xmlNodePtr firstChild = child->xmlChildrenNode;
    int has_children = (firstChild != NULL);

    // content가 없고 자식 노드도 없는 경우 삭제
    if (!has_content && !has_children) {
        xmlUnlinkNode(child);
        xmlFreeNode(child);
        return;
    }

    // content가 없지만 자식 노드가 있는 경우, 모든 자식이 삭제되었는지 확인
    if (!has_content && has_children) {
        xmlNodePtr remainingChild = child->xmlChildrenNode;
        int all_children_removed = 1;
        
        while (remainingChild != NULL) {
            if (remainingChild->parent != NULL) { // 아직 삭제되지 않은 자식이 있음
                all_children_removed = 0;
                break;
            }
            remainingChild = remainingChild->next;
        }
        
        // 모든 자식이 삭제된 경우 현재 노드도 삭제
        if (all_children_removed) {
            xmlUnlinkNode(child);
            xmlFreeNode(child);
            return;
        }
    }
}

char* trim_xml(char* xml)
{
   // load xml
   xmlDocPtr doc = xmlParseMemory(xml, strlen(xml));
   if (doc == NULL) {
    return NULL;
   }

   // read root node
   xmlNodePtr root = xmlDocGetRootElement(doc);
   if (root == NULL) {
    xmlFreeDoc(doc);
    return NULL;
   }

   // 루트 노드부터 시작하여 모든 자식 노드들을 재귀적으로 처리
   remove_empty_child_node(root);

   // build xml
   char* trimmed_xml = build_xml(doc);
   //printf("trimmed_xml: %s\n", trimmed_xml);

   xmlFreeDoc(doc);
   return trimmed_xml;
}

char* compress_xml(char* xml)
{
    if (xml == NULL) {
        return NULL;
    }

    // XML 문서 파싱
    xmlDocPtr doc = xmlParseMemory(xml, strlen(xml));
    if (doc == NULL) {
        return NULL;
    }

    // 루트 노드 가져오기
    xmlNodePtr root = xmlDocGetRootElement(doc);
    if (root == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // XML을 압축된 형태로 출력
    xmlBufferPtr buffer = xmlBufferCreate();
    if (buffer == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // XML을 압축된 형태로 출력 (공백과 들여쓰기 제거)
    // xmlNodeDump의 마지막 두 매개변수: 0 = 들여쓰기 없음, 0 = 포맷팅 없음
    xmlNodeDump(buffer, doc, root, 0, 0);
    
    // 버퍼에서 문자열 추출
    char* compressed_xml = (char*)malloc(xmlBufferLength(buffer) + 1);
    if (compressed_xml == NULL) {
        xmlBufferFree(buffer);
        xmlFreeDoc(doc);
        return NULL;
    }
    
    strcpy(compressed_xml, (char*)xmlBufferContent(buffer));
    
    // 추가 압축: 연속된 공백을 하나로 줄이고, 태그 사이의 공백 제거
    char* result = (char*)malloc(strlen(compressed_xml) + 1);
    if (result == NULL) {
        free(compressed_xml);
        xmlBufferFree(buffer);
        xmlFreeDoc(doc);
        return NULL;
    }
    
    char* src = compressed_xml;
    char* dst = result;
    int in_tag = 0;
    int last_was_space = 0;
    
    while (*src) {
        if (*src == '<') {
            in_tag = 1;
            *dst++ = *src++;
        } else if (*src == '>') {
            in_tag = 0;
            *dst++ = *src++;
        } else if (in_tag) {
            // 태그 내부에서는 모든 문자 그대로 복사
            *dst++ = *src++;
        } else {
            // 태그 외부에서는 공백 처리
            if (*src == ' ' || *src == '\t' || *src == '\n' || *src == '\r') {
                if (!last_was_space) {
                    *dst++ = ' ';
                    last_was_space = 1;
                }
                src++;
            } else {
                *dst++ = *src++;
                last_was_space = 0;
            }
        }
    }
    *dst = '\0';
    
    // 메모리 해제
    free(compressed_xml);
    xmlBufferFree(buffer);
    xmlFreeDoc(doc);
    
    return result;
}

char* compress_xml_minimal(char* xml)
{
    if (xml == NULL) {
        return NULL;
    }

    // XML 문서 파싱
    xmlDocPtr doc = xmlParseMemory(xml, strlen(xml));
    if (doc == NULL) {
        return NULL;
    }

    // 루트 노드 가져오기
    xmlNodePtr root = xmlDocGetRootElement(doc);
    if (root == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // XML을 압축된 형태로 출력
    xmlBufferPtr buffer = xmlBufferCreate();
    if (buffer == NULL) {
        xmlFreeDoc(doc);
        return NULL;
    }

    // XML을 압축된 형태로 출력 (공백과 들여쓰기 제거)
    xmlNodeDump(buffer, doc, root, 0, 0);
    
    // 버퍼에서 문자열 추출
    char* compressed_xml = (char*)malloc(xmlBufferLength(buffer) + 1);
    if (compressed_xml == NULL) {
        xmlBufferFree(buffer);
        xmlFreeDoc(doc);
        return NULL;
    }
    
    strcpy(compressed_xml, (char*)xmlBufferContent(buffer));
    
    // 최대 압축: 모든 공백 제거 (태그 내부 제외)
    char* result = (char*)malloc(strlen(compressed_xml) + 1);
    if (result == NULL) {
        free(compressed_xml);
        xmlBufferFree(buffer);
        xmlFreeDoc(doc);
        return NULL;
    }
    
    char* src = compressed_xml;
    char* dst = result;
    int in_tag = 0;
    
    while (*src) {
        if (*src == '<') {
            in_tag = 1;
            *dst++ = *src++;
        } else if (*src == '>') {
            in_tag = 0;
            *dst++ = *src++;
        } else if (in_tag) {
            // 태그 내부에서는 모든 문자 그대로 복사
            *dst++ = *src++;
        } else {
            // 태그 외부에서는 공백 완전 제거
            if (*src != ' ' && *src != '\t' && *src != '\n' && *src != '\r') {
                *dst++ = *src;
            }
            src++;
        }
    }
    *dst = '\0';
    
    // 메모리 해제
    free(compressed_xml);
    xmlBufferFree(buffer);
    xmlFreeDoc(doc);
    
    return result;
}

int test_trim_xml()
{
    const char* xmlfile = "xml/pacs.009_GTR_trim_test.xml";
    char* request_xml = read_file(xmlfile);
    printf("request_xml: %s\n", request_xml);
    char* trimmed_xml = trim_xml(request_xml);
    printf("trimmed_xml: %s\n", trimmed_xml);
    free(request_xml);
    free(trimmed_xml);
    return 0;
}

int test_compress_xml()
{
    const char* xmlfile = "xml/pacs.009_GTR_trim_test.xml";
    char* request_xml = read_file(xmlfile);
    printf("=== Original XML ===\n%s\n", request_xml);
    
    // 일반 압축 (공백 유지)
    char* compressed_xml = compress_xml(request_xml);
    printf("=== Compressed XML (with spaces) ===\n%s\n", compressed_xml);
    
    // 최대 압축 (모든 공백 제거)
    char* minimal_xml = compress_xml_minimal(request_xml);
    printf("=== Minimal XML (no spaces) ===\n%s\n", minimal_xml);
    
    // 압축 전후 크기 비교
    printf("\n=== Compression Results ===\n");
    printf("Original size: %zu bytes\n", strlen(request_xml));
    printf("Compressed size (with spaces): %zu bytes\n", strlen(compressed_xml));
    printf("Compression ratio (with spaces): %.2f%%\n", 
           (1.0 - (double)strlen(compressed_xml) / strlen(request_xml)) * 100);
    printf("Minimal size (no spaces): %zu bytes\n", strlen(minimal_xml));
    printf("Compression ratio (minimal): %.2f%%\n", 
           (1.0 - (double)strlen(minimal_xml) / strlen(request_xml)) * 100);
    
    free(request_xml);
    free(compressed_xml);
    free(minimal_xml);
    return 0;
}


int main() {
    // libxml2 초기화
    xmlInitParser();
    
    test_compress_xml();
    return 0;

    test_parse_bokwire_envelope();
    // test_build_SecurityHandshake();
    // test_build_ACK("SUCCESS", "pacs.009_CORE", "bok.rtgs.gtr.01", "202506131518S000000001");
    // test_response_ACK();
    test_dynamic_namespace();
    
    // libxml2 정리
    xmlCleanupParser();

    // get_msg_idr 함수 테스트
    // gc_seqFilePath 설정 (test_iso용)
    strcpy(gc_seqFilePath, ".");
    strcpy(gc_org_cd, "1101");

    printf("\n=== Testing get_msg_idr function ===\n");
    char msg_idr[35];
    int i;
    for (i = 0; i < 5; i++) {
        get_msg_idr(msg_idr);
        printf("Generated Message ID %d: %s\n", i+1, msg_idr);
    }
    return 0;
} 
