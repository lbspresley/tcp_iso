/******************************************************************************
 화일명     : tb_clw_pgm_inf_pt.h
 내용설명   : TB_CLW_PGM_INF pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLW_PGM_INF_PT_H__
#define	__TB_CLW_PGM_INF_PT_H__

int  db_Insert_tb_clw_pgm_inf(char *p_tstr);
int  db_Select_tb_clw_pgm_inf(char *p_tstr);
int  db_Update_tb_clw_pgm_inf(char *p_tstr);
void db_Disp_tb_clw_pgm_inf(char *p_tstr);
void db_Init_tb_clw_pgm_inf(char *p_tstr);

typedef	struct
{
	varchar pgm_id                     [  5+1];	/* NOT_DEF */
	varchar use_yn                     [  1+1];	/* NOT_DEF */
	varchar pgm_nm                     [ 50+1];	/* NOT_DEF */
	varchar menu_id                    [ 20+1];	/* NOT_DEF */
	varchar pgm_path                   [100+1];	/* NOT_DEF */
	int     sort_sqno                         ;	/* NOT_DEF */
	varchar pgm_img_fl                 [100+1];	/* NOT_DEF */
	varchar drup_dtm                     [ 24];	/* NOT_DEF */
	varchar mod_dtm                      [ 24];	/* NOT_DEF */
	varchar reg_eno                    [ 13+1];	/* NOT_DEF */
	varchar mod_eno                    [ 13+1];	/* NOT_DEF */
} TB_CLW_PGM_INF_PT;

#endif
