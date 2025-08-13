/******************************************************************************
 화일명     : tb_clr_sts_yr_ct.h
 내용설명   : TB_CLR_STS_YR c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLR_STS_YR_CT_H__
#define	__TB_CLR_STS_YR_CT_H__

int  db_Insert_tb_clr_sts_yr(char *p_tstr);
int  db_Select_tb_clr_sts_yr(char *p_tstr);
int  db_Update_tb_clr_sts_yr(char *p_tstr);
void db_Disp_tb_clr_sts_yr(char *p_tstr);
void db_Init_tb_clr_sts_yr(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  4+1]; } tr_yr;
	struct { unsigned short len; unsigned char arr[  4+1]; } ext_chan_id;
	struct { unsigned short len; unsigned char arr[  1+1]; } trt_op_dsc;
	struct { unsigned short len; unsigned char arr[  1+1]; } re_rs_dsc;
	int     tr_cn;
} TB_CLR_STS_YR_CT;

#endif
