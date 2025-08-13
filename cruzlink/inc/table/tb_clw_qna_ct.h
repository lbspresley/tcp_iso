/******************************************************************************
 화일명     : tb_clw_qna_ct.h
 내용설명   : TB_CLW_QNA c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLW_QNA_CT_H__
#define	__TB_CLW_QNA_CT_H__

int  db_Insert_tb_clw_qna(char *p_tstr);
int  db_Select_tb_clw_qna(char *p_tstr);
int  db_Update_tb_clw_qna(char *p_tstr);
void db_Disp_tb_clw_qna(char *p_tstr);
void db_Init_tb_clw_qna(char *p_tstr);

typedef	struct
{
	int     qna_id;
	struct { unsigned short len; unsigned char arr[200+1]; } title;
	struct { unsigned short len; unsigned char arr[2000+1]; } contents;
	struct { unsigned short len; unsigned char arr[100+1]; } file_nm;
	struct { unsigned short len; unsigned char arr[200+1]; } file_path;
	int     view_cnt;
	int     top_qna_id;
	int     qna_step;
	int     qna_level;
	struct { unsigned short len; unsigned char arr[  8+1]; } reg_dt;
	struct { unsigned short len; unsigned char arr[ 14+1]; } upd_dt;
	struct { unsigned short len; unsigned char arr[  1+1]; } del_yn;
	struct { unsigned short len; unsigned char arr[ 13+1]; } reg_eno;
	struct { unsigned short len; unsigned char arr[ 13+1]; } mod_eno;
} TB_CLW_QNA_CT;

#endif
