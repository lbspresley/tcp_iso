/******************************************************************************
 화일명     : tb_clm_tgrm_dtl_pt.h
 내용설명   : TB_CLM_TGRM_DTL pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLM_TGRM_DTL_PT_H__
#define	__TB_CLM_TGRM_DTL_PT_H__

int  db_Insert_tb_clm_tgrm_dtl(char *p_tstr);
int  db_Select_tb_clm_tgrm_dtl(char *p_tstr);
int  db_Update_tb_clm_tgrm_dtl(char *p_tstr);
void db_Disp_tb_clm_tgrm_dtl(char *p_tstr);
void db_Init_tb_clm_tgrm_dtl(char *p_tstr);

typedef	struct
{
	varchar clm_ap_code                [ 32+1];	/* NOT_DEF */
	varchar ext_chan_id                [  4+1];	/* NOT_DEF */
	varchar inp_chan_tgrm_id           [ 60+1];	/* NOT_DEF */
	varchar inp_snr_dsc                [  1+1];	/* NOT_DEF */
	int     clm_tgrm_cstt_sq                  ;	/* NOT_DEF */
	varchar clm_sr_dsc                 [  1+1];	/* NOT_DEF */
	varchar clm_tgrm_fld_dsc           [  2+1];	/* NOT_DEF */
	varchar clm_tgrm_fldnm             [ 32+1];	/* NOT_DEF */
	int     clm_tgrm_pos                      ;	/* NOT_DEF */
	int     clm_tgrm_len                      ;	/* NOT_DEF */
	varchar clm_tgrm_fld_cntn          [256+1];	/* NOT_DEF */
	varchar clm_tgrm_fld_kndc          [  1+1];	/* NOT_DEF */
} TB_CLM_TGRM_DTL_PT;

#endif
