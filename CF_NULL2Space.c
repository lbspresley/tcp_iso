#include "tcp_bok.h"


int CF_NULL2Space(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2)
{
  //int rc;
  char* in = (char*) *ppFrame;
  //char* out = (char*) *ppFrame;
  //int	inlen = *pFrameLen;
  //int	outlen = *pFrameLen;


  memset(in+214, 0x20, 34);



  return RC_NEXT_ACTION;
}
