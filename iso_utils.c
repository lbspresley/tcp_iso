#include "tcp_iso.h"

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

/*
 * 태그값 추출
 */
unsigned char* get_tag_value(char* msg, char* tag)
{
  static unsigned char _tag_value[1024];

  char startTag[256];
  char endTag[256];
  char *pStart = NULL;
  char *pEnd = NULL;
  char *current_msg = msg;

  // Multi-level 태그 처리 - strtok 대신 수동으로 분할
  char tag_copy[256];
  strcpy(tag_copy, tag);

  char *tag_ptr = tag_copy;
  char *slash_ptr;

  while ((slash_ptr = strchr(tag_ptr, '/')) != NULL)
  {
    // 현재 태그 이름 추출 (null로 종료)
    *slash_ptr = '\0';

    sprintf(startTag, "<%s", tag_ptr);
    sprintf(endTag, "</%s>", tag_ptr);

    pStart = strstr(current_msg, startTag);
    if (pStart == NULL)
    {
      return NULL;
    }

    // 현재 태그의 시작 위치
    // pStart += strlen(startTag);
    // '>' 문자를 찾아서 태그의 실제 끝 위치 확인
    char *tagEnd = strchr(pStart, '>');
    if (tagEnd == NULL)
    {
      return NULL;
    }

    // 태그 내용의 시작 위치 ('>' 다음)
    pStart = tagEnd + 1;

    // 현재 태그의 끝 위치
    pEnd = strstr(pStart, endTag);
    if (pEnd == NULL)
    {
      return NULL;
    }

    // 다음 태그를 찾기 위해 현재 태그의 시작 위치로 이동 (내부에서 검색)
    current_msg = pStart;

    // 다음 태그로 이동
    tag_ptr = slash_ptr + 1;
  }

  // 마지막 태그 처리
  if (strlen(tag_ptr) > 0)
  {
    sprintf(startTag, "<%s", tag_ptr);
    sprintf(endTag, "</%s>", tag_ptr);

    pStart = strstr(current_msg, startTag);
    if (pStart == NULL)
    {
      return NULL;
    }

    // pStart += strlen(startTag);
    //  '>' 문자를 찾아서 태그의 실제 끝 위치 확인
    char *tagEnd = strchr(pStart, '>');
    if (tagEnd == NULL)
    {
      return NULL;
    }

    // 태그 내용의 시작 위치 ('>' 다음)
    pStart = tagEnd + 1;
    pEnd = strstr(pStart, endTag);
    if (pEnd == NULL)
    {
      return NULL;
    }

    // 마지막 태그의 값을 추출
    memcpy(_tag_value, pStart, pEnd - pStart);
    _tag_value[pEnd - pStart] = '\0';
    return _tag_value;
  }

  return NULL;
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
    // 0: ETC-KR -> UTF-8
    strcpy(from_charset, "EUC-KR");
    strcpy(to_charset, "UTF-8");
  } else if (encode_type == 1) {
    // 1: UTF-8 -> ETC-KR
    strcpy(from_charset, "UTF-8");
    strcpy(to_charset, "EUC-KR");
  } else if (encode_type == 2) {
    // 2: MS949 -> UTF-8
    strcpy(from_charset, "MS949");
    strcpy(to_charset, "UTF-8");
  } else if (encode_type == 3) {
    // 3: UTF-8 -> MS949
    strcpy(from_charset, "UTF-8");
    strcpy(to_charset, "MS949");
  } else {
    ulog(_ERROR_, "Invalid encode type");
    return -1;
  }

  // charset convert
  iconv_t cd = iconv_open(to_charset, from_charset);
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

// 0: EUC-KR -> UTF-8, 2: MS949 -> UTF-8
unsigned char* convert_to_utf8(char* kr_encoding, char* msg, size_t msg_len, size_t *out_msg_len )
{
  static int _utf8_converted_msg_len = MAX_MSG_LEN;
  static unsigned char *_utf8_converted_msg = (unsigned char*)NULL;

  if( _utf8_converted_msg == NULL ) {
    _utf8_converted_msg = (unsigned char*)malloc(_utf8_converted_msg_len);
    if( _utf8_converted_msg == NULL ) {
      ulog(_ERROR_, "Failed to allocate memory for utf8 converted message");
      return (unsigned char*)NULL;
    }
  }

  int kr_encoding_type = 0;
  if( strcmp(kr_encoding, "EUC-KR") == 0 ) {
    kr_encoding_type = 0;
  } else if( strcmp(kr_encoding, "MS949") == 0 ) {
    kr_encoding_type = 2;
  } else {
    ulog(_ERROR_, "Invalid kr encoding");
    return (unsigned char*)NULL;
  }

  size_t out_len = charset_convert(kr_encoding_type, msg, msg_len, _utf8_converted_msg, out_msg_len);
  if( out_len < 0 ) {
    ulog(_ERROR_, "Failed to convert message to utf8");
    return (unsigned char*)NULL;  
  }

  *out_msg_len = out_len;  
  return _utf8_converted_msg;
}

