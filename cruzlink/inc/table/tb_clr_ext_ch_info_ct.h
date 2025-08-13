/******************************************************************************
 화일명     : tb_clr_ext_ch_info_ct.h
 내용설명   : TB_CLR_EXT_CH_INFO c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLR_EXT_CH_INFO_CT_H__
#define	__TB_CLR_EXT_CH_INFO_CT_H__

int  db_Insert_tb_clr_ext_ch_info(char *p_tstr);
int  db_Select_tb_clr_ext_ch_info(char *p_tstr);
int  db_Update_tb_clr_ext_ch_info(char *p_tstr);
void db_Disp_tb_clr_ext_ch_info(char *p_tstr);
void db_Init_tb_clr_ext_ch_info(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  4+1]; } ext_chan_id;
	struct { unsigned short len; unsigned char arr[  4+1]; } bed_chan_id;
	struct { unsigned short len; unsigned char arr[  1+1]; } search_err_use_yn;
	struct { unsigned short len; unsigned char arr[  2+1]; } search_err_hdr_comp_dsc;
	struct { unsigned short len; unsigned char arr[ 16+1]; } search_err_bed_svc_nm;
	struct { unsigned short len; unsigned char arr[ 32+1]; } eaiid;
} TB_CLR_EXT_CH_INFO_CT;

#endif
