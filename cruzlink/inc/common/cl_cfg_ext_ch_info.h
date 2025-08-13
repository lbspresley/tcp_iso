#ifndef __CL_CFG_EXT_CH_INFO_H__
#define __CL_CFG_EXT_CH_INFO_H__



/*	채널정보가
*	DB와 Config File을 같이 쓰기 위해서 Config 정의를 한다.	*/

/*	config mem	*/
typedef struct {
    char	    ext_chan_id     [  4];
	char		com_mthd_dsc	[  1];	/*	통신방식 코드		*/
	char		bed_chan_id		[  4];	/*	백엔드 채널 코드	*/
	char		srch_err_hdr_comp_dsc	[  2];	/*	검색실패헤더구성구분	*/
	char		srch_err_bed_svc_nm		[ 16];	/*	백엔드서비스명			*/
	char		eaiid			[ 32];	/*	EAI ID				*/
} S_CL_CFG_EXT_CH_INFO, *P_CL_CFG_EXT_CH_INFO;
#define CL_CFG_EXT_CH_INFO_LEN (sizeof(S_CL_CFG_EXT_CH_INFO))

#endif
