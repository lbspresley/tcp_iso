/******************************************************************************
 화일명     : tb_clc_x25_line_sts_pt.h
 내용설명   : TB_CLC_X25_LINE_STS pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_X25_LINE_STS_PT_H__
#define	__TB_CLC_X25_LINE_STS_PT_H__

int  db_Insert_tb_clc_x25_line_sts(char *p_tstr);
int  db_Select_tb_clc_x25_line_sts(char *p_tstr);
int  db_Update_tb_clc_x25_line_sts(char *p_tstr);
void db_Disp_tb_clc_x25_line_sts(char *p_tstr);
void db_Init_tb_clc_x25_line_sts(char *p_tstr);

typedef	struct
{
	varchar chan_id                    [  4+1];	/* NOT_DEF */
	varchar x25_line_nm                [  8+1];	/* NOT_DEF */
	varchar x25_link_id                [  8+1];	/* NOT_DEF */
	varchar mbnm                       [ 16+1];	/* NOT_DEF */
	varchar line_spd                   [ 16+1];	/* NOT_DEF */
	varchar int_line_no                [ 16+1];	/* NOT_DEF */
	varchar ext_line_no                [ 16+1];	/* NOT_DEF */
	varchar x25_pad                    [ 16+1];	/* NOT_DEF */
	varchar x25_slot                   [ 16+1];	/* NOT_DEF */
	varchar x25_port                   [ 16+1];	/* NOT_DEF */
	varchar x25_port_type              [  3+1];	/* NOT_DEF */
	varchar port_stsc                  [  1+1];	/* NOT_DEF */
} TB_CLC_X25_LINE_STS_PT;

#endif
