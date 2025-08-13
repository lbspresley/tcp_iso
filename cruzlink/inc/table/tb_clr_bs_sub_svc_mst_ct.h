/******************************************************************************
 화일명     : tb_clr_bs_sub_svc_mst_ct.h
 내용설명   : TB_CLR_BS_SUB_SVC_MST c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2011.01.17                  초기 작성
******************************************************************************/
#ifndef	__TB_CLR_BS_SUB_SVC_MST_CT_H__
#define	__TB_CLR_BS_SUB_SVC_MST_CT_H__

int  db_Insert_tb_clr_bs_sub_svc_mst(char *p_tstr);
int  db_Select_tb_clr_bs_sub_svc_mst(char *p_tstr);
int  db_Update_tb_clr_bs_sub_svc_mst(char *p_tstr);
void db_Disp_tb_clr_bs_sub_svc_mst(char *p_tstr);
void db_Init_tb_clr_bs_sub_svc_mst(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[ 32+1]; } ap_code;
	struct { unsigned short len; unsigned char arr[  1+1]; } trt_op_dsc;
	struct { unsigned short len; unsigned char arr[  9+1]; } input_gram_id;
	struct { unsigned short len; unsigned char arr[  2+1]; } input_gram_lwr_id;
} TB_CLR_BS_SUB_SVC_MST_CT;

#endif
