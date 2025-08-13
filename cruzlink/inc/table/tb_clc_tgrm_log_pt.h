/******************************************************************************
 화일명     : tb_clc_tgrm_log_pt.h
 내용설명   : TB_CLC_TGRM_LOG pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_TGRM_LOG_PT_H__
#define	__TB_CLC_TGRM_LOG_PT_H__

int  db_Insert_tb_clc_tgrm_log(char *p_tstr);
int  db_Select_tb_clc_tgrm_log(char *p_tstr);
int  db_Update_tb_clc_tgrm_log(char *p_tstr);
void db_Disp_tb_clc_tgrm_log(char *p_tstr);
void db_Init_tb_clc_tgrm_log(char *p_tstr);

typedef	struct
{
	varchar tr_dd                      [  2+1];	/* NOT_DEF */
	varchar tr_dt                      [  8+1];	/* NOT_DEF */
	double  tgrm_log_sqno                     ;	/* NOT_DEF */
	varchar tgrm_cntn                  [4000+1];	/* NOT_DEF */
	varchar chan_id                    [  4+1];	/* NOT_DEF */
	varchar rcv_tm                     [  9+1];	/* NOT_DEF */
} TB_CLC_TGRM_LOG_PT;

#endif
