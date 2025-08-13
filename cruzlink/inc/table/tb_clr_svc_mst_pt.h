/******************************************************************************
 화일명     : tb_clr_svc_mst_pt.h
 내용설명   : TB_CLR_SVC_MST pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLR_SVC_MST_PT_H__
#define	__TB_CLR_SVC_MST_PT_H__

int  db_Insert_tb_clr_svc_mst(char *p_tstr);
int  db_Select_tb_clr_svc_mst(char *p_tstr);
int  db_Update_tb_clr_svc_mst(char *p_tstr);
void db_Disp_tb_clr_svc_mst(char *p_tstr);
void db_Init_tb_clr_svc_mst(char *p_tstr);

typedef	struct
{
	varchar ap_code                    [ 32+1];	/* NOT_DEF */
	varchar trt_op_dsc                 [  1+1];	/* NOT_DEF */
	varchar fst_ap_code                [ 32+1];	/* NOT_DEF */
	varchar re_rs_dsc                  [  1+1];	/* NOT_DEF */
	varchar ext_chan_id                [  4+1];	/* NOT_DEF */
	varchar bed_chan_id                [  4+1];	/* NOT_DEF */
	varchar svc_flow_mst_dsc           [ 20+1];	/* NOT_DEF */
	varchar err_svcnm                  [ 16+1];	/* NOT_DEF */
	varchar to_svcnm                   [ 16+1];	/* NOT_DEF */
	varchar to_err_svcnm               [ 16+1];	/* NOT_DEF */
	varchar node_no                    [  2+1];	/* NOT_DEF */
	varchar rel_ap_code                [ 32+1];	/* NOT_DEF */
	varchar crypt_dsc                  [  1+1];	/* NOT_DEF */
	varchar crypt_mdlnm                [ 16+1];	/* NOT_DEF */
	varchar crypt_key_flnm             [ 64+1];	/* NOT_DEF */
	int     crypt_pos                         ;	/* NOT_DEF */
	int     crypt_len                         ;	/* NOT_DEF */
	int     decrypt_len                       ;	/* NOT_DEF */
	varchar dup_trtc                   [  1+1];	/* NOT_DEF */
	varchar tgrm_asodsc                [  1+1];	/* NOT_DEF */
	varchar seq_reg_dsc                [  1+1];	/* NOT_DEF */
	varchar seq_nm                     [ 32+1];	/* NOT_DEF */
	int     biz_seq_pos                       ;	/* NOT_DEF */
	int     biz_seq_len                       ;	/* NOT_DEF */
	int     ext_seq_pos                       ;	/* NOT_DEF */
	int     ext_seq_len                       ;	/* NOT_DEF */
	int     biz_dtl_dsc_pos                   ;	/* NOT_DEF */
	int     biz_dtl_dsc_len                   ;	/* NOT_DEF */
	varchar to_tm                      [  6+1];	/* NOT_DEF */
	varchar to_tr_c                    [  1+1];	/* NOT_DEF */
	int     to_rty_cn                         ;	/* NOT_DEF */
	varchar to_bed_hdr_comp_dsc        [  2+1];	/* NOT_DEF */
	varchar app_snd_tp_yn              [  1+1];	/* NOT_DEF */
	varchar x25_line_nm                [  8+1];	/* NOT_DEF */
	varchar x25_lu_no                  [  8+1];	/* NOT_DEF */
	varchar peer_ip                    [ 16+1];	/* NOT_DEF */
	varchar peer_port                  [  5+1];	/* NOT_DEF */
	varchar local_port                 [  5+1];	/* NOT_DEF */
	varchar bed_svc_nm                 [ 16+1];	/* NOT_DEF */
	varchar snd_err_bed_rtn_yn         [  1+1];	/* NOT_DEF */
	varchar snd_err_hdr_comp_dsc       [  2+1];	/* NOT_DEF */
	varchar snd_err_bed_svc_nm         [ 16+1];	/* NOT_DEF */
	varchar tgrm_log_dsc               [  1+1];	/* NOT_DEF */
	varchar eaiid                      [ 32+1];	/* NOT_DEF */
	varchar bed_hdr_comp_dsc           [  2+1];	/* NOT_DEF */
	varchar ext_hdr_comp_dsc           [  2+1];	/* NOT_DEF */
	varchar hdr_rec_yn                 [  1+1];	/* NOT_DEF */
	varchar opn_dt                     [  8+1];	/* NOT_DEF */
	varchar chan_bsn_dept_c            [ 10+1];	/* NOT_DEF */
	varchar ap_code_nm                 [256+1];	/* NOT_DEF */
	varchar tgrm_mrl_id                [ 50+1];	/* NOT_DEF */
	varchar ext_chan_tgrm_id           [ 60+1];	/* NOT_DEF */
	varchar ext_snr_dsc                [  1+1];	/* NOT_DEF */
	varchar bed_chan_tgrm_id           [ 60+1];	/* NOT_DEF */
	varchar bed_snr_dsc                [  1+1];	/* NOT_DEF */
} TB_CLR_SVC_MST_PT;

#endif
