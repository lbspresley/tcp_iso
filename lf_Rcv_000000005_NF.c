#include "tcp_bok.h"


int	lf_Rcv_000000005_NF(char* msg, int len)
{
    int rc;
	int             in_len; 
	int             out_len; 

	unsigned char*	pSKeyOut;
	BOK_NF_SKEY_STR*	pSKeyMsg;
	unsigned char 	SKeyIn[4096];
	char			tmpstr[32];


    ulog(_FLOW_, "[로그정보] 세션키 교환 확인 통보(000000005) 수신");

	pSKeyMsg = (BOK_NF_SKEY_STR*)msg;


	/* 암호화 정보 취득 */
	/* 버전정보  랜덤데이터1 */
	memset(tmpstr, 0x00, sizeof(tmpstr)); 
	memcpy(tmpstr, pSKeyMsg->indv_pt_len, 4); 
	in_len =  atoi(tmpstr) - 4; 
	memset(SKeyIn, 0x00, sizeof(SKeyIn) ); 
	memcpy(SKeyIn, &msg[SIZE_BOK_NF_SKEY_STR], in_len);

	rc = INL_Handshake_Final(g_server_ctx, SKeyIn, in_len, &pSKeyOut, &out_len);
	if(rc != 0 )
	{
		ulog(_ERROR_, "[장애정보] INL_FinalHandShake Failed\n" 
					  "[상세정보] errcode[%d], msg=[%s]" 
					, rc,  INL_ErrorString(rc) ); 
		if( pSKeyOut != NULL ) INL_Free_Buf(pSKeyOut);

		return -1; 
	}

	if( pSKeyOut != NULL ) INL_Free_Buf(pSKeyOut);

	ulog(_ERROR_, "[로그정보] 세션키 교환 완료 SERVER (BOK->BSBANK)" );

    return 0;
}

