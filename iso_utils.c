#include "tcp_iso.h"

/*
 * Setting variables
 * 1. BizMsgIdr(request 복사)
 * 2. MmbId(자신의 은행 코드) : gc_org_cd
 * 3. BizMsgIdr (신규발행) : new_biz_msg_idr
 * 4. CreDt (현재시간) : cre_dt
 * 5. BizPrcgDt (개시 시간 : 현재날짜+9시 고정)
 * 6. MsgId (3번항목 동일) : new_biz_msg_idr
 * 7. OrgtrRef (1번항목 동일) : biz_msg_idr
 * 8. EvtTm (request 복사)
*/
unsigned char* make_poll_response(char* reqxml)
{
  static unsigned char _poll_response[2048];

  // 1. get BizMsgIdr from request
  char biz_msg_idr [36] ;
  char new_biz_msg_idr [36] ;

  char* value = (char*)get_tag_value(reqxml, "BizMsgIdr");
  if( value == NULL ) {
    return NULL;
  }
  strcpy(biz_msg_idr, value);

  // 2. get new BizMsgIdr
  get_msg_idr(new_biz_msg_idr);

  // 3. get date time
  char cre_dt[32];
  get_iso_datetime(cre_dt);

  // 4. get BizPrcgDt
  char biz_prcg_dt[32];
  get_iso_date(biz_prcg_dt, NULL);

  // 5. get EvtTm from request
  char evt_tm[32];
  value = (char*)get_tag_value(reqxml, "EvtTm");
  if( value == NULL ) {
    return NULL;
  }
  strcpy(evt_tm, value);

  // 9개 항목
  sprintf((char*)_poll_response, POLL_RSP_TEMPLATE, 
      gc_plain_id, gc_plain_pw, gc_org_cd, 
      new_biz_msg_idr, cre_dt, biz_prcg_dt, 
      new_biz_msg_idr, biz_msg_idr, evt_tm);
  return _poll_response;
}

/*
 * Setting variables
 * 1. BizMsgIdr (신규발행)
 * 2. CreDt (현재시간) : cre_dt
 * 3. BizPrcgDt (개시 시간 : 현재날짜+9시 고정) : biz_prcg_dt
*/
unsigned char* make_poll_request()
{
  static unsigned char _poll_request[2048];

  // 1. get new BizMsgIdr
  char new_biz_msg_idr [36] ;
  get_msg_idr(new_biz_msg_idr);

  // 2. get date time
  char cre_dt[32];
  get_iso_datetime(cre_dt);

  // 3. get BizPrcgDt
  char biz_prcg_dt[32];
  get_iso_date(biz_prcg_dt, NULL);

  // 8개 항목
  sprintf((char*)_poll_request, POLL_REQ_TEMPLATE, 
      gc_plain_id, gc_plain_pw, gc_org_cd, 
      new_biz_msg_idr, cre_dt, biz_prcg_dt, 
      gc_org_cd, cre_dt);
  return _poll_request;
}

unsigned char* make_header(char* msg_tp_cd, char* body)
{
  static unsigned char _iso_full_message [1024*60];

  sprintf((char*)_iso_full_message, BOKWIRE_HEADER_TEMPLATE, 
        msg_tp_cd, gc_plain_id, gc_plain_pw, body);
  return _iso_full_message;
}

unsigned char* get_body(char* msg)
{
  static unsigned char _body [1024*60];

  char* body = (char*)get_tag_value(msg, "BokwireBody");
  if( body == NULL ) {
    return NULL;
  }

  strcpy((char*)_body, body);
  return _body;
}

