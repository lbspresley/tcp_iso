#ifndef __TCP_BOK_VAR_H__
#define __TCP_BOK_VAR_H__


char			g_rmpSvcName[16];
char			g_ServiceName[64];
/*char			g_SvcName[64]; */
char			g_VANCode[16];
char			g_APSvc[16];


int             g_maxterm_cnt;				/* Max Sesstion Cnt */ 
char            g_path_mycfg[128]; 
int				g_TimerInterval;			/* 기본적인 타이머 주기 */
int				g_DisCntInterval;			/* 기본적인 타이머 주기 */

int				g_ReqPollInterval;			/* Poll 보내는 주기 */
int				g_RspPollInterval;			/* Poll 응답대기 시간 */

int             g_Encrypt_Flag;             // (20200408) Encrypttion Flag


TERM_TABLE* 	g_TermTable;
int             g_SndIdx;
int             g_RCntCount;
int				g_SessStat;
int				g_DnSessLimit;
int				g_UpSessLimit;

int				g_UsePoll;
int				g_AutoDisCnt;
int				g_SessMonitor;

char			gc_Bityn[1+1];				/*	bit map 여부	*/
int				gi_dscfldcnt;


int				gi_BitMapYn[1];				/*	Bit map 여부 Y/N
											*	Bit map 이면 따로 코딩해야 
											*	함	*/
int				gi_SvcCnt;
char			g_ChanID[4+1];


char*           g_EncryptBuf;
char*           g_DecryptBuf;
char            gc_CmnCfg[256];             /* config file */
int             gi_ApDataBufAllocSize;      /* ap data tpalloc size */
char            gc_LogYn[1+1];             /* config file */


char			gc_plain_id[32];		
char			gc_plain_pw[32];	
char			gc_enc_id[32];		
char			gc_enc_pw[32];	
char 			g_inisafe_conf[512];
net_ctx*		g_client_ctx;
net_ctx*		g_server_ctx;

char    gc_EncIdPswd [32+1];    /* ID+PSWD */
char    gc_PlainIdPswd [32+1];    /* ID+PSWD */

// 신-한은망용 참가기관용 기관코드
char    gc_org_cd[32];
char    gc_bok_cd[32]; // 신-한은망용 한국은행 코드(1016)

int 	g_poll_started; // polling start flag

int	lf_Rcv_000000001(char* msg, int len);
int	lf_Rcv_000000002(char* msg, int len);
int	lf_Rcv_000000003(char* msg, int len);
int	lf_Rcv_000000004(char* msg, int len);
int	lf_Rcv_000000005(char* msg, int len);
int lf_Snd_000000001(char* PeerIP, char* PeerPort, char* LocalPort);

// 국고
char gc_BizCode[32];	// 국고 : "BOK", 신한은망 : "FTP"

int	lf_Rcv_000000001_NF(char* msg, int len);
int	lf_Rcv_000000002_NF(char* msg, int len);
int	lf_Rcv_000000003_NF(char* msg, int len);
int	lf_Rcv_000000004_NF(char* msg, int len);
int	lf_Rcv_000000005_NF(char* msg, int len);
int lf_Snd_000000001_NF(char* PeerIP, char* PeerPort, char* LocalPort);


int dbUpdateIDPW(char* pID, char* pPass);
void func_AClearTable(int idx);

int lf_SetErrStr(S_CL_HEADER* pHdr, S_CL_ERR_MSG* pErrMsg);

int	lf_Snd_Poll();
int	lf_Snd_Poll_NF();

// Polling_NF.c
int	lf_Rcv_PollReq_NF( char* msg, int len );
int	lf_Rcv_PollRsp_NF( char* msg, int len );
void TF_PollTimeout_NF(int TimerID, int lParam, int rParam);
void TF_SendPollReq_NF(int TimerID, int lParam, int rParam);

// Polling.c
int	lf_Rcv_PollReq( char* msg, int len );
int	lf_Rcv_PollRsp( char* msg, int len );
void TF_PollTimeout(int TimerID, int lParam, int rParam);
void TF_SendPollReq(int TimerID, int lParam, int rParam);

// db_GetBokInf.pc
int dbInsertIDPW(char* pID, char* pPass);
int dbGetIDPW( );
int dbUpdateIDPW(char* pID, char* pPass);

// db_tmp.c
int cf_dbcnx();
void cf_Disconnect();
int cf_GoImgLog(char *svc, char *dir, char *title, char* msg, int len);

#endif
