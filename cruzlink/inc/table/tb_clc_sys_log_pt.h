/******************************************************************************
 화일명     : tb_clc_sys_log_pt.h
 내용설명   : TB_CLC_SYS_LOG pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_SYS_LOG_PT_H__
#define	__TB_CLC_SYS_LOG_PT_H__

int  db_Insert_tb_clc_sys_log(char *p_tstr);
int  db_Select_tb_clc_sys_log(char *p_tstr);
int  db_Update_tb_clc_sys_log(char *p_tstr);
void db_Disp_tb_clc_sys_log(char *p_tstr);
void db_Init_tb_clc_sys_log(char *p_tstr);

typedef	struct
{
	varchar log_dt                     [  8+1];	/* NOT_DEF */
	varchar log_tm                     [  6+1];	/* NOT_DEF */
	int     log_sq                            ;	/* NOT_DEF */
	varchar mdl_nm                     [ 32+1];	/* NOT_DEF */
	varchar log_dsc                    [  2+1];	/* NOT_DEF */
	varchar sms_req_yn                 [  1+1];	/* NOT_DEF */
	varchar fr_dtl_cntn                [2048+1];	/* NOT_DEF */
} TB_CLC_SYS_LOG_PT;

#endif
