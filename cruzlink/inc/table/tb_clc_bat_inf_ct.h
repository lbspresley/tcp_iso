/******************************************************************************
 화일명     : tb_clc_bat_inf_ct.h
 내용설명   : TB_CLC_BAT_INF c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_BAT_INF_CT_H__
#define	__TB_CLC_BAT_INF_CT_H__

int  db_Insert_tb_clc_bat_inf(char *p_tstr);
int  db_Select_tb_clc_bat_inf(char *p_tstr);
int  db_Update_tb_clc_bat_inf(char *p_tstr);
void db_Disp_tb_clc_bat_inf(char *p_tstr);
void db_Init_tb_clc_bat_inf(char *p_tstr);

typedef	struct
{
	int     bat_no;
	struct { unsigned short len; unsigned char arr[ 80+1]; } batnm;
	struct { unsigned short len; unsigned char arr[  2+1]; } node_no;
	struct { unsigned short len; unsigned char arr[  1+1]; } wed_prc_yn;
	struct { unsigned short len; unsigned char arr[  1+1]; } hld_prc_yn;
	struct { unsigned short len; unsigned char arr[  1+1]; } biz_prc_yn;
	struct { unsigned short len; unsigned char arr[  2+1]; } bat_prc_mthdc;
	struct { unsigned short len; unsigned char arr[ 16+1]; } bat_prc_svcnm;
	struct { unsigned short len; unsigned char arr[256+1]; } bat_call_cmd_cntn;
	struct { unsigned short len; unsigned char arr[ 16+1]; } bat_err_prc_svcnm;
	struct { unsigned short len; unsigned char arr[  6+1]; } bat_err_prc_tm;
	struct { unsigned short len; unsigned char arr[  1+1]; } sms_snd_yn;
	struct { unsigned short len; unsigned char arr[ 10+1]; } chan_bsn_dept_c;
	int     bf_bat_no;
	struct { unsigned short len; unsigned char arr[  2+1]; } bat_prc_mon;
	struct { unsigned short len; unsigned char arr[  2+1]; } bat_prc_dt;
	struct { unsigned short len; unsigned char arr[  2+1]; } bat_prc_dow;
	struct { unsigned short len; unsigned char arr[  2+1]; } bat_prc_hr;
	struct { unsigned short len; unsigned char arr[  2+1]; } bat_prc_min;
	struct { unsigned short len; unsigned char arr[  1+1]; } nxt_biz_prc_yn;
	struct { unsigned short len; unsigned char arr[  1+1]; } use_yn;
	int     lst_bat_rsv_reg_sqno;
} TB_CLC_BAT_INF_CT;

#endif
