#include "tcp_bok.h"


int CF_Encrypt(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2)
{
  int rc;

  unsigned char* in = *ppFrame;
  unsigned char* tmpbuf; 

  //BOK_COMMON_STR*     pBokFrame;

  int	inlen = *pFrameLen;
  int	outlen;
  int offset=0;

  // 20200408 : Encrypt 안 할 경우
  if( g_Encrypt_Flag == 0 ) {
    ulog( _WARNING_, "[NOT-ENCRYPT] ONLY call data (%.10s...) len=%d", in, inlen );
    return RC_NEXT_ACTION;
  }

  ulog( _FLOW_, "[로그정보] Encrypt call data (%.10s...) len=%d", in, inlen );

  if( strcmp( gc_BizCode, "BOK" ) == 0 ) {    
    // 0 : BOK     (국고)
    offset = 4;
  } else {
    // 1 : NEW BOK (신한은망)
    BOK_COMMON_STR* pComm = (BOK_COMMON_STR*)in;
    if( pComm->enc_yn == 'Y' ) {
      // 공통부의 ID부터 암호화되어 있음
      offset = 168;
    } else {
      // 개별부 길이(4)제외한 부분 암호화되어 있음
      offset = SIZE_BOK_COMMON_STR + 4;
    }
  }

  if( inlen <= offset ){ 
    ulog( _FLOW_, "No need to Encrypt : inlen(%d), offset(%d)", inlen, offset ); 

    return RC_NEXT_ACTION; 
  }


  rc = INL_Encrypt(g_client_ctx, in+offset, inlen-offset, &tmpbuf, &outlen );
  if( rc != 0 )
  {
    ulog( _ERROR_, "[장애로그] Encrypt error (%d)", rc );
    if( tmpbuf != NULL ) INL_Free_Buf(tmpbuf);
    return RC_NEXT_ACTION;
  }

  ulog(_FLOW_, "in [%.5s]", in);

  if( offset > 0 ) {
    memcpy(g_EncryptBuf, in, offset);
  }
  memcpy(g_EncryptBuf+offset, tmpbuf, outlen);

  ulog(_FLOW_, "g_EncryptBuf [%.5s]", g_EncryptBuf);

  if( tmpbuf != NULL ) INL_Free_Buf(tmpbuf);


  ulog( _FLOW_, "[로그정보] Encrypt Success" );
  if( *pBufLen >= outlen+offset )
  {
    ulog(_FLOW_, "g_EncryptBuf [%.5s]", g_EncryptBuf);
    memcpy( (char*)*ppFrame, g_EncryptBuf, outlen+offset ); 
    *pFrameLen = outlen+offset; 

    /* TODO: check enc_yn */
    //pBokFrame->enc_yn = 'Y';

    return RC_NEXT_ACTION;
  }

  /* 할당되어 들어온 버퍼보다 output 이 큰경우 */
  tmpbuf = malloc(outlen+offset + 1);
  if(tmpbuf == NULL)
  {
    ulog(_ERROR_, "malloc fail.");
    return RC_NEXT_ACTION;
  }

  *pBufLen = outlen+offset + 1;
  *pFrameLen = outlen+offset + 1;

  memcpy(tmpbuf, g_EncryptBuf, outlen+offset);

  if(bufkind == MAX_STATIC_BUF)
  {
    *ppFrame = tmpbuf;
  }
  else
  {
    free(*ppFrame);
    *ppFrame = tmpbuf;
  }

  return RC_NEXT_ACTION;
}




