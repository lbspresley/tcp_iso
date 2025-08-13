#ifndef __CL_IMG_STR_H__
#define __CL_IMG_STR_H__

/*------------------------------------------------------------------------------
	이미지 로그 전문
*/

typedef struct {
	char c_MsgLen        [ 6];
	char c_ChanID        [ 4];	/*	채널코드	*/
	char c_SndRecvDsc	 [ 1];	/*	송수신 구분 : 송신 (S), 수신(R)	*/
	char c_Comment		 [256];	/*	송수신 구분 : 송신 (S), 수신(R)	*/
	char pApMsg[1]			 ;	/*	Msg			*/	
} S_CL_IMG_LOG;
#define SZ_S_CL_IMG_LOG (sizeof(S_CL_IMG_LOG)-1)

#endif
