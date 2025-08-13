/******************************************************************************
 화일명     : tb_clw_blbd_ct.h
 내용설명   : TB_CLW_BLBD c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLW_BLBD_CT_H__
#define	__TB_CLW_BLBD_CT_H__

int  db_Insert_tb_clw_blbd(char *p_tstr);
int  db_Select_tb_clw_blbd(char *p_tstr);
int  db_Update_tb_clw_blbd(char *p_tstr);
void db_Disp_tb_clw_blbd(char *p_tstr);
void db_Init_tb_clw_blbd(char *p_tstr);

typedef	struct
{
	int     blbd_sqno;
	struct { unsigned short len; unsigned char arr[  3+1]; } blbd_id;
	struct { unsigned short len; unsigned char arr[200+1]; } tit;
	struct { unsigned short len; unsigned char arr[2000+1]; } cntn;
	struct { unsigned short len; unsigned char arr[ 20+1]; } apdfl_nm;
	struct { unsigned short len; unsigned char arr[100+1]; } apdfl_path;
	int     inqmn_cnt;
	int     bup_rg_no;
	int     otxt_rg_no;
	int     lvl;
	struct { unsigned short len; unsigned char arr[ 24]; } drup_dtm;
	struct { unsigned short len; unsigned char arr[ 24]; } mod_dtm;
	struct { unsigned short len; unsigned char arr[  1+1]; } del_yn;
	struct { unsigned short len; unsigned char arr[  8+1]; } trdt;
	struct { unsigned short len; unsigned char arr[  6+1]; } trhr;
	struct { unsigned short len; unsigned char arr[  6+1]; } trbrc;
	struct { unsigned short len; unsigned char arr[ 13+1]; } bzno;
	struct { unsigned short len; unsigned char arr[  1+1]; } ans_yn;
	struct { unsigned short len; unsigned char arr[  8+1]; } ans_dt;
	struct { unsigned short len; unsigned char arr[ 13+1]; } reg_eno;
	struct { unsigned short len; unsigned char arr[ 13+1]; } mod_eno;
	struct { unsigned short len; unsigned char arr[ 13+1]; } ans_eno;
} TB_CLW_BLBD_CT;

#endif
