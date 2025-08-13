/******************************************************************************
 화일명     : tb_clr_deal_mst_ct.h
 내용설명   : TB_CLR_DEAL_MST c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLR_DEAL_MST_CT_H__
#define	__TB_CLR_DEAL_MST_CT_H__

int  db_Insert_tb_clr_deal_mst(char *p_tstr);
int  db_Select_tb_clr_deal_mst(char *p_tstr);
int  db_Update_tb_clr_deal_mst(char *p_tstr);
void db_Disp_tb_clr_deal_mst(char *p_tstr);
void db_Init_tb_clr_deal_mst(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  2+1]; } tr_dd;
	struct { unsigned short len; unsigned char arr[  8+1]; } tr_dt;
	int     mst_trx_sqno;
	struct { unsigned short len; unsigned char arr[ 32+1]; } fst_ap_code;
	struct { unsigned short len; unsigned char arr[ 32+1]; } ap_code;
	struct { unsigned short len; unsigned char arr[  1+1]; } trt_op_dsc;
	struct { unsigned short len; unsigned char arr[  1+1]; } re_rs_dsc;
	struct { unsigned short len; unsigned char arr[  4+1]; } ext_chan_id;
	struct { unsigned short len; unsigned char arr[  4+1]; } bed_chan_id;
	struct { unsigned short len; unsigned char arr[  4+1]; } mst_trt_rzt_c;
	struct { unsigned short len; unsigned char arr[ 12+1]; } biz_dtl_dsc;
	int     last_data_trx_sqno;
	struct { unsigned short len; unsigned char arr[  9+1]; } snd_tm;
	struct { unsigned short len; unsigned char arr[  9+1]; } rcv_tm;
	struct { unsigned short len; unsigned char arr[  2+1]; } node_no;
	struct { unsigned short len; unsigned char arr[ 32+1]; } biz_seq_cntn;
	struct { unsigned short len; unsigned char arr[ 32+1]; } ext_seq_cntn;
	struct { unsigned short len; unsigned char arr[  8+1]; } x25_line_nm;
	struct { unsigned short len; unsigned char arr[  8+1]; } x25_lu_no;
	struct { unsigned short len; unsigned char arr[ 16+1]; } peer_ip;
	struct { unsigned short len; unsigned char arr[  5+1]; } peer_port;
	int     sess_no;
	struct { unsigned short len; unsigned char arr[  4+1]; } bed_svrnm;
	struct { unsigned short len; unsigned char arr[  1+1]; } tgrm_asodsc;
	struct { unsigned short len; unsigned char arr[  4+1]; } trt_rzt_c;
} TB_CLR_DEAL_MST_CT;

#endif
