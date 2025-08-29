#include "tcp_iso.h"

int CF_ProcessMessage(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2)
{
  int rc;
  char *in = (char *)*ppFrame;
  int inlen = *pFrameLen;
  char *outbuf = (char *)NULL;
  int outlen = 0;
  int length_offset = 6;

  /*
    Encrypted : 데이터 전문 처리
      1. SVR session key로 복호화
      2. ACK 응답 전문 여부 확인
      3. (POLL전문 처리시) POLL 전문 여부 확인
      4. 전문변환 호출
      5. 전문변환 결과 확인
      6. FEP 헤더 조립
      7. 코어 송신(E2B)
  */

  in += length_offset;
  inlen -= length_offset;

  // Encrypt 안 할 경우
  if( g_Encrypt_Flag == 0 ) {
    ulog( _WARNING_, "[NO-ENCRYPT] ONLY call data (%.10s...) len=%d", in, inlen );
    outbuf = in;
    outlen = inlen;
  } else {
    rc = inl_decrypt(in, inlen, &outbuf, &outlen);
    if (rc < 0)
    {
      ulog(_ERROR_, "[로그정보] 데이터 전문 복호화 실패 !!");
      return RC_NEXT_ACTION;
    }
  }

  // ACK 응답 전문 여부 확인
  if( is_ack_response_msg(outbuf) ) {
    ulog(_ERROR_, "[ACK] 응답메시지 수신 !!");
    int rc = process_ack_response(outbuf);
    if( rc < 0 ) {
      ulog(_ERROR_, "[ACK] 응답메시지 처리 실패 !!");
      return RC_NEXT_ACTION;
    }
    return RC_NEXT_ACTION;
  }

  // POLL 전문 여부 확인
  if( is_poll_request_msg(outbuf) ) {
    ulog(_ERROR_, "[POLL] 요청메시지 수신 !!");
    int rc = process_poll_request(outbuf);
    if( rc < 0 ) {
      ulog(_ERROR_, "[POLL] 요청메시지 처리 실패 !!");
      return RC_NEXT_ACTION;
    }
    return RC_NEXT_ACTION;
  }



  // Make BOK Header
  BOK_HEADER bok_header;
  BOK_HEADER *pHeader = (BOK_HEADER *)outbuf;
  memset((char*)&bok_header, 0x20, SIZE_BOK_HEADER);

  // Request/Response 구분
  int is_request = 0;
  char* value = NULL;
  if( strstr(outbuf, "<Request>") != NULL || strstr(outbuf, "<bwh:Request>") != NULL ) {
    is_request = 1;
  }

  value = (char *)get_tag_value(outbuf, "MsgTpCd");
  if( value == NULL ) {
    ulog(_ERROR_, "MsgTpCd 추출 실패 !!");
    return RC_NEXT_ACTION;
  }

  if( check_msg_tp_cd(value) == 0 ) {
    ulog(_ERROR_, "[MsgTpCd] 메시지 유형 코드 체크 실패 !!(%s)", value);
    return RC_NEXT_ACTION;
  }
  memcpy(pHeader->MsgTpCd, value, strlen(value));

  if (is_request == 0) {
    // Response
    value = (char *)get_tag_value(outbuf, "RespCd");
    if (value == NULL)
    {
      ulog(_ERROR_, "RespCd 추출 실패 !!");
      return RC_NEXT_ACTION;
    }
    strcpy(pHeader->RespCd, value);

    value = (char *)get_tag_value(outbuf, "BizSvc");
    if (value == NULL)
    {
      ulog(_ERROR_, "BizSvc 추출 실패 !!");
      return RC_NEXT_ACTION;
    }
    strcpy(pHeader->BizSvc, value);

    value = (char *)get_tag_value(outbuf, "BizMsgIdr");
    if (value == NULL)
    {
      ulog(_ERROR_, "BizMsgIdr 추출 실패 !!");
      return RC_NEXT_ACTION;
    }
    strcpy(pHeader->BizMsgIdr, value);
  } else {
    // Request
    value = (char *)get_tag_value(outbuf, "Id");
    if (value == NULL)
    {
      ulog(_ERROR_, "Id 추출 실패 !!");
      return RC_NEXT_ACTION;
    }
    strcpy(pHeader->Id, value);

    value = (char *)get_tag_value(outbuf, "Password");
    if (value == NULL)
    {
      ulog(_ERROR_, "Password 추출 실패 !!");
      return RC_NEXT_ACTION;
    }
    strcpy(pHeader->Password, value);
  }


  // POLL 처리 로직
  // 1. check whether the message is POLL-response
  //   1-1. check requested Timer for POLL
  //   1-2. stop timer
  // 2. check Timer for POLL-request
  //   2-1. check POLL-request time-out 
  //   2-2. make POLL message
  //   2-3. send POLL message
  //   2-4. start timer for POLL-request


  return RC_NEXT_ACTION;
}
