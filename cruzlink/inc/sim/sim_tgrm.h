
#ifndef _SIM_TGRM_H_
#define _SIM_TGRM_H_

/*	화면 <=> 테스트시뮬레이션 서비스	*/
typedef struct {
	char	chan_id[20+1];
	char	tst_tp_no[6+1];
	int		st_no;
	int		snd_cnt;
	int		interval;
} STR_TRT_REQ_TGRM;



#endif
