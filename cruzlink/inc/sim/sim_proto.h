#ifndef __SIM_PROTO_H__
#define __SIM_PROTO_H__


int libsubfunc_CrtTgrm( char* chn_id
                    ,   char* tst_tp_no
					,   int   deal_sqno
					,   char* msg , long msg_len );

int libsubfunc_GetSvcMstShm(S_CL_HEADER *pHdr
                        , S_CL_CFG_SVCMST *pSvcMst
                        , long *hdrsize);

int libsubfunc_GetTstTp( char* chn_id, char* msg, char* tst_tp_no);

int libsubfunc_InsertBhThTr( char *p_tstr );

int libsubfunc_ReadFile( char* chn_id, char* tst_tp_no
                        , char* msg, int st_no, int snd_cnt, int interval
                        , char* file_dir );

#endif
