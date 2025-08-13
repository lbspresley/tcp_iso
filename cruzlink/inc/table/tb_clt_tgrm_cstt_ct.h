/******************************************************************************
 화일명     : tb_clt_tgrm_cstt_ct.h
 내용설명   : TB_CLT_TGRM_CSTT c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLT_TGRM_CSTT_CT_H__
#define	__TB_CLT_TGRM_CSTT_CT_H__

int  db_Insert_tb_clt_tgrm_cstt(char *p_tstr);
int  db_Select_tb_clt_tgrm_cstt(char *p_tstr);
int  db_Update_tb_clt_tgrm_cstt(char *p_tstr);
void db_Disp_tb_clt_tgrm_cstt(char *p_tstr);
void db_Init_tb_clt_tgrm_cstt(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  4+1]; } chan_id;
	struct { unsigned short len; unsigned char arr[  6+1]; } tst_tp_no;
	int     tst_tgrm_id_sqno;
	int     tp_id_loc_cn;
	int     tp_id_len;
	struct { unsigned short len; unsigned char arr[ 10+1]; } tp_id_val;
} TB_CLT_TGRM_CSTT_CT;

#endif
