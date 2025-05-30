#include "tcp_bok.h"


int CF_RcvSKeyMsg_NF(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2)
{
  int		rc;

  BOK_NF_SKEY_STR*			l_pRcv;
  char*	in				= (char*) *ppFrame;


  l_pRcv = (BOK_NF_SKEY_STR*)in;

  ulog(_FLOW_, "[로그정보] 전문ID : [%.9s]", l_pRcv->Common.bz_no);

  // 20200408 : Encrypt 안 할 경우
  if( g_Encrypt_Flag == 0 ) {
    ulog(_ERROR_, "[로그정보] 암복호화 Flag : OFF ==> Handshake 안함 !!");
    return RC_NEXT_ACTION;
  }

  if( memcmp(l_pRcv->Common.bz_no, SKEY_BZ_DST_CD_001, 9) == 0 ) 
  {
    rc = lf_Rcv_000000001_NF(in, *pFrameLen);
  }
  else if( memcmp(l_pRcv->Common.bz_no, SKEY_BZ_DST_CD_002, 9) == 0 ) 
  {
    rc = lf_Rcv_000000002_NF(in, *pFrameLen);
  }
  else if( memcmp(l_pRcv->Common.bz_no, SKEY_BZ_DST_CD_003, 9) == 0 ) 
  {
    rc = lf_Rcv_000000003_NF(in, *pFrameLen);
  }
  else if( memcmp(l_pRcv->Common.bz_no, SKEY_BZ_DST_CD_004, 9) == 0 ) 
  {
    rc = lf_Rcv_000000004_NF(in, *pFrameLen);
  }
  else if( memcmp(l_pRcv->Common.bz_no, SKEY_BZ_DST_CD_005, 9) == 0 ) 
  {
    rc = lf_Rcv_000000005_NF(in, *pFrameLen);
  }

  if (rc < 0) {
    ulog(_ERROR_, "RCV_SKEY_NF 전문 처리 실패 (code:%.9s) (rc:%d)", l_pRcv->Common.bz_no, rc);
  }

  return RC_NEXT_ACTION;
}