// 1: UTF-8 -> EUC-KR, 3: UTF-8 -> MS949
unsigned char* convert_to_kr(char* kr_encoding, char* msg, size_t msg_len, size_t *out_msg_len )
{
  static int _kr_converted_msg_len = MAX_MSG_LEN;
  static unsigned char *_kr_converted_msg = (unsigned char*)NULL;

  if( _kr_converted_msg == NULL ) {
    _kr_converted_msg = (unsigned char*)malloc(_kr_converted_msg_len);
    if( _kr_converted_msg == NULL ) {
      ulog(_ERROR_, "Failed to allocate memory for kr converted message");
      return (unsigned char*)NULL;
    }
  }

  int kr_encoding_type = 1;
  if( strcmp(kr_encoding, "EUC-KR") == 0 ) {
    kr_encoding_type = 1;
  } else if( strcmp(kr_encoding, "MS949") == 0 ) {
    kr_encoding_type = 3;
  } else {
    ulog(_ERROR_, "Invalid kr encoding");
    return (unsigned char*)NULL;
  }

  size_t out_len = charset_convert(kr_encoding_type, msg, msg_len, _kr_converted_msg, out_msg_len);
  if( out_len < 0 ) {
    ulog(_ERROR_, "Failed to convert message to kr");
    return (unsigned char*)NULL;
  }

  *out_msg_len = out_len;
  return _kr_converted_msg;
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

/* 
 * ACK 응답메시지 여부 체크
 */
int is_ack_response_msg(char* msg)
{
  char respcd[36] = {0};
  int ret = parse_xml_xpath(msg, "//Response/RespCd", respcd);
  if( ret < 0 ) {
    return 0;
  }

  if( strcmp(respcd, "SUCCESS") == 0 || strcmp(respcd, "FAILURE") == 0 ) {
    return 1;
  }

  // get BizMsgIdr
  char biz_msg_idr[36] = {0};
  ret = parse_xml_xpath(msg, "//Response/BizMsgIdr", biz_msg_idr);
  if( ret < 0 ) {
    return 0;
  }

  // search timer id with bizMsgIdr
  int timer_id ;

  // stop timer

  return 0;
}

/* 
 * ACK 메시지 응답여부 체크
 *
 * admi : admi.002, admi.004.ConnectionCheck, admi.004.SystemNotification, admi.006, admi.007, admi.011 (6 종)
 * camt : camt.005, camt.006, camt.007, camt.025, camt.029, camt.052, camt.053, camt.054, camt.056, camt.060, camt.110, camt.111 (12 종)
 * pacs : pacs.002.CLS, pacs.002.CORE, pacs.004.CLS, pacs.004.CORE, pacs.008.CORE, pacs.009.CLS, pacs.009.CORE, pacs.028 (8 종)
 */
int is_need_ack_msg(char* msg)
{
  // char *tr_cd = (char*)get_tr_cd(msg);
  char msg_tp_cd[36] = {0};
  int ret = parse_xml_xpath(msg, "//Request/MsgTpCd", msg_tp_cd);
  if( ret < 0 ) {
    return 0;
  }

  const char* ack_tr_cds[] = {
    "admi.002", "admi.004.ConnectionCheck", "admi.004.SystemNotification", "admi.006", "admi.007", "admi.011",
    "camt.005", "camt.006", "camt.007", "camt.025", "camt.029", "camt.052", "camt.053", "camt.054", "camt.056", "camt.060", "camt.110", "camt.111",
    "pacs.002.CLS", "pacs.002.CORE", "pacs.004.CLS", "pacs.004.CORE", "pacs.008.CORE", "pacs.009.CLS", "pacs.009.CORE", "pacs.028"
  };

  for( int i = 0; i < sizeof(ack_tr_cds) / sizeof(ack_tr_cds[0]); i++ ) {
    if( strcmp(msg_tp_cd, ack_tr_cds[i]) == 0 ) {
      return 1;
    }
  }


  return 0;
}

/* 
 * 표준 전문 송신
 */
int send_standard_msg(char* msg, int msg_len)
{
  char* bizMsgIdr = (char*)get_tag_value(msg, "BizMsgIdr");
  if( bizMsgIdr == NULL ) {
    return 0;
  }

  // timer id with bizMsgIdr

  return 0;
}


#if 0
unsigned char* make_poll_req(char* reqxml)
{
  static unsigned char _poll_req[1024];

  sprintf((char*)_poll_req, POLL_REQ_TEMPLATE, msgtpcd, bizsvc, bizmsgidr);
  return _poll_req;
}

unsigned char* make_poll_rsp(char* reqxml)
{
  static unsigned char _poll_rsp[1024];

  parse_xml_xpath(reqxml, "//Request/MsgTpCd", msgtpcd);
  sprintf((char*)_poll_rsp, POLL_RSP_TEMPLATE, respcd, msgtpcd, bizsvc, bizmsgidr);
  return _poll_rsp;
}
#endif