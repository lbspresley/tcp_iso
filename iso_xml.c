#include "tcp_bok.h"
#include "iso_xml.h"

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
    int size = 0;
    xmlDocDumpFormatMemory(doc, &xml, &size, 1);

     // XML 선언 제거
    if (xml != NULL) {
        char* xml_decl = strstr((char*)xml, "<?xml");
        if (xml_decl != NULL) {
            char* content_start = strstr(xml_decl, "?>");
            if (content_start != NULL) {
                content_start += 2; // "?>" 다음으로 이동
                memmove(xml, content_start, strlen(content_start) + 1);
            }
        }
    }
    return (char*)xml;
}

// add root node to xml
xmlDocPtr add_root_node(xmlDocPtr doc, const char* root_name, const char* namespace, const char* namespace_prefix) {
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
        xmlNsPtr ns = xmlNewNs(root, (const xmlChar*)namespace, (const xmlChar*)namespace_prefix);
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

xmlDocPtr add_namespace(xmlDocPtr doc, char* namespace, char* namespace_prefix)
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

    xmlNsPtr ns = xmlNewNs(root, (const xmlChar*)namespace, (const xmlChar*)namespace_prefix);
    if (!ns) {
        printf("Failed to create namespace\n");
        return NULL;
    }

    xmlSetNs(root, ns);
    return doc;
}

xmlDocPtr add_node(xmlDocPtr doc, char* node, char* value, char* namespace, char* namespace_prefix)
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
        xmlNsPtr ns = xmlNewNs(new_node, (const xmlChar*)namespace, (const xmlChar*)namespace_prefix);
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

    // 기본 네임스페이스 등록 (bwh)
    xmlXPathRegisterNs(xpathCtx, (const xmlChar*)"bwh", 
                      (const xmlChar*)"urn:bok:std:iso:20022:xsd:001");
    
    // xmlXPathRegisterNs(xpathCtx, (const xmlChar*)"h", 
    //                   (const xmlChar*)"urn:iso:std:iso:20022:tech:xsd:head.001.001.03");

    // XML에서 동적으로 namespace 추출 및 등록
    int ns_count = extract_namespaces_from_xml(xml, xpathCtx);
    // printf("Extracted and registered %d namespaces from XML\n", ns_count);

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
            // strncpy(value, (char*)content, 4095);
            // value[4095] = '\0';
            strcpy(value, (char*)content);
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

void change_local_name(const char* node_name, char* parent_node) {
    // node_name: /A/B
    // parent_node: /*[local-name()='A']/*[local-name()='B']

    //strcpy(parent_node, node_name);
    //return;

    if (!node_name || !parent_node) {
        printf("Invalid parameters\n");
        return;
    }

    // remove / from node_name
    char node_name_local[512] = "";
    const char *temp1, *temp2=node_name;
    parent_node[0]=0;

    do {
        temp1 = strstr(temp2, "/");
        if (!temp1) { break; }
        temp1++;
        temp2 = strstr(temp1, "/");
        if (!temp2) { temp2 = node_name + strlen(node_name); }

        sprintf(node_name_local, "/*[local-name()='%.*s']", (int)(temp2 - temp1), temp1);
        strcat(parent_node, node_name_local);
        temp1 = temp2+1;
    } while (temp1 && temp2) ;

    return;
}

