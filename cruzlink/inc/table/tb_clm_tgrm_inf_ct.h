/******************************************************************************
 화일명     : tb_clm_tgrm_inf_ct.h
 내용설명   : TB_CLM_TGRM_INF c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLM_TGRM_INF_CT_H__
#define	__TB_CLM_TGRM_INF_CT_H__

int  db_Insert_tb_clm_tgrm_inf(char *p_tstr);
int  db_Select_tb_clm_tgrm_inf(char *p_tstr);
int  db_Update_tb_clm_tgrm_inf(char *p_tstr);
void db_Disp_tb_clm_tgrm_inf(char *p_tstr);
void db_Init_tb_clm_tgrm_inf(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[ 32+1]; } clm_ap_code;
	struct { unsigned short len; unsigned char arr[  4+1]; } ext_chan_id;
	struct { unsigned short len; unsigned char arr[  1+1]; } inp_snr_dsc;
	struct { unsigned short len; unsigned char arr[ 60+1]; } inp_chan_tgrm_id;
	struct { unsigned short len; unsigned char arr[  1+1]; } clm_sr_dsc;
	struct { unsigned short len; unsigned char arr[ 50+1]; } tgrm_mrl_id;
	struct { unsigned short len; unsigned char arr[ 60+1]; } otp_chan_tgrm_id;
	struct { unsigned short len; unsigned char arr[  1+1]; } otp_snr_dsc;
} TB_CLM_TGRM_INF_CT;

#endif
