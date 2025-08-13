/******************************************************************************
 화일명     : tb_clr_trns_rule_info_pt.h
 내용설명   : TB_CLR_TRNS_RULE_INFO pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLR_TRNS_RULE_INFO_PT_H__
#define	__TB_CLR_TRNS_RULE_INFO_PT_H__

int  db_Insert_tb_clr_trns_rule_info(char *p_tstr);
int  db_Select_tb_clr_trns_rule_info(char *p_tstr);
int  db_Update_tb_clr_trns_rule_info(char *p_tstr);
void db_Disp_tb_clr_trns_rule_info(char *p_tstr);
void db_Init_tb_clr_trns_rule_info(char *p_tstr);

typedef	struct
{
	varchar trns_rule_name             [ 64+1];	/* NOT_DEF */
	varchar trns_rule_sqno             [ 18+1];	/* NOT_DEF */
	varchar src_fld_pos                [ 18+1];	/* NOT_DEF */
	varchar src_fld_len                [ 18+1];	/* NOT_DEF */
	varchar dst_fld_pos                [ 18+1];	/* NOT_DEF */
	varchar dst_fld_len                [ 18+1];	/* NOT_DEF */
	varchar use_func_nm                [ 18+1];	/* NOT_DEF */
	varchar use_yn                     [ 18+1];	/* NOT_DEF */
	varchar rule_wrt_nm                [ 32+1];	/* NOT_DEF */
	varchar rule_date                  [  8+1];	/* NOT_DEF */
	varchar rule_ver_no                [ 16+1];	/* NOT_DEF */
	varchar opn_dt                     [  8+1];	/* NOT_DEF */
} TB_CLR_TRNS_RULE_INFO_PT;

#endif
