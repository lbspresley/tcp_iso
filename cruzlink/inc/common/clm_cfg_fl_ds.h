#ifndef __CLM_CFG_FL_DS_H__
#define __CLM_CFG_FL_DS_H__

/*  일괄 업무정보 (파일 정보)가
*   DB와 Config File을 같이 쓰기 위해서 Config 정의를 한다. */
typedef struct  {
	char    chan_id        [4+1];
	int     fl_ds_inf_sqno          ;
} S_CLM_CFG_FL_DS_CNT, *P_CLM_CFG_FL_DS_CNT;
#define CLM_CFG_FL_DS_CNT_LEN (sizeof(S_CLM_CFG_FL_DS_CNT))

struct _clm_cfg_fl_ds_t {

	char    chan_id   [ 4];
	int     fl_ds_inf_sqno    ;
	int     tot_ds_cnt        ;
	int     fl_ds_pos1        ;
	int     fl_ds_len1        ;
	int     fl_ds_pos2        ;
	int     fl_ds_len2        ;
	int     fl_ds_pos3        ;
	int     fl_ds_len3        ;
	int     fl_ds_pos4        ;
	int     fl_ds_len4        ;
	int     fl_ds_pos5        ;
	int     fl_ds_len5        ;
};
typedef struct _clm_cfg_fl_ds_t S_CLM_CFG_FL_DS;

#define CLM_CFG_FL_DS_LEN (sizeof(S_CLM_CFG_FL_DS))

#endif
