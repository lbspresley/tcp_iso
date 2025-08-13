/******************************************************************************
 화일명     : tb_clw_pgm_inf_ct.h
 내용설명   : TB_CLW_PGM_INF c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLW_PGM_INF_CT_H__
#define	__TB_CLW_PGM_INF_CT_H__

int  db_Insert_tb_clw_pgm_inf(char *p_tstr);
int  db_Select_tb_clw_pgm_inf(char *p_tstr);
int  db_Update_tb_clw_pgm_inf(char *p_tstr);
void db_Disp_tb_clw_pgm_inf(char *p_tstr);
void db_Init_tb_clw_pgm_inf(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  5+1]; } pgm_id;
	struct { unsigned short len; unsigned char arr[  1+1]; } use_yn;
	struct { unsigned short len; unsigned char arr[ 50+1]; } pgm_nm;
	struct { unsigned short len; unsigned char arr[ 20+1]; } menu_id;
	struct { unsigned short len; unsigned char arr[100+1]; } pgm_path;
	int     sort_sqno;
	struct { unsigned short len; unsigned char arr[100+1]; } pgm_img_fl;
	struct { unsigned short len; unsigned char arr[ 24]; } drup_dtm;
	struct { unsigned short len; unsigned char arr[ 24]; } mod_dtm;
	struct { unsigned short len; unsigned char arr[ 13+1]; } reg_eno;
	struct { unsigned short len; unsigned char arr[ 13+1]; } mod_eno;
} TB_CLW_PGM_INF_CT;

#endif
