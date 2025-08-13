/******************************************************************************
 화일명     : tb_clc_svc_flow_mst_pt.h
 내용설명   : TB_CLC_SVC_FLOW_MST pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_SVC_FLOW_MST_PT_H__
#define	__TB_CLC_SVC_FLOW_MST_PT_H__

int  db_Insert_tb_clc_svc_flow_mst(char *p_tstr);
int  db_Select_tb_clc_svc_flow_mst(char *p_tstr);
int  db_Update_tb_clc_svc_flow_mst(char *p_tstr);
void db_Disp_tb_clc_svc_flow_mst(char *p_tstr);
void db_Init_tb_clc_svc_flow_mst(char *p_tstr);

typedef	struct
{
	varchar svc_flow_mst_dsc           [ 20+1];	/* NOT_DEF */
	int     svc_prc_sq                        ;	/* NOT_DEF */
	varchar ap_svc_nm                  [ 16+1];	/* NOT_DEF */
	varchar svc_kndc                   [  1+1];	/* NOT_DEF */
	varchar use_yn                     [  1+1];	/* NOT_DEF */
	varchar svc_flow_mst_nm            [256+1];	/* NOT_DEF */
	varchar chan_bsn_dept_c            [ 10+1];	/* NOT_DEF */
} TB_CLC_SVC_FLOW_MST_PT;

#endif
