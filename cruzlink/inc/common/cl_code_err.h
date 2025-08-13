#ifndef __CL_CODE_ERR_H__
#define __CL_CODE_ERR_H__

/*	에러코드	--------------------------------------------------------------*/
/*	S~ 송신 에러	*---------------------------------------------------------*/
#define DEF_ERR_SND_SVC_FAIL				"S001"	/*	Send to dest Service */
#define DEF_ERR_CALL_RECOVER_SVC_FAIL		"S002"	/*	Call Recover Service */
#define DEF_ERR_CALL_LOG_MASTER_SVC_FAIL	"S003"	/*	Call LogMaster Service*/
#define DEF_ERR_CALL_TIMER_SET_SVC_FAIL		"S004"	/*	Call Timer Set Service*/
#define DEF_ERR_CALL_LOG_DATA_SVC_FAIL		"S005"	/*	Call Log Data Service */
#define DEF_ERR_CALL_DEAL_CNT_SVC_FAIL		"S006"	/*	Call DealCount Service*/
#define DEF_ERR_TP_ALLOC_SND_BUF			"S009"	/*	Tp alloc Send Buf	  */
#define DEF_ERR_SND_EX_ADT_FAIL				"S010"	/*	Adaptor send fail	  */

/*	G~ 취득 오류	*---------------------------------------------------------*/
#define DEF_ERR_GET_ORG_TGRM		"G001"		/*	원거래 전문취득 		  */
#define DEF_ERR_GET_APCODE			"G002"		/*	업무구분코드 			  */
#define DEF_ERR_GET_EXT_INFO_CFG	"G003"		/*	대외채널정보 취득 		  */
#define DEF_ERR_BIZ_DT_DSC			"G004"		/*	일자 구분코드 오류		  */
#define DEF_ERR_CORE_HDR_SIZE_LEN	"G005"		/*	Core Header Size 길이 오류*/

/*	'D~' Data 관련 에러	*-----------------------------------------------------*/
#define DEF_ERR_GET_MST_SQNO		"D001"		/*	거래마스터순번 취득		*/
#define DEF_ERR_GET_DATA_SQNO		"D002"		/*	데이타로그순번 취득		*/
#define DEF_ERR_INSERT_ERR_LOG		"D003"		/*	에러로그 Insert 		*/
#define DEF_ERR_UPDATE_LOG_MST		"D004"		/*	거래로그 Update 		*/
#define DEF_ERR_INSERT_TMR_LOG		"D005"		/*	Timer Log Insert 		*/

#define DEF_ERR_ETC_SQNO_OPEN		"D006"		/*	대외계 채번Seq 취득Open	*/
#define DEF_ERR_ETC_SQNO_FETCH		"D007"		/*	대외계 채번Seq 취득Fetch*/
#define DEF_ERR_UPDATE_TMR_LOG		"D008"		/*	Timer Log Update 		*/
#define DEF_ERR_UPDATE_LOG_DATA		"D009"		/*	거래데이타로그 Update 	*/
#define DEF_ERR_INSERT_LOG_DATA		"D010"		/*	데이타로그 Insert 		*/
#define DEF_ERR_CONNECT_ERROR		"D011"		/*	DB Connect 				*/
#define DEF_ERR_GET_TGRM_SQNO		"D012"		/*	전문로그 순번 취득 		*/
#define DEF_ERR_INSERT_IMG_LOG		"D013"		/*	전문로그 Insert 		*/
#define DEF_ERR_MSG_LEN_SHORT		"D014"		/*	데이타길이 헤더보다작음 */
#define DEF_ERR_DUP_CHECK			"D015"		/*	중복 체크 Select 		*/
#define DEF_ERR_INSERT_LOG_MST		"D016"		/*	마스터거래로그 Update 	*/
#define DEF_ERR_CUR_CHK_TIMER_OPEN	"D017"		/*	Timer Cursor Open		*/
#define DEF_ERR_CUR_CHK_TIMER_FETCH	"D018"		/*	Timer Cursor Fetch		*/
#define DEF_ERR_SELECT_DATA_LOG		"D019"		/*	Select Data Log			*/

#define DEF_ERR_CLM_INSERT_LOG_MST	"D020"		/*	일괄 거래로그 Insert 	*/
#define DEF_ERR_CLM_UPDATE_LOG_MST	"D021"		/*	일괄 거래로그 Update 	*/

#define DEF_ERR_INSERT_STATICS		"D022"		/*	Insert statics			*/
#define DEF_ERR_UPDATE_STATICS		"D023"		/*	Update statics			*/
#define DEF_ERR_CUR_STATICS_OPEN	"D024"		/*	Open statics Cursor		*/
#define DEF_ERR_GET_BEFORE_HOUR		"D025"		/*	한시간 전 구하기		*/

