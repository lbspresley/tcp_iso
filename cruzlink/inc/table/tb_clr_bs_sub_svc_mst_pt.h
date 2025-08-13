/******************************************************************************
 화일명     : tb_clr_bs_sub_svc_mst_pt.h
 내용설명   : TB_CLR_BS_SUB_SVC_MST pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2011.01.17                  초기 작성
******************************************************************************/
#ifndef	__TB_CLR_BS_SUB_SVC_MST_PT_H__
#define	__TB_CLR_BS_SUB_SVC_MST_PT_H__

int  db_Insert_tb_clr_bs_sub_svc_mst(char *p_tstr);
int  db_Select_tb_clr_bs_sub_svc_mst(char *p_tstr);
int  db_Update_tb_clr_bs_sub_svc_mst(char *p_tstr);
void db_Disp_tb_clr_bs_sub_svc_mst(char *p_tstr);
void db_Init_tb_clr_bs_sub_svc_mst(char *p_tstr);

typedef	struct
{
	varchar ap_code                    [ 32+1];	/* NOT_DEF */
	varchar trt_op_dsc                 [  1+1];	/* NOT_DEF */
	varchar input_gram_id              [  9+1];	/* NOT_DEF */
	varchar input_gram_lwr_id          [  2+1];	/* NOT_DEF */
} TB_CLR_BS_SUB_SVC_MST_PT;

#endif
