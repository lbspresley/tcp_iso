#include "tcp_bok.h"

int	lf_Rcv_PollReq_NF( char* msg, int len )
{
  int		rc;
  int		msg_len = len;


  /* 사용자ID             */
  memcpy( pPollMsg->Common.enc_org_id, gc_plain_id, 20 );   

  /* 비밀번호             */
  memcpy( pPollMsg->Common.enc_org_pwd, gc_plain_id, 8 );    

  /* call rmp action */
  strcpy(g_rmpSvcName, "SNDMSG_PLAIN");
  rc = rmp_MessageProc( g_rmpSvcName, 0, (unsigned char*)pPollMsg, msg_len, 0, 0 );
  if( rc < 0 )
  {
    ulog( _ERROR_, "rmp_MessageProc(%s) Fail. RMP 호출 실패 (rc:%d/len:%d)", g_rmpSvcName, rc, msg_len );
    return -1;
  }

  // Start Poll Timer when BOK sent a test message
  if( g_poll_started == 0 ) {
    g_poll_started = 1;
    (void) TF_SendPollReq_NF( 0, 0, 0 );
    rdf_setTimer( TIMERID_REQ_POLL, g_ReqPollInterval*1000, -1, 0, 0, TF_SendPollReq_NF);
  }

  return 0;
}

int	lf_Rcv_PollRsp_NF( char* msg, int len )
{
  ulog( _ERROR_, "[로그정보] POLL Response Received !!!!!" );

  // 응답대기 Timer Off
  rdf_killTimer( TIMERID_RSP_POLL );

  // On Timer
  // set new polling timer (default : 30 minutes)
  //rdf_setTimer( TIMERID_REQ_POLL, g_ReqPollInterval*1000, -1, 0, 0, TF_SendPollReq_NF);
  ulog( _ERROR_, "[로그정보] Set Timer for POLL Request : %d seconds", g_ReqPollInterval );

  return 0;
}


// Timer callback
void TF_PollTimeout_NF(int TimerID, int lParam, int rParam)
{
  // 응답대기 Timer Off
  rdf_killTimer( TIMERID_RSP_POLL );

  ulog( _ERROR_, "TIMEOUT : Waiting Polling-Response message. !!!!! " );

  // TODO : Re-Polling 
  //(void) TF_SendPollReq_NF(TimerID, lParam, rParam);

  return;
}

void TF_SendPollReq_NF(int TimerID, int lParam, int rParam)
{
  int rc;

  rc = lf_Snd_Poll_NF();
  if( rc < 0 ) {
    ulog( _ERROR_, "Error in Sending Polling message. rc(%d)", rc );
    return;
  }

  // Poll응답 Timer 기동
  rdf_setTimer( TIMERID_RSP_POLL, g_RspPollInterval* 1000, 1, 0, 0, TF_PollTimeout_NF);

  ulog( _ERROR_, "[로그정보] Set Timer for POLL Request : %d seconds", g_RspPollInterval );

  return;
}

