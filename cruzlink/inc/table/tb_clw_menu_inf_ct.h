/******************************************************************************
 화일명     : tb_clw_menu_inf_ct.h
 내용설명   : TB_CLW_MENU_INF c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLW_MENU_INF_CT_H__
#define	__TB_CLW_MENU_INF_CT_H__

int  db_Insert_tb_clw_menu_inf(char *p_tstr);
int  db_Select_tb_clw_menu_inf(char *p_tstr);
int  db_Update_tb_clw_menu_inf(char *p_tstr);
void db_Disp_tb_clw_menu_inf(char *p_tstr);
void db_Init_tb_clw_menu_inf(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[ 20+1]; } menu_id;
	struct { unsigned short len; unsigned char arr[  1+1]; } ug_chan_dsc;
	struct { unsigned short len; unsigned char arr[ 20+1]; } up_menu_id;
	struct { unsigned short len; unsigned char arr[ 50+1]; } mnnm;
	struct { unsigned short len; unsigned char arr[ 50+1]; } menu_enm;
	struct { unsigned short len; unsigned char arr[ 50+1]; } menu_earnm;
	struct { unsigned short len; unsigned char arr[  1+1]; } menu_dsc;
	int     menu_stp_no;
	int     menu_sq;
	struct { unsigned short len; unsigned char arr[ 20+1]; } menu_pgid;
	struct { unsigned short len; unsigned char arr[200+1]; } pgm_exe_pathnm;
	struct { unsigned short len; unsigned char arr[100+1]; } menu_imgnm1;
	struct { unsigned short len; unsigned char arr[100+1]; } menu_imgnm2;
	struct { unsigned short len; unsigned char arr[  1+1]; } menu_uyn;
} TB_CLW_MENU_INF_CT;

#endif
