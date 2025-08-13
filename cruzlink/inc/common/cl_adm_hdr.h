#ifndef __CL_ADM_HDR_H__
#define __CL_ADM_HDR_H__

typedef struct {
    char	c_ApCode     [ 32]; /* 대외계APCode ( CHID_XXXX )	*/
    char    c_tgrm_dsc   [ 1 ]; /* 각 관리전문들의 구분자
									O : 개시
									S : 종료예고 ( 1차 종료예고, 2차 종료예고 )
									C : 종료
									B : 장애전문
									R : 회복전문
									T : Test Call
								*/
    char    c_rs_dsc     [ 1 ]; /* R' : 요청 'S' : 응답 */
    char    c_org_c      [ 12]; /*                      */
    char    c_tgrm_dt_cc [ 2 ]; /* yy                   */
    char    c_tgrm_dt_yy [ 2 ]; /* yy                   */
    char    c_tgrm_dt_mn [ 2 ]; /* mm                   */
    char    c_tgrm_dt_dy [ 2 ]; /* dd                   */
    char    c_tgrm_tm_hr [ 2 ]; /* 24hh                 */
    char    c_tgrm_tm_mi [ 2 ]; /* mi                   */
    char    c_tgrm_tm_sc [ 2 ]; /* ss                   */
	char    c_filler     [ 36]; /*                      */
} S_ADM_HDR;
#define CL_ADM_HDR_LEN (sizeof(S_ADM_HDR))

#endif