xmlDocPtr add_node_with_value(xmlDocPtr doc, const char* parent_xpath_param, const char* node_name, const char* node_value, const char* namespace, const char* namespace_prefix, int exclude_namespace) {
    if (!doc || !parent_xpath_param || !node_name) {
        printf("Invalid parameters\n");
        return NULL;
    }

    static char __parent_xpath[512] = "";
    change_local_name(parent_xpath_param, __parent_xpath);

    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (!xpathCtx) {
        printf("Failed to create XPath context\n");
        return NULL;
    }

    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((const xmlChar*)__parent_xpath, xpathCtx);
    if (!xpathObj) {
        printf("Failed to evaluate XPath expression: %s\n", __parent_xpath);
        xmlXPathFreeContext(xpathCtx);
        return NULL;
    }

    if (xpathObj->type != XPATH_NODESET || xpathObj->nodesetval->nodeNr == 0) {
        printf("No matching nodes found for XPath: %s\n", __parent_xpath);
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        return NULL;
    }

    xmlNodePtr parent = xpathObj->nodesetval->nodeTab[0];
    
    // 자식 노드 생성
    xmlNodePtr new_node = xmlNewNode(NULL, (const xmlChar*)node_name);
    if (!new_node) {
        printf("Failed to create new node: %s\n", node_name);
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        return NULL;
    }

    // 네임스페이스 설정
    if (namespace) {
        if (exclude_namespace) {
            // 네임스페이스를 제외하기 위해 NULL 네임스페이스 설정
            xmlNsPtr ns = xmlNewNs(new_node, NULL, NULL);
            if (!ns) {
                printf("Failed to create namespace\n");
                xmlFreeNode(new_node);
                xmlXPathFreeObject(xpathObj);
                xmlXPathFreeContext(xpathCtx);
                return NULL;
            }
            xmlSetNs(new_node, ns);
        } else {
            // 일반적인 네임스페이스 설정
            xmlNsPtr ns = xmlNewNs(new_node, (const xmlChar*)namespace, (const xmlChar*)namespace_prefix);
            if (!ns) {
                printf("Failed to create namespace\n");
                xmlFreeNode(new_node);
                xmlXPathFreeObject(xpathObj);
                xmlXPathFreeContext(xpathCtx);
                return NULL;
            }
            xmlSetNs(new_node, ns);
        }
    }

    // value 설정
    if (node_value) {
        xmlNodeSetContent(new_node, (const xmlChar*)node_value);
    }

    // 부모 노드에 추가
    xmlAddChild(parent, new_node);

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    return doc;
}

// XML에서 namespace를 동적으로 추출하는 함수
int extract_namespaces_from_xml(const char* xml, xmlXPathContextPtr xpathCtx) {
    xmlDocPtr doc = NULL;
    xmlNodePtr cur = NULL;
    int count = 0;
    
    if (xml == NULL || xpathCtx == NULL) {
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
    
    // 루트 노드의 namespace 등록
    xmlNsPtr ns = cur->nsDef;
    while (ns != NULL) {
        if (ns->prefix != NULL && ns->href != NULL) {
            xmlXPathRegisterNs(xpathCtx, ns->prefix, ns->href);
            // printf("Registered namespace: %s -> %s\n", ns->prefix, ns->href);
            count++;
        }
        ns = ns->next;
    }
    
    // 자식 노드들의 namespace도 확인 (특히 AppHdr)
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
        if (cur->type == XML_ELEMENT_NODE) {
            // AppHdr 노드인지 확인
            if (xmlStrcmp(cur->name, (const xmlChar*)"AppHdr") == 0) {
                // printf("Found AppHdr element\n");
                
                // AppHdr의 namespace 확인
                ns = cur->nsDef;
                while (ns != NULL) {
                    if (ns->prefix != NULL && ns->href != NULL) {
                        xmlXPathRegisterNs(xpathCtx, ns->prefix, ns->href);
                        // printf("Registered AppHdr namespace: %s -> %s\n", ns->prefix, ns->href);
                        count++;
                    } else if (ns->href != NULL) {
                        // 기본 namespace인 경우
                        xmlXPathRegisterNs(xpathCtx, (const xmlChar*)"h", ns->href);
                        // printf("Registered AppHdr default namespace: h -> %s\n", ns->href);
                        count++;
                    }
                    ns = ns->next;
                }
                
                // AppHdr의 xmlns 속성도 확인
                xmlAttrPtr attr = cur->properties;
                while (attr != NULL) {
                    if (xmlStrcmp(attr->name, (const xmlChar*)"xmlns") == 0) {
                        xmlChar* value = xmlNodeListGetString(doc, attr->children, 1);
                        if (value != NULL) {
                            xmlXPathRegisterNs(xpathCtx, (const xmlChar*)"h", value);
                            // printf("Registered AppHdr xmlns: h -> %s\n", value);
                            count++;
                            xmlFree(value);
                        }
                    }
                    attr = attr->next;
                }
            }
        }
        cur = cur->next;
    }
    
    xmlFreeDoc(doc);
    return count;
}
