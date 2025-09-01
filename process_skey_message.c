#include "tcp_iso.h"

#if 0
int CF_ProcessSessionKey(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2)
#else
int process_session_key( char* SrcSvc, char* in, int inlen)
#endif
{
  int		rc;
  /*
    1. SrcSvc : "CLI" or "SVR"
      1. CLI : session key(CLI)
      2. SVR : session key(SVR)
    2. Plain Text : 세션키 교환 전문 처리
      1. SrcSvc로 세션 종류 확인
      2. 세션키 교환 여부 및 진행 상태 확인
      3. 진행 상태에 따른 세션키 교환 전문 처리 
  */

  int isClientSession = 0;
  if(strcasecmp(SrcSvc, "CLI") == 0) {
    ulog(_ERROR_, "[로그정보] CLI 세션키 교환 전문 수신 !!");
    isClientSession = 1;
  }
  else if(strcasecmp(SrcSvc, "SVR") == 0) {
    ulog(_ERROR_, "[로그정보] SVR 세션키 교환 전문 수신 !!");
  }
  else {
    ulog(_ERROR_, "[로그정보] 세션 종류 확인 실패 !! SrcSvc : %s", SrcSvc);
    return RC_NEXT_ACTION;
  }

  char tr_cd[16];
  memset(tr_cd, 0, sizeof(tr_cd));
  strncpy(tr_cd, (char*)get_tr_cd(in), sizeof(tr_cd));

  if( isClientSession == 1 ) {
    rc = lf_Client_SessionKey(in, inlen, tr_cd);
  }
  else {
    rc = lf_Server_SessionKey(in, inlen, tr_cd);
  }

  if( rc < 0 ) {
    ulog(_ERROR_, "[로그정보] 세션키 교환 전문 처리 실패 !! tr_cd : %s", tr_cd);
    return RC_NEXT_ACTION;
  }

  return RC_NEXT_ACTION;
}

int lf_Client_SessionKey(char* msg, int len, char* tr_cd)
{
  // kill timer
  rdf_killTimer(TIMERID_KEY_CLI);

  if( strcmp(tr_cd, "000000002") == 0 ) {
    return cli_recv_2(msg, len);
  }

  if( strcmp(tr_cd, "000000004") == 0 ) {
    return cli_recv_4(msg, len);
  }

  return 0;
}

int lf_Server_SessionKey(char* msg, int len, char* tr_cd)
{
  if( strcmp(tr_cd, "000000001") == 0 ) {
    return svr_recv_1(msg, len);
  }

  // kill timer
  rdf_killTimer(TIMERID_KEY_SVR);

  if( strcmp(tr_cd, "000000003") == 0 ) {
    return svr_recv_3(msg, len);
  }

  if( strcmp(tr_cd, "000000005") == 0 ) {
    return svr_recv_5(msg, len);
  }

  return 0;
}