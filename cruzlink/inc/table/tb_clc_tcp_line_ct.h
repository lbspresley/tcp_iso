/******************************************************************************
 화일명     : tb_clc_tcp_line_ct.h
 내용설명   : TB_CLC_TCP_LINE c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_TCP_LINE_CT_H__
#define	__TB_CLC_TCP_LINE_CT_H__

int  db_Insert_tb_clc_tcp_line(char *p_tstr);
int  db_Select_tb_clc_tcp_line(char *p_tstr);
int  db_Update_tb_clc_tcp_line(char *p_tstr);
void db_Disp_tb_clc_tcp_line(char *p_tstr);
void db_Init_tb_clc_tcp_line(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[ 16+1]; } peer_ip;
	struct { unsigned short len; unsigned char arr[  2+1]; } node_no;
	struct { unsigned short len; unsigned char arr[ 16+1]; } line_speed;
	struct { unsigned short len; unsigned char arr[  4+1]; } ext_chan_id;
	struct { unsigned short len; unsigned char arr[  5+1]; } static_port;
	struct { unsigned short len; unsigned char arr[  5+1]; } dynamic_port;
	struct { unsigned short len; unsigned char arr[  3+1]; } com_mthd_dsc;
	int     sess_stat;
	struct { unsigned short len; unsigned char arr[  1+1]; } rs_mode;
	struct { unsigned short len; unsigned char arr[  8+1]; } stat_date;
	struct { unsigned short len; unsigned char arr[  6+1]; } stat_time;
} TB_CLC_TCP_LINE_CT;

#endif
