#include "tcp_bok.h"

int	lf_Snd_000000001_NF(char* PeerIP, char* PeerPort, char* LocalPort)
{
	int		rc;

	int		out_len;
	int		msg_len;

	unsigned char*	pMsg = NULL;
	unsigned char*	pSKeyOut = NULL;
	BOK_NF_SKEY_STR    SKeyMsg;
	//TGL_RESULT*		pResult = NULL;


	ulog(_FLOW_, "[로그정보] 세션키 교환 요구(000000001) 송신 준비" 
				  "[상세정보] %s->%s:%s"
			   , LocalPort, PeerIP, PeerPort); 

	memset((char*)&SKeyMsg, 0x20, SIZE_BOK_NF_SKEY_STR);

	/* 거래구분 코드 */
	memcpy(SKeyMsg.Common.bz_no, SKEY_BZ_DST_CD_001, sizeof(SKeyMsg.Common.bz_no));

	/* 업무코드 */
	memcpy(SKeyMsg.Common.apcode, "00", sizeof(SKeyMsg.Common.apcode));

	/* 거래종류코드 */
	memcpy(SKeyMsg.Common.bz_kind_cd, "00", sizeof(SKeyMsg.Common.bz_kind_cd));

	memcpy(SKeyMsg.Common.prc_res_cd, "0000", sizeof(SKeyMsg.Common.prc_res_cd));
#if 0
/* LHY 국고망 구조체 ----------------------------------------------*/
typedef struct _bok_nf_common_str_t 
{
	char	snd_len		[4];	/* 전문송신 Byte 수		*/
	char    bz_no       [9];    /* 거래번호             */
	char    apcode      [2];    /* 업무코드             */
	char    bz_kind_cd  [2];    /* 거래종류코드         */
	char    rs_flag;            /* 요청/응답 구분       */
	char    snd_org_cd  [3];    /* 송신기관             */
	char    rcv_org_cd  [3];    /* 수신기관             */
	char    bz_date     [8];    /* 거래일자             */
	char    bz_time     [6];    /* 거래시각             */
	char    tlg_mgm_no  [7];    /* 전문관리번호         */
	char    prc_org_cd  [3];    /* 처리기관코드         */
	char    prc_res_cd  [4];    /* 처리결과코드         */
	char    cd_chg_dst;         /* 코드변환구분         */
	char    filler1     [61];   /* 공란                 */
	char    ent_org_cd  [20];   /* 사용자ID             */
	char    ent_org_pwd [8];    /* 비밀번호             */
} BOK_NF_COMMON_STR;
#define SIZE_BOK_NF_COMMON_STR (sizeof(BOK_NF_COMMON_STR)) 

/* 개시, 회선시험 전문 */
typedef struct _bok_nf_passwd_str_t 
{
	BOK_NF_COMMON_STR  Common;

	char            chg_flag;           /* 변경여부         */
	char            NewID       [20];   /* 변경 ID          */
	char            NewPasswd   [16];   /* 변경 PASSWORD    */
	char            filler2     [292];  /* 공란             */
	char            end;                /* 종료표시         */
} BOK_NF_PASSWD_STR;
#define SIZE_BOK_NF_PASSWD_STR (sizeof(BOK_NF_PASSWD_STR))


/* 세션키 교환 전문 */
typedef struct _bok_nf_skey_str_t 
{
	BOK_NF_COMMON_STR  Common  ;        /* 공통부       */

	char            indv_pt_len [ 4];   /* 개별부 길이  */
	/* 개별부 존재 */
} BOK_NF_SKEY_STR;
#define SIZE_BOK_NF_SKEY_STR (SIZE_BOK_NF_COMMON_STR + 4)

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


	/* 개별부 */ 
	/* 개별부 길이 */
	char tmpstr[32];
	sprintf(tmpstr, "%04d", out_len + 4);
	memcpy(SKeyMsg.indv_pt_len, tmpstr, 4);

	/* 송신 메시지 */
	msg_len = out_len + SIZE_BOK_NF_SKEY_STR;
	pMsg = malloc( msg_len + 1 );
	if( pMsg == NULL)
	{
		ulog(_ERROR_, "[장애로그] 개별부 생성 오류\n"
					  "[상세로그] malloc fail!\n");
		if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);
		return -4;
	}
	memset( pMsg, 0x00, msg_len + 1 );
	memcpy( pMsg , &SKeyMsg, SIZE_BOK_NF_SKEY_STR );
	memcpy( &pMsg[SIZE_BOK_NF_SKEY_STR], pSKeyOut, out_len);


	/* call rmp action */
	rc = rmp_MessageProc( "SESS_KEY", 0, pMsg, msg_len, 0, 0 );
	if( rc < 0 )
	{
		ulog( _ERROR_, "Send Fail. CLIENT HandShake Init Msg. RMP 호출 실패 (rc:%d/len:%d)", rc, out_len );
	}

	if(pMsg != NULL) free(pMsg);
	if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);

	return RC_NEXT_ACTION;
}

