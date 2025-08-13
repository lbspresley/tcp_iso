/******************************************************************************
 화일명     : tb_clc_x25_lu_sts_ct.h
 내용설명   : TB_CLC_X25_LU_STS c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_X25_LU_STS_CT_H__
#define	__TB_CLC_X25_LU_STS_CT_H__

int  db_Insert_tb_clc_x25_lu_sts(char *p_tstr);
int  db_Select_tb_clc_x25_lu_sts(char *p_tstr);
int  db_Update_tb_clc_x25_lu_sts(char *p_tstr);
void db_Disp_tb_clc_x25_lu_sts(char *p_tstr);
void db_Init_tb_clc_x25_lu_sts(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  4+1]; } chan_id;
	struct { unsigned short len; unsigned char arr[  8+1]; } x25_line_nm;
	struct { unsigned short len; unsigned char arr[  8+1]; } x25_lu;
	struct { unsigned short len; unsigned char arr[  8+1]; } trx_x25_lcn;
	int     sess_stsc;
	struct { unsigned short len; unsigned char arr[  1+1]; } rs_dsc;
	struct { unsigned short len; unsigned char arr[  8+1]; } sts_mod_dt;
	struct { unsigned short len; unsigned char arr[  6+1]; } sts_mod_tm;
} TB_CLC_X25_LU_STS_CT;

#endif
