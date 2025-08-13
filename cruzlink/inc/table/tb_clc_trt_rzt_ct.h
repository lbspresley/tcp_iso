/******************************************************************************
 화일명     : tb_clc_trt_rzt_ct.h
 내용설명   : TB_CLC_TRT_RZT c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_TRT_RZT_CT_H__
#define	__TB_CLC_TRT_RZT_CT_H__

int  db_Insert_tb_clc_trt_rzt(char *p_tstr);
int  db_Select_tb_clc_trt_rzt(char *p_tstr);
int  db_Update_tb_clc_trt_rzt(char *p_tstr);
void db_Disp_tb_clc_trt_rzt(char *p_tstr);
void db_Init_tb_clc_trt_rzt(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  4+1]; } trt_rzt_c;
	struct { unsigned short len; unsigned char arr[1024+1]; } trt_rzt_cntn;
	struct { unsigned short len; unsigned char arr[  1+1]; } sms_snd_yn;
	struct { unsigned short len; unsigned char arr[160+1]; } sms_msg_cntn;
	struct { unsigned short len; unsigned char arr[ 10+1]; } chan_bsn_dept_c;
} TB_CLC_TRT_RZT_CT;

#endif
