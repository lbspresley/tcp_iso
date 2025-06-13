#include "tcp_bok.h"

void test_parse_bokwire_envelope() 
{
    // 테스트용 XML 문자열
    const char* test_xml = 
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
    printf("XPath test result: %d\n", ret);
    printf("TrCd: %s\n", ret_value);

    //ret = parse_xml_xpath((char*)test_xml, "//bwh:BokwireHeader/SecurityHandshake/TrCd", ret_value);
    ret = parse_xml_xpath((char*)test_xml, "//SecurityHandshake/TrCd", ret_value);
    printf("XPath full path result: %d\n", ret);
    printf("TrCd: %s\n", ret_value);

    // 다른 XPath 테스트
    ret = parse_xml_xpath((char*)test_xml, "//Key", ret_value);
    printf("XPath test result: %d\n", ret);
    printf("Key: %s\n", ret_value);

    // 잘못된 XML 테스트
    // const char* invalid_xml = "<InvalidXML>";
    // ret = parse_xml_xpath((char*)invalid_xml, "//TrCd", ret_value);
    // printf("Invalid XML case result: %d\n", ret);

    // 빈 문자열 테스트
    // ret = parse_xml_xpath("", "//TrCd", ret_value);
    // printf("Empty string case result: %d\n", ret);
}

void test_xml_operations() 
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

int main() {
    // libxml2 초기화
    xmlInitParser();
    
    test_parse_bokwire_envelope();
    test_xml_operations();
    
    // libxml2 정리
    xmlCleanupParser();
    return 0;
} 
