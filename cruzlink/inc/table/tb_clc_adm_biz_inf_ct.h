/******************************************************************************
 화일명     : tb_clc_adm_biz_inf_ct.h
 내용설명   : TB_CLC_ADM_BIZ_INF c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_ADM_BIZ_INF_CT_H__
#define	__TB_CLC_ADM_BIZ_INF_CT_H__

int  db_Insert_tb_clc_adm_biz_inf(char *p_tstr);
int  db_Select_tb_clc_adm_biz_inf(char *p_tstr);
int  db_Update_tb_clc_adm_biz_inf(char *p_tstr);
void db_Disp_tb_clc_adm_biz_inf(char *p_tstr);
void db_Init_tb_clc_adm_biz_inf(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  6+1]; } adm_bizc;
	struct { unsigned short len; unsigned char arr[ 32+1]; } adm_biz_nm;
} TB_CLC_ADM_BIZ_INF_CT;

#endif
