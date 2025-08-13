/******************************************************************************
 화일명     : tb_clw_grtp_auth_ct.h
 내용설명   : TB_CLW_GRTP_AUTH c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLW_GRTP_AUTH_CT_H__
#define	__TB_CLW_GRTP_AUTH_CT_H__

int  db_Insert_tb_clw_grtp_auth(char *p_tstr);
int  db_Select_tb_clw_grtp_auth(char *p_tstr);
int  db_Update_tb_clw_grtp_auth(char *p_tstr);
void db_Disp_tb_clw_grtp_auth(char *p_tstr);
void db_Init_tb_clw_grtp_auth(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[ 10+1]; } grp_id;
	struct { unsigned short len; unsigned char arr[ 50+1]; } grp_nm;
	struct { unsigned short len; unsigned char arr[  2+1]; } auth_type;
	struct { unsigned short len; unsigned char arr[  1+1]; } use_yn;
	struct { unsigned short len; unsigned char arr[  9+1]; } drumn_eno;
	struct { unsigned short len; unsigned char arr[ 24]; } drup_dtm;
	struct { unsigned short len; unsigned char arr[  9+1]; } modmn_eno;
	struct { unsigned short len; unsigned char arr[ 24]; } mod_dtm;
} TB_CLW_GRTP_AUTH_CT;

#endif
