#ifndef __CL_PROTO_CLCFG_H__
#define __CL_PROTO_CLCFG_H__


/*	File	:	cf_cfg_ap_list.pc	------------------------------------------*/
int cf_MkApListCfg(int);
int cf_GetApList( S_CL_HEADER*
				, S_CL_CFG_APLIST*
				, CFG_AP_LIST* );
int cf_LoadApList( CFG_AP_LIST** );
int cf_clm_GetApList( S_CLM_HEADER*     pHdr
                    , S_CL_CFG_APLIST*  ps_ApList
					, CFG_AP_LIST*      ps_Cfg );

/*	File	:	cf_cfg_bed_tgrm.pc	------------------------------------------*/
int cf_MkBedTgrmCfg(int);
int cf_GetBedTgrmCfg( S_CL_HEADER*
					, S_CL_CFG_BEDTGRM*
					, CFG_BED_TGRM* );
int cf_LoadBedTgrmCfg( CFG_BED_TGRM** );

/*	File	:	cf_cfg_ext_tgrm.pc	------------------------------------------*/
int cf_LoadExtTgrmCfg(char** 
					, int* 
					, char*
					, int
					, P_CL_ERR_FRAME );
int cf_GetExtTgrmCfg( char*
					, int*
					, char* 
					, char* 
					, int
					, CFG_SVC_DSC*
					, CFG_EXT_TGRM_CNT*
					, S_SVC_DSC_CFG*
					, P_CL_ERR_FRAME );

/*	File	:	cf_cfg_ext_tgrm_cnt.pc	-------------------------------------*/
int cf_MkExtTgrmCfgCnt(int);
int cf_GetExtTgrmCfgCnt( char*
						, S_CL_CFG_EXTTGRM_CNT*
						, CFG_EXT_TGRM_CNT* );
int cf_LoadExtTgrmCfgCnt( CFG_EXT_TGRM_CNT** );

/*	File	:	cf_cfg_svc_dsc.p	------------------------------------------*/
int cf_MkSvcDscCfg(int);
int cf_GetSvcDsc( S_CL_HEADER *
				, S_SVC_DSC_CFG*
				, CFG_SVC_DSC* 
				, S_CL_ERR_FRAME* );
int cf_LoadSvcDsc( CFG_SVC_DSC** );

/*	File	:	cf_cfg_svc_mst.pc	------------------------------------------*/
int cf_MkSvcMstCfg(int);
int cf_GetSvcMst( S_CL_HEADER*
				, P_CL_CFG_SVCMST
				, CFG_SVC_MST*
				, S_CL_ERR_FRAME* );
int cf_LoadSvcMst( CFG_SVC_MST** );
void cf_DispSvcMst(S_CL_CFG_SVCMST* pSvcMst);

/*	File	:	cf_cfg_ext_ch_info.pc	--------------------------------------*/
int cf_LoadExtChInfo( CFG_EXT_CHAN_INFO** ppExtChInfo );
int cf_MkExtChInfoCfg(int);
int cf_GetExtChInfo( S_CL_HEADER *pHdr
					, S_CL_CFG_EXT_CH_INFO* ps_ExtChInfo
					, CFG_EXT_CHAN_INFO* ps_Cfg );

/*  File    : cf_cfg_cfm_svc_mst.pc	------------------------------------------*/
int cf_MkClmSvcMstCfg(int);
int cf_GetClmSvcMst( S_CLM_HEADER*  	pHdr
					, P_CLM_CFG_SVCMST  ps_SvcMst
					, CFG_CLM_SVC_MST*  ps_Cfg
					, S_CLM_ERR_MSG*   	pErrMsg );
int cf_LoadClmSvcMst( CFG_CLM_SVC_MST** ppSvcMst );
void cf_DispClmSvcMst(P_CLM_CFG_SVCMST 	pSvcMst);

/*  File    : cf_cfg_clm_fl_ds_cnt.pc	--------------------------------------*/
int cf_MkFlDsCfgCnt(int);
int cf_GetFlDsCfgCnt( S_CLM_HEADER*			pHdr
					, S_CLM_CFG_FL_DS_CNT*	ps_FlDs
					, CFG_CLM_FL_DS_CNT* 	ps_Cfg );
