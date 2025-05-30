#include "tcp_bok.h"

int	lf_Snd_Poll_NF()
{
  int		rc;
  char    c_CurDt4Tm[32];
  int		msg_len = SIZE_BOK_NF_PASSWD_STR;
  BOK_NF_PASSWD_STR PollMsg;
  unsigned char*	pMsg = (unsigned char*)&PollMsg;


  // 20200408 : send to host when NOT use POLL in FEP
  if(g_UsePoll != 1) {
    // Do Nothing in here
    return 0;
  }


  ulog(_FLOW_, "[로그정보] 국고 회선시험 요청(TEJG00013)" );

  memset( pMsg, 0x20, SIZE_BOK_NF_PASSWD_STR );

  /* 거래구분 코드 */
  memcpy(PollMsg.Common.bz_no, "TEJG00013", sizeof(PollMsg.Common.bz_no));

  /* 업무코드 */
  memcpy(PollMsg.Common.apcode, "01", sizeof(PollMsg.Common.apcode));

  /* 거래종류코드 */
  memcpy(PollMsg.Common.bz_kind_cd, "13", sizeof(PollMsg.Common.bz_kind_cd));

  /* 요청/응답 구분       */
  PollMsg.Common.rs_flag = 'Q';            

  /* 송신기관ID */
  memcpy(PollMsg.Common.snd_org_cd, gc_org_cd , 3);

  /* 수신기관ID */
  memcpy(PollMsg.Common.rcv_org_cd, "001" , 3);

  /* 거래일자             */
  memset(c_CurDt4Tm, 0x00, sizeof(c_CurDt4Tm));
  (void) UC_SgetSysDateTime( YYYYMMDDHHMISS, c_CurDt4Tm, NULL, NULL );
  memcpy(PollMsg.Common.bz_date, c_CurDt4Tm, 8+6 );


  /* 처리기관ID */
  memcpy(PollMsg.Common.prc_org_cd, "001" , 3);

  memcpy(PollMsg.Common.prc_res_cd, "0000", sizeof(PollMsg.Common.prc_res_cd));

  /* 코드변환구분         */
  PollMsg.Common.cd_chg_dst = 'Y';         

  /* 사용자ID             */
  int len = strlen(gc_plain_id);
  if( len > 20 ) len = 20;
  memcpy( PollMsg.Common.enc_org_id, gc_plain_id, len );   

  /* 비밀번호             */
  len = strlen(gc_plain_pw);
  if( len > 8 ) len = 8;
  memcpy( PollMsg.Common.enc_org_pwd, gc_plain_pw, len );    

  // (20200410) 자체 polling 표시
  memcpy( PollMsg.Common.filler1, "90", 2 );

  /* 종료표시         */
  PollMsg.end = 'E';

  /* call rmp action */
  rc = rmp_MessageProc( "SNDMSG_PLAIN", 0, pMsg, msg_len, 0, 0 );
  if( rc < 0 )
  {
    ulog( _ERROR_, "Fail to Send POLLING message for SNDMSG_PLAIN. (rc:%d/len:%d)", rc, msg_len );
    return -1;
  }

  return 0;
}

