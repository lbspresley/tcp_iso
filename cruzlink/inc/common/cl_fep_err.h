#ifndef __CL_FEP_ERR_H__
#define __CL_FEP_ERR_H__

#include "common/cl_fep_hdr.h"

/*	실시간	*-----------------------------------------------------------------*/
typedef struct {
    char	c_MsgLen      [6  ]; 
    char	c_MsgDsc      [4  ]; /*	EGMG : Engine에서 주는 메시지 ( FlowMst에서 siteAP로 줄땐 APMG를 쓴다. )
									APMG : APSvc에서 주는 메시지 ( 엔진서비스를 재사용 위함 )
									RCFG : ReConfig
									ERSK : Skip ErrMsg : 리턴처리 안함.
									ERRT : Return ErrMsg 리턴 처리 함. ( 백엔드로만 리턴함. )
								*/
    char	c_FstApCode   [32 ]; /*	대표APCODE ( CHID_XXXX )	*/
    char	c_ApCode      [32 ]; /*	대외계APCode ( CHID_XXXX )	*/
    char	c_RsltCode    [4  ]; /*	에러코드                  	*/
    char	c_TrtOpDsc    [1  ]; /*	취급 : T / 개설 : O       	*/
    char	c_QADsc       [1  ]; /*	요청 : Q / 응답 : A       	*/
    char	c_ErrSvcName  [16 ]; /*	에러발생 서비스명         	*/
    char	c_BeChanID    [4  ]; /*	                          	*/
    char	c_ExChanID    [4  ]; /*	                          	*/
    char	c_BeSeqNo     [32 ]; /*	업무팀Seq내용           	*/
    char	c_ExSeqNo     [32 ]; /*	대외거래고유번호          	*/
    char	c_ExSysNo     [2  ]; /*	                          	*/
    char	c_BeSysNo     [2  ]; /*	                          	*/
    char	c_MstTrxNo    [8  ]; /*	마스터 거래고유번호       	*/
    char	c_PstTrxNo    [8  ]; /*	현재데이터로그번호         	*/
	char	c_BizHdrTrDsc [2  ]; /*	NO : NOTHING ( 없음 )
									CO : CORE
									EA : EAI
									CE : CORE + EAI */
	char	c_BizDtlDsc	  [12 ]; /*	업무상세구분코드 ( 속 : UserID )*/
	char	c_ErrMsg      [1024]; /*								*/
} S_CL_ERR_MSG;
#define CL_ERR_MSG_LEN (sizeof(S_CL_ERR_MSG))


/*	일괄	*-----------------------------------------------------------------*/
typedef struct {
	S_CLM_HEADER		  hdr;	 /*	대외일괄 헤더				*/
    char	c_ErrSvcName  [16 ]; /*	에러발생 서비스명         	*/
	char	c_ErrMsg      [1024];/*	에러내용					*/
} S_CLM_ERR_MSG;
#define SZ_CLM_ERR_MSG	(sizeof(S_CLM_ERR_MSG))


#endif
