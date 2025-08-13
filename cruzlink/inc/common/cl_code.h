#ifndef __CL_CODE_H__
#define __CL_CODE_H__

/*	CODE ---------------------------------------------------------------------*/

/*	에러코드						*-----------------------------------------*/
#include "common/cl_code_err.h"

/*	여부코드						*-----------------------------------------*/
#define DEF_YES					'Y'
#define DEF_NO					'N'

/*	DB LOG 여부						*-----------------------------------------*/
/*	Error Logging은 무조건한다. - DB 없으면 File 사용	*/
#define DEF_DB_LOG_DSC_ALL			'A'		/*	All Logging					*/
#define DEF_DB_LOG_DSC_MASTER		'M'		/*	Only Master Logging			*/
#define DEF_DB_LOG_DSC_NOTHING		'N'		/*	Not Log						*/

/*	서비스 구분코드	( AP_SVC_DSC )	*-----------------------------------------*/
#define DEF_AP_SVC_DSC_ADAPTOR		'V'
#define DEF_AP_SVC_DSC_SVC			'S'
#define DEF_AP_SVC_DSC_END			'E'

/*	취급/개설 구분코드	( TRT_OP_DSC )	*-------------------------------------*/
#define DEF_TRT_OP_DSC_OPN		'O'
#define DEF_TRT_OP_DSC_TRT		'T'

/*	요청/응답 구분코드	( RE_RS_DSC )	*-------------------------------------*/
#define DEF_RE_RS_DSC_REQ		'Q'
#define DEF_RE_RS_DSC_RSP		'A'
#define DEF_RE_RS_DSC_INF		'I'

/*  전문 속성 구분코드 (MsgDsc) 		*-------------------------------------*/
#define DEF_MSG_DSC_APMSG			"APMG"	/*	ApSvc에서 나온 메시지		*/
#define DEF_MSG_DSC_ENGINE			"EGMG"	/*	Engine에서 주는 메시지		*/
#define DEF_MSG_DSC_RECONFIG		"RCFG"	/*	Reconfig					*/
#define DEF_MSG_DSC_UPCHANNEL   	"UPCH"	/*	Adaptor up					*/
#define DEF_MSG_DSC_DOWNCHANNEL 	"DNCH"	/*	Adaptor down				*/
#define DEF_MSG_DSC_BATF			"BATF"	/*	BATCH 작업 					*/
#define DEF_MSG_DSC_WEBF			"WEBF"	/*	WEB에서 관리전문 생성		*/
#define DEF_MSG_DSC_WPNC			"WPNC"	/*	장애등록 요청전문 생성		*/
#define DEF_MSG_DSC_WRCV			"WRCV"	/*	장애회복 요청전문 생성		*/ 
#define DEF_MSG_DSC_NOT_ERRRETURN	"ERSK"	/*	에러처리시 - 리턴안함		*/
#define DEF_MSG_DSC_PRC_ERRRETURN	"ERRT"	/*	에러처리시 - 리턴함			*/
#define DEF_MSG_DSC_TIMER_SVC		"TMRS"
#define DEF_MSG_DSC_PRC_ERR_STOP	"STOP"	/*	에러처리시 - 흐름 멈춤		*/
#define DEF_MSG_DSC_PRC_ERR_LOGGING	"FLOW"	/*	에러처리시 - 데이터흐름과 상관없음	*/
#define DEF_MSG_DSC_REQ_VR_ADT		"VRRQ"	/*	Virtual adaptor로 요청송신	*/
#define DEF_MSG_DSC_ADMIN			"ADMG"	/*	관리전문 스케줄러MSG		*/
#define DEF_MSG_DSC_CHECK_MSG		"MCHK"	/*	load된 memory info			*/
#define DEF_MSG_DSC_RECONN			"RCON"	/*	DB Reconnect				*/

/*	헤더처리구분코드	(HDR_PRC_DSC)	*-------------------------------------*/
#define DEF_HDR_PRC_DSC_EXTHDR		"NO"	/* 대외					*/ 
#define DEF_HDR_PRC_DSC_EXTCORE		"XC"	/* 대외 + CORE			*/
#define DEF_HDR_PRC_DSC_EXTEAI		"XE"	/* 대외 + EAI			*/
#define DEF_HDR_PRC_DSC_EXTCOREEAI	"CE"	/* 대외 + CORE + EAI	*/
#define DEF_HDR_PRC_DSC_EXTEAICORE	"EC"	/* 대외 + EAI  + CORE	*/
#define DEF_HDR_PRC_DSC_COREEXT		"CX"	/* CORE + 대외			*/
#define DEF_HDR_PRC_DSC_EAIEXT		"EX"	/* EAI  + 대외			*/ 

