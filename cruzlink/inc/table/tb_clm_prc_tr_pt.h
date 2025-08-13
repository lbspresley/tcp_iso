/******************************************************************************
 화일명     : tb_clm_prc_tr_pt.h
 내용설명   : TB_CLM_PRC_TR pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLM_PRC_TR_PT_H__
#define	__TB_CLM_PRC_TR_PT_H__

int  db_Insert_tb_clm_prc_tr(char *p_tstr);
int  db_Select_tb_clm_prc_tr(char *p_tstr);
int  db_Update_tb_clm_prc_tr(char *p_tstr);
void db_Disp_tb_clm_prc_tr(char *p_tstr);
void db_Init_tb_clm_prc_tr(char *p_tstr);

typedef	struct
{
	varchar rsv_dd                     [  2+1];	/* NOT_DEF */
	varchar rsv_dt                     [  8+1];	/* NOT_DEF */
	int     clm_fl_rsv_sq                     ;	/* NOT_DEF */
	varchar clm_ap_code                [ 32+1];	/* NOT_DEF */
	varchar snr_dsc                    [  1+1];	/* NOT_DEF */
	varchar snr_rsv_tm                 [  6+1];	/* NOT_DEF */
	varchar snr_cmpl_tm                [  6+1];	/* NOT_DEF */
	varchar rsv_fl_prc_dsc             [  2+1];	/* NOT_DEF */
	varchar snr_dirnm                  [512+1];	/* NOT_DEF */
	varchar snr_cmpl_dirnm             [512+1];	/* NOT_DEF */
	varchar snr_flnm                   [ 32+1];	/* NOT_DEF */
	varchar node_no                    [  2+1];	/* NOT_DEF */
	varchar clm_ap_codenm              [512+1];	/* NOT_DEF */
} TB_CLM_PRC_TR_PT;

#endif
