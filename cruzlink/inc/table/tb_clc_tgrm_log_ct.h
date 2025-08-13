/******************************************************************************
 화일명     : tb_clc_tgrm_log_ct.h
 내용설명   : TB_CLC_TGRM_LOG c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_TGRM_LOG_CT_H__
#define	__TB_CLC_TGRM_LOG_CT_H__

int  db_Insert_tb_clc_tgrm_log(char *p_tstr);
int  db_Select_tb_clc_tgrm_log(char *p_tstr);
int  db_Update_tb_clc_tgrm_log(char *p_tstr);
void db_Disp_tb_clc_tgrm_log(char *p_tstr);
void db_Init_tb_clc_tgrm_log(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  2+1]; } tr_dd;
	struct { unsigned short len; unsigned char arr[  8+1]; } tr_dt;
	double  tgrm_log_sqno;
	struct { unsigned short len; unsigned char arr[4000+1]; } tgrm_cntn;
	struct { unsigned short len; unsigned char arr[  4+1]; } chan_id;
	struct { unsigned short len; unsigned char arr[  9+1]; } rcv_tm;
} TB_CLC_TGRM_LOG_CT;

#endif
