#ifndef __ISO_XML_H__
#define __ISO_XML_H__

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>

int parse_xml(char* xml, char* tag, char* value);
char* build_xml(xmlDocPtr doc);
xmlDocPtr add_root_node(xmlDocPtr doc, const char* root_name, const char* namespace);
xmlDocPtr add_namespace(xmlDocPtr doc, char* namespace);
xmlDocPtr add_node(xmlDocPtr doc, char* node, char* value, char* namespace);
xmlDocPtr add_node_xpath(xmlDocPtr doc, const char* xpath, const char* node_name, const char* node_value);
xmlDocPtr add_node_with_value(xmlDocPtr doc, const char* parent_xpath, const char* node_name, const char* node_value);

#endif