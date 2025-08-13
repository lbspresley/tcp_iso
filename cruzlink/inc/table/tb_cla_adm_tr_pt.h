/******************************************************************************
 화일명     : tb_cla_adm_tr_pt.h
 내용설명   : TB_CLA_ADM_TR pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLA_ADM_TR_PT_H__
#define	__TB_CLA_ADM_TR_PT_H__

int  db_Insert_tb_cla_adm_tr(char *p_tstr);
int  db_Select_tb_cla_adm_tr(char *p_tstr);
int  db_Update_tb_cla_adm_tr(char *p_tstr);
void db_Disp_tb_cla_adm_tr(char *p_tstr);
void db_Init_tb_cla_adm_tr(char *p_tstr);

typedef	struct
{
	varchar amn_tgrm_tms_dt            [  8+1];	/* NOT_DEF */
	varchar ext_chan_id                [  4+1];	/* NOT_DEF */
	varchar ap_code                    [ 32+1];	/* NOT_DEF */
	varchar trt_op_dsc                 [  1+1];	/* NOT_DEF */
	int     amn_tgrm_rgno                     ;	/* NOT_DEF */
	varchar amn_tgrm_kdc               [  1+1];	/* NOT_DEF */
	varchar amn_tgrm_tms_tm            [  9+1];	/* NOT_DEF */
	varchar amn_tgrm_cntn              [2000+1];	/* NOT_DEF */
} TB_CLA_ADM_TR_PT;

#endif
