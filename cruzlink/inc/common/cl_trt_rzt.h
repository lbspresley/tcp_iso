#ifndef __CL_TRT_RZT_H__
#define __CL_TRT_RZT_H__

#include "common/cl_code_err.h"

/*	송수신	------------------------------------------------------------------*/
/*  마스터 처리결과 코드    ( MST_TRT_RZT_C )   */
#define DEF_MST_TRT_RZT_C_WAIT		"WAIT"  /*  요청        */
#define DEF_MST_TRT_RZT_C_COMPLETE  "CMPL"  /*  완료        */
#define DEF_MST_TRT_RZT_C_RSP_ERROR "ERRQ"  /*  요청에러    */
#define DEF_MST_TRT_RZT_C_CMP_ERROR "ERRC"  /*  응답에러    */
#define DEF_MST_TRT_RZT_C_INF_ERROR "ERRI"  /*  통지에러    */


/*	송수신	------------------------------------------------------------------*/
#define DEF_TRT_RZT_SEND		"WAIT"		/*	요청 송신 완료	*/
#define DEF_TRT_RZT_END			"ENDD"		/*	응답 수신 완료	*/

/*	타이머	*-----------------------------------------------------------------*/
#define DEF_TRT_RZT_RTN			"TMOT"		/*	타임아웃 처리	*/


/*	일괄 처리 상태 코드	*-----------------------------------------------------*/
#define DEF_CLM_PRC_DSC_START       "STRT"  /*  파일 송수신 처리 시작   */
#define DEF_CLM_PRC_DSC_COMPLETE    "CMPL"  /*  파일 송수신 처리 완료   */
#define DEF_CLM_PRC_DSC_RESULT      "RSLT"  /*  파일 송수신 결과 처리 완료  */
#define DEF_CLM_PRC_DSC_WAIT  	    "WAIT"  /*  파일 송수신 대기중		*/
/* 20120128 */
#define DEF_CLM_PRC_DSC_ACCEPT 	    "ACPT"  /*  파일 송신 접수완료 송신대기 중 */

/*	배치 처리 결과 코드	*-----------------------------------------------------*/
#define DEF_BAT_PRC_RZT_C_COMPLETE  "CMPL"  /*  배치 처리 정상 완료 시작   */
#define DEF_BAT_PRC_RZT_C_ING	 	"PRCI"  /*  배치 처리 중 */


#endif
