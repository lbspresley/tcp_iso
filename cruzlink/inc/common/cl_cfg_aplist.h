#ifndef __CL_CFG_APLIST_H__
#define __CL_CFG_APLIST_H__



/*	흐름정보 (Ap list)가
*	DB와 Config File을 같이 쓰기 위해서 Config 정의를 한다.	*/

/*	config mem	*/
typedef struct {
    char        ap_list_dsc     [ 14];      /*  ap_list_idx || svc_prc_sq(5) */
    char	    ap_list_idx     [  8];
    int         svc_prc_sq      ;
	char		ap_svc_nm		[ 16];
	char		svc_kndc		[  1];
} S_CL_CFG_APLIST, *P_CL_CFG_APLIST;
#define CL_CFG_APLIST_LEN (sizeof(S_CL_CFG_APLIST))

#endif
