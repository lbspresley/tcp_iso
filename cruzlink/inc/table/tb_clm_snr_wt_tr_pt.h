/******************************************************************************
 화일명     : tb_clm_snr_wt_tr_pt.h
 내용설명   : TB_CLM_SNR_WT_TR pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLM_SNR_WT_TR_PT_H__
#define	__TB_CLM_SNR_WT_TR_PT_H__

int  db_Insert_tb_clm_snr_wt_tr(char *p_tstr);
int  db_Select_tb_clm_snr_wt_tr(char *p_tstr);
int  db_Update_tb_clm_snr_wt_tr(char *p_tstr);
void db_Disp_tb_clm_snr_wt_tr(char *p_tstr);
void db_Init_tb_clm_snr_wt_tr(char *p_tstr);

typedef	struct
{
	varchar snr_dd                     [  2+1];	/* NOT_DEF */
	varchar snr_dt                     [  8+1];	/* NOT_DEF */
	int     snr_wt_sq                         ;	/* NOT_DEF */
	varchar tr_dd                      [  2+1];	/* NOT_DEF */
	varchar tr_dt                      [  8+1];	/* NOT_DEF */
	int     mst_tr_sq                         ;	/* NOT_DEF */
	varchar fl_sq                      [  4+1];	/* NOT_DEF */
	int     snd_cnt                           ;	/* NOT_DEF */
	int     svc_prc_sq                        ;	/* NOT_DEF */
	varchar node_no                    [  2+1];	/* NOT_DEF */
	varchar vr_adt_svcnm               [ 16+1];	/* NOT_DEF */
	varchar clm_ap_code                [ 32+1];	/* NOT_DEF */
	varchar clm_biz_dtl_cd             [ 32+1];	/* NOT_DEF */
	varchar clm_sr_dsc                 [  1+1];	/* NOT_DEF */
	varchar ext_chan_id                [  4+1];	/* NOT_DEF */
	varchar im_prc_yn                  [  1+1];	/* NOT_DEF */
	varchar rsv_prc_hr                 [  6+1];	/* NOT_DEF */
	varchar wt_fl_dirnm                [512+1];	/* NOT_DEF */
	varchar wt_flnm                    [256+1];	/* NOT_DEF */
	varchar trt_rzt_c                  [  4+1];	/* NOT_DEF */
} TB_CLM_SNR_WT_TR_PT;

#endif
