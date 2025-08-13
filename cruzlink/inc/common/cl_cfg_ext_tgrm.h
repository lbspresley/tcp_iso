#ifndef __CL_CFG_EXT_TGRM_H__
#define __CL_CFG_EXT_TGRM_H__

typedef struct {
	char	ext_chan_id		[4+1];
	int		ext_tgrm_type_cnt;
} S_CL_CFG_EXTTGRM_CNT;
#define CL_CFG_EXTTGRM_CNT_LEN (sizeof(S_CL_CFG_EXTTGRM_CNT))

struct _cl_cfg_exttgrm_t {
	struct _cl_cfg_exttgrm_t* pNext;

	char	ext_chan_dsc	[ 7];
	char	ext_chan_id		[ 4];
	int		tgrm_info_sqno		;	/*	À¯Çüº° °¹¼ö	: 3 */
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
};
typedef struct _cl_cfg_exttgrm_t S_CL_CFG_EXTTGRM;

#define CL_CFG_EXTTGRM_LEN (sizeof(S_CL_CFG_EXTTGRM))


#endif
