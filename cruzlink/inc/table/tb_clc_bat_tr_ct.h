/******************************************************************************
 화일명     : tb_clc_bat_tr_ct.h
 내용설명   : TB_CLC_BAT_TR c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_BAT_TR_CT_H__
#define	__TB_CLC_BAT_TR_CT_H__

int  db_Insert_tb_clc_bat_tr(char *p_tstr);
int  db_Select_tb_clc_bat_tr(char *p_tstr);
int  db_Update_tb_clc_bat_tr(char *p_tstr);
void db_Disp_tb_clc_bat_tr(char *p_tstr);
void db_Init_tb_clc_bat_tr(char *p_tstr);

typedef	struct
{
	int     bat_no;
	int     bat_rsv_reg_sqno;
	struct { unsigned short len; unsigned char arr[  2+1]; } node_no;
	struct { unsigned short len; unsigned char arr[  8+1]; } bat_prc_rsv_dt;
	struct { unsigned short len; unsigned char arr[  6+1]; } bat_prc_rsv_tm;
	struct { unsigned short len; unsigned char arr[  2+1]; } bat_prc_mthdc;
	struct { unsigned short len; unsigned char arr[ 16+1]; } bat_prc_svcnm;
	struct { unsigned short len; unsigned char arr[256+1]; } bat_call_cmd_cntn;
	struct { unsigned short len; unsigned char arr[ 16+1]; } bat_err_prc_svcnm;
	struct { unsigned short len; unsigned char arr[  6+1]; } bat_err_prc_tm;
	struct { unsigned short len; unsigned char arr[  1+1]; } sms_snd_yn;
	int     bf_bat_no;
	struct { unsigned short len; unsigned char arr[  8+1]; } bat_tr_dt;
	struct { unsigned short len; unsigned char arr[  6+1]; } bat_prc_tm;
	struct { unsigned short len; unsigned char arr[  4+1]; } bat_prc_rzt_c;
	struct { unsigned short len; unsigned char arr[256+1]; } bat_call_tgrm_cntn;
} TB_CLC_BAT_TR_CT;

#endif
