/******************************************************************************
 화일명     : tb_clm_prc_tr_ct.h
 내용설명   : TB_CLM_PRC_TR c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLM_PRC_TR_CT_H__
#define	__TB_CLM_PRC_TR_CT_H__

int  db_Insert_tb_clm_prc_tr(char *p_tstr);
int  db_Select_tb_clm_prc_tr(char *p_tstr);
int  db_Update_tb_clm_prc_tr(char *p_tstr);
void db_Disp_tb_clm_prc_tr(char *p_tstr);
void db_Init_tb_clm_prc_tr(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  2+1]; } rsv_dd;
	struct { unsigned short len; unsigned char arr[  8+1]; } rsv_dt;
	int     clm_fl_rsv_sq;
	struct { unsigned short len; unsigned char arr[ 32+1]; } clm_ap_code;
	struct { unsigned short len; unsigned char arr[  1+1]; } snr_dsc;
	struct { unsigned short len; unsigned char arr[  6+1]; } snr_rsv_tm;
	struct { unsigned short len; unsigned char arr[  6+1]; } snr_cmpl_tm;
	struct { unsigned short len; unsigned char arr[  2+1]; } rsv_fl_prc_dsc;
	struct { unsigned short len; unsigned char arr[512+1]; } snr_dirnm;
	struct { unsigned short len; unsigned char arr[512+1]; } snr_cmpl_dirnm;
	struct { unsigned short len; unsigned char arr[ 32+1]; } snr_flnm;
	struct { unsigned short len; unsigned char arr[  2+1]; } node_no;
	struct { unsigned short len; unsigned char arr[512+1]; } clm_ap_codenm;
} TB_CLM_PRC_TR_CT;

#endif
