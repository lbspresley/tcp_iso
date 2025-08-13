/******************************************************************************
 화일명     : tb_cla_adm_tgrm_pt.h
 내용설명   : TB_CLA_ADM_TGRM pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLA_ADM_TGRM_PT_H__
#define	__TB_CLA_ADM_TGRM_PT_H__

int  db_Insert_tb_cla_adm_tgrm(char *p_tstr);
int  db_Select_tb_cla_adm_tgrm(char *p_tstr);
int  db_Update_tb_cla_adm_tgrm(char *p_tstr);
void db_Disp_tb_cla_adm_tgrm(char *p_tstr);
void db_Init_tb_cla_adm_tgrm(char *p_tstr);

typedef	struct
{
	varchar ext_chan_id                [  4+1];	/* NOT_DEF */
	varchar ap_code                    [ 32+1];	/* NOT_DEF */
	varchar trt_op_dsc                 [  1+1];	/* NOT_DEF */
	varchar re_rs_dsc                  [  1+1];	/* NOT_DEF */
	varchar orgnm                      [ 50+1];	/* NOT_DEF */
	varchar amn_tgrm_kdc               [  1+1];	/* NOT_DEF */
	varchar amn_tgrm_tms_tm            [  6+1];	/* NOT_DEF */
	varchar un_snd_obs_tm              [  6+1];	/* NOT_DEF */
	varchar strt_prc_tpc               [  1+1];	/* NOT_DEF */
	varchar node_no                    [  2+1];	/* NOT_DEF */
	varchar amn_tgrm_snr_tpc           [  1+1];	/* NOT_DEF */
	varchar snr_dt_prc_cd              [  2+1];	/* NOT_DEF */
	varchar bed_snd_yn                 [  1+1];	/* NOT_DEF */
	varchar rg_dt                      [  8+1];	/* NOT_DEF */
	varchar rgmn_eno                   [  9+1];	/* NOT_DEF */
	varchar chan_bsn_dept_c            [ 10+1];	/* NOT_DEF */
	varchar tgrm_mrl_id                [ 50+1];	/* NOT_DEF */
	varchar ext_chan_tgrm_id           [ 60+1];	/* NOT_DEF */
	varchar ext_snr_dsc                [  1+1];	/* NOT_DEF */
	varchar bed_chan_tgrm_id           [ 60+1];	/* NOT_DEF */
	varchar bed_snr_dsc                [  1+1];	/* NOT_DEF */
} TB_CLA_ADM_TGRM_PT;

#endif
