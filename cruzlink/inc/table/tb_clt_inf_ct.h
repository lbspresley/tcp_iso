/******************************************************************************
 화일명     : tb_clt_inf_ct.h
 내용설명   : TB_CLT_INF c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLT_INF_CT_H__
#define	__TB_CLT_INF_CT_H__

int  db_Insert_tb_clt_inf(char *p_tstr);
int  db_Select_tb_clt_inf(char *p_tstr);
int  db_Update_tb_clt_inf(char *p_tstr);
void db_Disp_tb_clt_inf(char *p_tstr);
void db_Init_tb_clt_inf(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  4+1]; } chan_id;
	struct { unsigned short len; unsigned char arr[  6+1]; } tst_tp_no;
	struct { unsigned short len; unsigned char arr[ 20+1]; } tstnm;
	struct { unsigned short len; unsigned char arr[ 32+1]; } ap_code;
	struct { unsigned short len; unsigned char arr[100+1]; } tst_expl;
	struct { unsigned short len; unsigned char arr[  1+1]; } tst_kdtc;
	struct { unsigned short len; unsigned char arr[  1+1]; } log_strg_yn;
	struct { unsigned short len; unsigned char arr[ 50+1]; } tst_rqr_flnm;
	struct { unsigned short len; unsigned char arr[  1+1]; } tgrm_cstt_metc;
	struct { unsigned short len; unsigned char arr[  2+1]; } cft_rsp_dsc;
	int     delay_rsp_sec;
	struct { unsigned short len; unsigned char arr[  1+1]; } tst_inf_uyn;
	struct { unsigned short len; unsigned char arr[ 14+1]; } rg_dtm;
	struct { unsigned short len; unsigned char arr[ 20+1]; } rgmn_eno;
} TB_CLT_INF_CT;

#endif
