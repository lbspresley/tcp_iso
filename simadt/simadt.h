/*------------------------------------------------------------------------------
                       columns = 80          tabstop = 4
----------------------------------------------------------------------------
	FILE NAME    : simadt.h
	DESCRIPTIOIN : simadt 헤더 파일

	DATA & NAME  : 2014/02/10 
------------------------------------------------------------------------------*/
#include "rome.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "tplib/atmi.h"
#include "rsof/rsof.h"
#include "rdf/rdf.h"
#include "smt/smt.h"
#include "tdrv_frame.h"
#include "common/sql_code.h" //20190827 YYK 추가

/*------------------------------------------------------------------------------
	DEFINE
------------------------------------------------------------------------------*/
#define     MAX_SESSION			400			/* 1000 보다 크면 안됨					*/
#define     MAX_MY_CHID			100
#define     MAX_GROUP			100

/*------------------------------------------------------------------------------
	STR
------------------------------------------------------------------------------*/
struct _groupinfo_t
{
	int				onuse;					/* 사용유무  1: 사용, 0: 미사용			*/
	int				group_idx;				/* GROUP INDEX							*/
	char			group_svcname[24];		/* GROUP SERVICE NAME					*/
};
typedef struct _groupinfo_t	_GROUPINFO_T;

struct _local_chidinfo_t
{
	int				onuse;					/* 사용유무  1: 사용, 0: 미사용			*/
	int				chid_idx;				/* CHID INDEX							*/
	unsigned short	port;					/* LISTEN PORT							*/
	unsigned short	subport;				/* CONNECT PORT							*/
	int				lsn_fd;
	int				lsn_stidx;
	char			chid_name[24];			/* CHANNEL ID NAME						*/
	char			group_svcname[24];		/* GROUP SERVICE NAME					*/
};
typedef struct _local_chidinfo_t	_LOCAL_CHIDINFO_T;

struct	_session_info_
{
	int		onuse;
	int		chid_idx;
	int		fd;
	int     stidx;
	char	mode;							/* MCI 기준 모드  S:서버, C:클라이언트  */
	char	rsv[3];

	unsigned short	l_port;
	unsigned short	r_port;
	int		l_ip;
	int		r_ip;
	char	l_ip_str[20];
	char	r_ip_str[20];
};
typedef struct _session_info_ SESSION_INFO;


/*------------------------------------------------------------------------------
	VAR
------------------------------------------------------------------------------*/
char		g_commoncfg[512];
char		g_name_mysvr[MAX_SVC_NAME+1];
char		g_name_mysvc[MAX_SVC_NAME+1];

char		g_my_mode;					/* M:Main, G:Group, S:Single			*/
int		g_my_group_idx;
char		g_group_main[MAX_SVC_NAME+1];

char		g_sim_ip[24];				/* SIM 접속 IP 							*/
char		g_sim_bind_ip[24];			/* SIM 접속용 BINDING IP 				*/
int			g_sim_port;					/* SIM 접속용 PORT						*/
int			g_local_listen_port;		/*	local listen port					*/
int			g_peer_port;				/* peerport								*/
int			g_local_port;				/* localport							*/

int 		max_group_count;			/* 최대 GROUP 갯수						*/
int 		max_group_per_ch;			/* GROUP 당 최대 수용 채널 갯수			*/
int			max_chid_count;				/* 최대 CHID 갯수						*/

int			gi_chid_count;				/* CHID 갯수							*/

_GROUPINFO_T		g_groupinfo[MAX_GROUP+1];
_LOCAL_CHIDINFO_T	g_chidinfo[MAX_MY_CHID+1];
SESSION_INFO 		g_session_info[MAX_SESSION*2];


/*------------------------------------------------------------------------------
PROTOTYPE
------------------------------------------------------------------------------*/
/* sv_sr_init.c */
int		Init_SessTbl();
int 	usermain(int argc,char** argv);
int		Read_FILE_Info();
int		read_common_info( );
int		read_group_info( );
int		read_chid_info( );

/* sv_sr_rrdf.c */
void 	rrdf_UserInit(void);
void 	rrdf_ProcSock(void);

/* sv_sr_rrdf.c */
void 	inet_Accept(int stidx, int fd, int svr_stidx);
int		inet_Connect();
void 	inet_Recv(int stidx, int fd, int svr_stidx);
void 	inet_Close(int stidx, int fd, int svr_stidx);
int 	inet_Send(int fd, char *ptr, int nbyte, int leninfo, char* pchanid);
int		SendN(int fd, char *ptr, int nbyte);
int 	inet_RecvTrt(int fd, char* pchanid, int leninfo);

/* tcp_action.c */
int tcp_Open(char *host, int port_no);
int tcp_Read(int fd, char *buf, int nbyte);
int tcp_ReadLen(int fd, char *buf, int nlenbyte);
int tcp_Write(int fd, char *buf, int nbyte);
int tcp_Listen( char* host, int port );
int tcp_Accept( int fd );

int lf_UpdateDealLog(char* msg);
int lf_SelectDealMaster( CFR_TDRV_FRAME* pFrame, char* ppeerip, int* ppeerport);
