/******************************************************************************
 화일명     : tb_clt_tgrm_inf_ct.h
 내용설명   : TB_CLT_TGRM_INF c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLT_TGRM_INF_CT_H__
#define	__TB_CLT_TGRM_INF_CT_H__

int  db_Insert_tb_clt_tgrm_inf(char *p_tstr);
int  db_Select_tb_clt_tgrm_inf(char *p_tstr);
int  db_Update_tb_clt_tgrm_inf(char *p_tstr);
void db_Disp_tb_clt_tgrm_inf(char *p_tstr);
void db_Init_tb_clt_tgrm_inf(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  4+1]; } chan_id;
	struct { unsigned short len; unsigned char arr[  6+1]; } tst_tp_no;
	struct { unsigned short len; unsigned char arr[ 10+1]; } tst_tgrm_fild_sqno;
	struct { unsigned short len; unsigned char arr[ 20+1]; } tst_tgrm_fildnm;
	struct { unsigned short len; unsigned char arr[  2+1]; } tst_tgrm_fild_tpc;
	int     tst_tgrm_fild_loc_cn;
	int     tst_tgrm_fild_len;
	struct { unsigned short len; unsigned char arr[  8+1]; } tst_tgrm_fild_tpby_attr_c;
	int     org_tgrm_cp_pos;
	int     org_tgrm_cp_len;
	struct { unsigned short len; unsigned char arr[4000+1]; } tst_fild_dgn_cntn;
} TB_CLT_TGRM_INF_CT;

#endif
