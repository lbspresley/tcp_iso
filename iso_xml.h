#ifndef __ISO_XML_H__
#define __ISO_XML_H__

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

int parse_xml(char* xml, char* tag, char* value);
int parse_xml_xpath(char* xml, const char* xpath, char* value);
char* build_xml(xmlDocPtr doc);
xmlDocPtr add_root_node(xmlDocPtr doc, const char* root_name, const char* namespace, const char* namespace_prefix);
xmlDocPtr add_namespace(xmlDocPtr doc, char* namespace, char* namespace_prefix);
xmlDocPtr add_node(xmlDocPtr doc, char* node, char* value, char* namespace, char* namespace_prefix);
xmlDocPtr add_node_xpath(xmlDocPtr doc, const char* xpath, const char* node_name, const char* node_value);
xmlDocPtr add_node_with_value(xmlDocPtr doc, const char* parent_xpath_param, const char* node_name, const char* node_value, const char* namespace, const char* namespace_prefix, int exclude_namespace) ;
void change_local_name(const char* node_name, char* parent_node);

#endif
