/******************************************************************************
 화일명     : tb_clw_hurtp_auth_pt.h
 내용설명   : TB_CLW_HURTP_AUTH pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLW_HURTP_AUTH_PT_H__
#define	__TB_CLW_HURTP_AUTH_PT_H__

int  db_Insert_tb_clw_hurtp_auth(char *p_tstr);
int  db_Select_tb_clw_hurtp_auth(char *p_tstr);
int  db_Update_tb_clw_hurtp_auth(char *p_tstr);
void db_Disp_tb_clw_hurtp_auth(char *p_tstr);
void db_Init_tb_clw_hurtp_auth(char *p_tstr);

typedef	struct
{
	varchar id                         [  9+1];	/* NOT_DEF */
	varchar gubun                      [  1+1];	/* NOT_DEF */
	varchar auth_type                  [  1+1];	/* NOT_DEF */
	int     grp_id                            ;	/* NOT_DEF */
} TB_CLW_HURTP_AUTH_PT;

#endif
