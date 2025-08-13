/******************************************************************************
 화일명     : tb_clr_svc_mst_ct.h
 내용설명   : TB_CLR_SVC_MST c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLR_SVC_MST_CT_H__
#define	__TB_CLR_SVC_MST_CT_H__

int  db_Insert_tb_clr_svc_mst(char *p_tstr);
int  db_Select_tb_clr_svc_mst(char *p_tstr);
int  db_Update_tb_clr_svc_mst(char *p_tstr);
void db_Disp_tb_clr_svc_mst(char *p_tstr);
void db_Init_tb_clr_svc_mst(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[ 32+1]; } ap_code;
	struct { unsigned short len; unsigned char arr[  1+1]; } trt_op_dsc;
	struct { unsigned short len; unsigned char arr[ 32+1]; } fst_ap_code;
	struct { unsigned short len; unsigned char arr[  1+1]; } re_rs_dsc;
	struct { unsigned short len; unsigned char arr[  4+1]; } ext_chan_id;
	struct { unsigned short len; unsigned char arr[  4+1]; } bed_chan_id;
	struct { unsigned short len; unsigned char arr[ 20+1]; } svc_flow_mst_dsc;
	struct { unsigned short len; unsigned char arr[ 16+1]; } err_svcnm;
	struct { unsigned short len; unsigned char arr[ 16+1]; } to_svcnm;
	struct { unsigned short len; unsigned char arr[ 16+1]; } to_err_svcnm;
	struct { unsigned short len; unsigned char arr[  2+1]; } node_no;
	struct { unsigned short len; unsigned char arr[ 32+1]; } rel_ap_code;
	struct { unsigned short len; unsigned char arr[  1+1]; } crypt_dsc;
	struct { unsigned short len; unsigned char arr[ 16+1]; } crypt_mdlnm;
	struct { unsigned short len; unsigned char arr[ 64+1]; } crypt_key_flnm;
	int     crypt_pos;
	int     crypt_len;
	int     decrypt_len;
	struct { unsigned short len; unsigned char arr[  1+1]; } dup_trtc;
	struct { unsigned short len; unsigned char arr[  1+1]; } tgrm_asodsc;
	struct { unsigned short len; unsigned char arr[  1+1]; } seq_reg_dsc;
	struct { unsigned short len; unsigned char arr[ 32+1]; } seq_nm;
	int     biz_seq_pos;
	int     biz_seq_len;
	int     ext_seq_pos;
	int     ext_seq_len;
	int     biz_dtl_dsc_pos;
	int     biz_dtl_dsc_len;
	struct { unsigned short len; unsigned char arr[  6+1]; } to_tm;
	struct { unsigned short len; unsigned char arr[  1+1]; } to_tr_c;
	int     to_rty_cn;
	struct { unsigned short len; unsigned char arr[  2+1]; } to_bed_hdr_comp_dsc;
	struct { unsigned short len; unsigned char arr[  1+1]; } app_snd_tp_yn;
	struct { unsigned short len; unsigned char arr[  8+1]; } x25_line_nm;
	struct { unsigned short len; unsigned char arr[  8+1]; } x25_lu_no;
	struct { unsigned short len; unsigned char arr[ 16+1]; } peer_ip;
	struct { unsigned short len; unsigned char arr[  5+1]; } peer_port;
	struct { unsigned short len; unsigned char arr[  5+1]; } local_port;
	struct { unsigned short len; unsigned char arr[ 16+1]; } bed_svc_nm;
	struct { unsigned short len; unsigned char arr[  1+1]; } snd_err_bed_rtn_yn;
	struct { unsigned short len; unsigned char arr[  2+1]; } snd_err_hdr_comp_dsc;
	struct { unsigned short len; unsigned char arr[ 16+1]; } snd_err_bed_svc_nm;
	struct { unsigned short len; unsigned char arr[  1+1]; } tgrm_log_dsc;
	struct { unsigned short len; unsigned char arr[ 32+1]; } eaiid;
	struct { unsigned short len; unsigned char arr[  2+1]; } bed_hdr_comp_dsc;
	struct { unsigned short len; unsigned char arr[  2+1]; } ext_hdr_comp_dsc;
	struct { unsigned short len; unsigned char arr[  1+1]; } hdr_rec_yn;
	struct { unsigned short len; unsigned char arr[  8+1]; } opn_dt;
	struct { unsigned short len; unsigned char arr[ 10+1]; } chan_bsn_dept_c;
	struct { unsigned short len; unsigned char arr[256+1]; } ap_code_nm;
	struct { unsigned short len; unsigned char arr[ 50+1]; } tgrm_mrl_id;
	struct { unsigned short len; unsigned char arr[ 60+1]; } ext_chan_tgrm_id;
	struct { unsigned short len; unsigned char arr[  1+1]; } ext_snr_dsc;
	struct { unsigned short len; unsigned char arr[ 60+1]; } bed_chan_tgrm_id;
	struct { unsigned short len; unsigned char arr[  1+1]; } bed_snr_dsc;
} TB_CLR_SVC_MST_CT;

#endif
