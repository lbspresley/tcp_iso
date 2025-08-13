/******************************************************************************
 화일명     : tb_clc_sysinfo_pt.h
 내용설명   : TB_CLC_SYSINFO pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_SYSINFO_PT_H__
#define	__TB_CLC_SYSINFO_PT_H__

int  db_Insert_tb_clc_sysinfo(char *p_tstr);
int  db_Select_tb_clc_sysinfo(char *p_tstr);
int  db_Update_tb_clc_sysinfo(char *p_tstr);
void db_Disp_tb_clc_sysinfo(char *p_tstr);
void db_Init_tb_clc_sysinfo(char *p_tstr);

typedef	struct
{
	varchar issue_dt                   [  8+1];	/* NOT_DEF */
	varchar issue_time_min             [  4+1];	/* NOT_DEF */
	varchar node_no                    [  2+1];	/* NOT_DEF */
	int     cpu_rate                          ;	/* NOT_DEF */
	int     mem_rate                          ;	/* NOT_DEF */
	int     hdd_rate                          ;	/* NOT_DEF */
} TB_CLC_SYSINFO_PT;

#endif
