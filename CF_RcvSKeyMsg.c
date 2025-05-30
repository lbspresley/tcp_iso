#include "tcp_bok.h"


int CF_RcvSKeyMsg(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2)
{
  int		rc;

  BOK_SKEY_STR*			l_pRcv;
  char*	in				= (char*) *ppFrame;


  l_pRcv = (BOK_SKEY_STR*)in;

  ulog(_FLOW_, "[로그정보] 전문ID : [%.9s]", l_pRcv->Common.bz_dst_cd);

  // 20200408 : Encrypt 안 할 경우
  if( g_Encrypt_Flag == 0 ) {
    ulog(_ERROR_, "[로그정보] 암복호화 Flag : OFF ==> Handshake 안함 !!");
    return RC_NEXT_ACTION;
  }

  if( memcmp(l_pRcv->Common.bz_dst_cd, SKEY_BZ_DST_CD_001, 9) == 0 ) 
  {
    rc = lf_Rcv_000000001(in, *pFrameLen);
  }
  else if( memcmp(l_pRcv->Common.bz_dst_cd, SKEY_BZ_DST_CD_002, 9) == 0 ) 
  {
    rc = lf_Rcv_000000002(in, *pFrameLen);
  }
  else if( memcmp(l_pRcv->Common.bz_dst_cd, SKEY_BZ_DST_CD_003, 9) == 0 ) 
  {
    rc = lf_Rcv_000000003(in, *pFrameLen);
  }
  else if( memcmp(l_pRcv->Common.bz_dst_cd, SKEY_BZ_DST_CD_004, 9) == 0 ) 
  {
    rc = lf_Rcv_000000004(in, *pFrameLen);
  }
  else if( memcmp(l_pRcv->Common.bz_dst_cd, SKEY_BZ_DST_CD_005, 9) == 0 ) 
  {
    rc = lf_Rcv_000000005(in, *pFrameLen);
  }


  return RC_NEXT_ACTION;
}

