/******************************************************************************
 화일명     : tb_clw_menu_inf_pt.h
 내용설명   : TB_CLW_MENU_INF pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLW_MENU_INF_PT_H__
#define	__TB_CLW_MENU_INF_PT_H__

int  db_Insert_tb_clw_menu_inf(char *p_tstr);
int  db_Select_tb_clw_menu_inf(char *p_tstr);
int  db_Update_tb_clw_menu_inf(char *p_tstr);
void db_Disp_tb_clw_menu_inf(char *p_tstr);
void db_Init_tb_clw_menu_inf(char *p_tstr);

typedef	struct
{
	varchar menu_id                    [ 20+1];	/* NOT_DEF */
	varchar ug_chan_dsc                [  1+1];	/* NOT_DEF */
	varchar up_menu_id                 [ 20+1];	/* NOT_DEF */
	varchar mnnm                       [ 50+1];	/* NOT_DEF */
	varchar menu_enm                   [ 50+1];	/* NOT_DEF */
	varchar menu_earnm                 [ 50+1];	/* NOT_DEF */
	varchar menu_dsc                   [  1+1];	/* NOT_DEF */
	int     menu_stp_no                       ;	/* NOT_DEF */
	int     menu_sq                           ;	/* NOT_DEF */
	varchar menu_pgid                  [ 20+1];	/* NOT_DEF */
	varchar pgm_exe_pathnm             [200+1];	/* NOT_DEF */
	varchar menu_imgnm1                [100+1];	/* NOT_DEF */
	varchar menu_imgnm2                [100+1];	/* NOT_DEF */
	varchar menu_uyn                   [  1+1];	/* NOT_DEF */
} TB_CLW_MENU_INF_PT;

#endif
