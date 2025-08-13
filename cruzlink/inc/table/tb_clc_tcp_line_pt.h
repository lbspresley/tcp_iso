/******************************************************************************
 화일명     : tb_clc_tcp_line_pt.h
 내용설명   : TB_CLC_TCP_LINE pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_TCP_LINE_PT_H__
#define	__TB_CLC_TCP_LINE_PT_H__

int  db_Insert_tb_clc_tcp_line(char *p_tstr);
int  db_Select_tb_clc_tcp_line(char *p_tstr);
int  db_Update_tb_clc_tcp_line(char *p_tstr);
void db_Disp_tb_clc_tcp_line(char *p_tstr);
void db_Init_tb_clc_tcp_line(char *p_tstr);

typedef	struct
{
	varchar peer_ip                    [ 16+1];	/* NOT_DEF */
	varchar node_no                    [  2+1];	/* NOT_DEF */
	varchar line_speed                 [ 16+1];	/* NOT_DEF */
	varchar ext_chan_id                [  4+1];	/* NOT_DEF */
	varchar static_port                [  5+1];	/* NOT_DEF */
	varchar dynamic_port               [  5+1];	/* NOT_DEF */
	varchar com_mthd_dsc               [  3+1];	/* NOT_DEF */
	int     sess_stat                         ;	/* NOT_DEF */
	varchar rs_mode                    [  1+1];	/* NOT_DEF */
	varchar stat_date                  [  8+1];	/* NOT_DEF */
	varchar stat_time                  [  6+1];	/* NOT_DEF */
} TB_CLC_TCP_LINE_PT;

#endif
