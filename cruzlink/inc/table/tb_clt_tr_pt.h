/******************************************************************************
 화일명     : tb_clt_tr_pt.h
 내용설명   : TB_CLT_TR pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLT_TR_PT_H__
#define	__TB_CLT_TR_PT_H__

int  db_Insert_tb_clt_tr(char *p_tstr);
int  db_Select_tb_clt_tr(char *p_tstr);
int  db_Update_tb_clt_tr(char *p_tstr);
void db_Disp_tb_clt_tr(char *p_tstr);
void db_Init_tb_clt_tr(char *p_tstr);

typedef	struct
{
	varchar tr_dt                      [  8+1];	/* NOT_DEF */
	int     tst_tr_sqno                       ;	/* NOT_DEF */
	varchar chan_id                    [  4+1];	/* NOT_DEF */
	varchar ap_code                    [ 32+1];	/* NOT_DEF */
	varchar tst_tp_no                  [  6+1];	/* NOT_DEF */
	varchar tst_tm                     [  6+1];	/* NOT_DEF */
	varchar ext_seq_cntn               [ 32+1];	/* NOT_DEF */
	varchar ext_chan_tgrm_id           [ 60+1];	/* NOT_DEF */
	varchar tst_tgrm_srch_cntn         [ 32+1];	/* NOT_DEF */
	varchar tst_tgrm_cntn1             [4000+1];	/* NOT_DEF */
	varchar tst_tgrm_cntn2             [4000+1];	/* NOT_DEF */
	varchar tst_tgrm_cntn3             [4000+1];	/* NOT_DEF */
	varchar tst_tgrm_cntn4             [4000+1];	/* NOT_DEF */
} TB_CLT_TR_PT;

#endif
