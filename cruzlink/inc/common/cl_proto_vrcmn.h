#ifndef __CL_PROTO_VRCMN_H__
#define __CL_PROTO_VRCMN_H__

/*	VRCMN	------------------------------------------------------------------*/
int cf_CheckStatusStart(char* chan_id);
int cf_GetStatus(char* chan_id, char* StartStatus, char* Status);
int cf_SelectRecSize( char* chanid, char* ap_code, char* sr_dsc, int* phdsz, int* pdtsz, int* ptrsz );
int cf_SetStatus(char* chan_id, char* StartStatus, char* Status);
int cf_UpdateDealMst(char* tr_dt, char* mst_tr_sq, char* trt_rzt_c);
int cf_UpdateWtTb(char* tr_dt, char* mst_tr_sq, char* trt_rzt_c);
int cf_UpdateWtTb2(char* snr_dt, char* rsv_sqno, char* trt_rzt_c);
int cf_UpdateWtTb2_for_Recv(char* snr_dt, char* rsv_sqno, char* trt_rzt_c);
int cf_UpdateWtTb10_for_Recv(char* snr_dt, char* rsv_sqno, char* trt_rzt_c);
void cf_ProcErr( char* ApCode , char* ChanID , char* BizDtlCd , char* SrDsc , int   NodeNo , 
				char* TrDt , int   MstTrxSqNo , char* FlSq , char* DirNm , char* FlNm , 
				int   CrzFlSz , char* SvcNm , char* rslt_code , char* err_msg );
#endif

