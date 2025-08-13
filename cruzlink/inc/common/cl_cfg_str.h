#ifndef __CL_CFG_STR_H__
#define __CL_CFG_STR_H__

#include "common/cl_cfg_svc_mst.h"
#include "common/cl_cfg_ext_tgrm.h"
#include "common/cl_cfg_bed_tgrm.h"
#include "common/cl_cfg_aplist.h"
#include "common/cl_cfg_svc_dsc.h"
#include "common/cl_cfg_ext_ch_info.h"
#include "common/cl_cfg_dt.h"

#include "common/cl_cfg_adm.h"

/*	일괄	*/
#include "common/clm_cfg_svc_mst.h"
#include "common/clm_cfg_fl_ds.h"
#include "common/clm_cfg_fl_svc_dsc.h"
#include "common/clm_cfg_dir_inf.h"

/*	Load되는 Config 갯수 for config check	*/
/*	추가되면 바꿔 줘야 함.					*/
#define DEF_CONFIG_COUNT			(13)

/*	Config Header	*/
typedef struct {
	int	cfg_cnt	;
	int	cfg_size;
} CFG_HD_T, *CFG_HD_P;

/*	Service Master	*/
typedef struct {
	CFG_HD_T		shdr;
	S_CL_CFG_SVCMST	svc_mst[1];
} CFG_SVC_MST;

/*	Ap List */
typedef struct {
	CFG_HD_T		shdr;
	S_CL_CFG_APLIST	aplist[1];
} CFG_AP_LIST;

/*	Ext Tgrm	*/
typedef struct {
	CFG_HD_T				shdr;
	S_CL_CFG_EXTTGRM_CNT	exttgrm[1];
} CFG_EXT_TGRM_CNT;

/*	Bed Tgrm	*/
typedef struct {
	CFG_HD_T			shdr;
	S_CL_CFG_BEDTGRM	bedtgrm[1];
} CFG_BED_TGRM;

/*	Service Dsc	*/
typedef struct {
	CFG_HD_T			shdr;
	S_SVC_DSC_CFG		svc_dsc[1];
} CFG_SVC_DSC;

/*	Ext Chan ID */
typedef struct {
	CFG_HD_T				shdr;
	S_CL_CFG_EXT_CH_INFO	ext_ch_info[1];
} CFG_EXT_CHAN_INFO;

/*  일괄 Service Master */
typedef struct {
	CFG_HD_T          shdr;
	S_CLM_CFG_SVCMST    svc_mst[1];
} CFG_CLM_SVC_MST;

/*  일괄 파일 구분  */
typedef struct {
	CFG_HD_T          shdr;
	S_CLM_CFG_FL_DS_CNT fl_ds[1];
} CFG_CLM_FL_DS_CNT;

/*  일괄 파일 구분  */
typedef struct {
	CFG_HD_T          shdr;
	S_CLM_CFG_FL_DS		fl_ds[1];
} CFG_CLM_FL_DS;

/*  일괄 파일 Service Dsc   */
typedef struct {
	CFG_HD_T          shdr;
	S_CLM_SVC_DSC_CFG   svc_dsc[1];
} CFG_CLM_SVC_DSC;

/*  영업일 정보 Memory		*/
typedef struct {
	CFG_HD_T		shdr;
	S_CL_CFG_DT		dt_inf[1];
} CFG_CLC_CFG_DT;

/*  디렉토리 정보 Memory		*/
typedef struct {
	CFG_HD_T		shdr;
	S_CL_CFG_DIR	dir_inf[1];
} CFG_CLC_CFG_DIR;

/*  관리전문 정보 Memory		*/
typedef struct {
	CFG_HD_T		 shdr;
	S_CL_CFG_ADM_INF adm_inf[1];
} CFG_CLA_CFG_ADM;

/*	Config Check Msg	*/
typedef struct {
	char	cSvcNm[16];
	char	ClSvcMstYn;		/*	CFG_SVC_MST*        pClSvcMst	*/
	char	ApListYn;		/*	CFG_AP_LIST*        pApList	*/
	char	ExtTgrmCntYn;	/*	CFG_EXT_TGRM_CNT*   pExtTgrmCnt	*/
	char	BedTgrmYn;		/*	CFG_BED_TGRM*       pBedTgrm	*/
	char	SvcDscYn;		/*	CFG_SVC_DSC*        pSvcDsc	*/
	char	ExtChanInfoYn;	/*	CFG_EXT_CHAN_INFO*  pExtChanInfo	*/
	char	ClmSvcMstYn;	/*	CFG_CLM_SVC_MST*    pClmSvcMst	*/
	char	ClmFlDsCntYn;	/*	CFG_CLM_FL_DS_CNT*  pClmFlDsCnt	*/
	char	ClmFlDsYn;		/*	CFG_CLM_FL_DS*      pClmFlDs	*/
	char	ClmSvcDscYn;	/*	CFG_CLM_SVC_DSC*    pClmSvcDsc	*/
	char	DtYn;			/*	CFG_CLC_CFG_DT*     pClmDt	*/
	char	DirYn;			/*	CFG_CLC_CFG_DIR*    pClmDir	*/
	char	AdmYn;			/*	CFG_CLA_CFG_ADM*    pClmAdm	*/
	char	CfgData[1];
} CFG_CHK_MSG;

#endif
