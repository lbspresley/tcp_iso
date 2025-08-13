/******************************************************************************
 화일명     : tb_clr_mis_sq_cntn_pt.h
 내용설명   : TB_CLR_MIS_SQ_CNTN pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLR_MIS_SQ_CNTN_PT_H__
#define	__TB_CLR_MIS_SQ_CNTN_PT_H__

int  db_Insert_tb_clr_mis_sq_cntn(char *p_tstr);
int  db_Select_tb_clr_mis_sq_cntn(char *p_tstr);
int  db_Update_tb_clr_mis_sq_cntn(char *p_tstr);
void db_Disp_tb_clr_mis_sq_cntn(char *p_tstr);
void db_Init_tb_clr_mis_sq_cntn(char *p_tstr);

typedef	struct
{
	varchar tr_dd                      [  2+1];	/* NOT_DEF */
	varchar trt_dt                     [  8+1];	/* NOT_DEF */
	varchar ext_chan_id                [  4+1];	/* NOT_DEF */
	varchar trt_op_dsc                 [  1+1];	/* NOT_DEF */
	int     tgrm_prc_sq                       ;	/* NOT_DEF */
	varchar prc_sq_dsc                 [  1+1];	/* NOT_DEF */
} TB_CLR_MIS_SQ_CNTN_PT;

#endif
