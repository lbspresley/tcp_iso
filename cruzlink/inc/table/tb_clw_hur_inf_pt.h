/******************************************************************************
 화일명     : tb_clw_hur_inf_pt.h
 내용설명   : TB_CLW_HUR_INF pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLW_HUR_INF_PT_H__
#define	__TB_CLW_HUR_INF_PT_H__

int  db_Insert_tb_clw_hur_inf(char *p_tstr);
int  db_Select_tb_clw_hur_inf(char *p_tstr);
int  db_Update_tb_clw_hur_inf(char *p_tstr);
void db_Disp_tb_clw_hur_inf(char *p_tstr);
void db_Init_tb_clw_hur_inf(char *p_tstr);

typedef	struct
{
	varchar eno                        [  9+1];	/* NOT_DEF */
	varchar oft_nm                     [ 15+1];	/* NOT_DEF */
	varchar eno_nm                     [ 32+1];	/* NOT_DEF */
	varchar hdp_no                     [ 32+1];	/* NOT_DEF */
	varchar adm_bizc                   [  6+1];	/* NOT_DEF */
	varchar adop_sts_dsc               [  1+1];	/* NOT_DEF */
} TB_CLW_HUR_INF_PT;

#endif
