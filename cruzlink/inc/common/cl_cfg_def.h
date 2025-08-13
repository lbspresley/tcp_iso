#ifndef __CL_CFG_DEF_H__
#define __CL_CFG_DEF_H__

/*	Config	------------------------------------------------------------------*/
#define CL_CFG_DIR			"%s/cfg/%s.ini"
#define CL_BIZ_CFG_FILE		"%s/.bizdata/%s"

#if 1 /*	20101103 : mrpeng add loaded config checking	*/

#define CL_BIZ_CFG_CHK_FILE		"%s/.bizdata/%s.db" 	/*	cfg명.db		*/
#define CL_BIZ_CFG_LOADED_SVC	"%s/.bizdata/%s.%s.svc" /*	cfg명.svc명.svc	*/
#define CL_BIZ_CFG_DIFF			"%s/.bizdata/%s.diff" 	/*	cfg명.diff 		*/

#define CFG_FILE_MAKE		(0)
#define CFG_FILE_CHEK		(1)

#endif

#define COMMON_CFG			"ap_common"
#define GI_ALLOCSZ			"AP_DATA_BUF_ALLOC_SIZE"
#define CORE_HDR_SZ			"SZ_CORE_HDR"
#define EAI_HDR_SZ			"SZ_EAI_HDR"
#define BAT_LOOP_SEC		"BAT_LOOP_SECOND"

#if 0
#define SVC_LIST_CFG		"ap_svc_list"
#endif

#define SVC_LIST_CFG		"svc_list"

/*	공통	*---------------------------------------*/
#define MAX_BIZDT_INF_CNT (365*20)		/*	10 years	*/

/*	실시간	*---------------------------------------*/
#define MAX_SVC_MST_CNT (10000)
#define MAX_SVC_DSC_CNT (10000)
#define MAX_AP_LIST_CNT (10000)
#define MAX_BED_TGRM_CNT (500)
#define MAX_EXT_CHAN_CNT (500)
#define MAX_EXT_TGRM_TYPE_CNT (10000)
#define MAX_ADM_INF_CNT (500)

/*	일괄	*--------------------------------------*/
#define MAX_CFM_SVC_MST_CNT (5000)
#define MAX_FL_DS_TYPE_CNT (1000)
#define MAX_DIR_INF_CNT  (2000)

/*	config file	*------------------------------------------------------------*/
#define DEF_AP_LIST_CFG_FILE    	"cl_cfg_ap_list"
#define DEF_BED_TGRM_CFG_FILE   	"cl_cfg_bed_tgrm"
#define DEF_EXT_TGRM_CFG_CNT_FILE   "cl_cfg_ext_tgrm_cnt"
#define DEF_SVC_DSC_CFG_FILE    	"cl_cfg_svc_dsc"
#define DEF_SVC_MST_CFG_FILE    	"cl_cfg_svc_mst"
#define DEF_EXT_CH_INFO_FILE    	"cl_cfg_ext_ch_info"
#define DEF_BIZDT_INF_FILE			"cl_cfg_dt_inf"
#define DEF_ADM_INF_FILE			"cl_cfg_adm_inf"
#define DEF_EXT_TGRM_CFG_FILE   	"cl_cfg_ext_tgrm" /* 20101102 추가 chkmem*/

/*	일괄	*-------------------------------------*/
#define DEF_CLM_SVC_MST_CFG_FILE    "clm_cfg_svc_mst"
#define DEF_CLM_FL_DS_CFG_FILE      "clm_cfg_fl_ds"
#define DEF_CLM_SVC_DSC_CFG_FILE    "clm_cfg_svc_dsc"
#define DEF_CLM_DIR_CFG_FILE		"clm_cfg_dir_inf"

#endif
