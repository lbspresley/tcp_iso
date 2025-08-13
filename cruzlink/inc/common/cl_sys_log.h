#ifndef __CL_SYS_LOG_H__
#define __CL_SYS_LOG_H__

typedef struct {
    char	c_MsgLen      [6  ]; 
    char	c_MsgDsc      [4  ]; /*	RCFG : ReConfig				*/
    char	c_ApCode      [32 ]; /*	대외계APCode ( CHID_XXXX )	*/
    char	c_TrtOpDsc    [1  ]; /*	취급 : T / 개설 : O       	*/
    char	c_QADsc       [1  ]; /*	요청 : Q / 응답 : A       	*/
    char	c_SRDsc       [1  ]; /*	송신 : S / 수신 : R			*/
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
    char	c_OcuSvcName  [16 ]; /*	발생 서비스명         		*/
	char	c_LogDsc	  [ 2 ]; /*	로그 구분코드 					*/
	char	c_SmsYn		  [ 1 ]; /*	SMS 송신여부					*/
	char	c_OcuMsg      [1024]; /* 로그 메시지					*/
} S_CL_SYS_LOG;
#define CL_SYS_LOG_LEN (sizeof(S_CL_SYS_LOG))


#endif