unsigned char* strip_xml_message(char* msg)
{
  static unsigned char _stripped_message [1024*60];

  strcpy((char*)_stripped_message, (char*)msg);

  // remove xml declaration
  char* xml_decl = strstr((char*)_stripped_message, "<?xml");
  if( xml_decl != NULL ) {
    char* content_start = strstr(xml_decl, "?>");
    if( content_start != NULL ) {
      content_start += 2;
      memmove((char*)_stripped_message, content_start, strlen(content_start) + 1);
    }
  }

  // remove whitespace between tags with regex
  regex_t regex;
  regmatch_t match;
  if( regcomp(&regex, ">\\s+<", REG_EXTENDED) == 0 ) {
    while( regexec(&regex, (char*)_stripped_message, 1, &match, 0) == 0 ) {
      int match_len = match.rm_eo - match.rm_so;
      if( match_len > 0 ) {
        memmove((char*)_stripped_message + match.rm_so, (char*)_stripped_message + match.rm_eo, strlen((char*)_stripped_message + match.rm_eo) + 1);
      }
    }
    regfree(&regex);
  }

  // remove empty tags with regex
  if( regcomp(&regex, "<[^/>][^>]*/>", REG_EXTENDED) == 0 ) {
    while( regexec(&regex, (char*)_stripped_message, 1, &match, 0) == 0 ) {
      int match_len = match.rm_eo - match.rm_so;
      if( match_len > 0 ) {
        memmove((char*)_stripped_message + match.rm_so, (char*)_stripped_message + match.rm_eo, strlen((char*)_stripped_message + match.rm_eo) + 1);
      }
    }
    regfree(&regex);
  }


  return _stripped_message;
}

unsigned char* make_unescaped_value(char* msg)
{
  static char* __escaped_strings[] = {
    "&amp;",
    "&lt;",
    "&gt;",
    "&quot;",
    "&apos;"
  };
  static char* __escaped_values[] = {
    "&",
    "<",
    ">",
    "\"",
    "'"
  };
  static int __escaped_values_len = sizeof(__escaped_values) / sizeof(__escaped_values[0]);
  static unsigned char _unescaped_value[1024];

  int src_len;
  int dst_pos = 0;
  int i, j;
  int found = 0;

  if( msg == NULL ) {
    return NULL;
  }

  src_len = strlen(msg);

  for( i = 0; i < src_len && dst_pos < sizeof(_unescaped_value) - 10; i++ ) {
    found = 0;
    
    // 현재 위치에서 이스케이프된 문자열이 시작되는지 확인
    for( j = 0; j < __escaped_values_len; j++ ) {
      int escape_len = strlen(__escaped_strings[j]);
      if( strncmp(msg + i, __escaped_strings[j], escape_len) == 0 ) {
        // 이스케이프된 문자열을 찾았음
        strcpy((char*)_unescaped_value + dst_pos, __escaped_values[j]);
        dst_pos += strlen(__escaped_values[j]);
        i += escape_len - 1; // -1은 for 루프에서 i++이 실행되기 때문
        found = 1;
        break;
      }
    }
    
    if( !found ) {
      // 이스케이프된 문자열이 아니면 그대로 복사
      _unescaped_value[dst_pos++] = msg[i];
    }
  }

  _unescaped_value[dst_pos] = '\0';
  return _unescaped_value;
}

