/******************************************************************************
 화일명     : tb_clc_trt_rzt_pt.h
 내용설명   : TB_CLC_TRT_RZT pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_TRT_RZT_PT_H__
#define	__TB_CLC_TRT_RZT_PT_H__

int  db_Insert_tb_clc_trt_rzt(char *p_tstr);
int  db_Select_tb_clc_trt_rzt(char *p_tstr);
int  db_Update_tb_clc_trt_rzt(char *p_tstr);
void db_Disp_tb_clc_trt_rzt(char *p_tstr);
void db_Init_tb_clc_trt_rzt(char *p_tstr);

typedef	struct
{
	varchar trt_rzt_c                  [  4+1];	/* NOT_DEF */
	varchar trt_rzt_cntn               [1024+1];	/* NOT_DEF */
	varchar sms_snd_yn                 [  1+1];	/* NOT_DEF */
	varchar sms_msg_cntn               [160+1];	/* NOT_DEF */
	varchar chan_bsn_dept_c            [ 10+1];	/* NOT_DEF */
} TB_CLC_TRT_RZT_PT;

#endif
