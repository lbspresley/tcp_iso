#include "tcp_bok.h"

int	lf_Snd_Poll()
{
  int		rc;
  char    c_CurDt4Tm[32];
  int		msg_len = SIZE_BOK_COMMON_STR;
  BOK_COMMON_STR PollMsg;
  unsigned char*	pMsg = (unsigned char*)&PollMsg;

  // 20200408 : send to host when NOT use POLL in FEP
  if(g_UsePoll != 1) {
    // Do Nothing in here
    return 0;
  }

  ulog(_FLOW_, "[로그정보] 신-한은망 회선시험 요청(000000008)" );

  memset( pMsg, 0x20, SIZE_BOK_COMMON_STR );

  /* 전문송신 Byte 수		*/
  memset( PollMsg.snd_len, 0x30, 5 );		
  /* 거래구분 코드		*/
  memcpy( PollMsg.bz_dst_cd	,"000000008", 9 );	
  /* System ID			*/
  memcpy( PollMsg.sys_id		,"BOK", 3 );	
  /* 전문종별 코드		*/
  memcpy( PollMsg.tlg_tp		,"0800", 4 );	

  /* 거래일자             */
  memset(c_CurDt4Tm, 0x00, sizeof(c_CurDt4Tm));
  (void) UC_SgetSysDateTime( YYYYMMDDHHMISS, c_CurDt4Tm, NULL, NULL );

  /* 영업일자				*/
  memcpy( PollMsg.bz_date		, c_CurDt4Tm,   8 );	
  /* STATUS				*/
  memcpy( PollMsg.bz_sts		,"0000", 4 );	
  /* 응답코드				*/
  memcpy( PollMsg.rsp_cd		,"0000", 4 );	
  /* 전문관리번호			*/
  //memset( PollMsg.tlg_mgm_no	, 0x30, 20 );	

  // 관리번호체계 : 영업일자(8) + 참가기관(4) + 일련번호(8)
  memcpy( PollMsg.tlg_mgm_no      , c_CurDt4Tm, 8 );  // YYYYMMDD
  memcpy( PollMsg.tlg_mgm_no +  8 , gc_org_cd, 4 );
  memcpy( PollMsg.tlg_mgm_no + 12 , "90",      2 );   // polling prefix : 90
  memcpy( PollMsg.tlg_mgm_no + 14 , c_CurDt4Tm+8, 6 ); // hhmmss

  /* 전문전송시간			*/
  memcpy( PollMsg.tlg_snd_tm	, c_CurDt4Tm,   14 );	
  /* 참조번호				*/
  memset( PollMsg.rfr_no		, 0x30,  20 );	
  /* 송신기관				*/
  memcpy( PollMsg.snd_org_cd	, gc_org_cd, 4 );	
  /* 수신기관				*/
  memcpy( PollMsg.rcv_org_cd	, gc_bok_cd, 4 );	
  /* 암호화 여부			*/	
  PollMsg.enc_yn = 'Y';	
  /* 전송횟수				*/
  memcpy( PollMsg.snd_nft		,"000", 3 );	
  /* 공란					*/
  memset( PollMsg.filler		,0x20,  65 );	

  /* 참가기관 ID			*/
  int len = strlen(gc_plain_id);
  if( len > 16 ) len = 16;
  memcpy( PollMsg.enc_org_id	, gc_plain_id, len );	

  /* 참가기관 비밀번호	*/
  len = strlen(gc_plain_pw);
  if( len > 16 ) len = 16;
  memcpy( PollMsg.enc_org_pwd	, gc_plain_pw, len );	

  /* call rmp action */
  strcpy(g_rmpSvcName, "SNDMSG_PLAIN");
  rc = rmp_MessageProc( g_rmpSvcName, 0, pMsg, msg_len, 0, 0 );
  if( rc < 0 )
  {
    ulog( _ERROR_, "rmp_MessageProc(%s) Fail. RMP 호출 실패 (rc:%d/len:%d)", g_rmpSvcName, rc, msg_len );
    return -1;
  }

  return 0;
}

