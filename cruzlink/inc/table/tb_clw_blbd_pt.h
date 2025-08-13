/******************************************************************************
 화일명     : tb_clw_blbd_pt.h
 내용설명   : TB_CLW_BLBD pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLW_BLBD_PT_H__
#define	__TB_CLW_BLBD_PT_H__

int  db_Insert_tb_clw_blbd(char *p_tstr);
int  db_Select_tb_clw_blbd(char *p_tstr);
int  db_Update_tb_clw_blbd(char *p_tstr);
void db_Disp_tb_clw_blbd(char *p_tstr);
void db_Init_tb_clw_blbd(char *p_tstr);

typedef	struct
{
	int     blbd_sqno                         ;	/* NOT_DEF */
	varchar blbd_id                    [  3+1];	/* NOT_DEF */
	varchar tit                        [200+1];	/* NOT_DEF */
	varchar cntn                       [2000+1];	/* NOT_DEF */
	varchar apdfl_nm                   [ 20+1];	/* NOT_DEF */
	varchar apdfl_path                 [100+1];	/* NOT_DEF */
	int     inqmn_cnt                         ;	/* NOT_DEF */
	int     bup_rg_no                         ;	/* NOT_DEF */
	int     otxt_rg_no                        ;	/* NOT_DEF */
	int     lvl                               ;	/* NOT_DEF */
	varchar drup_dtm                     [ 24];	/* NOT_DEF */
	varchar mod_dtm                      [ 24];	/* NOT_DEF */
	varchar del_yn                     [  1+1];	/* NOT_DEF */
	varchar trdt                       [  8+1];	/* NOT_DEF */
	varchar trhr                       [  6+1];	/* NOT_DEF */
	varchar trbrc                      [  6+1];	/* NOT_DEF */
	varchar bzno                       [ 13+1];	/* NOT_DEF */
	varchar ans_yn                     [  1+1];	/* NOT_DEF */
	varchar ans_dt                     [  8+1];	/* NOT_DEF */
	varchar reg_eno                    [ 13+1];	/* NOT_DEF */
	varchar mod_eno                    [ 13+1];	/* NOT_DEF */
	varchar ans_eno                    [ 13+1];	/* NOT_DEF */
} TB_CLW_BLBD_PT;

#endif
