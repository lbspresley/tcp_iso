/******************************************************************************
 화일명     : tb_clm_err_log_ct.h
 내용설명   : TB_CLM_ERR_LOG c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLM_ERR_LOG_CT_H__
#define	__TB_CLM_ERR_LOG_CT_H__

int  db_Insert_tb_clm_err_log(char *p_tstr);
int  db_Select_tb_clm_err_log(char *p_tstr);
int  db_Update_tb_clm_err_log(char *p_tstr);
void db_Disp_tb_clm_err_log(char *p_tstr);
void db_Init_tb_clm_err_log(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  2+1]; } tr_dd;
	struct { unsigned short len; unsigned char arr[  8+1]; } tr_dt;
	int     mst_tr_sq;
	struct { unsigned short len; unsigned char arr[ 32+1]; } ap_code;
	struct { unsigned short len; unsigned char arr[  4+1]; } ext_chan_id;
	struct { unsigned short len; unsigned char arr[  4+1]; } bed_chan_id;
	struct { unsigned short len; unsigned char arr[ 12+1]; } biz_dtl_dsc;
	struct { unsigned short len; unsigned char arr[  1+1]; } snr_dsc;
	struct { unsigned short len; unsigned char arr[  8+1]; } snd_dt;
	struct { unsigned short len; unsigned char arr[  4+1]; } fl_sq;
	struct { unsigned short len; unsigned char arr[  4+1]; } trt_rzt_c;
	struct { unsigned short len; unsigned char arr[  9+1]; } trt_tm;
	struct { unsigned short len; unsigned char arr[  2+1]; } node_no;
	struct { unsigned short len; unsigned char arr[ 16+1]; } issue_svc_nm;
	struct { unsigned short len; unsigned char arr[128+1]; } flnm;
	double  flsz;
	struct { unsigned short len; unsigned char arr[256+1]; } dirnm;
	struct { unsigned short len; unsigned char arr[1024+1]; } err_cntn;
} TB_CLM_ERR_LOG_CT;

#endif
