#include "tcp_bok.h"

int	lf_Rcv_PollReq( char* msg, int len )
{
  int		rc;
  int		msg_len = len;
  BOK_COMMON_STR* pPollMsg = (BOK_COMMON_STR*) msg;;

  ulog(_FLOW_, "신-한은망 회선시험 요청 수신 - 응답 송신 (000000009)" );

  /* 전문송신 Byte 수		*/
  //memset( pPollMsg->snd_len, 0x30, 5 );		
  /* 거래구분 코드		*/
  //memcpy( pPollMsg->bz_dst_cd	,"000000009", 9 );	
  /* System ID			*/
  //memcpy( pPollMsg->sys_id		,"BOK", 3 );	
  /* 전문종별 코드		*/
  memcpy( pPollMsg->tlg_tp		,"0810", 4 );	

  /* 거래일자             */
  //memset(c_CurDt4Tm, 0x00, sizeof(c_CurDt4Tm));
  //(void) UC_SgetSysDateTime( YYYYMMDDHHMISS, c_CurDt4Tm, NULL, NULL );

  /* 영업일자				*/
  //memcpy( pPollMsg->bz_date		, c_CurDt4Tm,   8 );	
  /* STATUS				*/
  //memcpy( pPollMsg->bz_sts		,"0000", 4 );	
  /* 응답코드				*/
  //memcpy( pPollMsg->rsp_cd		,"0000", 4 );	
  /* 전문관리번호			*/
  //memcpy( pPollMsg->tlg_mgm_no	, 0x30, 20 );	
  /* 전문전송시간			*/
  //memcpy( pPollMsg->tlg_snd_tm	, c_CurDt4Tm,   14 );	
  /* 참조번호				*/
  //memcpy( pPollMsg->rfr_no		, 0x30,  20 );	

  /* 송신기관				*/
  //memcpy( pPollMsg->snd_org_cd	, gc_org_cd, 4 );	
  memcpy( pPollMsg->snd_org_cd	, pPollMsg->rcv_org_cd, 4 );	

  /* 수신기관				*/
  memcpy( pPollMsg->rcv_org_cd	, gc_bok_cd, 4 );	

  /* 암호화 여부			*/	
  pPollMsg->enc_yn = 'Y';	

  /* 전송횟수				*/
  //memcpy( pPollMsg->snd_nft		,"000", 3 );	
  /* 공란					*/
  //memset( pPollMsg->filler		,0x20,  65 );	

  /* 참가기관 ID			*/
  memcpy( pPollMsg->enc_org_id	, gc_plain_id, 16 );	
  /* 참가기관 비밀번호	*/
  memcpy( pPollMsg->enc_org_pwd	, gc_plain_pw, 16 );	


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

    (void) TF_SendPollReq( 0, 0, 0 );
    rdf_setTimer( TIMERID_REQ_POLL, g_ReqPollInterval*1000, -1, 0, 0, TF_SendPollReq);
  }

  return 0;
}

int	lf_Rcv_PollRsp( char* msg, int len )
{
  ulog( _ERROR_, "[로그정보] POLL Response Received !!!!!" );

  // 응답대기 Timer Off
  rdf_killTimer( TIMERID_RSP_POLL );

  ulog( _ERROR_, "[로그정보] Set Timer for POLL Request : %d seconds", g_ReqPollInterval );

  return 0;
}


// Timer callback
void TF_PollTimeout(int TimerID, int lParam, int rParam)
{
  // 응답대기 Timer Off
  rdf_killTimer( TIMERID_RSP_POLL );

  ulog( _ERROR_, "TIMEOUT : Waiting Polling-Response message. !!!!! " );

  // TODO : Re-Polling 

  return;
}

void TF_SendPollReq(int TimerID, int lParam, int rParam)
{
  int rc;

  rc = lf_Snd_Poll();
  if( rc < 0 ) {
    ulog( _ERROR_, "Error in Sending Polling message. rc(%d)", rc );
    return;
  }

  // Poll응답 Timer 기동
  rdf_setTimer( TIMERID_RSP_POLL, g_RspPollInterval* 1000, 1, 0, 0, TF_PollTimeout);

  ulog( _ERROR_, "[로그정보] Set Timer for POLL Request : %d seconds", g_RspPollInterval );

  return;
}

