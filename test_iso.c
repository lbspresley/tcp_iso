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


int main() {
    // libxml2 초기화
    xmlInitParser();
    
    
    // test_parse_bokwire_envelope();
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
    for (int i = 0; i < 5; i++) {
        get_msg_idr(msg_idr);
        printf("Generated Message ID %d: %s\n", i+1, msg_idr);
    }
    return 0;
} 
