#ifndef __CLM_CFG_DIR_INF_H__
#define __CLM_CFG_DIR_INF_H__

typedef struct  {
	char clm_ap_code	[32+1];	/*	업무코드		*/
	char ext_chan_id	[4+1];	/*	대외채널코드	*/
	char bed_chan_id	[4+1];	/*	백엔드채널코드	*/
	char clm_sr_dsc		[1+1];	/*	송수신구분코드	*/
	char node_no		[2+1];	/*	노드 번호		*/
	char inp_dir		[512];	/*	디렉토리		*/
} S_CL_CFG_DIR;
#define CL_CFG_DIR_LEN (sizeof(S_CL_CFG_DIR))


#endif