/*	송신실패백엔드헤더구성구분코드	(SND_ERR_HDR_COMP_DSC)	*-----------------*/
#define DEF_SND_ERR_HDR_COMP_DSC_NOTHING	"NO"	/* NOTHING		*/ 
#define DEF_SND_ERR_HDR_COMP_DSC_CORE		"XC"	/* CORE			*/
#define DEF_SND_ERR_HDR_COMP_DSC_EAI		"XE"	/* EAI			*/
#define DEF_SND_ERR_HDR_COMP_DSC_COREEAI	"CE"	/* CORE + EAI	*/
#define DEF_SND_ERR_HDR_COMP_DSC_EAICORE	"EC"	/* EAI  + CORE	*/

/*	에러시현전문헤더정보(ERR_TGRM_HDR_DSC)	*---------------------------------*/
#define DEF_ERR_TGRM_HDR_DSC_NOTHING	"NO"	/* NOTHING		*/ 
#define DEF_ERR_TGRM_HDR_DSC_CORE		"CO"	/* CORE			*/
#define DEF_ERR_TGRM_HDR_DSC_EAI		"EA"	/* EAI			*/
#define DEF_ERR_TGRM_HDR_DSC_COREEAI	"CE"	/* CORE + EAI	*/
#define DEF_ERR_TGRM_HDR_DSC_EAICORE	"EC"	/* EAI  + CORE	*/

/*	타임아웃 처리구분코드	(TO_TR_C)	*-------------------------------------*/
#define DEF_TO_TR_C_NOTHING				'N'	/*	do nothing			*/
#define DEF_TO_TR_C_SMS					'S'	/*	sms	end				*/
#define DEF_TO_TR_C_INFINITY			'I'	/*	Backend infinity	*/
#define DEF_TO_TR_C_LIMIT				'L'	/*	Backend limit		*/
#define DEF_TO_TR_C_EXT_RETRY_LIMIT		'R'	/*	retry to ext limited count	*/
#define DEF_TO_TR_C_EXT_RETRY_INFINITY	'F'	/*	retry to ext infinity		*/
#define DEF_TO_TR_C_FEP_SVC_CALL		'A'	/*	time out시 Fep Ap Svc Call	*/

/*	Seq채번구분코드 (SEQ_REG_DSC)		*-------------------------------------*/
#define DEF_SEQ_REG_DSC_BIZ		'B'
#define DEF_SEQ_REG_DSC_EXT		'E'

/*	전문구성구분코드(TGRM_ASODSC)		*-------------------------------------*/
#define DEF_TGRM_ASODSC_ASCII	'A'
#define DEF_TGRM_ASODSC_BINARY	'B'

/*  송수신구분코드(SR_DSC)  			*-------------------------------------*/
#define DEF_SR_DSC_SEND         'S'
#define DEF_SR_DSC_RECV         'R'

/*  파일 순번 취득 구분코드     		*-------------------------------------*/
#define DEF_FL_SQ_GET_MTHD_FORCE_ONE	"FC"	/*	무조건 1	*/
#define DEF_FL_SQ_GET_MTHD_FILE_NAME	"FN"	/*	FILE 이름 에서 구함	*/
#define DEF_FL_SQ_GET_MTHD_FILE_INSIDE	"FI"	/*	FILE 내에서 구함	*/
#define DEF_FL_SQ_GET_MTHD_PROC_COUNT	"PC"	/*	처리 횟수	*/

/*	업무상세코드 취득 방법				*-------------------------------------*/
#define DEF_CLM_BIZ_DTL_GET_KNDC_FORCE		'F'
#define DEF_CLM_BIZ_DTL_GET_KNDC_FILE_NAME	'N'
#define DEF_CLM_BIZ_DTL_GET_KNDC_FILE_DATA	'I'

