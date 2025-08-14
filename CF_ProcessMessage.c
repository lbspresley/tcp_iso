#include "tcp_iso.h"

int CF_ProcessMessage(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2)
{
  int		rc;
  char*	in				= (char*) *ppFrame;

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
 rc = CF_Decrypt(in, *pFrameLen, *pBufLen);
 if( rc < 0 ) {
  ulog(_ERROR_, "[로그정보] 데이터 전문 복호화 실패 !!");
  return RC_NEXT_ACTION;
 }

  char tr_cd[16];
  memset(tr_cd, 0, sizeof(tr_cd));
  strncpy(tr_cd, (char*)get_tr_cd(in), sizeof(tr_cd));

  return RC_NEXT_ACTION;
}