#define DEF_ERR_STATICS_HOUR_INSERT	"D026"		/*	INSERT HOUR	STATICS		*/
#define DEF_ERR_STATICS_HOUR_UPDATE	"D027"		/*	UPDATE HOUR STATICS		*/
#define DEF_ERR_STATICS_DATE_INSERT	"D028"		/*	INSERT DATE	STATICS		*/
#define DEF_ERR_STATICS_DATE_UPDATE	"D029"		/*	UPDATE DATE STATICS		*/
#define DEF_ERR_STATICS_MON_INSERT	"D030"		/*	INSERT MON STATICS		*/
#define DEF_ERR_STATICS_MON_UPDATE	"D031"		/*	UPDATE MON STATICS		*/
#define DEF_ERR_STATICS_YEAR_INSERT	"D032"		/*	INSERT YEAR	STATICS		*/
#define DEF_ERR_STATICS_YEAR_UPDATE	"D033"		/*	UPDATE YEAR STATICS		*/

#define DEF_ERR_SNR_WT_TR_INSERT	"D034"		/*	INSERT SNR WT			*/
#define DEF_ERR_SNR_WT_TR_SELECT	"D035"		/*	SELECT SNR WT			*/
#define DEF_ERR_SNR_WT_TR_OPEN		"D036"		/*	CURSOR OPEN SNR WT		*/
#define DEF_ERR_SNR_WT_TR_FETCH		"D037"		/*	CURSOR FETCH SNR WT		*/
#define DEF_ERR_GET_WT_SQNO			"D038"		/*	대기순번Seq 취득		*/

#define DEF_ERR_CUR_STATICS_FETCH	"D039"		/*	Fetch statics Cursor	*/

#define DEF_ERR_INSERT_ADM_TR		"D040"		/*	insert into adm tr		*/
#define DEF_ERR_GET_ADM_RGNO		"D041"		/*	ADM SEQ 취득			*/
#define DEF_ERR_OPEN_RSP_MSG		"D042"		/*	ADM 응답전문 취득		*/
#define DEF_ERR_UPDATE_NET_STS		"D043"		/*	망관리상태갱신			*/
#define DEF_ERR_INSERT_NET_STS		"D044"		/*	망관리상태Insert		*/
#define DEF_ERR_INSERT_NET_STS_TR	"D045"		/*	망관리상태변경내역Insert*/
#define DEF_ERR_OPEN_REQ_MSG		"D042"		/*	ADM 요청전문 취득		*/
#define DEF_ERR_OPEN_ADM_JOB		"D043"		/*	ADM 스케줄 취득OPEN		*/
#define DEF_ERR_FETCH_ADM_JOB		"D044"		/*	ADM 스케줄 취득FETCH	*/
#define DEF_ERR_GET_ERR_SQNO		"D045"		/*	ERR SEQ 취득			*/


/*	F~ File 관련 오류	*-----------------------------------------------------*/
#define DEF_ERR_RS_DSC_NO_DEFINE	"FD01"		/*	요청/응답구분코드 없음	*/
#define DEF_ERR_OPEN_IMG_FILE_LOG	"F002"		/*	전문로그 File Open 		*/
#define DEF_ERR_MAIL_BOX_DATA_FILE_OPEN "F003"  /*  일괄파일 오픈 오류      */
#define DEF_ERR_MAIL_BOX_DATA_FILE_READ "F004"  /*  일괄파일 읽기 오류      */
#define DEF_ERR_MAIL_BOX_GET_FILE_SEQ   "F005"  /*  일괄파일 시퀀스 취득 실패 */
#define DEF_ERR_MAIL_BOX_MK_OUT_FL_NM   "F006"  /*  출력 파일명 생성 실패   */
#define DEF_ERR_RESULT_FILE_OPEN	"F007"		/*	결과파일 OPEN 오류		*/
#define DEF_ERR_DATA_FILE_RENAME	"F008"		/*	DataFile rename 오류	*/
#define DEF_ERR_DATA_FILE_SIZE		"F009"		/*	DataFile 크기 오류		*/

/*	C~ Config 관련 오류	*-----------------------------------------------------*/
#define DEF_ERR_CONFIG_READ_DBYN	"C001"		/*	Config FileRead(DBYN) 	*/
#define DEF_ERR_CONFIG_READ_FILEYN	"C002"		/*	Config FileRead(FILEYN)	*/
#define DEF_ERR_GET_EXT_TGRM_CFG_CNT "C004"		/*	Ext Tgrm Count 취득		*/
#define DEF_ERR_GET_EXT_TGRM_CFG	"C005"		/*	Ext Tgrm 취득			*/
#define DEF_ERR_NOT_DEF_TGRM		"C006"		/*	대상 전문은 미등록		*/
#define DEF_ERR_NOT_SVC_DSC			"C007"		/*	전문 구분오류			*/
#define DEF_ERR_NOT_SVC_MST			"C008"		/*	AP CODe 취득			*/
#define DEF_ERR_NOT_BACKEND_TGRM	"C009"		/*	BackEnd 전문구성취득	*/
#define DEF_ERR_NOT_ADM_INF			"C010"		/*	관리 전문구분취득		*/
#define DEF_ERR_ADM_KDC_DSC			"C011"		/*	관리전문구분 오류		*/

