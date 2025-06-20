
#include "tcp_bok.h"

char* make_network_msg()
{
  static char _network_msg[1024];

  // date time
  char timestr[32];
  get_iso_datetime(timestr);

  sprintf(_network_msg, NETWORK_TEMPLATE, gc_org_cd, timestr);
  return _network_msg;
}

char* make_sess_key_msg(int step, char* key)
{
  static char _sess_key_msg[1024];

  sprintf(_sess_key_msg, SKEY_TEMPLATE, step, key);
  return _sess_key_msg;
}

char* get_tag_value(char* msg, char* tag)
{
  static char _tag_value[1024];

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
char* get_sess_key(char* msg)
{
  return get_tag_value(msg, "Key");
}

/* 
 * 트랜잭션코드를 추출
 */
char* get_tr_cd(char* msg)
{
  return get_tag_value(msg, "TrCd");
}

/*
 * 타임스트링을 ISO 8601 형식으로 변환
*/
void get_iso_datetime(char timestr[32])
{
  char outstr[200];
  struct tm *pTm;
  struct timeval tv;
  int milliseconds ; 

  gettimeofday(&tv, NULL);
  pTm = localtime(&tv.tv_sec);

  strftime(outstr, sizeof(outstr), "%Y-%m-%dT%H:%M:%S", pTm);

  milliseconds = tv.tv_usec / 1000;
  sprintf(outstr, "%s.%03d", outstr, milliseconds);
  strcpy(timestr, outstr);
  strcat(timestr, "+09:00");
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
size_t charset_convert(int encode_type, char* msg, size_t msg_len, char* out_msg, size_t *out_msg_len )
{
  static char _converted_msg[MAX_MSG_LEN];
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
    return msg;
  }

  char* pIn = msg;
  char* pOut = out_msg;
  size_t inLen = msg_len;
  size_t outLen = iconv(cd, &pIn, &inLen, &pOut, out_msg_len);
  if (outLen == (size_t)-1) {
    perror("iconv");
    return -1;
  }

  *out_msg_len = outLen;

  iconv_close(cd);

  return 0;
}

char* convert_to_utf8(char* msg, size_t msg_len, size_t *out_msg_len )
{
  static char _converted_msg[MAX_MSG_LEN];

  size_t out_len = charset_convert(0, msg, msg_len, _converted_msg, out_msg_len);
  *out_msg_len = out_len;
  return _converted_msg;
}

char* convert_to_euc_kr(char* msg, size_t msg_len, size_t *out_msg_len )
{
  static char _converted_msg[MAX_MSG_LEN];

  size_t out_len = charset_convert(1, msg, msg_len, _converted_msg, out_msg_len);
  *out_msg_len = out_len;
  return _converted_msg;
}
