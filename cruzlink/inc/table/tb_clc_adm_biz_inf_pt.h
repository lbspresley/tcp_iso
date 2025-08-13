/******************************************************************************
 화일명     : tb_clc_adm_biz_inf_pt.h
 내용설명   : TB_CLC_ADM_BIZ_INF pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_ADM_BIZ_INF_PT_H__
#define	__TB_CLC_ADM_BIZ_INF_PT_H__

int  db_Insert_tb_clc_adm_biz_inf(char *p_tstr);
int  db_Select_tb_clc_adm_biz_inf(char *p_tstr);
int  db_Update_tb_clc_adm_biz_inf(char *p_tstr);
void db_Disp_tb_clc_adm_biz_inf(char *p_tstr);
void db_Init_tb_clc_adm_biz_inf(char *p_tstr);

typedef	struct
{
	varchar adm_bizc                   [  6+1];	/* NOT_DEF */
	varchar adm_biz_nm                 [ 32+1];	/* NOT_DEF */
} TB_CLC_ADM_BIZ_INF_PT;

#endif
