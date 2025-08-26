#include "tcp_iso.h"

int lf_SendMessage(char* pFrame)
{
  int		rc;
  char*	out				= (char*) pFrame;
  char*	outbuf = (char *)NULL;
  int outlen = 0;
  int length_offset = 6;

  /*
    Encrypted : 데이터 전문 처리
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

  ulog(_FLOW_, "[로그정보] 업무 전문 송신 !!");

  return 0;
}
