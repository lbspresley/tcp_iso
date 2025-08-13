/******************************************************************************
 화일명     : tb_cla_adm_tgrm_ct.h
 내용설명   : TB_CLA_ADM_TGRM c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLA_ADM_TGRM_CT_H__
#define	__TB_CLA_ADM_TGRM_CT_H__

int  db_Insert_tb_cla_adm_tgrm(char *p_tstr);
int  db_Select_tb_cla_adm_tgrm(char *p_tstr);
int  db_Update_tb_cla_adm_tgrm(char *p_tstr);
void db_Disp_tb_cla_adm_tgrm(char *p_tstr);
void db_Init_tb_cla_adm_tgrm(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  4+1]; } ext_chan_id;
	struct { unsigned short len; unsigned char arr[ 32+1]; } ap_code;
	struct { unsigned short len; unsigned char arr[  1+1]; } trt_op_dsc;
	struct { unsigned short len; unsigned char arr[  1+1]; } re_rs_dsc;
	struct { unsigned short len; unsigned char arr[ 50+1]; } orgnm;
	struct { unsigned short len; unsigned char arr[  1+1]; } amn_tgrm_kdc;
	struct { unsigned short len; unsigned char arr[  6+1]; } amn_tgrm_tms_tm;
	struct { unsigned short len; unsigned char arr[  6+1]; } un_snd_obs_tm;
	struct { unsigned short len; unsigned char arr[  1+1]; } strt_prc_tpc;
	struct { unsigned short len; unsigned char arr[  2+1]; } node_no;
	struct { unsigned short len; unsigned char arr[  1+1]; } amn_tgrm_snr_tpc;
	struct { unsigned short len; unsigned char arr[  2+1]; } snr_dt_prc_cd;
	struct { unsigned short len; unsigned char arr[  1+1]; } bed_snd_yn;
	struct { unsigned short len; unsigned char arr[  8+1]; } rg_dt;
	struct { unsigned short len; unsigned char arr[  9+1]; } rgmn_eno;
	struct { unsigned short len; unsigned char arr[ 10+1]; } chan_bsn_dept_c;
	struct { unsigned short len; unsigned char arr[ 50+1]; } tgrm_mrl_id;
	struct { unsigned short len; unsigned char arr[ 60+1]; } ext_chan_tgrm_id;
	struct { unsigned short len; unsigned char arr[  1+1]; } ext_snr_dsc;
	struct { unsigned short len; unsigned char arr[ 60+1]; } bed_chan_tgrm_id;
	struct { unsigned short len; unsigned char arr[  1+1]; } bed_snr_dsc;
} TB_CLA_ADM_TGRM_CT;

#endif
