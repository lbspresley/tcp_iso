#include "tcp_iso.h"

int CF_ReceiveMessage(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2)
{
  char*	in	= (char*) *ppFrame;
  int inlen = *pFrameLen;
  int rc = 0;
  
  // remove length (5) field
  in = in + 5;
  inlen = inlen - 5;

  /*
    1. 암호화 여부 확인
      1. plain text(x) or encrypted(o)
    2. SrcSvc : "CLI" or "SVR"
      1. CLI : session key(CLI)
      2. SVR : session key(SVR)
    3. Plain Text : 세션키 교환 전문 처리
      1. SrcSvc로 세션 종류 확인
      2. 세션키 교환 여부 및 진행 상태 확인
      3. 진행 상태에 따른 세션키 교환 전문 처리 
    4. Encrypted : 데이터 전문 처리
      1. SVR session key로 복호화
      2. ACK 응답 전문 여부 확인
      3. (POLL전문 처리시) POLL 전문 여부 확인
      4. 전문변환 호출
      5. 전문변환 결과 확인
      6. FEP 헤더 조립
      7. 코어 송신(E2B)
  */

  if( strstr(in, "BokwireEnvelope") != NULL ) {
    ulog(_ERROR_, "[로그정보] Handshake 전문 수신 !!");
    // return CF_ProcessSessionKey(bufkind, ppFrame, pBufLen, pFrameLen, SrcSvc, Srcpidx, callback_name, info1, info2);
    rc = process_session_key(SrcSvc, in, inlen);
    if( rc < 0 ) {
      ulog(_ERROR_, "[로그정보] 세션키 교환 전문 처리 실패 !!");
      return RC_NEXT_ACTION;
    }

    return RC_NEXT_ACTION;
  }

  ulog(_ERROR_, "[로그정보] 업무 전문 수신 !!");
  // return CF_ProcessMessage(bufkind, ppFrame, pBufLen, pFrameLen, SrcSvc, Srcpidx, callback_name, info1, info2);
  rc = process_message(in, inlen);

  if( rc < 0 ) {
    ulog(_ERROR_, "[로그정보] 업무 전문 처리 실패 !! rc(%d)", rc);
    return RC_NEXT_ACTION;
  }

  return RC_NEXT_ACTION;
}