/*	영업일 구분코드						*-------------------------------------*/
#define DEF_DT_DSC_BIZ_DT		'B'			/*	영업일		*/
#define DEF_DT_DSC_HALF_DT		'C'			/*	반공휴일	*/
#define DEF_DT_DSC_HOLIDAY_DT	'H'			/*	휴일		*/

/*	배치처리방식 코드					*-------------------------------------*/
#define DEF_BAT_PRC_MTHDC_SVC_CALL		"SC"
#define DEF_BAT_PRC_MTHDC_SYSTEM_CALL	"SY"

/*  송수신일자처리코드		  			*-------------------------------------*/
#define DEF_SNR_DT_PRC_CD_IMMEDIATE     "IM"		/*	즉시처리	*/
#define DEF_SNR_DT_PRC_CD_NEXT_DAY      "ND"		/*	익일처리	*/
#define DEF_SNR_DT_PRC_CD_EVERYDAY      "ED"		/*	매일처리	*/
#define DEF_SNR_DT_PRC_CD_BIZ_DAY       "BD"		/*	영업일처리	*/
#define DEF_SNR_DT_PRC_CD_NEXT_BIZ_DAY  "NB"		/*	익영업일처리	*/

/*	필드유형 코드	*---------------------------------------------------------*/
#define DEF_FILD_TPC_TR_DT				"00"		/*	거래일자필드	*/
#define DEF_FILD_TPC_TR_TM				"01"		/*	거래시각필드	*/
#define DEF_FILD_TPC_TR_SQ				"02"		/*	거래고유번호필드	*/
#define DEF_FILD_TPC_ETC				"03"		/*	일반필드		*/

/*	필드유형속성코드	*-----------------------------------------------------*/
#define	DEF_FILD_KND_YYYYMMDD			"YYYYMMDD"
#define	DEF_FILD_KND_MMDD				"MMDD"
#define	DEF_FILD_KND_YYMMDD				"YYMMDD"
#define	DEF_FILD_KND_HHMISS				"HHMISS"
#define	DEF_FILD_KND_HH24MISS			"HH24MISS"
#define	DEF_FILD_KND_MISS				"MISS"
#define	DEF_FILD_KND_HHMI				"HHMI"
#define	DEF_FILD_KND_HH24MI				"HH24MI"

/*	관리전문종류	*---------------------------------------------------------*/
#define DEF_AMN_TGRM_KDC_OPEN			'O'		/*	개시	*/
#define DEF_AMN_TGRM_KDC_BEFORE_END		'S'		/*	종료예고	*/
#define DEF_AMN_TGRM_KDC_END			'C'		/*	종료	*/
#define DEF_AMN_TGRM_KDC_BROKEN			'B'		/*	장애전문	*/
#define DEF_AMN_TGRM_KDC_RECOVER		'R'		/*	회복전문	*/
#define DEF_AMN_TGRM_KDC_TEST_CALL		'T'		/*	Test CALL	*/

/*	망상태구분코드	*---------------------------------------------------------*/
#define DEF_NET_STS_DSC_NML				"00"	/*	개시		*/
#define DEF_NET_STS_DSC_BROKEN			"BR"	/*	장애		*/
#define DEF_NET_STS_DSC_OPENING			"SI"	/*	개시중		*/
#define DEF_NET_STS_DSC_ENDING			"EI"	/*	종료중		*/
#define DEF_NET_STS_DSC_BEFORE_END		"BF"	/*	종료예고	*/
#define DEF_NET_STS_DSC_END				"ED"	/*	종료		*/

/*	관리전문 송수신일자구분	*-------------------------------------------------*/
#define DEF_SNR_DT_PRC_CD_EVERYDAY		 "ED"	/*	매일				*/
#define DEF_SNR_DT_PRC_CD_ONLY_BIZDAY	 "BD"	/*	영업일만 처리		*/
#define DEF_SNR_DT_PRC_CD_EXCEPT_HOLIDAY "HD"	/*	휴일만 제외처리		*/

/*	관리전문 개시처리유형구분코드	*-----------------------------------------*/
#define DEF_STRT_PRC_TPC_NO_OPEN		'0'		/*	개시처리하지 않음	*/
#define DEF_STRT_PRC_TPC_OPEN_PRC		'1'		/*	개시처리함			*/
#define DEF_STRT_PRC_TPC_FORCE_OPEN		'2'		/*	강제개시처리함			*/

