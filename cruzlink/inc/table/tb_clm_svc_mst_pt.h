/******************************************************************************
 화일명     : tb_clm_svc_mst_pt.h
 내용설명   : TB_CLM_SVC_MST pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLM_SVC_MST_PT_H__
#define	__TB_CLM_SVC_MST_PT_H__

int  db_Insert_tb_clm_svc_mst(char *p_tstr);
int  db_Select_tb_clm_svc_mst(char *p_tstr);
int  db_Update_tb_clm_svc_mst(char *p_tstr);
void db_Disp_tb_clm_svc_mst(char *p_tstr);
void db_Init_tb_clm_svc_mst(char *p_tstr);

typedef	struct
{
	varchar clm_ap_code                [ 32+1];	/* NOT_DEF */
	varchar ext_chan_id                [  4+1];	/* NOT_DEF */
	varchar clm_sr_dsc                 [  1+1];	/* NOT_DEF */
	varchar node_no                    [  2+1];	/* NOT_DEF */
	varchar bed_chan_id                [  4+1];	/* NOT_DEF */
	varchar vr_adt_svcnm               [ 16+1];	/* NOT_DEF */
	varchar clm_biz_dtl_get_kndc       [  1+1];	/* NOT_DEF */
	int     clm_biz_dtl_pos                   ;	/* NOT_DEF */
	int     clm_biz_dtl_len                   ;	/* NOT_DEF */
	varchar clm_biz_dtl_cd             [ 32+1];	/* NOT_DEF */
	varchar ext_org_cd                 [ 32+1];	/* NOT_DEF */
	varchar bed_org_cd                 [ 32+1];	/* NOT_DEF */
	varchar snd_dt_get_mthd_cd         [  2+1];	/* NOT_DEF */
	int     snd_dt_pos                        ;	/* NOT_DEF */
	int     snd_dt_len                        ;	/* NOT_DEF */
	varchar snd_dt_fom_cd              [ 16+1];	/* NOT_DEF */
	varchar wk_dt_get_mthd_cd          [  2+1];	/* NOT_DEF */
	int     wk_dt_pos                         ;	/* NOT_DEF */
	int     wk_dt_len                         ;	/* NOT_DEF */
	varchar fl_dup_prc_cd              [  1+1];	/* NOT_DEF */
	varchar fl_sq_get_mthd_cd          [  2+1];	/* NOT_DEF */
	int     fl_sq_get_pos                     ;	/* NOT_DEF */
	int     fl_sq_get_len                     ;	/* NOT_DEF */
	varchar svc_mst_flow_dsc           [ 20+1];	/* NOT_DEF */
	varchar err_svcnm                  [ 16+1];	/* NOT_DEF */
	varchar rsv_err_svcnm              [ 16+1];	/* NOT_DEF */
	varchar rsv_err_prc_dsc            [  2+1];	/* NOT_DEF */
	varchar rsv_prc_hr                 [  6+1];	/* NOT_DEF */
	varchar snr_dt_prc_cd              [  2+1];	/* NOT_DEF */
	varchar use_yn                     [  1+1];	/* NOT_DEF */
	varchar chan_bsn_dept_c            [ 10+1];	/* NOT_DEF */
	varchar otp_bsc_flnm               [ 64+1];	/* NOT_DEF */
	varchar otp_flnm_fom               [ 64+1];	/* NOT_DEF */
	varchar otp_dirnm                  [512+1];	/* NOT_DEF */
	varchar inp_dirnm                  [512+1];	/* NOT_DEF */
	varchar cmpl_dirnm                 [512+1];	/* NOT_DEF */
	varchar use_tool_cmd               [512+1];	/* NOT_DEF */
	varchar ext_org_dirnm              [512+1];	/* NOT_DEF */
	varchar clm_ap_code_nm             [512+1];	/* NOT_DEF */
} TB_CLM_SVC_MST_PT;

#endif
