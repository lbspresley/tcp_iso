#include "tcp_iso.h"

/*
 * Server 세션키 교환 요구(1) 수신
 */
int svr_recv_1(char* msg, int len)
{
  int		rc;
  int		out_len;
  int		msg_len;

  unsigned char*	pMsg = NULL;
  unsigned char*	pSKeyOut = NULL;


  ulog(_FLOW_, "[로그정보] Server 세션키 교환 요구(1) 수신\n%s", msg); 

  /*  Server  */
  rc = INL_Initialize( SERVER_CTX, g_inisafe_conf, NULL );
  if( rc != 0 )
  {
    ulog(_ABEND_, "Server INL_Initialize(%d:%s)", rc, INL_ErrorString(rc) );
    return(-1);
  }

  /* ctx 포인터 변수에 대한 메모리 할당 */
  if( g_server_ctx != NULL ) {
    INL_CtxFree(g_server_ctx);
  }

  rc = INL_New_Ctx( SERVER_CTX, &g_server_ctx );
  if( rc != 0 )
  {
    /* ret 가 0 이면 정상*/
    ulog(_ERROR_, "INL_New_Ctx SERVER Failed. code=%d\n", rc);
    return -2;
  }

  unsigned char* pKey = get_sess_key(msg);
  if(pKey == NULL) {
    ulog(_ERROR_, "[장애정보] 세션키를 찾을 수 없습니다.");
    return -3;
  }


  rc = INL_Handshake_Init( g_server_ctx, pKey, strlen((char*)pKey), &pSKeyOut, &out_len);
  if( rc != 0 )
  {
    ulog(_ERROR_, "INL_Handshake_Init SERVER Failed. errcode=%d msg[%s]"
        , rc, INL_ErrorString(rc));
    if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);
    return -4;
  }	

  ulog(_FLOW_, "[로그정보] MSG 000000002 DATA부\n" 
      "[상세정보] (len:%d)[%s]\n" 
      , strlen((char*)pSKeyOut), pSKeyOut); 


  /* 송신 메시지 : 세션키 교환 요구(2) */
  pMsg = make_sess_key_msg(2, (char*)pSKeyOut);
  msg_len = strlen((char*)pMsg);

  if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);

  /* call rmp action */
  strcpy(g_rmpSvcName, "SVR_SKEY");
  rc = rmp_MessageProc(g_rmpSvcName, 0, pMsg, msg_len, 0, 0 );
  if( rc < 0 ) {
    ulog( _ERROR_, "rmp_MessageProc(%s) Fail. RMP 호출 실패 (rc:%d/len:%d)", g_rmpSvcName, rc, msg_len );
  }

  // set timer
  rdf_setTimer(TIMERID_KEY_SVR, 10000, -1, 0, 0, TF_Key_Timeout);


  return RC_NEXT_ACTION;
}

/*
 * Server 세션키 교환 통보(3) 수신
 */
int svr_recv_3(char* msg, int len)
{
  int rc;

  int		out_len; 
  int		msg_len;    /* tpacall 송신 메시지 길이 */

  long	Info1 = 0;
  long	Info2 = 0;

  unsigned char*	pMsg = NULL;
  unsigned char*	pSKeyOut;


  ulog(_FLOW_, "[로그정보] Server 세션키 교환 통보(3) 수신\n%s", msg);

  unsigned char* pKey = get_sess_key(msg);
  if(pKey == NULL) {
    ulog(_ERROR_, "[장애정보] 세션키를 찾을 수 없습니다.");
    return -1;
  }

  /* 암호화 정보 취득 */
  rc = INL_Handshake_Update(g_server_ctx, pKey, strlen((char*)pKey), &pSKeyOut, &out_len);
  if( rc != 0 ) { 
    ulog(_ERROR_, "[장애정보] INL_Handshake_Update Failed\n" 
        "[상세정보] errcode[%d], msg[%s]" 
        , rc, INL_ErrorString(rc) ); 
    if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);
    return -2; 
  }

  ulog(_FLOW_, "[로그정보] MSG 000000004 DATA부\n" 
      "[상세정보] (len:%d)[%s]\n" 
      , out_len , pSKeyOut); 

  /* 송신 메시지 : 세션키 교환 요구(4)*/
  pMsg = make_sess_key_msg(4, (char*)pSKeyOut);
  msg_len = strlen((char*)pMsg);

  if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);

  /* call rmp action */
  strcpy(g_rmpSvcName, "SVR_SKEY");
  rc = rmp_MessageProc(g_rmpSvcName, 0, pMsg, msg_len, &Info1, &Info2); 
  if(rc < 0) { 
    ulog(_ERROR_, "rmp_MessageProc(%s) Fail. RMP 호출 실패 (rc:%d/len:%d)", g_rmpSvcName, rc, msg_len ); 
    return -3;
  }

  // set timer
  rdf_setTimer(TIMERID_KEY_SVR, 10000, -1, 0, 0, TF_Key_Timeout);

  return RC_NEXT_ACTION;
}


/*
 * Server 세션키 교환 통보(5) 수신
 */
int svr_recv_5(char* msg, int len)
{
  int rc;
  int		out_len; 
  unsigned char*	pSKeyOut;

  ulog(_FLOW_, "[로그정보] Server 세션키 교환 통보(5) 수신\n%s", msg);

  unsigned char* pKey = get_sess_key(msg);
  if(pKey == NULL) {
    ulog(_ERROR_, "[장애정보] 세션키를 찾을 수 없습니다.");
    return -1;
  }

  /* 암호화 정보 취득 */
  rc = INL_Handshake_Final(g_server_ctx, pKey, strlen((char*)pKey), &pSKeyOut, &out_len);
  if( rc != 0 ) { 
    ulog(_ERROR_, "[장애정보] INL_Handshake_Final SERVER Failed\n" 
        "[상세정보] errcode[%d], msg[%s]" 
        , rc, INL_ErrorString(rc) ); 
    if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);
    return -2; 
  }

  if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);

  ulog(_ERROR_, "[로그정보] 세션키 교환 완료 SERVER (BOK->BSBANK)\n" );

  return RC_NEXT_ACTION;
}

void TF_Key_Timeout(int TimerID, int lParam, int rParam)
{
  int isClient = TimerID == TIMERID_KEY_CLI ? 1 : 0;

  if(isClient == 1) {
    ulog(_ERROR_, "CLIENT SESSION-KEY Exchange Timeout. !!!!! ");
  } else {
    ulog(_ERROR_, "SERVER SESSION-KEY Exchange Timeout. !!!!! ");
  }

  // Close all sessions
  close_all_sessions();

  return;
}