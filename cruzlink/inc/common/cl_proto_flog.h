#ifndef __CL_PROTO_FLOG_H__
#define __CL_PROTO_FLOG_H__

/*	FLOG	------------------------------------------------------------------*/
int cf_clm_LogDataDumpF( int flag, char* fname, int LogMaxSize, char* DType, char* Frame, int nSize, char* StrMsg );
int cf_StrLog( int levl, char *fname, char srtype, char *msg, int msglen, char *frame, char *frame_msg);
void cf_DataDump( int levl, char *logdir, char *svcname, int  *plogIdx, char srtype, 
				 char *msg, int msglen, char *frame, char *frame_msg);
void cf_HexLog(FILE *fp, char *msgbuf, int msglen);
#endif

