#ifndef __CL_DEF_H__
#define __CL_DEF_H__

#include "common/cl_cfg_def.h"
#include "common/cl_file_def.h"
#include "common/cl_code.h"
#include "common/cl_def_length.h"

/*******************************************************************************
*	common define
*/
/*	COMMON	------------------------------------------------------------------*/
#define FL __FILE__
#define FF __FUNCTION__
#define LL __LINE__

#define TPERRNO	tperrno

/*	The specified SVC Name	 -------------------------------------------------*/


#define ERR_SVC_NM		"CFR_LOG_ERR"	/*	Error Service			*/
#define MCA_OAP_SVCNM	"CFR_E2B_MST"	/*  개설요청시 호출될 MCA어뎁터명   */
#define MCA_CAP_SVCNM	"CFR_B2E_MST"	/*  취급요청시 호출될 MCA어뎁터명   */
#define MSG_RECOVER_SVC	"CFR_REC_MSG"	/*  거래복구 서비스					*/
#define LOG_MST_SVC		"CFR_LOG_MST"	/*  Log Master Service				*/
#define TIMER_SET_SVC	"CFR_TMR_SET"	/*  Timer Set/Recover Service		*/
#define LOG_DATA_SVC	"CFR_LOG_DATA"	/*  Log Data Service				*/
#define DEAL_CNT_SVC	"CFR_DEAL_STS"	/*  Deal Count Service				*/

#define SIM_SVC_TRT_RCV	"CFR_TST_RCV"	/*  Test simulator recv Service		*/
#define BED_TEST_ADT	"BCBS_TEALR"	/*  백엔드 TEST Adaptor				*/
#define BED_DEV_ADT		"BCBS_DEALR"	/*  백엔드 DEV Adaptor				*/

/*	일괄	*/
#define CFM_B2E_MST_SVC "CFM_B2E_MST"	/*	일괄 B2E Master					*/
#define CFM_E2B_MST_SVC "CFM_E2B_MST"	/*	일괄 E2B Master					*/
#define CFM_LOG_MST_SVC "CFM_LOG_MST"	/*	일괄 로그 마스터				*/
#define CFM_LOG_DATA_SVC "CFM_LOG_DATA"	/*	일괄 로그 데이타				*/
#define CFM_ERR_SVC_NM	"CFM_LOG_ERR"	/*	Error Service			*/

#define DEF_DATE_LEN	8
#define DEF_TIMEMS_LEN	9

/*	ByPass ApCode	*---------------------------------------------------------*/
#define DEF_BYPASS_APCODE	"BYPASS"
#define DEF_FEP_AP_CHANID	"FEP"

/*	Form Define(출력파일명형식내용)		*-------------------------------------*/
#define DEF_FLFOM_BASIC_FILE_NAME	'F' /*	기본파일명			*/
#define DEF_FLFOM_EXT_CHAN_ID		'E' /* 대외채널코드			*/
#define DEF_FLFOM_BED_CHAN_ID		'B' /* 백엔드채널코드		*/
#define DEF_FLFOM_USER_ID			'A' /* 업무상세코드			*/
#define DEF_FLFOM_YYYYMMDD			'Y' /* 거래일자 ( YYYYMMDD )*/
#define DEF_FLFOM_YYMMDD			'P' /* 거래일자 ( YYMMDD )	*/
#define DEF_FLFOM_MMDD				'M' /* 거래일자 ( MMDD )	*/
#define DEF_FLFOM_DD				'D' /* 거래일자 ( DD )		*/
#define DEF_FLFOM_FL_SQNO			'Q' /* 파일일련번호 ( 반드시 길이줘야함. L=xx )	*/
#define DEF_FLFOM_FILE_CNTN			'I' /* 파일 내부 ( 반드시 위치/길이 줘야함. P=xx:L=xx )	*/
#define DEF_FLFOM_DIVIEDC			'&' /* 구분자				*/
#define DEF_FLFOM_VALUES			'=' /* 구분자				*/
#define DEF_FLFOM_POSTION			'P' /* POSITION				*/
#define DEF_FLFOM_LENGTH			'L' /* LENGTH				*/
#define DEF_FLFOM_POSLEN_DIVIED		':' /* 구분자				*/

/*	Define Count	*---------------------------------------------------------*/
#define MAX_CSTT_CNT			(1024)			/*  전문구성필드 최대 갯수  */
#define DEF_MAX_BAT_CNT			(1000)
#define DEF_MAX_STATICS			(10000)
#define DEF_MAX_SNR_WAIT_CNT	(1000)
#define DEF_MAX_ADM_TGRM		(2000)
#define DEF_MAX_SVC_CNT			(512)
#define DEF_MAX_CONST_CNT		(20)			/*	FileForm에서 상수개수 */

/*	Define Get Next Day Mode	*---------------------------------------------*/
#define DEF_GET_NEXT_DAY_NEXT_HALF_BIZ_DT	(0)
#define DEF_GET_NEXT_DAY_NEXT_BIZ_DT		(1)
#define DEF_GET_NEXT_DAY_NEXT_HLY_DT		(2)

#endif
