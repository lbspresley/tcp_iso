/******************************************************************************
 화일명     : tb_clc_tcp_sts_ct.h
 내용설명   : TB_CLC_TCP_STS c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_TCP_STS_CT_H__
#define	__TB_CLC_TCP_STS_CT_H__

int  db_Insert_tb_clc_tcp_sts(char *p_tstr);
int  db_Select_tb_clc_tcp_sts(char *p_tstr);
int  db_Update_tb_clc_tcp_sts(char *p_tstr);
void db_Disp_tb_clc_tcp_sts(char *p_tstr);
void db_Init_tb_clc_tcp_sts(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  4+1]; } chan_id;
	struct { unsigned short len; unsigned char arr[ 16+1]; } adt_nm;
	int     sess_sqno;
	struct { unsigned short len; unsigned char arr[ 20+1]; } ext_ip;
	int     ext_port;
	int     local_port;
	struct { unsigned short len; unsigned char arr[  1+1]; } conn_drct_c;
	struct { unsigned short len; unsigned char arr[  1+1]; } conn_sts_dsc;
	int     rsof_fd_no;
	struct { unsigned short len; unsigned char arr[  1+1]; } conn_tpc;
	int     conn_try_cnt;
	int     cls_try_cnt;
	struct { unsigned short len; unsigned char arr[  6+1]; } conn_tm;
	struct { unsigned short len; unsigned char arr[  6+1]; } cls_tm;
	struct { unsigned short len; unsigned char arr[  8+1]; } conn_td;
	struct { unsigned short len; unsigned char arr[  8+1]; } cls_td;
} TB_CLC_TCP_STS_CT;

#endif
