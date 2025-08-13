/******************************************************************************
 화일명     : tb_clm_deal_mst_pt.h
 내용설명   : TB_CLM_DEAL_MST pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLM_DEAL_MST_PT_H__
#define	__TB_CLM_DEAL_MST_PT_H__

int  db_Insert_tb_clm_deal_mst(char *p_tstr);
int  db_Select_tb_clm_deal_mst(char *p_tstr);
int  db_Update_tb_clm_deal_mst(char *p_tstr);
void db_Disp_tb_clm_deal_mst(char *p_tstr);
void db_Init_tb_clm_deal_mst(char *p_tstr);

typedef	struct
{
	varchar tr_dd                      [  2+1];	/* NOT_DEF */
	varchar tr_dt                      [  8+1];	/* NOT_DEF */
	int     mst_tr_sq                         ;	/* NOT_DEF */
	varchar node_no                    [  2+1];	/* NOT_DEF */
	varchar clm_ap_code                [ 32+1];	/* NOT_DEF */
	varchar clm_biz_dtl_cd             [ 32+1];	/* NOT_DEF */
	varchar ext_chan_id                [  4+1];	/* NOT_DEF */
	varchar bed_chan_id                [  4+1];	/* NOT_DEF */
	varchar clm_sr_dsc                 [  1+1];	/* NOT_DEF */
	varchar trt_rzt_c                  [  4+1];	/* NOT_DEF */
	varchar snr_dt                     [  8+1];	/* NOT_DEF */
	varchar biz_prc_dt                 [  8+1];	/* NOT_DEF */
	varchar fl_sq                      [  4+1];	/* NOT_DEF */
	int     snd_cnt                           ;	/* NOT_DEF */
	varchar snr_strt_dt                [  8+1];	/* NOT_DEF */
	varchar snr_strt_tm                [  6+1];	/* NOT_DEF */
	varchar snr_cmpl_dt                [  8+1];	/* NOT_DEF */
	varchar snr_cmpl_tm                [  6+1];	/* NOT_DEF */
	varchar ext_ip                     [ 20+1];	/* NOT_DEF */
	int     ext_port                          ;	/* NOT_DEF */
	varchar ext_linenm                 [  5+1];	/* NOT_DEF */
	varchar ext_lunm                   [  5+1];	/* NOT_DEF */
	varchar inp_flnm                   [128+1];	/* NOT_DEF */
	varchar otp_flnm                   [128+1];	/* NOT_DEF */
	varchar ext_flnm                   [512+1];	/* NOT_DEF */
	int     snr_fl_sz                         ;	/* NOT_DEF */
	varchar inp_dirnm                  [512+1];	/* NOT_DEF */
	double  snr_fl_tr_sz                      ;	/* NOT_DEF */
	varchar otp_dirnm                  [512+1];	/* NOT_DEF */
	varchar cmpl_dirnm                 [512+1];	/* NOT_DEF */
	varchar ext_dirnm                  [512+1];	/* NOT_DEF */
} TB_CLM_DEAL_MST_PT;

#endif
