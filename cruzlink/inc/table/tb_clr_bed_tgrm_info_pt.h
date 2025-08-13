/******************************************************************************
 화일명     : tb_clr_bed_tgrm_info_pt.h
 내용설명   : TB_CLR_BED_TGRM_INFO pc용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLR_BED_TGRM_INFO_PT_H__
#define	__TB_CLR_BED_TGRM_INFO_PT_H__

int  db_Insert_tb_clr_bed_tgrm_info(char *p_tstr);
int  db_Select_tb_clr_bed_tgrm_info(char *p_tstr);
int  db_Update_tb_clr_bed_tgrm_info(char *p_tstr);
void db_Disp_tb_clr_bed_tgrm_info(char *p_tstr);
void db_Init_tb_clr_bed_tgrm_info(char *p_tstr);

typedef	struct
{
	varchar bed_chan_id                [  4+1];	/* NOT_DEF */
	int     tot_sep_cn                        ;	/* NOT_DEF */
	int     tgrm_ds_pos1                      ;	/* NOT_DEF */
	int     tgrm_ds_len1                      ;	/* NOT_DEF */
	int     tgrm_ds_pos2                      ;	/* NOT_DEF */
	int     tgrm_ds_len2                      ;	/* NOT_DEF */
	int     tgrm_ds_pos3                      ;	/* NOT_DEF */
	int     tgrm_ds_len3                      ;	/* NOT_DEF */
	int     tgrm_ds_pos4                      ;	/* NOT_DEF */
	int     tgrm_ds_len4                      ;	/* NOT_DEF */
	int     tgrm_ds_pos5                      ;	/* NOT_DEF */
	int     tgrm_ds_len5                      ;	/* NOT_DEF */
} TB_CLR_BED_TGRM_INFO_PT;

#endif
