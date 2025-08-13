#ifndef __CL_PROTO_CLCMN_H__
#define __CL_PROTO_CLCMN_H__


int cf_DefaultCall( S_CL_FRAME*
				,	S_CL_CFG_SVCMST*
				,	char*
				,	int
				,	S_CL_ERR_FRAME* );
int cf_SetErrStr( char* pcMsgDsc
				, char* pcApCode 
				, char* pcRsltCode 
				, char* pcTrtOpDsc 
				, char* pcQADsc 
				, char* pcErrSvcName 
				, char* pcBeChanID 
				, char* pcExChanID 
				, char* pcExSeqNo 
				, char* pcExSysNo 
				, char* pcBeSysNo 
				, char* pcPstTrxNo 
				, char* pcBizHdrTrDsc 
				, char* pcErrMsg
				, S_CL_ERR_FRAME* pErrFrame );

int cf_SetTpMsg( S_CL_FRAME*            pFrame
                ,   S_CL_CFG_SVCMST*    pSvcMst
                ,   int*                piMsgLen
                ,   char**              ppSndBuf
                ,   int*                piAllocSize
                ,   S_CL_ERR_FRAME*     pErrFrame );

/*	cf_GoNextSvc.c	*/
int cf_GoNextSvc( char* pData
                , int iLen
                , S_CL_CFG_APLIST* pS_ApList
                , CFG_AP_LIST* ps_Cfg
                , S_CL_ERR_FRAME* pErrFrame );

/*	cf_ProcLogErr.c	*/
void cf_ProcLogErr( S_CL_ERR_FRAME* pErrFrame
                , S_CL_FRAME*       pFrame
                , S_CL_CFG_SVCMST*  pSvcMst
                , char* pApData
                , int i_ApDataRealLen );

int cf_ChkDupTgrm(  S_CL_HEADER*        pHdr
				,   char* 				pTbl
				,   S_CL_ERR_FRAME*     pErrStr);
int cf_MkExtHdr( S_CL_FRAME*        pFrame
				, int               iMsgLen
				, char*             pApDataBuf
				, S_CL_CFG_SVCMST*  pSvcMst
				, S_CL_ERR_FRAME*   pErrStr );
int cf_GetHdrCompDsc( S_CL_CFG_SVCMST*  pSvcMst
				,   char*               pHdrDsc);
int cf_DispExtHdr( S_CL_HEADER* );

/*	ÀÏ°ý	*-----------------------------------------------------------------*/
int cf_DispClmHdr( S_CLM_HEADER* );

int cf_clm_DefaultCall( S_CLM_HEADER*   pFrame
					,   P_CLM_CFG_SVCMST    pSvcMst
				    ,   char*               pSndBuf
					,   int                 iMsgLen
					,   S_CLM_ERR_MSG*      pErrFrame );
int cf_clm_GoNextSvc( char*             pData
                    , int               iLen
					, CFG_CLC_CFG_DT*   pDtCfg
					, S_CL_CFG_DT*      pDtInf
					, P_CLM_CFG_SVCMST	pSvcMst
					, S_CL_CFG_APLIST*  pS_ApList
					, CFG_AP_LIST*      ps_Cfg
					, S_CLM_ERR_MSG*     pErrFrame );
void cf_clm_ProcLogErr( S_CLM_ERR_MSG* pErrHdr
                    , S_CLM_HEADER* pHdr
					, S_CLM_CFG_SVCMST* pSvcMst );
int cf_MkFlSqNo( P_CLM_CFG_SVCMST	pSvcMst
				, S_CLM_HEADER*		gpFrame
				, char*	
				, S_CLM_ERR_MSG*		gpErrFrame);

int cf_SetFlSq( S_CLM_HEADER*   pHdr
                , S_CLM_ERR_MSG*    pErrMsg );

int cf_MkOutFlNm( P_CLM_CFG_SVCMST  pSvcMst
                , S_CLM_HEADER* pClmHdr
				, S_CLM_ERR_MSG* pErrHdr
				, char* pc_OtpFlNm );
int cf_InsertWt(S_CLM_HEADER*	pHdr
				, P_CLM_CFG_SVCMST	pSvcMst
				, CFG_CLC_CFG_DT*	pDtCfg
				, S_CL_CFG_DT*		pDtInf
				, char*				c_NxtSvc
				, S_CLM_ERR_MSG*	pErrFrame );

int cf_RegFlSndSize( S_CLM_HEADER*  pHdr
                    , int           iSndSize
                    , char*         pcLogYn
                    , S_CLM_ERR_MSG*    pErrMsg );
int cf_FlRename( S_CLM_HEADER*      pClmHdr
	                , S_CLM_ERR_MSG*    pErrHdr );

/*	°øÅë	*-----------------------------------------------------------------*/
int cf_GetNxtDay( int               iMode
                , char*             pSrcDt
				, CFG_CLC_CFG_DT*   pDtCfg
				, char*             pDstDt
				, S_CL_ERR_MSG*     pErrMsg );

int cf_GetCoreHdrSz( char*  pc_CoreLenVar
                    , int   i_Pos
					, int   i_Len
					, int*  pi_Size
					, char* pc_data
					, S_CL_ERR_MSG* pErrHdr );





#endif

