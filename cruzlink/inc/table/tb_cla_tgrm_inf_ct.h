/******************************************************************************
 화일명     : tb_cla_tgrm_inf_ct.h
 내용설명   : TB_CLA_TGRM_INF c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLA_TGRM_INF_CT_H__
#define	__TB_CLA_TGRM_INF_CT_H__

int  db_Insert_tb_cla_tgrm_inf(char *p_tstr);
int  db_Select_tb_cla_tgrm_inf(char *p_tstr);
int  db_Update_tb_cla_tgrm_inf(char *p_tstr);
void db_Disp_tb_cla_tgrm_inf(char *p_tstr);
void db_Init_tb_cla_tgrm_inf(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  4+1]; } ext_chan_id;
	struct { unsigned short len; unsigned char arr[  1+1]; } amn_tgrm_kdc;
	struct { unsigned short len; unsigned char arr[ 10+1]; } amn_tgrm_fild_sqno;
	struct { unsigned short len; unsigned char arr[ 20+1]; } amn_tgrm_fildnm;
	struct { unsigned short len; unsigned char arr[  2+1]; } amn_tgrm_fild_tpc;
	int     amn_tgrm_fild_pos;
	int     amn_tgrm_fild_len;
	struct { unsigned short len; unsigned char arr[  8+1]; } amn_tgrm_fild_tpby_kndc;
	struct { unsigned short len; unsigned char arr[  1+1]; } amn_tgrm_fild_kndc;
	int     amn_tgrm_copy_pos;
	int     amn_tgrm_copy_len;
	struct { unsigned short len; unsigned char arr[4000+1]; } amn_fild_dgn_cntn;
} TB_CLA_TGRM_INF_CT;

#endif
