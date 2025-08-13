/******************************************************************************
 화일명     : tb_clr_ext_ch_info_pt.h
 내용설명   : TB_CLR_EXT_CH_INFO pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLR_EXT_CH_INFO_PT_H__
#define	__TB_CLR_EXT_CH_INFO_PT_H__

int  db_Insert_tb_clr_ext_ch_info(char *p_tstr);
int  db_Select_tb_clr_ext_ch_info(char *p_tstr);
int  db_Update_tb_clr_ext_ch_info(char *p_tstr);
void db_Disp_tb_clr_ext_ch_info(char *p_tstr);
void db_Init_tb_clr_ext_ch_info(char *p_tstr);

typedef	struct
{
	varchar ext_chan_id                [  4+1];	/* NOT_DEF */
	varchar bed_chan_id                [  4+1];	/* NOT_DEF */
	varchar search_err_use_yn          [  1+1];	/* NOT_DEF */
	varchar search_err_hdr_comp_dsc    [  2+1];	/* NOT_DEF */
	varchar search_err_bed_svc_nm      [ 16+1];	/* NOT_DEF */
	varchar eaiid                      [ 32+1];	/* NOT_DEF */
} TB_CLR_EXT_CH_INFO_PT;

#endif
