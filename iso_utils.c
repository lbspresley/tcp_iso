
#include "tcp_bok.h"

unsigned char* make_network_msg()
{
  static unsigned char _network_msg[1024];

  // date time
  char timestr[32];
  get_iso_datetime(timestr);

  sprintf((char*)_network_msg, NETWORK_TEMPLATE, gc_org_cd, timestr);
  return _network_msg;
}

unsigned char* make_sess_key_msg(int step, char* key)
{
  static unsigned char _sess_key_msg[1024];

  sprintf((char*)_sess_key_msg, SKEY_TEMPLATE, step, key);
  return _sess_key_msg;
}

unsigned char* get_tag_value(char* msg, char* tag)
{
  static unsigned char _tag_value[1024];

  char startTag[256];
  char endTag[256];
  char* pStart = NULL;
  char* pEnd = NULL;

  sprintf(startTag, "<%s>", tag);
  sprintf(endTag, "</%s>", tag);

  pStart = strstr(msg, startTag);
  if(pStart == NULL) {
    return NULL;
  }
  pStart += strlen(startTag);
  pEnd = strstr(pStart, endTag);

  memset(_tag_value, 0x00, sizeof(_tag_value));
  memcpy(_tag_value, pStart, pEnd - pStart);
  return _tag_value;
}

/* 
 * 세션키를 추출
 */
unsigned char* get_sess_key(char* msg)
{
  return (unsigned char*)get_tag_value(msg, "Key");
}

/* 
 * 트랜잭션코드를 추출
 */
unsigned char* get_tr_cd(char* msg)
{
  return (unsigned char*)get_tag_value(msg, "TrCd");
}

/*
 * 타임스트링을 ISO 8601 형식으로 변환
*/
void get_iso_datetime(char timestr[32])
{
  char outstr[200];
  char local_timestr[40];
  struct tm *pTm;
  struct timeval tv;
  int milliseconds ; 

  gettimeofday(&tv, NULL);
  pTm = localtime(&tv.tv_sec);

  strftime(local_timestr, sizeof(local_timestr), "%Y-%m-%dT%H:%M:%S", pTm);

  milliseconds = tv.tv_usec / 1000;
  sprintf(outstr, "%s.%03d", local_timestr, milliseconds);
  strcat(outstr, "+09:00");
  strcpy(timestr, outstr);

  return;
}

void get_iso_datetime_old(char timestr[32])
{
  struct tm *pTm;
  time_t t;
  char outstr[200];

  t = time(NULL);
  pTm = localtime(&t);
  if (pTm == NULL) {
    return;
  }

  strftime(outstr, sizeof(outstr), "%Y-%m-%dT%H:%M:%S.000", pTm);
  strcpy(timestr, outstr);
  strcat(timestr, "+09:00");
  return;
}

// 문자셋 변환
size_t charset_convert(int encode_type, char* msg, size_t msg_len, unsigned char* out_msg, size_t *out_msg_len )
{
  char from_charset[32];
  char to_charset[32];

  if (encode_type == 0) {
    // ETC-KR -> UTF-8
    strcpy(from_charset, "EUC-KR");
    strcpy(to_charset, "UTF-8");
  } else {
    // UTF-8 -> ETC-KR
    strcpy(from_charset, "UTF-8");
    strcpy(to_charset, "EUC-KR");
  }

  // UTF-8 to EUC-KR
  iconv_t cd = iconv_open(from_charset, to_charset);
  if (cd == (iconv_t)-1) {
    perror("iconv");
    return -1;
  }

  char* pIn = msg;
  char* pOut = (char*)out_msg;
  size_t inLen = msg_len;
  size_t outLen = iconv(cd, &pIn, &inLen, &pOut, out_msg_len);
  if (outLen == (size_t)-1) {
    perror("iconv");
    return -2;
  }

  *out_msg_len = outLen;

  iconv_close(cd);

  return 0;
}

unsigned char* convert_to_utf8(char* msg, size_t msg_len, size_t *out_msg_len )
{
  static unsigned char _utf8_converted_msg[MAX_MSG_LEN];

  size_t out_len = charset_convert(0, msg, msg_len, _utf8_converted_msg, out_msg_len);
  *out_msg_len = out_len;
  return _utf8_converted_msg;
}

unsigned char* convert_to_euc_kr(char* msg, size_t msg_len, size_t *out_msg_len )
{
  static unsigned char _euckr_converted_msg[MAX_MSG_LEN];

  size_t out_len = charset_convert(1, msg, msg_len, _euckr_converted_msg, out_msg_len);
  *out_msg_len = out_len;
  return _euckr_converted_msg;
}

unsigned char* make_ack_msg(char* reqxml)
{
  static unsigned char _ack_msg[1024];

    // parse request xml
    char respcd[36] = "SUCCESS";
    char msgtpcd[36] = {0};
    char bizsvc[36] = {0};
    char bizmsgidr[36] = {0};

    parse_xml_xpath(reqxml, "//Request/MsgTpCd", msgtpcd);
    parse_xml_xpath(reqxml, "//h:BizSvc", bizsvc);
    parse_xml_xpath(reqxml, "//h:BizMsgIdr", bizmsgidr);

  sprintf((char*)_ack_msg, ACK_TEMPLATE, respcd, msgtpcd, bizsvc, bizmsgidr);
  return _ack_msg;
}
