#ifndef __CL_PROTO_DBCMN_H__
#define __CL_PROTO_DBCMN_H__

/*	DBCMN	------------------------------------------------------------------*/
/*	cf_dbcnx.pc	*/
int cf_dbcnx();
void cf_Disconnect();
int comf_DB_Commit();
int comf_DB_RollBack();
int comf_CheckDBCLS(int SqlCode);
int cf_ReConn();

/*	cf_seq.pc	*/
int cf_get_tst_tr( int* pi_trx_sqno );
int cf_get_snr_wt( int* pi_trx_sqno );
int cf_get_mst_sqno( int* pi_trx_sqno );
int cf_get_trx_sqno_err( int* pi_trx_sqno );
int cf_get_data_sqno( int* pi_trx_sqno );
int cf_get_etc_sqno( char* pSeqNm, int* sqno, S_CL_ERR_MSG* pErrStr );
int cf_get_tgrm_log_sqno( int* pi_tgrm_sqno );
int cf_get_rgno( int* pi_rg_sq );


#endif

