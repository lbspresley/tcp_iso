/******************************************************************************
 화일명     : tb_clc_line_sts_ct.h
 내용설명   : TB_CLC_LINE_STS c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_LINE_STS_CT_H__
#define	__TB_CLC_LINE_STS_CT_H__

int  db_Insert_tb_clc_line_sts(char *p_tstr);
int  db_Select_tb_clc_line_sts(char *p_tstr);
int  db_Update_tb_clc_line_sts(char *p_tstr);
void db_Disp_tb_clc_line_sts(char *p_tstr);
void db_Init_tb_clc_line_sts(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[ 16+1]; } adt_nm;
	struct { unsigned short len; unsigned char arr[  1+1]; } adt_stsc;
	struct { unsigned short len; unsigned char arr[  1+1]; } line_stsc;
	struct { unsigned short len; unsigned char arr[  1+1]; } buf_stsc;
	struct { unsigned short len; unsigned char arr[  3+1]; } com_mthd_dsc;
	struct { unsigned short len; unsigned char arr[256+1]; } chan_knm;
	struct { unsigned short len; unsigned char arr[  1+1]; } chan_dirc_dsc;
	struct { unsigned short len; unsigned char arr[  4+1]; } chan_id;
	struct { unsigned short len; unsigned char arr[  2+1]; } node_no;
	struct { unsigned short len; unsigned char arr[  6+1]; } adm_bizc;
} TB_CLC_LINE_STS_CT;

#endif