int cf_LoadFlDsCfgCnt( CFG_CLM_FL_DS_CNT** 	ppFlDsCfg );

/*  cf_cfg_clm_fl_ds.pc	------------------------------------------------------*/
int cf_MkClmApDsCfg(int);
int cf_LoadClmApDsCfg(CFG_CLM_FL_DS** ppFlDsCfg
				, int* 				pCnt
				, S_CLM_ERR_MSG*		pErrFrame );
int cf_GetClmFlDsSvcMst( S_CLM_HEADER*      pFrame         /*  Inp Msg     */
                        , char*             pc_ChanID      /*  Inp ChanID  */
                        , CFG_CLM_SVC_MST*  p_ClmSvcMstCfg /*  Loaded      */
                        , CFG_CLM_FL_DS*    p_FlDsCfg      /*  Loaded      */
                        , P_CLM_CFG_SVCMST  pClmSvcMst
                        , S_CLM_ERR_MSG*     pErrFrame );

/*  cf_cfg_clm_svc_dsc.pc	--------------------------------------------------*/
int cf_GetClmSvcDsc( S_CLM_HEADER*          pHdr
					, S_CLM_SVC_DSC_CFG*    ps_ClmSvcDsc
					, CFG_CLM_SVC_DSC*      ps_Cfg
					, S_CLM_ERR_MSG*      p_ErrFrame );
int cf_MkClmSvcDscCfg(int);
int cf_GetClmSvcDsc( S_CLM_HEADER*          pHdr
					, S_CLM_SVC_DSC_CFG*    ps_ClmSvcDsc
					, CFG_CLM_SVC_DSC*      ps_Cfg
					, S_CLM_ERR_MSG*       p_ErrFrame );
int cf_LoadClmSvcDsc( CFG_CLM_SVC_DSC** ppClmSvcDsc );

/*	cf_cfg_biz_dt.pc	------------------------------------------------------*/
int cf_MkBizDtCfg(int);
int cf_LoadBizDt( CFG_CLC_CFG_DT** ppBizDt );
int cf_GetBizDtInf( char*               pDt         /*  ³¯Â¥    */
				,   S_CL_CFG_DT*        ps_BizDt
				,   CFG_CLC_CFG_DT*     ps_Cfg
				,   S_CL_ERR_MSG*       pErrMsg );

/*	cf_cfg_dir.pc	----------------------------------------------------------*/
int cf_MkDirCfg(int);
int cf_LoadDirInf( CFG_CLC_CFG_DIR** ppDirInf );


/*	cf_cfg_adm_inf.pc	------------------------------------------------------*/
int cf_MkAdmCfg(int);
int cf_LoadAdmInf( CFG_CLA_CFG_ADM** ppAdmInf );
int cf_GetAdmInf( S_CL_HEADER*    	  pHdr
                , S_CL_CFG_ADM_INF*   ps_AdmInf
				, CFG_CLA_CFG_ADM*    ps_Cfg
				, S_CL_ERR_MSG*       pErrMsg );

/*	cf_CheckConfig.c	------------------------------------------------------*/
int cf_CheckConfig( char*               pcerrmsg
				,   char*               pcSvcName
				,   CFG_SVC_MST*        pClSvcMst
				,   CFG_AP_LIST*        pApList
				,   CFG_EXT_TGRM_CNT*   pExtTgrmCnt
				,   CFG_BED_TGRM*       pBedTgrm
				,   CFG_SVC_DSC*        pSvcDsc
				,   CFG_EXT_CHAN_INFO*  pExtChanInfo
				,   CFG_CLM_SVC_MST*    pClmSvcMst
				,   CFG_CLM_FL_DS_CNT*  pClmFlDsCnt
				,   CFG_CLM_FL_DS*      pClmFlDs
				,   CFG_CLM_SVC_DSC*    pClmSvcDsc
				,   CFG_CLC_CFG_DT*     pClmDt
				,   CFG_CLC_CFG_DIR*    pClmDir
				,   CFG_CLA_CFG_ADM*    pClmAdm );






#endif

