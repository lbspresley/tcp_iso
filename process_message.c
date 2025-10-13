#include "tcp_iso.h"

int process_message(char* in, int inlen)
{
  int rc;
  char *outbuf = (char *)NULL;
  int outlen = 0;
  // int length_offset = 5;  // 길이 5바이트 오프셋

  /*
      1. 암호화 여부 및 복호화 처리
      2. ACK 응답 전문 여부 및 처리
      3. 수신 전문에 대한 ACK 전문 송신
      4. (POLL전문 처리시) POLL 전문 여부 및 처리
      5. 코어 송신(E2B)
        a. FEP 헤더 생성
        b. 전문변환 처리
        c. 인코딩 변환 처리
  */

  // 1. 암호화 여부 및 복호화 처리
  if( g_Encrypt_Flag == 0 ) {
    ulog( _WARNING_, "[NO-ENCRYPT] ONLY call data (%.10s...) len=%d", in, inlen );
    outbuf = in;
    outlen = inlen;
  } else {
    rc = inl_decrypt(in, inlen, &outbuf, &outlen);
    if (rc < 0)
    {
      ulog(_ERROR_, "[로그정보] 데이터 전문 복호화 실패 !! rc(%d)", rc);
      return -1;
    }
  }

  utrc(outlen, outbuf, "수신전문 복호화 len(%d)", outlen);

  // 2. ACK 응답 전문 여부 및 처리
  if( is_ack_response_msg(outbuf) ) {
    ulog(_FLOW_, "[ACK] 응답메시지 수신 !!");
    int rc = process_ack_response(outbuf);
    if( rc < 0 ) {
      ulog(_ERROR_, "[ACK] 응답메시지 처리 실패 !!");
      return -2;
    }

    ulog(_FLOW_, "[ACK] 응답메시지 처리 성공!!");

    // ACK 응답 전문 처리 성공
    return 0;
  }

  // 3. 수신 전문에 대한 ACK 전문 송신
  rc = send_ack_response(outbuf);
  if( rc < 0 ) {
    ulog(_ERROR_, "[ACK] 응답메시지 송신 실패 !!");
    return -3;
  }
  

  // 4. POLL 전문 여부 확인 및 처리
  if( is_poll_request_msg(outbuf) ) {
    ulog(_ERROR_, "[POLL] 요청메시지 수신 !!");
    int rc = process_poll_request(outbuf);
    if( rc < 0 ) {
      ulog(_ERROR_, "[POLL] 요청메시지 처리 실패 !!");
      return -4;
    }
    return 0;
  }

  // 5. 코어 송신(E2B)
  rc = send_to_core(outbuf, outlen);
  if( rc < 0 ) {
    ulog(_ERROR_, "[코어 송신] 코어 송신 실패 !!");
    return -5;
  }

  return 0;
}

