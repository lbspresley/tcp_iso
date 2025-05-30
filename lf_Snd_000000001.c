#include "tcp_bok.h"

//int	lf_Snd_000000001()
int	lf_Snd_000000001(char* PeerIP, char* PeerPort, char* LocalPort)
{
  int rc;
  BOK_SKEY_STR	SKeyMsg;

  char*	pMsg = NULL;
  char	tmpstr[32];
  long	Info1 = 0;
  long	Info2 = 0;

  /* 암호화 */
  unsigned char	*pSKeyOut;
  int		out_len;
  int		msg_len;    /* tpacall 송신 메시지 길이 */


  ulog(_FLOW_, "[로그정보] 세션키 교환 요구(000000001) 송신"
      "[상세정보] %s->%s:%s"
      , LocalPort, PeerIP, PeerPort);

  memset((char*)&SKeyMsg, 0x20, SIZE_BOK_SKEY_STR); 

  /* Network 정보 입력 */
  //memcpy(SKeyMsg.sess_inf.PeerIP, PeerIP, strlen(PeerIP));
  //memcpy(SKeyMsg.sess_inf.PeerPort, PeerPort, strlen(PeerPort));
  //memcpy(SKeyMsg.sess_inf.LocalPort, LocalPort, strlen(LocalPort));


  /* 거래구분 코드 */
  memcpy(SKeyMsg.Common.bz_dst_cd, SKEY_BZ_DST_CD_001, 9);

  /* 전문종별 코드 */
  memcpy(SKeyMsg.Common.tlg_tp, SKEY_TLG_TP, 4); 		

  /* 송신기관ID */                                 
  memcpy(SKeyMsg.Common.snd_org_cd, "1328" , 4); 

  /* 수신기관ID */                                 
  memcpy(SKeyMsg.Common.rcv_org_cd, "1016" , 4); 

#if 1 // additional formatting reset
  /* System ID */
  memcpy(SKeyMsg.Common.sys_id, "BOK", 3); // BOK

  char CurDtTm[32];
  memset( CurDtTm, 0, sizeof(CurDtTm) );
  UC_SgetSysDateTime( YYYYMMDDHHMISSMIS, CurDtTm, NULL, NULL );

  memcpy(SKeyMsg.Common.bz_date, CurDtTm, 8); 	/* 영업일자             */
  memcpy(SKeyMsg.Common.tlg_snd_tm, CurDtTm, 14); /* 전문전송시간         */
  SKeyMsg.Common.enc_yn = 'N'; /* 암호화 여부          */

  // additional formatting reset
  memset(SKeyMsg.Common.bz_sts, 0x30, 4); /* STATUS               */ 
  memset(SKeyMsg.Common.tlg_mgm_no, 0x30, 20); /* 전문관리번호         */
  memset(SKeyMsg.Common.rfr_no, 0x30, 20); /* 참조번호             N */
  memcpy(SKeyMsg.Common.snd_nft, "001", 3); /* 전송횟수             N */

#endif

#if 0
  struct _bok_common_str_t
  {
    char    snd_len     [5];    /* 전문송신 Byte 수     N */
    char    bz_dst_cd   [9];    /* 거래구분 코드        N */
    char    sys_id      [3];    /* System ID            N */
    char    tlg_tp      [4];    /* 전문종별 코드        N */
    char    bz_date     [8];    /* 영업일자             N */
    char    bz_sts      [4];    /* STATUS               N */
    char    rsp_cd      [4];    /* 응답코드             AN */
    char    tlg_mgm_no  [20];   /* 전문관리번호         N */
    char    tlg_snd_tm  [14];   /* 전문전송시간         N */
    char    rfr_no      [20];   /* 참조번호             N */
    char    snd_org_cd  [4];    /* 송신기관             N */
    char    rcv_org_cd  [4];    /* 수신기관             N */
    char    enc_yn          ;   /* 암호화 여부          AN */
    char    snd_nft     [3];    /* 전송횟수             N */
    char    filler      [65];   /* 공란                 AN */
    char    ent_org_cd  [16];   /* 참가기관 ID          AN */
    char    ent_org_pwd [16];   /* 참가기관 비밀번호    AN */
  };
#endif

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

  rc =  INL_Handshake_Init( g_client_ctx, NULL, 0, &pSKeyOut, &out_len);
  if( rc != 0 )
  { /* ret 가 0 이면 정상*/
    ulog(_ERROR_,"INL_Handshake_Init CLIENT Failed. code=%d", rc);
    return -3;
  }

  ulog(_FLOW_, "[로그정보] MSG 000000001 DATA부\n" 
      "[상세정보] (len:%d)[%s]\n"
      , strlen((char*)pSKeyOut), pSKeyOut);

  /* 개별부 */
  /* 개별부 길이 */
  // sprintf(SKeyMsg.indv_pt_len, "%04d", (unsigned short)(out_len + 4));
  sprintf(tmpstr, "%04d", (unsigned short)(out_len + 4));
  memcpy(SKeyMsg.indv_pt_len, tmpstr, 4);

  /* 송신 메시지 */
  msg_len = out_len + SIZE_BOK_SKEY_STR;
  pMsg = malloc( msg_len + 1 );
  if( pMsg == NULL)
  {
    ulog(_ERROR_, "[장애로그] 개별부 생성 오류\n" 
        "[상세로그] malloc fail!" );
    return -4;
  }
  memset( pMsg, 0x00, msg_len + 1 );
  memcpy( pMsg , (char*)&SKeyMsg, SIZE_BOK_SKEY_STR );
  memcpy( &pMsg[SIZE_BOK_SKEY_STR], pSKeyOut, out_len);

  strcpy(g_rmpSvcName, "SESS_KEY");
  rc = rmp_MessageProc(g_rmpSvcName, 0, (unsigned char*)pMsg, msg_len, &Info1, &Info2);
  if(rc < 0)
  {
    ulog(_ERROR_, "rmp_MessageProc(%s) Fail. RMP 호출 실패 (rc:%d/len:%d)", g_rmpSvcName, rc, msg_len );
  }

  if(pMsg != NULL)
  {
    free(pMsg);
  }

  if( pSKeyOut != NULL ) INL_Free_Buf(pSKeyOut);

  return 0;
}
