#include "tcp_iso.h"

int CF_ProcessMessage(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2)
{
  int rc;
  char *in = (char *)*ppFrame;
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
  rc = inl_decrypt(in + length_offset, *pFrameLen - length_offset, &outbuf, &outlen);
  if (rc < 0)
  {
    ulog(_ERROR_, "[로그정보] 데이터 전문 복호화 실패 !!");
    return RC_NEXT_ACTION;
  }

  char *tr_cd = (char *)get_tr_cd(outbuf);
  if (tr_cd == NULL)
  {
    ulog(_ERROR_, "[로그정보] 트랜잭션 코드 추출 실패 !!");
    return RC_NEXT_ACTION;
  }

  ulog(_ERROR_, "[로그정보] 트랜잭션 코드 : %s", tr_cd);

  // ACK 처리 로직
  // 1. check whether the message is response-ACK
  //   1-1. check requested Timer for response-ACK
  //   1-2. stop timer
  //   1-3. check time-out for each message
  // 
  // 2. check whether the message is need to send ACK
  //   2-1. make ACK message
  //   2-2. send ACK message

  if( is_ack_response_msg(outbuf) ) {
    ulog(_ERROR_, "[로그정보] ACK 응답메시지 수신 !!");
    //   1-1. check requested Timer for response-ACK
    //   1-2. stop timer
    //   1-3. check time-out for each message
    return RC_NEXT_ACTION;
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
