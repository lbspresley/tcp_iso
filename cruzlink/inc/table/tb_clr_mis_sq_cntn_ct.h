/******************************************************************************
 화일명     : tb_clr_mis_sq_cntn_ct.h
 내용설명   : TB_CLR_MIS_SQ_CNTN c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLR_MIS_SQ_CNTN_CT_H__
#define	__TB_CLR_MIS_SQ_CNTN_CT_H__

int  db_Insert_tb_clr_mis_sq_cntn(char *p_tstr);
int  db_Select_tb_clr_mis_sq_cntn(char *p_tstr);
int  db_Update_tb_clr_mis_sq_cntn(char *p_tstr);
void db_Disp_tb_clr_mis_sq_cntn(char *p_tstr);
void db_Init_tb_clr_mis_sq_cntn(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  2+1]; } tr_dd;
	struct { unsigned short len; unsigned char arr[  8+1]; } trt_dt;
	struct { unsigned short len; unsigned char arr[  4+1]; } ext_chan_id;
	struct { unsigned short len; unsigned char arr[  1+1]; } trt_op_dsc;
	int     tgrm_prc_sq;
	struct { unsigned short len; unsigned char arr[  1+1]; } prc_sq_dsc;
} TB_CLR_MIS_SQ_CNTN_CT;

#endif
