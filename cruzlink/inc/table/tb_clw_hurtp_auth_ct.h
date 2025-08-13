/******************************************************************************
 화일명     : tb_clw_hurtp_auth_ct.h
 내용설명   : TB_CLW_HURTP_AUTH c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLW_HURTP_AUTH_CT_H__
#define	__TB_CLW_HURTP_AUTH_CT_H__

int  db_Insert_tb_clw_hurtp_auth(char *p_tstr);
int  db_Select_tb_clw_hurtp_auth(char *p_tstr);
int  db_Update_tb_clw_hurtp_auth(char *p_tstr);
void db_Disp_tb_clw_hurtp_auth(char *p_tstr);
void db_Init_tb_clw_hurtp_auth(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  9+1]; } id;
	struct { unsigned short len; unsigned char arr[  1+1]; } gubun;
	struct { unsigned short len; unsigned char arr[  1+1]; } auth_type;
	int     grp_id;
} TB_CLW_HURTP_AUTH_CT;

#endif
