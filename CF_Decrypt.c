#include "tcp_iso.h"

int CF_Decrypt(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2)
{
  int rc;
  unsigned char* in = *ppFrame;
  unsigned char* tmpbuf;

  int inlen = *pFrameLen;
  int outlen = 0;
  int offset=0;

  // 20200408 : Encrypt 안 할 경우
  if( g_Encrypt_Flag == 0 ) {
    ulog( _WARNING_, "[NO-ENCRYPT] ONLY call data (%.10s...) len=%d", in, inlen );
    return RC_NEXT_ACTION;
  }

  ulog( _FLOW_, "[로그정보] Decrypt call data (%.10s...) len=%d", in, inlen );

  // ISO : Length 5bytes
  offset = 5;

  if( inlen <= offset ){
    ulog( _FLOW_, "No need to Decrypt : inlen(%d), offset(%d)", inlen, offset );

    return RC_NEXT_ACTION;
  }

  memset(g_DecryptBuf, 0x00, gi_ApDataBufAllocSize);
  rc = INL_Decrypt(g_server_ctx, in+offset, inlen-offset, &tmpbuf, &outlen);
  if( rc != 0 ) {
    ulog( _ERROR_, "[장애로그] Decrypt error (%d)", rc );
    if( tmpbuf != NULL ) INL_Free_Buf( tmpbuf);

    return RC_NEXT_ACTION;
  }

  if( offset > 0 ) {
    memcpy(g_DecryptBuf, in, offset);
  }
  memcpy(g_DecryptBuf+offset, tmpbuf, outlen);

  if( tmpbuf != NULL ) INL_Free_Buf( tmpbuf);

  ulog( _FLOW_, "[로그정보] Decrypt Success" );

#ifdef _DEBUG_
  ulog( _ERROR_, "[로그정보] CHECK SIZE : buffer size(%d) outlen(%d) ", *pBufLen, outlen );
#endif

  if( *pBufLen >= outlen+offset ) {
    memcpy( (char*)*ppFrame, g_DecryptBuf, outlen+offset );
    *pFrameLen = outlen+offset;

    return RC_NEXT_ACTION;
  }
  
  /* 할당되어 들어온 버퍼보다 output 이 큰경우 */
  tmpbuf = malloc(outlen+offset + 1);
  if(tmpbuf == NULL) {
    ulog(_ERROR_, "malloc fail.");
    return RC_NEXT_ACTION;
  }
  *pBufLen = outlen+offset + 1;
  *pFrameLen = outlen+offset + 1;

  memcpy(tmpbuf, g_DecryptBuf, outlen+offset);

  if(bufkind == MAX_STATIC_BUF) {
    *ppFrame = tmpbuf;
  } else {
    free(*ppFrame);
    *ppFrame = tmpbuf;
  }

  return RC_NEXT_ACTION;
}
