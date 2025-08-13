/******************************************************************************
 화일명     : tb_clc_bat_tr_pt.h
 내용설명   : TB_CLC_BAT_TR pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_BAT_TR_PT_H__
#define	__TB_CLC_BAT_TR_PT_H__

int  db_Insert_tb_clc_bat_tr(char *p_tstr);
int  db_Select_tb_clc_bat_tr(char *p_tstr);
int  db_Update_tb_clc_bat_tr(char *p_tstr);
void db_Disp_tb_clc_bat_tr(char *p_tstr);
void db_Init_tb_clc_bat_tr(char *p_tstr);

typedef	struct
{
	int     bat_no                            ;	/* NOT_DEF */
	int     bat_rsv_reg_sqno                  ;	/* NOT_DEF */
	varchar node_no                    [  2+1];	/* NOT_DEF */
	varchar bat_prc_rsv_dt             [  8+1];	/* NOT_DEF */
	varchar bat_prc_rsv_tm             [  6+1];	/* NOT_DEF */
	varchar bat_prc_mthdc              [  2+1];	/* NOT_DEF */
	varchar bat_prc_svcnm              [ 16+1];	/* NOT_DEF */
	varchar bat_call_cmd_cntn          [256+1];	/* NOT_DEF */
	varchar bat_err_prc_svcnm          [ 16+1];	/* NOT_DEF */
	varchar bat_err_prc_tm             [  6+1];	/* NOT_DEF */
	varchar sms_snd_yn                 [  1+1];	/* NOT_DEF */
	int     bf_bat_no                         ;	/* NOT_DEF */
	varchar bat_tr_dt                  [  8+1];	/* NOT_DEF */
	varchar bat_prc_tm                 [  6+1];	/* NOT_DEF */
	varchar bat_prc_rzt_c              [  4+1];	/* NOT_DEF */
	varchar bat_call_tgrm_cntn         [256+1];	/* NOT_DEF */
} TB_CLC_BAT_TR_PT;

#endif
