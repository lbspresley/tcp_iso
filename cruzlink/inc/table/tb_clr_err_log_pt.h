/******************************************************************************
 화일명     : tb_clr_err_log_pt.h
 내용설명   : TB_CLR_ERR_LOG pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLR_ERR_LOG_PT_H__
#define	__TB_CLR_ERR_LOG_PT_H__

int  db_Insert_tb_clr_err_log(char *p_tstr);
int  db_Select_tb_clr_err_log(char *p_tstr);
int  db_Update_tb_clr_err_log(char *p_tstr);
void db_Disp_tb_clr_err_log(char *p_tstr);
void db_Init_tb_clr_err_log(char *p_tstr);

typedef	struct
{
	varchar tr_dd                      [  2+1];	/* NOT_DEF */
	varchar tr_dt                      [  8+1];	/* NOT_DEF */
	int     err_log_sqno                      ;	/* NOT_DEF */
	int     data_trx_sqno                     ;	/* NOT_DEF */
	varchar fst_ap_code                [ 32+1];	/* NOT_DEF */
	varchar ap_code                    [ 32+1];	/* NOT_DEF */
	varchar trt_op_dsc                 [  1+1];	/* NOT_DEF */
	varchar re_rs_dsc                  [  1+1];	/* NOT_DEF */
	varchar ext_chan_id                [  4+1];	/* NOT_DEF */
	varchar bed_chan_id                [  4+1];	/* NOT_DEF */
	varchar biz_dtl_dsc                [ 12+1];	/* NOT_DEF */
	int     mst_trx_sqno                      ;	/* NOT_DEF */
	varchar trt_rzt_c                  [  4+1];	/* NOT_DEF */
	varchar trt_tm                     [  9+1];	/* NOT_DEF */
	varchar node_no                    [  2+1];	/* NOT_DEF */
	varchar issue_svc_nm               [ 16+1];	/* NOT_DEF */
	varchar issue_svc_kndc             [  1+1];	/* NOT_DEF */
	varchar biz_seq_cntn               [ 32+1];	/* NOT_DEF */
	varchar ext_seq_cntn               [ 32+1];	/* NOT_DEF */
	varchar err_cntn                   [1024+1];	/* NOT_DEF */
	int     head_len                          ;	/* NOT_DEF */
	int     data_len                          ;	/* NOT_DEF */
	varchar head_cntn                  [1024+1];	/* NOT_DEF */
	varchar data_cntn                  [4000+1];	/* NOT_DEF */
} TB_CLR_ERR_LOG_PT;

#endif
