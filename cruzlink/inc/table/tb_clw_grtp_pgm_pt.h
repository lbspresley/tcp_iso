/******************************************************************************
 화일명     : tb_clw_grtp_pgm_pt.h
 내용설명   : TB_CLW_GRTP_PGM pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLW_GRTP_PGM_PT_H__
#define	__TB_CLW_GRTP_PGM_PT_H__

int  db_Insert_tb_clw_grtp_pgm(char *p_tstr);
int  db_Select_tb_clw_grtp_pgm(char *p_tstr);
int  db_Update_tb_clw_grtp_pgm(char *p_tstr);
void db_Disp_tb_clw_grtp_pgm(char *p_tstr);
void db_Init_tb_clw_grtp_pgm(char *p_tstr);

typedef	struct
{
	varchar pgm_id                     [  5+1];	/* NOT_DEF */
	varchar grp_id                     [ 10+1];	/* NOT_DEF */
	varchar use_yn                     [  1+1];	/* NOT_DEF */
} TB_CLW_GRTP_PGM_PT;

#endif
