/******************************************************************************
 화일명     : tb_clr_deal_data_ct.h
 내용설명   : TB_CLR_DEAL_DATA c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLR_DEAL_DATA_CT_H__
#define	__TB_CLR_DEAL_DATA_CT_H__

int  db_Insert_tb_clr_deal_data(char *p_tstr);
int  db_Select_tb_clr_deal_data(char *p_tstr);
int  db_Update_tb_clr_deal_data(char *p_tstr);
void db_Disp_tb_clr_deal_data(char *p_tstr);
void db_Init_tb_clr_deal_data(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  2+1]; } tr_dd;
	struct { unsigned short len; unsigned char arr[  8+1]; } tr_dt;
	int     data_trx_sqno;
	struct { unsigned short len; unsigned char arr[ 32+1]; } fst_ap_code;
	struct { unsigned short len; unsigned char arr[ 32+1]; } ap_code;
	struct { unsigned short len; unsigned char arr[  1+1]; } trt_op_dsc;
	struct { unsigned short len; unsigned char arr[  1+1]; } re_rs_dsc;
	struct { unsigned short len; unsigned char arr[  4+1]; } ext_chan_id;
	struct { unsigned short len; unsigned char arr[  4+1]; } bed_chan_id;
	struct { unsigned short len; unsigned char arr[ 12+1]; } biz_dtl_dsc;
	int     mst_trx_sqno;
	struct { unsigned short len; unsigned char arr[ 60+1]; } chan_tgrm_id;
	struct { unsigned short len; unsigned char arr[  4+1]; } trt_rzt_c;
	struct { unsigned short len; unsigned char arr[  1+1]; } snr_dsc;
	struct { unsigned short len; unsigned char arr[  9+1]; } trt_tm;
	struct { unsigned short len; unsigned char arr[ 32+1]; } biz_seq_cntn;
	struct { unsigned short len; unsigned char arr[ 32+1]; } ext_seq_cntn;
	int     core_hdr_len;
	int     eai_hdr_len;
	int     data_len;
	struct { unsigned short len; unsigned char arr[1024+1]; } core_hdr_cntn;
	struct { unsigned short len; unsigned char arr[1024+1]; } eai_hdr_cntn;
	struct { unsigned short len; unsigned char arr[4000+1]; } data_cntn;
} TB_CLR_DEAL_DATA_CT;

#endif
