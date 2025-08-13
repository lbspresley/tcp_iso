/******************************************************************************
 화일명     : tb_clc_x25_lu_sts_pt.h
 내용설명   : TB_CLC_X25_LU_STS pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLC_X25_LU_STS_PT_H__
#define	__TB_CLC_X25_LU_STS_PT_H__

int  db_Insert_tb_clc_x25_lu_sts(char *p_tstr);
int  db_Select_tb_clc_x25_lu_sts(char *p_tstr);
int  db_Update_tb_clc_x25_lu_sts(char *p_tstr);
void db_Disp_tb_clc_x25_lu_sts(char *p_tstr);
void db_Init_tb_clc_x25_lu_sts(char *p_tstr);

typedef	struct
{
	varchar chan_id                    [  4+1];	/* NOT_DEF */
	varchar x25_line_nm                [  8+1];	/* NOT_DEF */
	varchar x25_lu                     [  8+1];	/* NOT_DEF */
	varchar trx_x25_lcn                [  8+1];	/* NOT_DEF */
	int     sess_stsc                         ;	/* NOT_DEF */
	varchar rs_dsc                     [  1+1];	/* NOT_DEF */
	varchar sts_mod_dt                 [  8+1];	/* NOT_DEF */
	varchar sts_mod_tm                 [  6+1];	/* NOT_DEF */
} TB_CLC_X25_LU_STS_PT;

#endif
