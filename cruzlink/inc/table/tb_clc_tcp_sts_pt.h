/******************************************************************************
 화일명     : tb_clc_tcp_sts_pt.h
 내용설명   : TB_CLC_TCP_STS pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_TCP_STS_PT_H__
#define	__TB_CLC_TCP_STS_PT_H__

int  db_Insert_tb_clc_tcp_sts(char *p_tstr);
int  db_Select_tb_clc_tcp_sts(char *p_tstr);
int  db_Update_tb_clc_tcp_sts(char *p_tstr);
void db_Disp_tb_clc_tcp_sts(char *p_tstr);
void db_Init_tb_clc_tcp_sts(char *p_tstr);

typedef	struct
{
	varchar chan_id                    [  4+1];	/* NOT_DEF */
	varchar adt_nm                     [ 16+1];	/* NOT_DEF */
	int     sess_sqno                         ;	/* NOT_DEF */
	varchar ext_ip                     [ 20+1];	/* NOT_DEF */
	int     ext_port                          ;	/* NOT_DEF */
	int     local_port                        ;	/* NOT_DEF */
	varchar conn_drct_c                [  1+1];	/* NOT_DEF */
	varchar conn_sts_dsc               [  1+1];	/* NOT_DEF */
	int     rsof_fd_no                        ;	/* NOT_DEF */
	varchar conn_tpc                   [  1+1];	/* NOT_DEF */
	int     conn_try_cnt                      ;	/* NOT_DEF */
	int     cls_try_cnt                       ;	/* NOT_DEF */
	varchar conn_tm                    [  6+1];	/* NOT_DEF */
	varchar cls_tm                     [  6+1];	/* NOT_DEF */
	varchar conn_td                    [  8+1];	/* NOT_DEF */
	varchar cls_td                     [  8+1];	/* NOT_DEF */
} TB_CLC_TCP_STS_PT;

#endif