unsigned char* make_escaped_value(char* msg)
{
  static unsigned char _escaped_value[1024];
  int src_len = strlen(msg);
  int dst_pos = 0;
  int i;

  if( msg == NULL ) {
    return NULL;
  }

  // 최대 길이 체크 (이스케이프로 인해 최대 5배까지 증가 가능)
  if( src_len * 5 >= sizeof(_escaped_value) - 1 ) {
    return NULL;
  }

  for( i = 0; i < src_len && dst_pos < sizeof(_escaped_value) - 10; i++ ) {
    switch( msg[i] ) {
      case '&':
        if( dst_pos + 5 < sizeof(_escaped_value) ) {
          strcpy((char*)_escaped_value + dst_pos, "&amp;");
          dst_pos += 5;
        }
        break;
      case '<':
        if( dst_pos + 4 < sizeof(_escaped_value) ) {
          strcpy((char*)_escaped_value + dst_pos, "&lt;");
          dst_pos += 4;
        }
        break;
      case '>':
        if( dst_pos + 4 < sizeof(_escaped_value) ) {
          strcpy((char*)_escaped_value + dst_pos, "&gt;");
          dst_pos += 4;
        }
        break;
      case '"':
        if( dst_pos + 6 < sizeof(_escaped_value) ) {
          strcpy((char*)_escaped_value + dst_pos, "&quot;");
          dst_pos += 6;
        }
        break;
      case '\'':
        if( dst_pos + 6 < sizeof(_escaped_value) ) {
          strcpy((char*)_escaped_value + dst_pos, "&apos;");
          dst_pos += 6;
        }
        break;
      default:
        _escaped_value[dst_pos++] = msg[i];
        break;
    }
  }

  _escaped_value[dst_pos] = '\0';
  return _escaped_value;
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

  char startTag[512];
  char endTag[512];
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

void get_iso_date(char datestr[32], char timestr[9])
{
  char local_timestr[40];
  struct tm *pTm;
  struct timeval tv;

  gettimeofday(&tv, NULL);
  pTm = localtime(&tv.tv_sec);

  if( timestr != NULL ) {
    strftime(local_timestr, sizeof(local_timestr), "%Y-%m-%dT", pTm );
    strcat(local_timestr, timestr);
    strcat(local_timestr, "+09:00");
  } else {
    strftime(local_timestr, sizeof(local_timestr), "%Y-%m-%dT09:00:00+09:00", pTm);
  }

  strcpy(datestr, local_timestr);

  return;
}


void get_today(char date[32])
{
  char tmpstr[20];
  struct tm *pTm;
  time_t t;

  t = time(NULL);
  pTm = localtime(&t);
  if (pTm == NULL) {
    return;
  }

  strftime(tmpstr, sizeof(tmpstr), "%Y%m%d", pTm);
  strcpy(date, tmpstr);
  return;
}

void get_seq(char seq[7], char date[32])
{
    char seq_file[1024];
    int current_seq = 900001;
    FILE* fp = NULL;

    if( strlen(date) == 0 ) {
      get_today(date);
    }

    // 시퀀스 파일 경로 설정 
    sprintf(seq_file, "%s/msg_seq_%s.dat", gc_seqFilePath, date);

    // 시퀀스 파일을 읽기/쓰기 모드로 열기
    fp = fopen(seq_file, "r+");
    if (fp != NULL) {
        // 현재 시퀀스 읽기
        if (fscanf(fp, "%d", &current_seq) == 1) {
            current_seq++;  // 다음 시퀀스로 증가
        } else {
            current_seq = 900001;  // 읽기 실패 시 1부터 시작
        }
        
        // 파일 포인터를 처음으로 되돌리기
        rewind(fp);
        
        // 새로운 시퀀스로 파일 업데이트
        fprintf(fp, "%d", current_seq);
        fflush(fp);  // 버퍼 즉시 쓰기
        
        fclose(fp);
        fp = NULL;
    } else {
        // 파일이 존재하지 않는 경우 새로 생성
        fp = fopen(seq_file, "w");
        if (fp != NULL) {
            fprintf(fp, "%d", current_seq);
            fflush(fp);
            fclose(fp);
            fp = NULL;
        } else {
            // 파일 생성 실패 시 로그 출력 (선택사항)
            // ulog(_WARNING_, "Failed to create sequence file: %s", seq_file);
        }
    }
    
    sprintf(seq, "%06d", current_seq);
    return;
}

/*
 * 날짜별로 메시지 고유번호 생성
 * 프로세스 재기동시에도 이전 메시지 고유번호를 이어서 생성 가능하도록 함
 */
void get_msg_idr(char msgidr[35])
{
    char date[32];
    char orgid[5] = {0};
    char serial[9] = "00000000";
    char seq[7] = {0};

    get_today(date);
    get_seq(seq, date);

    // 조직 코드 설정
    if( strlen(gc_org_cd) > 0 ) {
      strcpy(orgid, gc_org_cd);
    } else {
      strcpy(orgid, "1016");
    }
    
    // 메시지 ID 생성
    sprintf(msgidr, "%.8s%.4s%c%.8s%.6s", date, orgid, 'S', serial, seq);
    // sprintf(msgidr, "%8s%4s%c%8s%6s", date, orgid, 'S', serial, seq);
    
    return;
}

int delete_send_msg(char* msgidr)
{
  char send_msg_file[1024];
  sprintf(send_msg_file, "%s/%s.dat", gc_seqFilePath, msgidr);
  if( access(send_msg_file, F_OK) != -1 ) {
    unlink(send_msg_file);
    return 0;
  }
  return -1;
}

/*
  msgidr 기준으로 전송 메시지 파일 저장
*/
int save_send_msg(char* msgidr, unsigned char* msg, int msg_len)
{
  char send_msg_file[1024];
  sprintf(send_msg_file, "%s/%s.dat", gc_seqFilePath, msgidr);

  // 파일 존재 여부 확인
  if( access(send_msg_file, F_OK) != -1 ) {
    // 파일 존재 시 오류 리턴
    return -1;
  }

  // 파일 생성
  FILE* fp = fopen(send_msg_file, "w");
  if( fp != NULL ) {
    fwrite(msg, 1, msg_len, fp);
    fclose(fp);
    return 0;
  }
  return -2;
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
    // 2: CP949 -> UTF-8
    strcpy(from_charset, "CP949");
    strcpy(to_charset, "UTF-8");
  } else if (encode_type == 3) {
    // 3: UTF-8 -> CP949
    strcpy(from_charset, "UTF-8");
    strcpy(to_charset, "CP949");
  } else {
    #ifdef ISO_TEST
    printf("Invalid encode type\n");
    #else
    ulog(_ERROR_, "Invalid encode type");
    #endif
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

// 0: EUC-KR -> UTF-8, 2: CP949 -> UTF-8
unsigned char* convert_to_utf8(char* kr_encoding, char* msg, size_t msg_len, size_t *out_msg_len )
{
  static int _utf8_converted_msg_len = MAX_MSG_LEN;
  static unsigned char *_utf8_converted_msg = (unsigned char*)NULL;

  if( _utf8_converted_msg == NULL ) {
    _utf8_converted_msg = (unsigned char*)malloc(_utf8_converted_msg_len);
    if( _utf8_converted_msg == NULL ) {
      #ifdef ISO_TEST
      printf("Failed to allocate memory for utf8 converted message\n");
      #else
      ulog(_ERROR_, "Failed to allocate memory for utf8 converted message");
      #endif
      return (unsigned char*)NULL;
    }
  }

  int kr_encoding_type = 0;
  if( strcmp(kr_encoding, "EUC-KR") == 0 ) {
    kr_encoding_type = 0;
  } else if( strcmp(kr_encoding, "CP949") == 0 ) {
    kr_encoding_type = 2;
  } else {
    #ifdef ISO_TEST
    printf("Invalid kr encoding\n");
    #else
    ulog(_ERROR_, "Invalid kr encoding");
    #endif
    return (unsigned char*)NULL;
  }

  size_t out_len = charset_convert(kr_encoding_type, msg, msg_len, _utf8_converted_msg, out_msg_len);
  if( out_len < 0 ) {
    #ifdef ISO_TEST
    printf("Failed to convert message to utf8\n");
    #else
    ulog(_ERROR_, "Failed to convert message to utf8");
    #endif
    return (unsigned char*)NULL;  
  }

  *out_msg_len = out_len;  
  return _utf8_converted_msg;
}

// 1: UTF-8 -> EUC-KR, 3: UTF-8 -> CP949
unsigned char* convert_to_kr(char* kr_encoding, char* msg, size_t msg_len, size_t *out_msg_len )
{
  static int _kr_converted_msg_len = MAX_MSG_LEN;
  static unsigned char *_kr_converted_msg = (unsigned char*)NULL;

  if( _kr_converted_msg == NULL ) {
    _kr_converted_msg = (unsigned char*)malloc(_kr_converted_msg_len);
    if( _kr_converted_msg == NULL ) {
      #ifdef ISO_TEST
      printf("Failed to allocate memory for kr converted message\n");
      #else
      ulog(_ERROR_, "Failed to allocate memory for kr converted message");
      #endif
      return (unsigned char*)NULL;
    }
  }

  int kr_encoding_type = 1;
  if( strcmp(kr_encoding, "EUC-KR") == 0 ) {
    kr_encoding_type = 1;
  } else if( strcmp(kr_encoding, "CP949") == 0 ) {
    kr_encoding_type = 3;
  } else {
    #ifdef ISO_TEST
    printf("Invalid kr encoding\n");
    #else
    ulog(_ERROR_, "Invalid kr encoding");
    #endif
    return (unsigned char*)NULL;
  }

  size_t out_len = charset_convert(kr_encoding_type, msg, msg_len, _kr_converted_msg, out_msg_len);
  if( out_len < 0 ) {
    #ifdef ISO_TEST
    printf("Failed to convert message to kr\n");
    #else
    ulog(_ERROR_, "Failed to convert message to kr");
    #endif
    return (unsigned char*)NULL;
  }

  *out_msg_len = out_len;
  return _kr_converted_msg;
}

// ACK 메시지 생성
unsigned char* make_ack_msg(char* reqxml)
{
  static unsigned char _ack_msg[1024];

    // parse request xml
    char respcd[36] = "SUCCESS";
    char msgtpcd[36] = {0};
    char bizsvc[36] = {0};
    char bizmsgidr[36] = {0};

#ifdef __USE_XML_PARSER__
    parse_xml_xpath(reqxml, "//Request/MsgTpCd", msgtpcd);
    parse_xml_xpath(reqxml, "//h:BizSvc", bizsvc);
    parse_xml_xpath(reqxml, "//h:BizMsgIdr", bizmsgidr);
#else
    char *value = NULL;
    value = get_tag_value(reqxml, "Request/MsgTpCd");
    if( value != NULL ) {
      strcpy(msgtpcd, value);
    }
    value = get_tag_value(reqxml, "h:BizSvc");
    if( value != NULL ) {
      strcpy(bizsvc, value);
    }
    value = get_tag_value(reqxml, "h:BizMsgIdr");
    if( value != NULL ) {
      strcpy(bizmsgidr, value);
    }
#endif

  sprintf((char*)_ack_msg, ACK_TEMPLATE, respcd, msgtpcd, bizsvc, bizmsgidr);
  return _ack_msg;
}

/* 
 * ACK 응답메시지 여부 체크
 */
int is_ack_response_msg(char* msg)
{
  char respcd[36] = {0};
  char biz_msg_idr[36] = {0};

#ifdef __USE_XML_PARSER__
  int ret = parse_xml_xpath(msg, "//Response/RespCd", respcd);
  if( ret < 0 ) {
    return 0;
  }

  // get BizMsgIdr
  ret = parse_xml_xpath(msg, "//Response/BizMsgIdr", biz_msg_idr);
  if( ret < 0 ) {
    return 0;
  }
#else
  char *value = NULL;
  value = get_tag_value(msg, "Response/RespCd");
  if( value == NULL ) {
    return 0;
  }
  strcpy(respcd, value);

  value = get_tag_value(msg, "Response/BizMsgIdr");
  if( value == NULL ) {
    return 0;
  }
  strcpy(biz_msg_idr, value);
#endif

  if( strcmp(respcd, "SUCCESS") == 0 || strcmp(respcd, "FAILURE") == 0 ) {
    return 1;
  }

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

#ifdef __USE_XML_PARSER__
  int ret = parse_xml_xpath(msg, "//Request/MsgTpCd", msg_tp_cd);
  if( ret < 0 ) {
    return 0;
  }
#else
  char *value = get_tag_value(msg, "Request/MsgTpCd");
  if( value == NULL ) {
    return 0;
  }
  strcpy(msg_tp_cd, value);
#endif

  const char* ack_tr_cds[] = {
    "admi.002", "admi.004.ConnectionCheck", "admi.004.SystemNotification", "admi.006", "admi.007", "admi.011",
    "camt.005", "camt.006", "camt.007", "camt.025", "camt.029", "camt.052", "camt.053", "camt.054", "camt.056", "camt.060", "camt.110", "camt.111",
    "pacs.002.CLS", "pacs.002.CORE", "pacs.004.CLS", "pacs.004.CORE", "pacs.008.CORE", "pacs.009.CLS", "pacs.009.CORE", "pacs.028"
  };

  int i;
  for( i = 0; i < sizeof(ack_tr_cds) / sizeof(ack_tr_cds[0]); i++ ) {
    if( strcmp(msg_tp_cd, ack_tr_cds[i]) == 0 ) {
      return 1;
    }
  }


  return 0;
}

/*
 * POLL 요청메시지 여부 체크
 */
int is_poll_request_msg(char* msg)
{
  char* value = (char*)get_tag_value(msg, "EvtCd");
  if( value == NULL ) {
    return 0;
  }

  if( strcmp(value, "PING") == 0 ) {
    return 1;
  }

  return 0;
}
