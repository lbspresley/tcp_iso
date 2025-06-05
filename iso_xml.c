#include "tcp_bok.h"

int parse_xml(char* xml, char* tag, char* value)
{
    xmlDocPtr doc = NULL;
    xmlNodePtr cur = NULL;

    if (xml == NULL || strlen(xml) == 0) {
        return -1;
    }

    doc = xmlParseMemory(xml, strlen(xml));
    if (doc == NULL) {
        return -2;
    }

    cur = xmlDocGetRootElement(doc);
    if (cur == NULL) {
        xmlFreeDoc(doc);
        return -3;
    }

    // find tag
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
        printf("cur->name: %s\n", cur->name);
        if (xmlStrcmp(cur->name, (const xmlChar *)tag) == 0) {
            break;
        }
        cur = cur->next;
    }

    if (cur == NULL) {
        xmlFreeDoc(doc);
        return -4;
    }

    xmlChar* ret_value = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
    if (ret_value != NULL) {
        strcpy(value, (char*)ret_value);
        xmlFree(ret_value);
    }

    return 0;
}

/*
Security Handshake

<bwh:BokwireEnvelope xmlns:bwh="urn:bok:std:iso:20022:xsd:001">
    <bwh:BokwireHeader>
        <SecurityHandshake>
            <TrCd>000000001</TrCd>
            <Key>0084MTEwMXZlcgAAAAAENTAwMXJhbjEAAAAUvz4%2FD4lM3ZdUmhZQQMRlC0deSNxjdHlwAAAABENFUlQ%3D</Key>
        </SecurityHandshake>
    </bwh:BokwireHeader>
</bwh:BokwireEnvelope>
*/

char* build_xml(xmlDocPtr doc)
{
    unsigned char* xml = NULL;
    (void) xmlDocDumpMemory(doc, &xml, 0);
    return (char*)xml;
}

// add root node to xml
xmlDocPtr add_root_node(xmlDocPtr doc, const char* root_name, const char* namespace) {
    if (!doc || !root_name) {
        printf("Invalid parameters\n");
        return NULL;
    }

    // 루트 노드 생성
    xmlNodePtr root = xmlNewNode(NULL, (const xmlChar*)root_name);
    if (!root) {
        printf("Failed to create root node\n");
        xmlFreeDoc(doc);  // 실패 시 원본 doc 해제
        return NULL;
    }

    // 네임스페이스 설정
    if (namespace) {
        xmlNsPtr ns = xmlNewNs(root, (const xmlChar*)namespace, NULL);
        if (!ns) {
            printf("Failed to create namespace\n");
            xmlFreeNode(root);
            xmlFreeDoc(doc);  // 실패 시 원본 doc 해제
            return NULL;
        }
        xmlSetNs(root, ns);
    }

    // 루트 노드를 문서에 추가
    xmlDocSetRootElement(doc, root);
    return doc;
}

xmlDocPtr add_namespace(xmlDocPtr doc, char* namespace)
{
    if (!doc || !namespace) {
        printf("Invalid parameters\n");
        return NULL;
    }

    xmlNodePtr root = xmlDocGetRootElement(doc);
    if (!root) {
        printf("Failed to get root element\n");
        return NULL;
    }

    xmlNsPtr ns = xmlNewNs(root, (const xmlChar*)namespace, NULL);
    if (!ns) {
        printf("Failed to create namespace\n");
        return NULL;
    }

    xmlSetNs(root, ns);
    return doc;
}

xmlDocPtr add_node(xmlDocPtr doc, char* node, char* value, char* namespace)
{
    if (!doc || !node) {
        printf("Invalid parameters\n");
        return NULL;
    }

    xmlNodePtr root = xmlDocGetRootElement(doc);
    if (!root) {
        printf("Failed to get root element\n");
        return NULL;
    }

    xmlNodePtr new_node = xmlNewNode(NULL, (const xmlChar*)node);
    if (!new_node) {
        printf("Failed to create new node\n");
        return NULL;
    }

    if (namespace) {
        xmlNsPtr ns = xmlNewNs(new_node, (const xmlChar*)namespace, NULL);
        if (!ns) {
            printf("Failed to create namespace\n");
            xmlFreeNode(new_node);
            return NULL;
        }
        xmlSetNs(new_node, ns);
    }

    if (value) {
        xmlNodeSetContent(new_node, (const xmlChar*)value);
    }

    xmlAddChild(root, new_node);
    return doc;
}

// check if xml is valid
int isValidXml(char* xml)
{
    xmlDocPtr doc = NULL;
    doc = xmlParseMemory(xml, strlen(xml));
    if (doc == NULL) {
        return 0;
    }

    xmlFreeDoc(doc);
    return 1;
}


