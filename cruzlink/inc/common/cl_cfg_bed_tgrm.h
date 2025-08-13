#ifndef __CL_CFG_BED_TGRM_H__
#define __CL_CFG_BED_TGRM_H__

typedef struct {
	char	bed_chan_id		[4];
	int		tot_sep_cn			;
	int		tgrm_ds_pos1		;
	int		tgrm_ds_len1		;
	int		tgrm_ds_pos2		;
	int		tgrm_ds_len2		;
	int		tgrm_ds_pos3		;
	int		tgrm_ds_len3		;
	int		tgrm_ds_pos4		;
	int		tgrm_ds_len4		;
	int		tgrm_ds_pos5		;
	int		tgrm_ds_len5		;
} S_CL_CFG_BEDTGRM, *P_CL_CFG_BEDTGRM;
#define CL_CFG_BEDTGRM_LEN (sizeof(S_CL_CFG_BEDTGRM))


#endif
