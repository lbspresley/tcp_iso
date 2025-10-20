#ifndef __TCP_BOK_DEF_H__
#define __TCP_BOK_DEF_H__


#if defined(_KSFC_)
#define 	ISO_APCODE 		"OAL2_ISOMSG_I"
#else
#define 	ISO_APCODE 		"ISO_INBOUND_MSG"
#endif
#define 	MAX_READ_SIZE	4096


#define		FRAME_TYPE_REQ		1	// 요청전문
#define		FRAME_TYPE_RSP		2	// 응답전문


#define		TIMERID_KEY_CLI 	1000		/* CLIENT 세션키 교환 응답 TIMERID */
#define		TIMERID_KEY_SVR 	1001		/* SERVER 세션키 교환 응답 TIMERID */
#define		TIMERID_REQ_POLL 	2000		/* Poll 전문 생성을 위한 TIMERID */
#define		TIMERID_REQ_ACK		3000		/* ACK 요청메시지 송신 TIMERID */

#define		SKEY_BZ_DST_CD_001		"000000001"
#define		SKEY_BZ_DST_CD_002		"000000002"
#define		SKEY_BZ_DST_CD_003		"000000003"
#define		SKEY_BZ_DST_CD_004		"000000004"
#define		SKEY_BZ_DST_CD_005		"000000005"
#define		SKEY_TLG_TP				"0000"


#define		SIZE_SKEY_000000001		92
#define		SIZE_SKEY_000000002		1792
#define		SIZE_SKEY_000000003		268
#define		SIZE_SKEY_000000004		108
#define		SIZE_SKEY_000000005		92


//#define		INISAFENET_CONF			"/app/mcx/initech/INISAFE_Net_for_C/conf/INISAFENet_PSB.cnf"


#endif
