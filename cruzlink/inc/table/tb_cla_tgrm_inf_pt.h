/******************************************************************************
 화일명     : tb_cla_tgrm_inf_pt.h
 내용설명   : TB_CLA_TGRM_INF pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLA_TGRM_INF_PT_H__
#define	__TB_CLA_TGRM_INF_PT_H__

int  db_Insert_tb_cla_tgrm_inf(char *p_tstr);
int  db_Select_tb_cla_tgrm_inf(char *p_tstr);
int  db_Update_tb_cla_tgrm_inf(char *p_tstr);
void db_Disp_tb_cla_tgrm_inf(char *p_tstr);
void db_Init_tb_cla_tgrm_inf(char *p_tstr);

typedef	struct
{
	varchar ext_chan_id                [  4+1];	/* NOT_DEF */
	varchar amn_tgrm_kdc               [  1+1];	/* NOT_DEF */
	varchar amn_tgrm_fild_sqno         [ 10+1];	/* NOT_DEF */
	varchar amn_tgrm_fildnm            [ 20+1];	/* NOT_DEF */
	varchar amn_tgrm_fild_tpc          [  2+1];	/* NOT_DEF */
	int     amn_tgrm_fild_pos                 ;	/* NOT_DEF */
	int     amn_tgrm_fild_len                 ;	/* NOT_DEF */
	varchar amn_tgrm_fild_tpby_kndc    [  8+1];	/* NOT_DEF */
	varchar amn_tgrm_fild_kndc         [  1+1];	/* NOT_DEF */
	int     amn_tgrm_copy_pos                 ;	/* NOT_DEF */
	int     amn_tgrm_copy_len                 ;	/* NOT_DEF */
	varchar amn_fild_dgn_cntn          [4000+1];	/* NOT_DEF */
} TB_CLA_TGRM_INF_PT;

#endif
