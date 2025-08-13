/******************************************************************************
 화일명     : tb_clr_trns_rule_info_ct.h
 내용설명   : TB_CLR_TRNS_RULE_INFO c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLR_TRNS_RULE_INFO_CT_H__
#define	__TB_CLR_TRNS_RULE_INFO_CT_H__

int  db_Insert_tb_clr_trns_rule_info(char *p_tstr);
int  db_Select_tb_clr_trns_rule_info(char *p_tstr);
int  db_Update_tb_clr_trns_rule_info(char *p_tstr);
void db_Disp_tb_clr_trns_rule_info(char *p_tstr);
void db_Init_tb_clr_trns_rule_info(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[ 64+1]; } trns_rule_name;
	struct { unsigned short len; unsigned char arr[ 18+1]; } trns_rule_sqno;
	struct { unsigned short len; unsigned char arr[ 18+1]; } src_fld_pos;
	struct { unsigned short len; unsigned char arr[ 18+1]; } src_fld_len;
	struct { unsigned short len; unsigned char arr[ 18+1]; } dst_fld_pos;
	struct { unsigned short len; unsigned char arr[ 18+1]; } dst_fld_len;
	struct { unsigned short len; unsigned char arr[ 18+1]; } use_func_nm;
	struct { unsigned short len; unsigned char arr[ 18+1]; } use_yn;
	struct { unsigned short len; unsigned char arr[ 32+1]; } rule_wrt_nm;
	struct { unsigned short len; unsigned char arr[  8+1]; } rule_date;
	struct { unsigned short len; unsigned char arr[ 16+1]; } rule_ver_no;
	struct { unsigned short len; unsigned char arr[  8+1]; } opn_dt;
} TB_CLR_TRNS_RULE_INFO_CT;

#endif
