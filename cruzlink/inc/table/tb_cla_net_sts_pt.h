/******************************************************************************
 화일명     : tb_cla_net_sts_pt.h
 내용설명   : TB_CLA_NET_STS pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLA_NET_STS_PT_H__
#define	__TB_CLA_NET_STS_PT_H__

int  db_Insert_tb_cla_net_sts(char *p_tstr);
int  db_Select_tb_cla_net_sts(char *p_tstr);
int  db_Update_tb_cla_net_sts(char *p_tstr);
void db_Disp_tb_cla_net_sts(char *p_tstr);
void db_Init_tb_cla_net_sts(char *p_tstr);

typedef	struct
{
	varchar ext_chan_id                [  4+1];	/* NOT_DEF */
	varchar rg_dt                      [  8+1];	/* NOT_DEF */
	varchar mod_rg_tm                  [  6+1];	/* NOT_DEF */
	varchar net_sts_dsc                [  2+1];	/* NOT_DEF */
} TB_CLA_NET_STS_PT;

#endif
