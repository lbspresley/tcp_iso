/******************************************************************************
 화일명     : tb_clc_line_sts_pt.h
 내용설명   : TB_CLC_LINE_STS pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_LINE_STS_PT_H__
#define	__TB_CLC_LINE_STS_PT_H__

int  db_Insert_tb_clc_line_sts(char *p_tstr);
int  db_Select_tb_clc_line_sts(char *p_tstr);
int  db_Update_tb_clc_line_sts(char *p_tstr);
void db_Disp_tb_clc_line_sts(char *p_tstr);
void db_Init_tb_clc_line_sts(char *p_tstr);

typedef	struct
{
	varchar adt_nm                     [ 16+1];	/* NOT_DEF */
	varchar adt_stsc                   [  1+1];	/* NOT_DEF */
	varchar line_stsc                  [  1+1];	/* NOT_DEF */
	varchar buf_stsc                   [  1+1];	/* NOT_DEF */
	varchar com_mthd_dsc               [  3+1];	/* NOT_DEF */
	varchar chan_knm                   [256+1];	/* NOT_DEF */
	varchar chan_dirc_dsc              [  1+1];	/* NOT_DEF */
	varchar chan_id                    [  4+1];	/* NOT_DEF */
	varchar node_no                    [  2+1];	/* NOT_DEF */
	varchar adm_bizc                   [  6+1];	/* NOT_DEF */
} TB_CLC_LINE_STS_PT;

#endif