/*	일괄			*---------------------------------------------------------*/
#define DEF_ERR_GET_FILE_DSC_CFG    "C012"      /*  파일 구분 취득          */
#define DEF_ERR_FILE_NOT_SVC_DSC    "C013"      /*  파일 구분 오류          */
#define DEF_ERR_GET_FILE_DSC_CFG_CNT "C014"     /*  파일 구분 Count 취득    */
#define DEF_ERR_NOT_DEF_FILE        "C015"      /*  파일 구분 미등록        */
#define DEF_ERR_DATA_FILE_NOT_FOUND "C016"      /*  데이터파일 없음			*/
#define DEF_ERR_CONFIG_FILE_OPEN	"C017"      /*  파일 오픈오류			*/
#define DEF_ERR_GET_FILE_DS_SIZE	"C018"      /*  파일 구분 사이즈 취득	*/

#define DEF_ERR_WAIT_FILE_CHK_LOOP	"C019"		/*	WAIT FILE Check 		*/
#define DEF_ERR_GET_TPALLOC_SIZE	"C020"		/*	tpalloc size 취득		*/
#define DEF_ERR_LOAD_DATE_INF		"C021"		/*	load date info			*/
#define DEF_ERR_LOAD_DIR_INF		"C022"		/*	load directory			*/

/*	T~ Simulator 관련	*-----------------------------------------------------*/
#define DEF_ERR_TST_SRCH_BIZ_SEQ	"T001"		/*	Search Req Msg 			*/

/*	M~ 전문 에러	*---------------------------------------------------------*/
#define DEF_ERR_TRT_OP_RS_RE		"M001"		/*	취급/개설, 요청/응답구분  */
#define DEF_ERR_MSG_DSC				"M002"		/*	Message 구분			  */
#define DEF_ERR_BAT_PRIMITIVE		"M003"		/*	Batch Primitive           */
#define DEF_ERR_WEB_PRIMITIVE		"M004"		/*	Web Primitive 		 	  */

/*	AP~ AP 오류	*-------------------------------------------------------------*/
#define	DEF_ERR_GET_NXT_DAY_INP_MOD	"A001"		/* Get NextDay 입력모드 없음*/
#define	DEF_ERR_AP_SMS				"A002"		/* SMS 서비스 오류			*/

/*	Batch 오류	*-------------------------------------------------------------*/
#define DEF_ERR_BAT_INF_OPEN		"B001"		/*	Batch Table Open		*/
#define DEF_ERR_BAT_INF_FETCH		"B002"		/*	Batch Table Fetch		*/
#define DEF_ERR_BAT_INF_RESULT		"B003"		/*	Batch result			*/

/*	User Data 설정 오류	*-----------------------------------------------------*/
#define DEF_CLM_SVC_MST_SNR_DT_PRC_CD	"U001"	/*	송수신일자처리코드 Value  */
#define DEF_CLM_DUP_PROC_NOT_PERMIT		"U002"	/*	중복거래 안됨.			  */

/*	Profile 설정 오류	*-----------------------------------------------------*/
#define DEF_ERR_GET_FILE_HOME		"P001"		/*	CL_FILE_HOME 설정 없음	*/

/*	채널 관련 오류	*---------------------------------------------------------*/
#define DEF_ERR_LINE_DISCONNECT		"L001"		/*	회선 끊어짐				*/
#define DEF_ERR_LINE_CONNECT		"L002"		/*	회선 연결됨				*/


/*	ETC~ 기타 에러	*---------------------------------------------------------*/
#define DEF_ERR_SVC_NOT_SET_ETC		"ETC0"		/*	기타에러				*/
#define	DEF_ERR_GET_ERR_FROM_EX		"ETC1"		/*	기관에서 에러코드 수신	*/



/*	추가 에러	*---------------------------------------------------------*/
#define DEF_ERR_SNR_WT_TR_UPDATE	"D046"		/*	UPDATE SNR WT			*/
#define DEF_ERR_SNR_WT_TR_UPD_PRC	"D047"		/*	UPDATE SNR WT to START	*/
#define DEF_ERR_DEAL_MST_UPD_PRC	"D048"		/*	UPDATE Mst log to START	*/

#if 1 /*    mrpeng 20111005: busan bank arrange */

#define DEF_ERR_MAIL_BOX_FTP_PUT	"FPUT"		/*	FTP	PUT					*/
#define DEF_ERR_MAIL_BOX_FTP_GET	"FGET"		/*	FTP GET					*/

#endif


#endif
