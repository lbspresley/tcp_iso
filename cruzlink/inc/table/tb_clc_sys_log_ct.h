/******************************************************************************
 화일명     : tb_clc_sys_log_ct.h
 내용설명   : TB_CLC_SYS_LOG c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_SYS_LOG_CT_H__
#define	__TB_CLC_SYS_LOG_CT_H__

int  db_Insert_tb_clc_sys_log(char *p_tstr);
int  db_Select_tb_clc_sys_log(char *p_tstr);
int  db_Update_tb_clc_sys_log(char *p_tstr);
void db_Disp_tb_clc_sys_log(char *p_tstr);
void db_Init_tb_clc_sys_log(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  8+1]; } log_dt;
	struct { unsigned short len; unsigned char arr[  6+1]; } log_tm;
	int     log_sq;
	struct { unsigned short len; unsigned char arr[ 32+1]; } mdl_nm;
	struct { unsigned short len; unsigned char arr[  2+1]; } log_dsc;
	struct { unsigned short len; unsigned char arr[  1+1]; } sms_req_yn;
	struct { unsigned short len; unsigned char arr[2048+1]; } fr_dtl_cntn;
} TB_CLC_SYS_LOG_CT;

#endif
