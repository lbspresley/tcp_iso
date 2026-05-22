#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <regex.h>

unsigned char* strip_xml_message(char* msg)
{
  static unsigned char _stripped_message [1024*60];

  strcpy((char*)_stripped_message, (char*)msg);
  //char*s, *e;
  //s = _stripped_message;

  // remove whitespace between tags with regex
  regex_t regex;
  regmatch_t match;
  //if( regcomp(&regex, ">\\s+<", REG_EXTENDED) == 0 ) {
  if( regcomp(&regex, "> +<", REG_EXTENDED) == 0 ) {
    while( regexec(&regex, (char*)_stripped_message, 1, &match, 0) == 0 ) {
	printf("REG : start(%d) end(%d)\n", match.rm_so, match.rm_eo);
      match.rm_so++;
      match.rm_eo--;
      int match_len = match.rm_eo - match.rm_so;
      if( match_len > 0 ) {
        memmove((char*)_stripped_message + match.rm_so, (char*)_stripped_message + match.rm_eo, strlen((char*)_stripped_message + match.rm_eo) + 1);
      }
    }
	printf("REG : %s\n", _stripped_message);
    regfree(&regex);
  }
  return _stripped_message;
}
main()
{
    // 테스트용 XML 문자열
    const char* test_xml = 
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<bwh:BokwireEnvelope xmlns:bwh=\"urn:bok:std:iso:20022:xsd:001\">"
        "    <bwh:BokwireHeader>"
        "            <TrCd>falseValue</TrCd>   <asdf>   <dd> </dd> </asdf>"
        "        <SecurityHandshake>"
        "            <TrCd>000000001</TrCd>"
        "            <Key>0084MTEwMXZlcgAAAAAENTAwMXJhbjEAAAAUvz4%2FD4lM3ZdUmhZQQMRlC0deSNxjdHlwAAAABENFUlQ%3D</Key>"
        "        </SecurityHandshake>"
        "    </bwh:BokwireHeader>"
        "</bwh:BokwireEnvelope>";

    printf("Testing parse_bokwire_envelope...\n");
    
    char ret_value[4096] = {0};
    int ret;

	// strip XML test
	printf("Original xml : \n%s\n", test_xml);
	char* strip_msg = (char*)strip_xml_message((char*)test_xml);
	printf("Strip xml : \n%s\n", strip_msg);
}

