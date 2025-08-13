#ifndef __CL_FEP_HDR_H__
#define __CL_FEP_HDR_H__

/*------------------------------------------------------------------------------
	대외계 헤더
	전체 : 256 byte -> 320 byte : 업무상세코드 추가
			        -> 384 byte : 전문변환정보 추가
*/

typedef struct {
	char c_Len           [ 6]; /*  0	1. 전체길이
								*			- 대외계헤더길이 + 데이타길이		  */
	char c_MsgDsc        [ 4]; /*  6	2. Msg구분
								*			- EGMG : Engine에서 주는 메시지 
								*	  		( FlowMst에서 siteAP로 줄땐 APMG를 쓴다. )	
								*			- APMG : APSvc에서 주는 메시지 
								*	  		( 엔진서비스를 재사용 위함 )
								*			- RCFG : ReConfig
								*			- ERSK : Skip ErrMsg : 리턴처리 안함.
								*			- ERRT : Return ErrMsg 리턴 처리 함. 
								*			- TMRS : 타이머서비스에서 보냄.
								*	  		( 백엔드로만 리턴함. )
							   */
	char c_ApCode        [32]; /* 10	3. BIZ코드
								*			- 대외계APCode ( CHID_XXXX )          */
	char c_RsltCode      [ 4]; /* 42	4. 결과코드  
								*			- 0000 : 정상                         */
	char c_TrtOpDsc      [ 1]; /* 46	5. 취급/개설 구분  
								*			- 취급 : T / 개설 : O                 */
	char c_QADsc         [ 1]; /* 47	6. 요청/응답구분   
								*			- 요청 : Q / 응답 : A                 */
	char c_RpstApCode    [32]; /* 48	7. 대표BIZ코드     
								*			- 대외계APCode ( CHID_XXXX )의 
								*			  대표BIZ코드						  */
	char c_ApDtlCode     [32]; /* 80	8. 업무상세코드							  */
	char c_BeChanID      [ 4]; /*112	9. BackEnd 채널코드  :                    */
	char c_ExChanID      [ 4]; /*116	10. 대외 채널코드    :                    */
	char c_ExSeqNo       [32]; /*120	11. 대외기관 Seq번호  : 대외거래고유번호  */
	char c_BeSeqNo       [32]; /*152	12. 업무팀   Seq번호  : 업무팀 Seq 번호	  */
	char c_PeerIP        [15]; /*184	13. PeerIP                                */
	char c_PeerPort      [ 5]; /*199	14. PeerPort                              */
	char c_LocalPort     [ 5]; /*204	15. LocalPort                             */
	char c_SessNo        [ 2]; /*209	16. SessNo                                */
	char c_LuName        [ 4]; /*211	17. LU 이름                               */
	char c_LuFlag        [ 1]; /*215	18. LU Flag                               */
	char c_BedSysNo      [ 4]; /*216	19. 백엔드시스템번호					  */
	char c_ExSysNo       [ 2]; /*220	20. 대외계 시스템 번호                    */
	char c_TrDt			 [ 8]; /*222	21. 거래일자							  */
	char c_MstTrxNo      [ 8]; /*230	22. 거래마스터 순번						  */
	char c_PstTrxNo      [ 8]; /*238	23. 현재 Data로그-순번                    */
	char c_RelTrxNo      [ 8]; /*246	24. 상대 Data로그-순번	
								*		- 1. 취급응답시 	
								*			 TimeOut을 삭제 하기 위하여	
								*		- 2. 응답 거래시 	
								*			 실시간 거래내역을 바로 찾기 위하여	
							   */
	char c_ApListIdx     [20]; /*254	25. APList IDX                            */
	char c_SvcPrcSq      [ 5]; /*274	26. APList 순번                           */
	char c_CurHdrTypeCode[ 2]; /*279	27. 현재헤더처리구분코드	
								*		NO : NOTHING ( 대외계 헤더 )
								*		XC : EXT + CORE
								*		XE : EXT + EAI
								*		CX : CORE + EXT
								*		EX : EAI + EXT
								*		CE : EXT + CORE + EAI
								*		EC : EXT + EAI + CORE
								*/
	char c_PstTgrmID	 [30]; /*281	28. 현재 전문 ID						  */
	char c_TgrmSnrDsc	 [ 1]; /*311	29. 전문송수신구분코드					  */
	char c_BedHdrLen	 [ 6]; /*312	30. 벡엔드 헤더 길이					  */
	char c_ExtTgrmLen	 [ 6]; /*318	31. 데이터 전문 길이					  */
	char c_DupYN		 [ 1]; /*324	32. 중복거래 여부						  */
	char c_RelApCode     [32]; /*325	33. 상대대표BIZ코드       				  */
	char c_Filler        [27]; /*357	34. Filler         						  */
} S_CL_HEADER;
#define EXT_HDR_LEN (sizeof(S_CL_HEADER))



/*------------------------------------------------------------------------------
	대외계 헤더 - 일괄 헤더
	전체 : 640 byte
*/

typedef struct {
	char    c_Len       [6  ];  /*  전체길이           :'0*' */
	char    c_MsgDsc    [4  ];  /*  Msg구분	
								*	가상어뎁터로 송신 : DEF_MSG_DSC_REQ_VR_ADT
								*/
	char    c_ApCode    [32 ];  /*  일괄업무코드       : RTrim */
	char    c_ApDtlCode [32 ];  /*  일괄업무상세코드   : RTrim */
	char    c_RsltCode  [4  ];  /*  결과코드            */
	char    c_ExChanID  [4  ];  /*  대외채널코드       : RTrim */
	char    c_BeChanID  [4  ];  /*  백엔드채널코드     : RTrim */
	char    c_SRDsc     [1  ];  /*  송수신구분코드      */
	char    c_ExSysNo   [2  ];  /*  대외계 시스템 번호 :'0*' */
	char    c_TrDt      [8  ];  /*  거래일자            */
	char    c_MstTrxNo  [8  ];  /*  거래마스터 순번     */
	char    c_ApListIdx [20 ];  /*  APList IDX          */
	char    c_SvcPrcSq  [5  ];  /*  APList 순번        :'0*' */
	char    c_FlSq      [4  ];  /*  파일순번   : '0*'   */
	char    c_CmpltHr   [6  ];  /*  완료시각            */
	char    c_CrzFlSz   [10 ];  /*  File Size  : '0*'   */
	char    c_FlNm      [128];  /*  File Name : 반드시RTrim해서넣을것		*/
	char    c_DirNm     [256];  /*  File Directory : 반드시 RTrim 해서 넣을것 */
	char    c_ApGrpID   [32 ];  /*  일괄그룹코드		*/
	char    c_RsvDt     [8  ];  /*  예약일자			*/
	char    c_Rsvno 	[8  ];  /*  예약순번			*/
	char    c_WkDt 		[8  ];  /*  기준일자			*/
	char    c_Filler    [50 ];  /*  필러                */
} S_CLM_HEADER;
#define CLM_HDR_LEN (sizeof(S_CLM_HEADER))

#endif
