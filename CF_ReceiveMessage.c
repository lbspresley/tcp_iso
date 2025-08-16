#include "tcp_iso.h"
int CF_ProcessSessionKey(int bufkind, unsigned char** ppFrame, int* pBufLen, int* pFrameLen, char SrcSvc[64],int SrcPidx, char* callback_name, long* info1, long* info2);
int CF_ProcessMessage(int bufkind, unsigned char** ppFrame, int* pBufLen, int* pFrameLen, char SrcSvc[64],int SrcPidx, char* callback_name, long* info1, long* info2);

int CF_ReceiveMessage(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int SrcPidx,
    char* callback_name,
    long* info1, long* info2)
{
  int		rc;
  char*	in				= (char*) *ppFrame;

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
    ulog(_ERROR_, "[%s] Receive Handshake Message", SrcSvc);
    return CF_ProcessSessionKey(bufkind, ppFrame, pBufLen, pFrameLen, SrcSvc, SrcPidx, callback_name, info1, info2);
  }

  ulog(_ERROR_, "[%s] Receive Encrypted Message", SrcSvc);
  return CF_ProcessMessage(bufkind, ppFrame, pBufLen, pFrameLen, SrcSvc, SrcPidx, callback_name, info1, info2);
}
