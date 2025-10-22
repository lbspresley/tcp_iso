#include "tcp_iso.h"

/*
 * Client 세션키 교환 요구(1) 송신
 */
int cli_send_1(char* PeerIP, char* PeerPort, char* LocalPort)
{
  int		rc;
  int		out_len;
  int		msg_len;

  unsigned char*	pMsg = NULL;
  unsigned char*	pSKeyOut = NULL;

  ulog(_FLOW_, "[로그정보] Client 세션키 교환 요구(1) 송신 준비" 
      "[상세정보] %s->%s:%s"
      , LocalPort, PeerIP, PeerPort); 

  /*  Client  */
  rc = INL_Initialize( CLIENT_CTX, g_inisafe_conf, NULL );
  if( rc != 0 )
  {
    ulog(_ABEND_, "Client INL_Initialize(%d:%s)", rc, INL_ErrorString(rc) );
    return(-1);
  }

  /* ctx 포인터 변수에 대한 메모리 할당 */
  if( g_client_ctx != NULL ) {
    INL_CtxFree(g_client_ctx);
  }

  rc = INL_New_Ctx( CLIENT_CTX, &g_client_ctx );
  if( rc != 0 )
  {
    /* ret 가 0 이면 정상*/
    ulog(_ERROR_, "INL_New_Ctx CLIENT Failed. code=%d\n", rc);
    return -2;
  }

  rc = INL_Handshake_Init( g_client_ctx, NULL, 0, &pSKeyOut, &out_len);
  if( rc != 0 )
  {
    ulog(_ERROR_, "INL_Handshake_Init CLIENT Failed. errcode=%d msg[%s]"
        , rc, INL_ErrorString(rc));
    if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);
    return -3;
  }	

  ulog(_FLOW_, "[로그정보] MSG 000000001 DATA부\n" 
      "[상세정보] (len:%d)[%s]\n" 
      , strlen((char*)pSKeyOut), pSKeyOut); 


  /* 송신 메시지 : 세션키 교환 요구(1) */
  pMsg = make_sess_key_msg(1, (char*)pSKeyOut);
  msg_len = strlen((char*)pMsg);

  if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);

  /* call rmp action */
  strcpy(g_rmpSvcName, "CLI_SKEY");
  rc = rmp_MessageProc(g_rmpSvcName, 0, pMsg, msg_len, 0, 0 );
  if( rc < 0 ) {
    ulog( _ERROR_, "RMP error(%d) Session Key Request(1) len(%d)", rc, g_rmpSvcName, msg_len );
    return -1;
  }

  // set timer
  rdf_setTimer(TIMERID_KEY_CLI, 10000, -1, 0, 0, TF_Key_Timeout);

  return RC_NEXT_ACTION;
}

/*
 * Client 세션키 교환 통보(2) 수신
 */
int cli_recv_2(char* msg, int len)
{
  int rc;

  int		out_len; 
  int		msg_len;    /* tpacall 송신 메시지 길이 */

  long	Info1 = 0;
  long	Info2 = 0;

  unsigned char*	pMsg = NULL;
  unsigned char*	pSKeyOut;

  ulog(_FLOW_, "[로그정보] Client 세션키 교환 통보(2) 수신(%d)\n%s", len, msg);

  unsigned char* pKey = get_sess_key(msg);
  if(pKey == NULL) {
    ulog(_ERROR_, "[장애정보] 세션키를 찾을 수 없습니다.");
    return -2;
  }

  /* 암호화 정보 취득 */
  rc = INL_Handshake_Update(g_client_ctx, pKey, strlen((char*)pKey), &pSKeyOut, &out_len);
  if( rc != 0 ) { 
    ulog(_ERROR_, "[장애정보] INL_Handshake_Update Failed\n" 
        "[상세정보] errcode[%d], msg[%s]" 
        , rc, INL_ErrorString(rc) ); 
    if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);
    return -1; 
  }

  ulog(_FLOW_, "[로그정보] MSG 000000003 DATA부\n" 
      "[상세정보] (len:%d)[%s]\n" 
      , out_len , pSKeyOut); 

  /* 송신 메시지 : 세션키 교환 요구(3)*/
  pMsg = make_sess_key_msg(3, (char*)pSKeyOut);
  msg_len = strlen((char*)pMsg);

  if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);

  /* call rmp action */
  strcpy(g_rmpSvcName, "CLI_SKEY");
  rc = rmp_MessageProc(g_rmpSvcName, 0, pMsg, msg_len, &Info1, &Info2); 
  if(rc < 0) { 
    ulog(_ERROR_, "RMP error(%d) Session Key Request(3) len(%d)", rc, msg_len ); 
    return -1;
  }

  // set timer
  rdf_setTimer(TIMERID_KEY_CLI, 10000, -1, 0, 0, TF_Key_Timeout);

  return 0;
}


/*
 * Client 세션키 교환 통보(4) 수신
 */
int cli_recv_4(char* msg, int len)
{
  int rc;

  int		out_len; 
  int		msg_len;    /* tpacall 송신 메시지 길이 */

  long	Info1 = 0;
  long	Info2 = 0;

  unsigned char*	pMsg = NULL;
  unsigned char*	pSKeyOut;

  ulog(_FLOW_, "[로그정보] Client 세션키 교환 통보(4) 수신(%d)\n%s", len, msg);

  unsigned char* pKey = get_sess_key(msg);
  if(pKey == NULL) {
    ulog(_ERROR_, "[장애정보] 세션키를 찾을 수 없습니다.");
    return -2;
  }

  /* 암호화 정보 취득 */
  rc = INL_Handshake_Final(g_client_ctx, pKey, strlen((char*)pKey), &pSKeyOut, &out_len);
  if( rc != 0 ) { 
    ulog(_ERROR_, "[장애정보] INL_Handshake_Final Failed\n" 
        "[상세정보] errcode[%d], msg[%s]" 
        , rc, INL_ErrorString(rc) ); 
    if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);
    return -1; 
  }

  ulog(_FLOW_, "[로그정보] MSG 000000005 DATA부\n" 
      "[상세정보] (len:%d)[%s]\n" 
      , out_len , pSKeyOut); 

  /* 송신 메시지 : 세션키 교환 요구(5)*/
  pMsg = make_sess_key_msg(5, (char*)pSKeyOut);
  msg_len = strlen((char*)pMsg);

  if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);

  /* call rmp action */
  strcpy(g_rmpSvcName, "CLI_SKEY");
  rc = rmp_MessageProc(g_rmpSvcName, 0, pMsg, msg_len, &Info1, &Info2); 
  if(rc < 0) { 
    ulog(_ERROR_, "RMP error(%d) (CLI)Session Key Request(5) len(%d)", rc, msg_len ); 
    return -1;
  }

  ulog(_ERROR_, "[로그정보] 세션키 교환 완료 CLIENT (Client Session to BOK)\n" );

#if 0 // move to server session completion
  // Start POLL-REQ with Timer
  if (g_UsePoll == 1)
  {
    ulog(_ERROR_, "POLL-REQ Timer Start : %d", g_ReqPollInterval);
    (void) TF_SendPollReq(TIMERID_REQ_POLL, 0, 0);
  } else {
    ulog(_ERROR_, "[POLL-REQ] Not Use Poll-Request");
  }
#endif

  return 0;
}

