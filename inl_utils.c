#include "tcp_iso.h"

int inl_decrypt(char* in, int inlen, char** out, int* outlen)
{
  static int _decrypt_buf_len = MAX_MSG_LEN;
  static char *_decrypt_buf = (char*)NULL;
  net_ctx* _ctx = (net_ctx*)g_server_ctx;
  unsigned char* _out = (unsigned char*)NULL;
  int _outlen = 0;
  int rc = 0;

  if (g_Encrypt_Flag == 0) {
    ulog(_WARNING_, "[NO-ENCRYPT] ONLY call data (%.10s...) len=%d", in, inlen);
    *out = in;
    *outlen = inlen;
    return 1;
  }


  // alloc initial buffer
  if( _decrypt_buf == NULL ) {
    _decrypt_buf = (char*)malloc(_decrypt_buf_len);
    if( _decrypt_buf == NULL ) {
      ulog(_ERROR_, "Failed to allocate memory for decrypt buffer");
      return -1;
    }
  }

  // decrypt
  rc = INL_Decrypt(_ctx, (unsigned char*)in, inlen, &_out, &_outlen);
  if( rc < 0 ) {
    ulog(_ERROR_, "Failed to decrypt message");
    if( _out != NULL ) { INL_Free_Buf(_out); }
    return -2;
  }

  if( _outlen > _decrypt_buf_len ) {
    _decrypt_buf_len = _outlen;
    _decrypt_buf = (char*)realloc(_decrypt_buf, _decrypt_buf_len);
    if( _decrypt_buf == NULL ) {
      ulog(_ERROR_, "Failed to reallocate memory for decrypt buffer");
      return -3;
    }
  }

  memcpy(_decrypt_buf, _out, _outlen);
  if( _out != NULL ) { INL_Free_Buf(_out); }
  *out = _decrypt_buf;
  *outlen = _outlen;

  return 0;
}

int inl_encrypt(char* in, int inlen, char** out, int* outlen)
{
  static int _encrypt_buf_len = MAX_MSG_LEN;
  static char *_encrypt_buf = (char*)NULL;
  net_ctx* _ctx = (net_ctx*)g_client_ctx;
  unsigned char* _out = (unsigned char*)NULL;
  int _outlen = 0;
  int rc = 0;

  if (g_Encrypt_Flag == 0) {
    ulog(_WARNING_, "[NO-ENCRYPT] ONLY call data (%.10s...) len=%d", in, inlen);
    *out = in;
    *outlen = inlen;
    return 1;
  }

  // Encrypt 안 할 경우
  if( g_Encrypt_Flag == 0 ) {
    ulog( _WARNING_, "[NO-ENCRYPT] ONLY call data (%.10s...) len=%d", in, inlen );
    return 1;
  }


  // alloc initial buffer
  if( _encrypt_buf == NULL ) {
    _encrypt_buf = (char*)malloc(_encrypt_buf_len);
    if( _encrypt_buf == NULL ) {
      ulog(_ERROR_, "Failed to allocate memory for encrypt buffer");
      return -1;
    }
  }

  // encrypt
  rc = INL_Encrypt(_ctx, (unsigned char*)in, inlen, &_out, &_outlen);
  if( rc < 0 ) {
    ulog(_ERROR_, "Failed to encrypt message");
    if( _out != NULL ) { INL_Free_Buf(_out); }
    return -2;
  }

  if( _outlen > _encrypt_buf_len ) {
    _encrypt_buf_len = _outlen;
    _encrypt_buf = (char*)realloc(_encrypt_buf, _encrypt_buf_len);
    if( _encrypt_buf == NULL ) {
      ulog(_ERROR_, "Failed to reallocate memory for encrypt buffer");
      return -3;
    }
  }

  memcpy(_encrypt_buf, _out, _outlen);
  if( _out != NULL ) { INL_Free_Buf(_out); }
  *out = _encrypt_buf;
  *outlen = _outlen;

  return 0;
}
