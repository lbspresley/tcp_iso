/******************************************************************************
 화일명     : tb_clm_snr_wt_tr_ct.h
 내용설명   : TB_CLM_SNR_WT_TR c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLM_SNR_WT_TR_CT_H__
#define	__TB_CLM_SNR_WT_TR_CT_H__

int  db_Insert_tb_clm_snr_wt_tr(char *p_tstr);
int  db_Select_tb_clm_snr_wt_tr(char *p_tstr);
int  db_Update_tb_clm_snr_wt_tr(char *p_tstr);
void db_Disp_tb_clm_snr_wt_tr(char *p_tstr);
void db_Init_tb_clm_snr_wt_tr(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  2+1]; } snr_dd;
	struct { unsigned short len; unsigned char arr[  8+1]; } snr_dt;
	int     snr_wt_sq;
	struct { unsigned short len; unsigned char arr[  2+1]; } tr_dd;
	struct { unsigned short len; unsigned char arr[  8+1]; } tr_dt;
	int     mst_tr_sq;
	struct { unsigned short len; unsigned char arr[  4+1]; } fl_sq;
	int     snd_cnt;
	int     svc_prc_sq;
	struct { unsigned short len; unsigned char arr[  2+1]; } node_no;
	struct { unsigned short len; unsigned char arr[ 16+1]; } vr_adt_svcnm;
	struct { unsigned short len; unsigned char arr[ 32+1]; } clm_ap_code;
	struct { unsigned short len; unsigned char arr[ 32+1]; } clm_biz_dtl_cd;
	struct { unsigned short len; unsigned char arr[  1+1]; } clm_sr_dsc;
	struct { unsigned short len; unsigned char arr[  4+1]; } ext_chan_id;
	struct { unsigned short len; unsigned char arr[  1+1]; } im_prc_yn;
	struct { unsigned short len; unsigned char arr[  6+1]; } rsv_prc_hr;
	struct { unsigned short len; unsigned char arr[512+1]; } wt_fl_dirnm;
	struct { unsigned short len; unsigned char arr[256+1]; } wt_flnm;
	struct { unsigned short len; unsigned char arr[  4+1]; } trt_rzt_c;
} TB_CLM_SNR_WT_TR_CT;

#endif
