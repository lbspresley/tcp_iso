/******************************************************************************
 화일명     : tb_clt_inf_pt.h
 내용설명   : TB_CLT_INF pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLT_INF_PT_H__
#define	__TB_CLT_INF_PT_H__

int  db_Insert_tb_clt_inf(char *p_tstr);
int  db_Select_tb_clt_inf(char *p_tstr);
int  db_Update_tb_clt_inf(char *p_tstr);
void db_Disp_tb_clt_inf(char *p_tstr);
void db_Init_tb_clt_inf(char *p_tstr);

typedef	struct
{
	varchar chan_id                    [  4+1];	/* NOT_DEF */
	varchar tst_tp_no                  [  6+1];	/* NOT_DEF */
	varchar tstnm                      [ 20+1];	/* NOT_DEF */
	varchar ap_code                    [ 32+1];	/* NOT_DEF */
	varchar tst_expl                   [100+1];	/* NOT_DEF */
	varchar tst_kdtc                   [  1+1];	/* NOT_DEF */
	varchar log_strg_yn                [  1+1];	/* NOT_DEF */
	varchar tst_rqr_flnm               [ 50+1];	/* NOT_DEF */
	varchar tgrm_cstt_metc             [  1+1];	/* NOT_DEF */
	varchar cft_rsp_dsc                [  2+1];	/* NOT_DEF */
	int     delay_rsp_sec                     ;	/* NOT_DEF */
	varchar tst_inf_uyn                [  1+1];	/* NOT_DEF */
	varchar rg_dtm                     [ 14+1];	/* NOT_DEF */
	varchar rgmn_eno                   [ 20+1];	/* NOT_DEF */
} TB_CLT_INF_PT;

#endif
