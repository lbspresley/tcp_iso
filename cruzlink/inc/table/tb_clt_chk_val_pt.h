/******************************************************************************
 화일명     : tb_clt_chk_val_pt.h
 내용설명   : TB_CLT_CHK_VAL pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLT_CHK_VAL_PT_H__
#define	__TB_CLT_CHK_VAL_PT_H__

int  db_Insert_tb_clt_chk_val(char *p_tstr);
int  db_Select_tb_clt_chk_val(char *p_tstr);
int  db_Update_tb_clt_chk_val(char *p_tstr);
void db_Disp_tb_clt_chk_val(char *p_tstr);
void db_Init_tb_clt_chk_val(char *p_tstr);

typedef	struct
{
	varchar tst_tp_no                  [  6+1];	/* NOT_DEF */
	int     tst_tgrm_id_sqno                  ;	/* NOT_DEF */
	int     tp_id_loc_cn                      ;	/* NOT_DEF */
	int     tp_id_len                         ;	/* NOT_DEF */
	varchar tp_id_val                  [ 10+1];	/* NOT_DEF */
	varchar chan_id                    [  4+1];	/* NOT_DEF */
} TB_CLT_CHK_VAL_PT;

#endif
