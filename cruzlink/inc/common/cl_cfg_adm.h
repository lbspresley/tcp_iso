#ifndef __CL_CFG_ADM_H__
#define __CL_CFG_ADM_H__

typedef struct  {
	char adm_dsc               	   [4+32+1+1];	/*	±¸ºÐ°ª 	*/
	char ext_chan_id               [4+1];
	char ap_code                   [32+1];
	char trt_op_dsc                [1+1];
	char re_rs_dsc                 [1+1];
	char orgnm                     [50+1];
	char amn_tgrm_kdc              [1+1];
	char amn_tgrm_tms_tm           [6+1];
	char un_snd_obs_tm             [6+1];
	char strt_prc_tpc              [1+1];
	char node_no                   [2+1];
	char amn_tgrm_snr_tpc          [1+1];
	char snr_dt_prc_cd             [2+1];
	char bed_snd_yn                [1+1];
	char rg_dt                     [8+1];
	char rgmn_eno                  [9+1];
	char chan_bsn_dept_c           [10+1];
	char tgrm_mrl_id               [50+1];
	char ext_chan_tgrm_id          [60+1];
	char ext_snr_dsc               [1+1];
	char bed_chan_tgrm_id          [60+1];
	char bed_snr_dsc               [1+1];
} S_CL_CFG_ADM_INF;
#define CL_CFG_ADM_INF_LEN (sizeof(S_CL_CFG_ADM_INF))


#endif
