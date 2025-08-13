/******************************************************************************
 화일명     : tb_clw_qna_pt.h
 내용설명   : TB_CLW_QNA pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLW_QNA_PT_H__
#define	__TB_CLW_QNA_PT_H__

int  db_Insert_tb_clw_qna(char *p_tstr);
int  db_Select_tb_clw_qna(char *p_tstr);
int  db_Update_tb_clw_qna(char *p_tstr);
void db_Disp_tb_clw_qna(char *p_tstr);
void db_Init_tb_clw_qna(char *p_tstr);

typedef	struct
{
	int     qna_id                            ;	/* NOT_DEF */
	varchar title                      [200+1];	/* NOT_DEF */
	varchar contents                   [2000+1];	/* NOT_DEF */
	varchar file_nm                    [100+1];	/* NOT_DEF */
	varchar file_path                  [200+1];	/* NOT_DEF */
	int     view_cnt                          ;	/* NOT_DEF */
	int     top_qna_id                        ;	/* NOT_DEF */
	int     qna_step                          ;	/* NOT_DEF */
	int     qna_level                         ;	/* NOT_DEF */
	varchar reg_dt                     [  8+1];	/* NOT_DEF */
	varchar upd_dt                     [ 14+1];	/* NOT_DEF */
	varchar del_yn                     [  1+1];	/* NOT_DEF */
	varchar reg_eno                    [ 13+1];	/* NOT_DEF */
	varchar mod_eno                    [ 13+1];	/* NOT_DEF */
} TB_CLW_QNA_PT;

#endif
