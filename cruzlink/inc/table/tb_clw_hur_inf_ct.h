/******************************************************************************
 화일명     : tb_clw_hur_inf_ct.h
 내용설명   : TB_CLW_HUR_INF c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLW_HUR_INF_CT_H__
#define	__TB_CLW_HUR_INF_CT_H__

int  db_Insert_tb_clw_hur_inf(char *p_tstr);
int  db_Select_tb_clw_hur_inf(char *p_tstr);
int  db_Update_tb_clw_hur_inf(char *p_tstr);
void db_Disp_tb_clw_hur_inf(char *p_tstr);
void db_Init_tb_clw_hur_inf(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  9+1]; } eno;
	struct { unsigned short len; unsigned char arr[ 15+1]; } oft_nm;
	struct { unsigned short len; unsigned char arr[ 32+1]; } eno_nm;
	struct { unsigned short len; unsigned char arr[ 32+1]; } hdp_no;
	struct { unsigned short len; unsigned char arr[  6+1]; } adm_bizc;
	struct { unsigned short len; unsigned char arr[  1+1]; } adop_sts_dsc;
} TB_CLW_HUR_INF_CT;

#endif