/*
* 코어 송신(E2B)
* a. FEP 헤더 생성
* b. BOK 헤더 생성
* c. Set Data
* d. (전문변환여부)전문변환 처리
* e. (인코딩 변환 여부)인코딩 변환 처리
*/
int send_to_core(char* outbuf, int outlen)
{
  static char* _tpalloc_msg = (char*)NULL;
  static int _tpalloc_msg_len = MAX_MSG_LEN + sizeof(S_CL_HEADER) + SIZE_BOK_HEADER;
  int rc;

  // alloc initial buffer
  if( _tpalloc_msg == NULL ) {
    _tpalloc_msg = (char*)tpalloc("CARRAY", NULL, _tpalloc_msg_len);
    if( _tpalloc_msg == NULL ) {
      ulog(_ERROR_, "Failed to allocate memory for tpalloc message");
      return -1;
    }
  }

  // check tpalloc buffer size
  if( outlen + sizeof(S_CL_HEADER) + SIZE_BOK_HEADER > _tpalloc_msg_len ) {
    _tpalloc_msg_len = outlen + sizeof(S_CL_HEADER) + SIZE_BOK_HEADER;
    tpfree(_tpalloc_msg);
    _tpalloc_msg = (char*)tpalloc("CARRAY", NULL, _tpalloc_msg_len);
    if( _tpalloc_msg == NULL ) {
      ulog(_ERROR_, "Failed to allocate memory for tpalloc message");
      return -2;
    }
  }

  BOK_HEADER *pBokHdr = (BOK_HEADER *)_tpalloc_msg + sizeof(S_CL_HEADER);
  memset((char*)pBokHdr, 0x20, SIZE_BOK_HEADER);

  // Request/Response 구분
  int is_request = 0;
  char* value = NULL;

	char RespCd   [7+1] = {0};   // REQ(O),RSP(O) (REQ:SPACE, RSP:SUCCESS/FAIL)
	char MsgTpCd  [35+1] = {0};  // REQ(O),RSP(O) (Max 27)
	char BizSvc   [35+1] = {0};  // REQ(X),RSP(O)
	char BizMsgIdr[35+1] = {0};  // REQ(X),RSP(O)
	char Id       [16+1] = {0};  // REQ(O),RSP(X)
	char Password [16+1] = {0};  // REQ(O),RSP(X)

  if( strstr(outbuf, "<Request>") != NULL || strstr(outbuf, "<bwh:Request>") != NULL ) {
    is_request = 1;
  }

  value = (char *)get_tag_value(outbuf, "MsgTpCd");
  if( value == NULL ) {
    ulog(_ERROR_, "MsgTpCd 추출 실패 !!");
    return -5;
  }

  if( check_msg_tp_cd(value) == 0 ) {
    ulog(_ERROR_, "[MsgTpCd] 메시지 유형 코드 체크 실패 !!(%s)", value);
    return -6;
  }
  strcpy(MsgTpCd, value);

  if (is_request == 0) {
    // Response
    memcpy(pBokHdr->RespCd, "RSP", 3);

    value = (char *)get_tag_value(outbuf, "RespCd");
    if (value == NULL) {
      ulog(_ERROR_, "RespCd 추출 실패 !!");
      return -7;
    }
    strcpy(RespCd, value);

    value = (char *)get_tag_value(outbuf, "BizSvc");
    if (value == NULL) {
      ulog(_ERROR_, "BizSvc 추출 실패 !!");
      return -8;
    }
    strcpy(BizSvc, value);

    value = (char *)get_tag_value(outbuf, "BizMsgIdr");
    if (value == NULL) {
      ulog(_ERROR_, "BizMsgIdr 추출 실패 !!");
      return -9;
    }
    strcpy(BizMsgIdr, value);
  } else {
    memcpy(pBokHdr->RespCd, "REQ", 3);
    // Request
    value = (char *)get_tag_value(outbuf, "Id");
    if (value == NULL) {
      ulog(_ERROR_, "Id 추출 실패 !!");
      return -10;
    }
    strcpy(Id, value);

    value = (char *)get_tag_value(outbuf, "Password");
    if (value == NULL) {
      ulog(_ERROR_, "Password 추출 실패 !!");
      return -11;
    }
    strcpy(Password, value);
  }


  if (strlen(MsgTpCd) > 0) {
    memcpy(pBokHdr->MsgTpCd, MsgTpCd, strlen(MsgTpCd));
  }
  if (strlen(RespCd) > 0) {
    memcpy(pBokHdr->RespCd, RespCd, strlen(RespCd));
  }
  if (strlen(BizSvc) > 0) {
    memcpy(pBokHdr->BizSvc, BizSvc, strlen(BizSvc));
  }
  if (strlen(BizMsgIdr) > 0) {
    memcpy(pBokHdr->BizMsgIdr, BizMsgIdr, strlen(BizMsgIdr));
  }
  if (strlen(Id) > 0) {
    memcpy(pBokHdr->Id, Id, strlen(Id));
  }
  if (strlen(Password) > 0) {
    memcpy(pBokHdr->Password, Password, strlen(Password));
  }

  ulog(_FLOW_, "[BOK 헤더] 생성 완료 !!");
  ulog(_FLOW_, "[BOK 헤더] RespCd: %s, MsgTpCd: %s, BizSvc: %s, BizMsgIdr: %s, Id: %s, Password: %s", RespCd, MsgTpCd, BizSvc, BizMsgIdr, Id, Password);

// TODO: 전문변환 및 인코딩 처리

#if 0
  // d. 전문변환 처리
  // 1) BokwireBody 추출
  char* bokwire_body = (char*)get_tag_value(outbuf, "bwh:BokwireBody");
  if( bokwire_body == NULL ) {
    ulog(_ERROR_, "BokwireBody 추출 실패 !!");
    return -12;
  }

rc = req_trs(g_transform_ip, g_transform_port, outbuf, outlen, &outbuf, &outlen);
if( rc < 0 ) {
  ulog(_ERROR_, "[전문변호환] 전문변호환 실패 !!");
  return -12;
}

  if( g_transform_port != 0 ) {
    // TODO: 전문변환 처리
    // 변환 요청 / 응답
    rc = 0;
    if( rc < 0 ) {
      ulog(_ERROR_, "[전문변환] 전문변환 실패 !!");
      return -12;
    }
  }

// TODO: config에서 변환요청(IP/PORT), 한글 인코딩 타입(UTF-8/EUC-KR/CP949) 설정 처리
  if( g_kr_encoding != NULL ) {
    // TODO: 인코딩 변환 처리
    // 변환 요청 / 응답
    rc = 0;
    if( rc < 0 ) {
      ulog(_ERROR_, "[인코딩] 인코딩 실패 !!");
      return -13;
    }
  }
#endif

  // c. Set Data 
  memcpy(_tpalloc_msg + sizeof(S_CL_HEADER) + SIZE_BOK_HEADER, outbuf, outlen);

#ifdef _KSFC_
  // a. FEP 헤더 생성
  S_CL_HEADER *pFepHdr = (S_CL_HEADER *)_tpalloc_msg;
  memset((char*)pFepHdr, 0x20, sizeof(S_CL_HEADER));

  // set FEP Header : c_Len
  int msg_len = outlen + sizeof(S_CL_HEADER) + SIZE_BOK_HEADER;
  char msg_len_str[6+1];
  sprintf(msg_len_str, "%06d", msg_len);
  memcpy(pFepHdr->c_Len, msg_len_str, 6);

  memcpy(pFepHdr->c_ExChanID, g_ServiceName, sizeof(pFepHdr->c_ExChanID));
  memcpy(pFepHdr->c_MsgDsc, "APMG", sizeof(pFepHdr->c_MsgDsc));

  char interfaceID[100];
  (void) replaceString(MsgTpCd, ".", "_");
  sprintf(interfaceID, "%s_I1", MsgTpCd);
  memcpy(pFepHdr->c_ApCode, interfaceID, strlen(interfaceID));

  // TODO: set FEP Header : BeChanID, ExChanID, c_ExSeqNo, c_ApCode, c_RpstApCode 

  // 6. 코어 송신(E2B)
  rc = tpacall("CFR_E2B_MST", _tpalloc_msg, msg_len, TPNOREPLY | TPBLOCK);
  if( rc < 0 ) {
    ulog(_ERROR_, "[코어 송신] 코어 송신 실패 !!");
    return -14;
  }

  ulog(_FLOW_, "[코어 송신] 코어 송신 성공 !!");
#endif

  return 0;
}

void replaceString(char* str, char* org, char* rep)
{
  char* ptr = str;
  while( ptr != NULL ) {
    ptr = strstr(ptr, org);
    if( ptr != NULL ) {
      *ptr = rep;
    }
  }
}