/*	서비스 종류구분코드	*-----------------------------------------------------*/
#define DEF_SVC_KNDC_EXT_REAL			'R'		/*	Adaptor	- 실기관라인	*/
#define DEF_SVC_KNDC_EXT_SIM			'T'		/*	Adaptor	- 시뮬레이터	*/
#define DEF_SVC_KNDC_APSVC				'A'		/*	AP SVC					*/
#define DEF_SVC_KNDC_BATCH				'B'		/*	Batch Service			*/
#define DEF_SVC_KNDC_STS_SVC			'S'		/*	모니터링서비스			*/
#define DEF_SVC_KNDC_TEST_LINE			'V'		/*	백엔드 Adaptor	- TEST	*/
#define DEF_SVC_KNDC_DEV_LINE			'D'		/*	백엔드 Adaptor	- 개발	*/

/*	로그 종류구분코드	*-----------------------------------------------------*/
#define DEF_SYSLOG_NML					"WR"	/*	단순참고				*/
#define DEF_SYSLOG_SVC_DOWN				"SD"	/*	서비스모듈다운			*/
#define DEF_SYSLOG_SVC_UP				"SU"	/*	서비스 업				*/
#define DEF_SYSLOG_CHAN_DOWN			"CD"	/*	채널다운				*/
#define DEF_SYSLOG_CHAN_UP				"CU"	/*	업						*/
#define DEF_SYSLOG_CHAN_ERR				"CE"	/*	장애					*/
#define DEF_SYSLOG_TOME_DOWN			"TD"	/*	tome down				*/
#define DEF_SYSLOG_TOME_UP				"TU"	/*	tome up					*/

/*	요일구분코드	*---------------------------------------------------------*/
#define DEF_DOW_MON 					"MON"	/*	월	*/
#define DEF_DOW_TUE 					"TUE"	/*	화	*/
#define DEF_DOW_WED 					"WED"	/*	수	*/
#define DEF_DOW_THU 					"THU"	/*	목	*/
#define DEF_DOW_FRI 					"FRI"	/*	금	*/
#define DEF_DOW_SAT 					"SAT"	/*	토	*/
#define DEF_DOW_SUN 					"SUN"	/*	일	*/

#define DEF_DOW_KOR_MON 				"월"	/*	월	*/
#define DEF_DOW_KOR_TUE 				"화"	/*	화	*/
#define DEF_DOW_KOR_WED 				"수"	/*	수	*/
#define DEF_DOW_KOR_THU 				"목"	/*	목	*/
#define DEF_DOW_KOR_FRI 				"금"	/*	금	*/
#define DEF_DOW_KOR_SAT 				"토"	/*	토	*/
#define DEF_DOW_KOR_SUN 				"일"	/*	일	*/

/*	배치기동특정일	*---------------------------------------------------------*/
#define DEF_BAT_PRC_ALL					"*"		/*	배치 매 날짜/요일/월	*/
#define DEF_BAT_PRC_DT_LASTDAY			"99"	/*	매월 말일				*/

/*	채널  처리 구분코드(CHAN_PRC_DSC)	*------------------------------------*/
#define DEF_CHAN_PRC_DSC_ONLINE			'R'		/*	온라인(실시간) 채널		*/
#define DEF_CHAN_PRC_DSC_BATCH			'M'		/*	배치 채널				*/

/*	채널  방향 구분코드(CHAN_DIRC_DSC)	*-----------------------------------*/
#define DEF_CHAN_DIRC_DSC_BACK			'B'		/*	백엔드 채널				*/
#define DEF_CHAN_DIRC_DSC_EXT			'E'		/*	대외 채널				*/

#if 1 /*    mrpeng : busan bank arrange */
/*  개행처리 구분코드(NEW_LINE_DSC)     *-----------------------------------*/
#define DEF_NEW_LINE_DSC_NONTRANS       "NO"    /*  No transform			*/
#define DEF_NEW_LINE_DSC_ADD_DOS        "AD"    /*  add 0x0d0x0a            */
#define DEF_NEW_LINE_DSC_ADD_UNIX       "AA"    /*  add 0x0a                */
#define DEF_NEW_LINE_DSC_DELETE_DOS     "DD"    /*  delete 0x0d0x0a         */
#define DEF_NEW_LINE_DSC_DELETE_UNIX    "DA"    /*  delete 0x0a             */
#endif



#endif
