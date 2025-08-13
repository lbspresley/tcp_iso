/******************************************************************************
 화일명     : tb_clc_sysinfo_ct.h
 내용설명   : TB_CLC_SYSINFO c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_SYSINFO_CT_H__
#define	__TB_CLC_SYSINFO_CT_H__

int  db_Insert_tb_clc_sysinfo(char *p_tstr);
int  db_Select_tb_clc_sysinfo(char *p_tstr);
int  db_Update_tb_clc_sysinfo(char *p_tstr);
void db_Disp_tb_clc_sysinfo(char *p_tstr);
void db_Init_tb_clc_sysinfo(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  8+1]; } issue_dt;
	struct { unsigned short len; unsigned char arr[  4+1]; } issue_time_min;
	struct { unsigned short len; unsigned char arr[  2+1]; } node_no;
	int     cpu_rate;
	int     mem_rate;
	int     hdd_rate;
} TB_CLC_SYSINFO_CT;

#endif