// parse xml using xpath
int parse_xml_xpath(char* xml, const char* xpath, char* value)
{
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    int ret = 0;

    if (xml == NULL || xpath == NULL || value == NULL) {
        return -1;
    }

    // XML 문자열 파싱
    doc = xmlParseMemory(xml, strlen(xml));
    if (doc == NULL) {
        return -2;
    }

    // XPath 컨텍스트 생성
    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return -3;
    }

    // 네임스페이스 등록
    xmlXPathRegisterNs(xpathCtx, (const xmlChar*)"bwh", 
                      (const xmlChar*)"urn:bok:std:iso:20022:xsd:001");

    // XPath 평가
    xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath, xpathCtx);
    if (xpathObj == NULL) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return -4;
    }

    // 결과 처리
    if (xpathObj->nodesetval && xpathObj->nodesetval->nodeNr > 0) {
        xmlNodePtr node = xpathObj->nodesetval->nodeTab[0];
        xmlChar* content = xmlNodeGetContent(node);
        if (content != NULL) {
            strncpy(value, (char*)content, 4095);
            value[4095] = '\0';
            xmlFree(content);
            ret = 0;
        } else {
            ret = -5;
        }
    } else {
        ret = -6;
    }

    // 메모리 해제
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return ret;
}

// parse BokwireEnvelope
int parse_bokwire_envelope(char* xml)
{
    xmlDocPtr doc = NULL;
    xmlNodePtr cur = NULL;
    int ret = 0;

    if (xml == NULL || strlen(xml) == 0) {
        return -1;
    }

    // XML 문자열 파싱
    doc = xmlParseMemory(xml, strlen(xml));
    if (doc == NULL) {
        return -2;
    }

    // 루트 노드 가져오기
    cur = xmlDocGetRootElement(doc);
    if (cur == NULL) {
        xmlFreeDoc(doc);
        return -3;
    }

    // BokwireEnvelope 태그 확인
    if (xmlStrcmp(cur->name, (const xmlChar *)"BokwireEnvelope")) {
        xmlFreeDoc(doc);
        return -4;
    }

    // 자식 노드 순회
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
        if (cur->type == XML_ELEMENT_NODE) {
            xmlChar* value = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            if (value != NULL) {
                printf("Tag: %s, Value: %s\n", cur->name, value);
                xmlFree(value);
            }
        }
        cur = cur->next;
    }

    // 메모리 해제
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return ret;
}

xmlDocPtr add_node_xpath(xmlDocPtr doc, const char* xpath, const char* node_name, const char* node_value) {
    if (!doc || !xpath || !node_name) {
        printf("Invalid parameters\n");
        return NULL;
    }

    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (!xpathCtx) {
        printf("Failed to create XPath context\n");
        return NULL;
    }

    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath, xpathCtx);
    if (!xpathObj) {
        printf("Failed to evaluate XPath expression: %s\n", xpath);
        xmlXPathFreeContext(xpathCtx);
        return NULL;
    }

    if (xpathObj->type != XPATH_NODESET || xpathObj->nodesetval->nodeNr == 0) {
        printf("No matching nodes found for XPath: %s\n", xpath);
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        return NULL;
    }

    xmlNodePtr parent = xpathObj->nodesetval->nodeTab[0];
    xmlNodePtr new_node = xmlNewChild(parent, NULL, (const xmlChar*)node_name, NULL);
    if (!new_node) {
        printf("Failed to create new node: %s\n", node_name);
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        return NULL;
    }

    if (node_value) {
        xmlNodeSetContent(new_node, (const xmlChar*)node_value);
    }

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    return doc;
}

xmlDocPtr add_node_with_value(xmlDocPtr doc, const char* parent_xpath, const char* node_name, const char* node_value) {
    if (!doc || !parent_xpath || !node_name) {
        printf("Invalid parameters\n");
        return NULL;
    }

    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (!xpathCtx) {
        printf("Failed to create XPath context\n");
        return NULL;
    }

    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar*)parent_xpath, xpathCtx);
    if (!xpathObj) {
        printf("Failed to evaluate XPath expression: %s\n", parent_xpath);
        xmlXPathFreeContext(xpathCtx);
        return NULL;
    }

    if (xpathObj->type != XPATH_NODESET || xpathObj->nodesetval->nodeNr == 0) {
        printf("No matching nodes found for XPath: %s\n", parent_xpath);
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        return NULL;
    }

    xmlNodePtr parent = xpathObj->nodesetval->nodeTab[0];
    
    // 자식 노드 생성
    xmlNodePtr new_node = xmlNewChild(parent, NULL, (const xmlChar*)node_name, NULL);
    if (!new_node) {
        printf("Failed to create new node: %s\n", node_name);
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        return NULL;
    }

    // value 설정
    if (node_value) {
        xmlNodeSetContent(new_node, (const xmlChar*)node_value);
    }

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    return doc;
}
