#ifndef __CLM_CFG_SVC_MST_H__
#define __CLM_CFG_SVC_MST_H__

/*  일괄 업무정보 (SVC_MASTER)가
*   DB와 Config File을 같이 쓰기 위해서 Config 정의를 한다. */
typedef struct  {
	char	clm_svc_mst_dsc		[32+1];
	char	clm_ap_code			[32+1];
	char	node_no				[2+1];
	char	ext_chan_id			[4+1];
	char	bed_chan_id			[4+1];
	char	clm_sr_dsc			[1+1];
	char	vr_adt_svcnm		[16+1];
	char	clm_biz_dtl_get_kndc[1+1];
	int		clm_biz_dtl_pos		;
	int		clm_biz_dtl_len		;
	char	clm_biz_dtl_cd		[32+1];
	char	snd_dt_get_mthd_cd	[2+1];
	int		snd_dt_pos			;
	int		snd_dt_len			;
	char	snd_dt_fom_cd		[16+1];
	char	wk_dt_get_mthd_cd	[2+1];
	int		wk_dt_pos			;
	int		wk_dt_len			;
	char	ext_org_cd			[32+1];
	char	bed_org_cd			[32+1];
	char	fl_dup_prc_cd		[1+1];
	char	fl_sq_get_mthd_cd	[2+1];
	int		fl_sq_get_pos		;
	int		fl_sq_get_len		;
	char	svc_mst_flow_dsc	[20+1];
	char	err_svcnm			[16+1];
	char	rsv_err_svcnm		[16+1];
	char	rsv_err_prc_dsc		[2+1];
	char	rsv_prc_hr			[6+1];
	char	snr_dt_prc_cd		[2+1];
	char	use_yn				[1+1];
	char	chan_bsn_dept_c		[6+1];
	char	otp_bsc_flnm		[64+1];
	char	otp_flnm_fom		[64+1];
	char	otp_dirnm			[512+1];
	char	inp_dirnm			[512+1];
	char	cmpl_dirnm			[512+1];
	char	use_tool_cmd		[512+1];
	char	ext_org_dirnm		[512+1];
	char	clm_ap_code_nm		[512+1];
} S_CLM_CFG_SVCMST, *P_CLM_CFG_SVCMST;
#define CLM_CFG_SVCMST_LEN (sizeof(S_CLM_CFG_SVCMST))

#endif
