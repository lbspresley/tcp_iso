/******************************************************************************
 화일명     : tb_clt_tr_ct.h
 내용설명   : TB_CLT_TR c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLT_TR_CT_H__
#define	__TB_CLT_TR_CT_H__

int  db_Insert_tb_clt_tr(char *p_tstr);
int  db_Select_tb_clt_tr(char *p_tstr);
int  db_Update_tb_clt_tr(char *p_tstr);
void db_Disp_tb_clt_tr(char *p_tstr);
void db_Init_tb_clt_tr(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  8+1]; } tr_dt;
	int     tst_tr_sqno;
	struct { unsigned short len; unsigned char arr[  4+1]; } chan_id;
	struct { unsigned short len; unsigned char arr[ 32+1]; } ap_code;
	struct { unsigned short len; unsigned char arr[  6+1]; } tst_tp_no;
	struct { unsigned short len; unsigned char arr[  6+1]; } tst_tm;
	struct { unsigned short len; unsigned char arr[ 32+1]; } ext_seq_cntn;
	struct { unsigned short len; unsigned char arr[ 60+1]; } ext_chan_tgrm_id;
	struct { unsigned short len; unsigned char arr[ 32+1]; } tst_tgrm_srch_cntn;
	struct { unsigned short len; unsigned char arr[4000+1]; } tst_tgrm_cntn1;
	struct { unsigned short len; unsigned char arr[4000+1]; } tst_tgrm_cntn2;
	struct { unsigned short len; unsigned char arr[4000+1]; } tst_tgrm_cntn3;
	struct { unsigned short len; unsigned char arr[4000+1]; } tst_tgrm_cntn4;
} TB_CLT_TR_CT;

#endif
