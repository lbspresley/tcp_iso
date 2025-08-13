/******************************************************************************
 화일명     : tb_cla_net_sts_tr_ct.h
 내용설명   : TB_CLA_NET_STS_TR c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLA_NET_STS_TR_CT_H__
#define	__TB_CLA_NET_STS_TR_CT_H__

int  db_Insert_tb_cla_net_sts_tr(char *p_tstr);
int  db_Select_tb_cla_net_sts_tr(char *p_tstr);
int  db_Update_tb_cla_net_sts_tr(char *p_tstr);
void db_Disp_tb_cla_net_sts_tr(char *p_tstr);
void db_Init_tb_cla_net_sts_tr(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  8+1]; } rg_dt;
	struct { unsigned short len; unsigned char arr[  4+1]; } ext_chan_id;
	int     rgsq;
	struct { unsigned short len; unsigned char arr[  6+1]; } mod_rg_tm;
	struct { unsigned short len; unsigned char arr[  2+1]; } net_sts_dsc;
} TB_CLA_NET_STS_TR_CT;

#endif
