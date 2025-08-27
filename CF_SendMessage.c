#include "tcp_iso.h"

int lf_SendMessage(char* pFrame)
{
  int		rc;
  char*	out				= (char*) pFrame;
  char*	outbuf = (char *)NULL;
  int outlen = 0;
  int length_offset = 6;

  /*
    Decrypted : 데이터 전문 처리
      1. FEP 헤더 처리
       - IF id 추출
       - 전문 타입 추출
      2. 전문변환 호출
       - struct IF_HEADER
      3. 전문변환 결과 확인
      4. 전문 암호화
      5. 전문 저장
      6. 전문 송신
      7. ACK 응답 타이머 기동
  */

  //1. FEP 헤더 처리
  S_CL_HEADER		*pHdr=(S_CL_HEADER*)pFrame;

  ISO_FEP_HEADER FEP_Header ;
  ISO_FEP_HEADER* pFEPHeader = &FEP_Header;

  memset((char*)pFEPHeader, 0x20, sizeof(ISO_FEP_HEADER));

  char bizmsgidr[30+1];
  char msgtpcd[30+1];
  char bizsvc[30+1];

  memset(bizmsgidr, 0, sizeof(bizmsgidr));
  memset(msgtpcd, 0, sizeof(msgtpcd));
  memset(bizsvc, 0, sizeof(bizsvc));

  memcpy(bizmsgidr, pHdr->c_ExSeqNo, sizeof(pHdr->c_ExSeqNo));
  memcpy(msgtpcd, pHdr->c_RpstApCode, sizeof(pHdr->c_RpstApCode));
  memcpy(bizsvc, pHdr->c_ApCode, sizeof(pHdr->c_ApCode));

  // set ISO_FEP_HEADER
  memcpy(pFEPHeader->command, "REQ", strlen("REQ"));
  memcpy(pFEPHeader->bizmsgidr, bizmsgidr, strlen(pHdr->c_ExSeqNo));
  memcpy(pFEPHeader->msgtpcd, msgtpcd, strlen(pHdr->c_RpstApCode));
  memcpy(pFEPHeader->bizsvc, bizsvc, strlen(pHdr->c_ApCode));

  ulog(_FLOW_, "[로그정보] 업무 전문 송신 !!");

  return 0;
}
