/******************************************************************************
 화일명     : tb_clm_ap_ds_inf_ct.h
 내용설명   : TB_CLM_AP_DS_INF c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLM_AP_DS_INF_CT_H__
#define	__TB_CLM_AP_DS_INF_CT_H__

int  db_Insert_tb_clm_ap_ds_inf(char *p_tstr);
int  db_Select_tb_clm_ap_ds_inf(char *p_tstr);
int  db_Update_tb_clm_ap_ds_inf(char *p_tstr);
void db_Disp_tb_clm_ap_ds_inf(char *p_tstr);
void db_Init_tb_clm_ap_ds_inf(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  4+1]; } chan_id;
	int     fl_ds_inf_sqno;
	int     tot_ds_cnt;
	int     fl_ds_pos1;
	int     fl_ds_len1;
	int     fl_ds_pos2;
	int     fl_ds_len2;
	int     fl_ds_pos3;
	int     fl_ds_len3;
	int     fl_ds_pos4;
	int     fl_ds_len4;
	int     fl_ds_pos5;
	int     fl_ds_len5;
} TB_CLM_AP_DS_INF_CT;

#endif
