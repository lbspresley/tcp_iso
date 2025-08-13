/******************************************************************************
 화일명     : tb_clm_deal_mst_ct.h
 내용설명   : TB_CLM_DEAL_MST c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLM_DEAL_MST_CT_H__
#define	__TB_CLM_DEAL_MST_CT_H__

int  db_Insert_tb_clm_deal_mst(char *p_tstr);
int  db_Select_tb_clm_deal_mst(char *p_tstr);
int  db_Update_tb_clm_deal_mst(char *p_tstr);
void db_Disp_tb_clm_deal_mst(char *p_tstr);
void db_Init_tb_clm_deal_mst(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  2+1]; } tr_dd;
	struct { unsigned short len; unsigned char arr[  8+1]; } tr_dt;
	int     mst_tr_sq;
	struct { unsigned short len; unsigned char arr[  2+1]; } node_no;
	struct { unsigned short len; unsigned char arr[ 32+1]; } clm_ap_code;
	struct { unsigned short len; unsigned char arr[ 32+1]; } clm_biz_dtl_cd;
	struct { unsigned short len; unsigned char arr[  4+1]; } ext_chan_id;
	struct { unsigned short len; unsigned char arr[  4+1]; } bed_chan_id;
	struct { unsigned short len; unsigned char arr[  1+1]; } clm_sr_dsc;
	struct { unsigned short len; unsigned char arr[  4+1]; } trt_rzt_c;
	struct { unsigned short len; unsigned char arr[  8+1]; } snr_dt;
	struct { unsigned short len; unsigned char arr[  8+1]; } biz_prc_dt;
	struct { unsigned short len; unsigned char arr[  4+1]; } fl_sq;
	int     snd_cnt;
	struct { unsigned short len; unsigned char arr[  8+1]; } snr_strt_dt;
	struct { unsigned short len; unsigned char arr[  6+1]; } snr_strt_tm;
	struct { unsigned short len; unsigned char arr[  8+1]; } snr_cmpl_dt;
	struct { unsigned short len; unsigned char arr[  6+1]; } snr_cmpl_tm;
	struct { unsigned short len; unsigned char arr[ 20+1]; } ext_ip;
	int     ext_port;
	struct { unsigned short len; unsigned char arr[  5+1]; } ext_linenm;
	struct { unsigned short len; unsigned char arr[  5+1]; } ext_lunm;
	struct { unsigned short len; unsigned char arr[128+1]; } inp_flnm;
	struct { unsigned short len; unsigned char arr[128+1]; } otp_flnm;
	struct { unsigned short len; unsigned char arr[512+1]; } ext_flnm;
	int     snr_fl_sz;
	struct { unsigned short len; unsigned char arr[512+1]; } inp_dirnm;
	double  snr_fl_tr_sz;
	struct { unsigned short len; unsigned char arr[512+1]; } otp_dirnm;
	struct { unsigned short len; unsigned char arr[512+1]; } cmpl_dirnm;
	struct { unsigned short len; unsigned char arr[512+1]; } ext_dirnm;
} TB_CLM_DEAL_MST_CT;

#endif
