/******************************************************************************
 화일명     : tb_clm_svc_mst_ct.h
 내용설명   : TB_CLM_SVC_MST c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLM_SVC_MST_CT_H__
#define	__TB_CLM_SVC_MST_CT_H__

int  db_Insert_tb_clm_svc_mst(char *p_tstr);
int  db_Select_tb_clm_svc_mst(char *p_tstr);
int  db_Update_tb_clm_svc_mst(char *p_tstr);
void db_Disp_tb_clm_svc_mst(char *p_tstr);
void db_Init_tb_clm_svc_mst(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[ 32+1]; } clm_ap_code;
	struct { unsigned short len; unsigned char arr[  4+1]; } ext_chan_id;
	struct { unsigned short len; unsigned char arr[  1+1]; } clm_sr_dsc;
	struct { unsigned short len; unsigned char arr[  2+1]; } node_no;
	struct { unsigned short len; unsigned char arr[  4+1]; } bed_chan_id;
	struct { unsigned short len; unsigned char arr[ 16+1]; } vr_adt_svcnm;
	struct { unsigned short len; unsigned char arr[  1+1]; } clm_biz_dtl_get_kndc;
	int     clm_biz_dtl_pos;
	int     clm_biz_dtl_len;
	struct { unsigned short len; unsigned char arr[ 32+1]; } clm_biz_dtl_cd;
	struct { unsigned short len; unsigned char arr[ 32+1]; } ext_org_cd;
	struct { unsigned short len; unsigned char arr[ 32+1]; } bed_org_cd;
	struct { unsigned short len; unsigned char arr[  2+1]; } snd_dt_get_mthd_cd;
	int     snd_dt_pos;
	int     snd_dt_len;
	struct { unsigned short len; unsigned char arr[ 16+1]; } snd_dt_fom_cd;
	struct { unsigned short len; unsigned char arr[  2+1]; } wk_dt_get_mthd_cd;
	int     wk_dt_pos;
	int     wk_dt_len;
	struct { unsigned short len; unsigned char arr[  1+1]; } fl_dup_prc_cd;
	struct { unsigned short len; unsigned char arr[  2+1]; } fl_sq_get_mthd_cd;
	int     fl_sq_get_pos;
	int     fl_sq_get_len;
	struct { unsigned short len; unsigned char arr[ 20+1]; } svc_mst_flow_dsc;
	struct { unsigned short len; unsigned char arr[ 16+1]; } err_svcnm;
	struct { unsigned short len; unsigned char arr[ 16+1]; } rsv_err_svcnm;
	struct { unsigned short len; unsigned char arr[  2+1]; } rsv_err_prc_dsc;
	struct { unsigned short len; unsigned char arr[  6+1]; } rsv_prc_hr;
	struct { unsigned short len; unsigned char arr[  2+1]; } snr_dt_prc_cd;
	struct { unsigned short len; unsigned char arr[  1+1]; } use_yn;
	struct { unsigned short len; unsigned char arr[ 10+1]; } chan_bsn_dept_c;
	struct { unsigned short len; unsigned char arr[ 64+1]; } otp_bsc_flnm;
	struct { unsigned short len; unsigned char arr[ 64+1]; } otp_flnm_fom;
	struct { unsigned short len; unsigned char arr[512+1]; } otp_dirnm;
	struct { unsigned short len; unsigned char arr[512+1]; } inp_dirnm;
	struct { unsigned short len; unsigned char arr[512+1]; } cmpl_dirnm;
	struct { unsigned short len; unsigned char arr[512+1]; } use_tool_cmd;
	struct { unsigned short len; unsigned char arr[512+1]; } ext_org_dirnm;
	struct { unsigned short len; unsigned char arr[512+1]; } clm_ap_code_nm;
} TB_CLM_SVC_MST_CT;

#endif
