#include "tcp_bok.h"


int CF_ImgLogRecv(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2)
{
  int rc;
  char* in = (char*) *ppFrame;
  int	inlen = *pFrameLen;

  char	tmpstr[70];
  memset( tmpstr, 0x00, sizeof(tmpstr));
  sprintf(tmpstr, "%s-Recv", g_ServiceName );

  ulog(_FLOW_, "[로그정보] 수신 Image Log Call 준비 !!");

  if( gc_LogYn[0] == DEF_YES )
  {
    ulog(_FLOW_, "[로그정보] 수신 Image Log Call !!");
    rc = cf_GoImgLog( g_ServiceName, "R", tmpstr, (char*)in, inlen );
    if (rc < 0) {
      ulog(_ERROR_, "cf_GoImgLog(%s) Fail. 이미지 로그 처리 실패 (rc:%d)", g_ServiceName, rc);
    }
  }

  return RC_NEXT_ACTION;
}
