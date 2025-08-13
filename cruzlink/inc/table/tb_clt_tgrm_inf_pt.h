/******************************************************************************
 화일명     : tb_clt_tgrm_inf_pt.h
 내용설명   : TB_CLT_TGRM_INF pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLT_TGRM_INF_PT_H__
#define	__TB_CLT_TGRM_INF_PT_H__

int  db_Insert_tb_clt_tgrm_inf(char *p_tstr);
int  db_Select_tb_clt_tgrm_inf(char *p_tstr);
int  db_Update_tb_clt_tgrm_inf(char *p_tstr);
void db_Disp_tb_clt_tgrm_inf(char *p_tstr);
void db_Init_tb_clt_tgrm_inf(char *p_tstr);

typedef	struct
{
	varchar chan_id                    [  4+1];	/* NOT_DEF */
	varchar tst_tp_no                  [  6+1];	/* NOT_DEF */
	varchar tst_tgrm_fild_sqno         [ 10+1];	/* NOT_DEF */
	varchar tst_tgrm_fildnm            [ 20+1];	/* NOT_DEF */
	varchar tst_tgrm_fild_tpc          [  2+1];	/* NOT_DEF */
	int     tst_tgrm_fild_loc_cn              ;	/* NOT_DEF */
	int     tst_tgrm_fild_len                 ;	/* NOT_DEF */
	varchar tst_tgrm_fild_tpby_attr_c  [  8+1];	/* NOT_DEF */
	int     org_tgrm_cp_pos                   ;	/* NOT_DEF */
	int     org_tgrm_cp_len                   ;	/* NOT_DEF */
	varchar tst_fild_dgn_cntn          [4000+1];	/* NOT_DEF */
} TB_CLT_TGRM_INF_PT;

#endif
