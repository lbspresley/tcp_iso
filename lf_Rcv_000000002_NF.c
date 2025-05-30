#include "tcp_bok.h"


int	lf_Rcv_000000002_NF(char* msg, int len)
{
  int rc;

  int		in_len; 
  int		out_len; 
  int		msg_len;    /* tpacall 송신 메시지 길이 */

  long	Info1 = 0;
  long	Info2 = 0;

  unsigned char*	pMsg = NULL;
  unsigned char*	pSKeyOut;
  BOK_NF_SKEY_STR*	pSKeyMsg;
  unsigned char	SKeyIn[4096];
  char			tmpstr[32];


  ulog(_FLOW_, "[로그정보] 세션키 교환 통보(000000002) 수신");

  pSKeyMsg = (BOK_NF_SKEY_STR*)msg;


  /* 암호화 정보 취득 */
  /* 버전정보  랜덤데이터1 */
  memset(tmpstr, 0x00, sizeof(tmpstr));
  memcpy(tmpstr, pSKeyMsg->indv_pt_len, 4); 
  in_len =  atoi(tmpstr) -4 ;
  memset(SKeyIn, 0x00, sizeof(SKeyIn));
  memcpy(SKeyIn, &msg[SIZE_BOK_NF_SKEY_STR], in_len); 

  rc = INL_Handshake_Update(g_client_ctx, SKeyIn, in_len, &pSKeyOut, &out_len);
  if( rc != 0 )
  { 
    ulog(_ERROR_, "[장애정보] INL_Handshake_Update Failed\n" 
        "[상세정보] errcode[%d], msg[%s]" 
        , rc, INL_ErrorString(rc) ); 
    if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);
    return -1; 
  }

  ulog(_FLOW_, "[로그정보] MSG 000000003 DATA부\n" 
      "[상세정보] (len:%d)[%s]\n" 
      , out_len , pSKeyOut); 


  /* 공통부 */
  /* 거래구분 코드 */
  memcpy(pSKeyMsg->Common.bz_no, SKEY_BZ_DST_CD_003, sizeof(pSKeyMsg->Common.bz_no));
  /* 업무코드 */
  memcpy(pSKeyMsg->Common.apcode, "00", sizeof(pSKeyMsg->Common.apcode));
  /* 거래종류코드 */
  memcpy(pSKeyMsg->Common.bz_kind_cd, "00", sizeof(pSKeyMsg->Common.bz_kind_cd));


  /* 개별부 */
  /* 개별부 길이 */
  memset(tmpstr, 0x00, sizeof(tmpstr)); 
  snprintf(tmpstr, sizeof(tmpstr), "%04d", out_len  + 4);
  memcpy(pSKeyMsg->indv_pt_len, tmpstr, 4);


  /* 송신 메시지 */
  msg_len = out_len + SIZE_BOK_NF_SKEY_STR;
  pMsg = malloc( msg_len +1 );
  if( pMsg == NULL) 
  { 
    ulog(_ERROR_, "[장애로그] 개별부 생성 오류\n" 
        "[상세로그] malloc fail!\n");
    if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);
    return -1; 
  } 

  memset( pMsg, 0x00, msg_len + 1 );
  memcpy( pMsg , pSKeyMsg, SIZE_BOK_NF_SKEY_STR ); 

  /* KEY 교환 메시지 */
  memcpy( &pMsg[SIZE_BOK_NF_SKEY_STR], pSKeyOut, out_len);
  rc = rmp_MessageProc("SESS_KEY", 0, pMsg, msg_len, &Info1, &Info2); 
  if(rc < 0) 
  { 
    ulog(_ERROR_, "[장애정보] rmp_MessageProc 오류 [%d]", rc); 
  }

  if(pMsg != NULL) free(pMsg); 
  if( pSKeyOut != NULL ) INL_Free_Buf(pSKeyOut);

  return 0;
}

