#include "tcp_bok.h"


int	lf_Rcv_000000001_NF(char* msg, int len)
{
    int rc;

	BOK_NF_SKEY_STR*	pSKeyMsg;

	char	tmpstr[32];
	long	Info1 = 0;
	long	Info2 = 0;

	/* 암호화 */
	unsigned char	SKeyIn[4096];
	unsigned char*	pMsg = NULL;
	unsigned char*	pSKeyOut = NULL;

	int		in_len;
	int		out_len;
    int		msg_len; 	/* tpacall 송신 메시지 길이 */


	ulog(_FLOW_, "[로그정보] 세션키 교환 요구(000000001) 수신" );

	pSKeyMsg = (BOK_NF_SKEY_STR*)msg;


	/* 암호화 정보 취득 */
	/* 버전정보  랜덤데이터1 */
	memset(tmpstr, 0x00, sizeof(tmpstr));
	memcpy(tmpstr, pSKeyMsg->indv_pt_len, 4);
	in_len =  atoi(tmpstr) - 4;
	memset(SKeyIn, 0x00, sizeof(SKeyIn) );
	memcpy(SKeyIn, &msg[SIZE_BOK_NF_SKEY_STR], in_len); 


    rc = INL_Initialize( SERVER_CTX, g_inisafe_conf, NULL );
    if( rc != 0 )
    {
        ulog(_ABEND_, "Server INL_Initialize(%d:%s)", rc, INL_ErrorString(rc) );
        return(-3);
    }

    /* ctx 포인터 변수에 대한 메모리 할당 */
	if( g_server_ctx != NULL ) {
		INL_CtxFree(g_server_ctx);
	}

    rc = INL_New_Ctx( SERVER_CTX, &g_server_ctx );
    if( rc != 0 )
    {
        /* ret 가 0 이면 정상*/
        ulog(_ERROR_, "INL_New_Ctx CLIENT Failed. code=%d\n", rc);
        return -5;
    }

	rc = INL_Handshake_Init(g_server_ctx, SKeyIn, in_len, &pSKeyOut, &out_len);
	if(rc != 0)
	{
		ulog(_ERROR_, "[장애정보] INL_Handshake_Init Failed\n" 
					  "[상세정보]  errcode[%d], msg[%s]" 
					, rc, INL_ErrorString(rc) );
		if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);
		return -1; 
	}

#ifdef _DEBUG_ 
	ulog(_FLOW_, "[로그정보] MSG 000000002 DATA부\n" 
				 "[상세정보] (len:%d)[%s]\n" 
			   , out_len , pSKeyOut); 
#endif


	/* 공통부 */
	/* 거래구분 코드 */
	memcpy(pSKeyMsg->Common.bz_no, SKEY_BZ_DST_CD_002, sizeof(pSKeyMsg->Common.bz_no));
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
					  "[상세로그] malloc fail!\n" );
		if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);
		return -1; 
	} 

	memset( pMsg, 0x00, msg_len + 1 );
	memcpy( pMsg , pSKeyMsg, SIZE_BOK_NF_SKEY_STR ); 

	/* 버전정보 _ 랜덤데이터1 검증 결과 */
	memcpy( &pMsg[SIZE_BOK_NF_SKEY_STR], pSKeyOut, out_len);

	rc = rmp_MessageProc("SESS_KEY_SVR", 0, pMsg, msg_len, &Info1, &Info2); 
	if(rc < 0) 
	{ 
		ulog(_ERROR_, "[장애정보] rmp_MessageProc 오류 [%d]", rc); 
	}

	if(pMsg != NULL) free(pMsg);  
	if(pSKeyOut != NULL) INL_Free_Buf(pSKeyOut);

    return 0;
}

