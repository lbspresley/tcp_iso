/******************************************************************************
 화일명     : tb_clc_bizdt_inf_pt.h
 내용설명   : TB_CLC_BIZDT_INF pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_BIZDT_INF_PT_H__
#define	__TB_CLC_BIZDT_INF_PT_H__

int  db_Insert_tb_clc_bizdt_inf(char *p_tstr);
int  db_Select_tb_clc_bizdt_inf(char *p_tstr);
int  db_Update_tb_clc_bizdt_inf(char *p_tstr);
void db_Disp_tb_clc_bizdt_inf(char *p_tstr);
void db_Init_tb_clc_bizdt_inf(char *p_tstr);

typedef	struct
{
	varchar yr                         [  4+1];	/* NOT_DEF */
	varchar mm                         [  2+1];	/* NOT_DEF */
	varchar dd                         [  2+1];	/* NOT_DEF */
	varchar dt_dsc                     [  1+1];	/* NOT_DEF */
	varchar dow_dsc                    [  3+1];	/* NOT_DEF */
	varchar dt_dtlc                    [ 30+1];	/* NOT_DEF */
} TB_CLC_BIZDT_INF_PT;

#endif
