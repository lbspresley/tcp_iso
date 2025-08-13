/******************************************************************************
 화일명     : tb_clr_ext_tgrm_info_ct.h
 내용설명   : TB_CLR_EXT_TGRM_INFO c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLR_EXT_TGRM_INFO_CT_H__
#define	__TB_CLR_EXT_TGRM_INFO_CT_H__

int  db_Insert_tb_clr_ext_tgrm_info(char *p_tstr);
int  db_Select_tb_clr_ext_tgrm_info(char *p_tstr);
int  db_Update_tb_clr_ext_tgrm_info(char *p_tstr);
void db_Disp_tb_clr_ext_tgrm_info(char *p_tstr);
void db_Init_tb_clr_ext_tgrm_info(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  4+1]; } ext_chan_id;
	int     tgrm_info_sqno;
	int     tot_sep_cn;
	int     tgrm_ds_pos1;
	int     tgrm_ds_len1;
	int     tgrm_ds_pos2;
	int     tgrm_ds_len2;
	int     tgrm_ds_pos3;
	int     tgrm_ds_len3;
	int     tgrm_ds_pos4;
	int     tgrm_ds_len4;
	int     tgrm_ds_pos5;
	int     tgrm_ds_len5;
} TB_CLR_EXT_TGRM_INFO_CT;

#endif
