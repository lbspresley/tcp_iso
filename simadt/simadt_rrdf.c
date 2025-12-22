/*------------------------------------------------------------------------------
                       columns = 80          tabstop = 4                        
  ----------------------------------------------------------------------------  
   FILE NAME    :  
   DESCRIPTIOIN :  

   DATA & NAME  : 2010/12/16 (이영근)
------------------------------------------------------------------------------*/

#include "simadt.h"
#include "tplib/ulog.h"


extern CFR_TDRV_FRAME sDrvFrame;

void rrdf_UserInit(void)
{
    //int             rc;
    /*-------------------------------------*
    |   통신관련 초기화 ...                |
    *-------------------------------------*/
    return;
}


void rrdf_ProcSock(void)
{
	int				stidx;
	int				rc;
	int				i;
	int				fd_inet;
	int				nReason;
	unsigned short	lsn_port = 0 ;

	//   RSOF 초기화
	rc = rsof_init();
	if(rc < 0) {
		ulog(_ERROR_,	"rsof_init() failed. rc=%d", rc);
		exit(-1);
	}

	//  Port Listen 시작
	//  AsyncSelect :  
	//  Close function/Rcv Function 등록  
	if( g_my_mode == 'M' ) {
		rsof_main();
		return;
	}

	//	TODO
	lsn_port = g_local_listen_port;
	if((fd_inet = rsof_listenINET(lsn_port, SOCK_STREAM, 1500, &nReason)) < 0) {
		ulog(_ERROR_,  "rsof_listenINET failed. idx(%d) chid[%s] Port(%d) Reason(%d)"
					, i, g_chidinfo[i].chid_name, lsn_port, nReason);
		exit(-1);
	}

	//20190827 YYK
	ulog(_WARNING_, "Port Listen Start\n"
			"Port : %d\n"
			"fd   : %d", lsn_port, fd_inet);

	rc = rsof_asyncSelect(_IGNORE, fd_inet, _IGNORE, inet_Accept, NULL, NULL);
	if(rc < 0) {
		ulog(_ERROR_,  "rsof_asyncSelect failed. g_chidinfo[%d] rc=%d", i, rc);
		exit(-1);
	}

	stidx = rsof_findStidx(TYPE_LOCAL, 2, 0, lsn_port );

#if (1) /*	SMT Used */
	STbl_AddNewSessionAct( _IGNORE, _IGNORE, lsn_port, stidx );
#endif

	// rsof main
	rsof_main();
}

#if (1) /* LBH(20120613) add session info */
int getSessionInfo( int fd, int* plcl_ip, char* plcl_ip_str, int* plcl_port, int* ppeer_ip, char* ppeer_ip_str, int* ppeer_port )
{
	int rc;
	struct sockaddr_in addr;
	struct in_addr ipaddr;
#if defined (_HPUX) /* LBH (20100629) */
	int len;
#else
	socklen_t len;
#endif

#if defined (_HPUX) /* LBH (20100629) */
	len = (int)sizeof(addr);
	rc = getsockname( fd,(struct sockaddr*)&addr,(int*)&len);
#else
	len = (socklen_t)sizeof(addr);
	rc = getsockname( fd,(struct sockaddr*)&addr,(socklen_t*)&len);
#endif
	if( rc < 0 ) {
		ulog(_ABEND_,	"getsockname() failed. errno=%d", errno);
		return -1;
	}

	if( plcl_port != (int*) NULL) {
		*plcl_port  = ntohs(addr.sin_port);
	}

	if( plcl_ip != (int*) NULL) {
		*plcl_ip    = addr.sin_addr.s_addr;
	}

	if( plcl_ip_str != (char*) NULL) {
		ipaddr.s_addr = addr.sin_addr.s_addr; 
		strcpy( plcl_ip_str, inet_ntoa(ipaddr) );
	}

#if defined (_HPUX) /* LBH (20100629) */
	len = (int)sizeof(addr);
	getpeername( fd,(struct sockaddr*)&addr,(int*)&len);
#else
	len = (socklen_t)sizeof(addr);
	getpeername( fd,(struct sockaddr*)&addr,(socklen_t*)&len);
#endif
	if( rc < 0 ) {
		ulog(_ABEND_,	"getpeername() failed. errno=%d", errno);
		return -2;
	}

	if( ppeer_port != (int*) NULL) {
		*ppeer_port  = ntohs(addr.sin_port);
	}

	if( ppeer_ip != (int*) NULL) {
		*ppeer_ip    = addr.sin_addr.s_addr;
	}

	if( ppeer_ip_str != (char*) NULL) {
		ipaddr.s_addr = addr.sin_addr.s_addr; 
		strcpy( ppeer_ip_str, inet_ntoa(ipaddr) );
	}

	return 0;

}
#endif

void inet_Accept(int stidx, int fd, int udvalue)
{
	int					rc = 0;
	int					opt		= 1;
	int					optlen	= sizeof(opt);
	int					l_sess_idx = 0;

#if (1) /*  add session info */
	int					local_ip;
	char				local_ip_str[20];
	int					local_port;
	int					peer_ip;
	char				peer_ip_str[20];
	int					peer_port;
#endif

	if((rc = setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (void*)&opt, optlen)) < 0) {
		ulog(_ABEND_,	"setsockopt() failed. rc=%d errno=%d", rc, errno);
		rsof_resetFD(stidx, fd, _IGNORE);
		return;
	}

	rc = getSessionInfo( fd, &local_ip, local_ip_str, &local_port, 
							  &peer_ip, peer_ip_str, &peer_port );
	if(rc < 0) {
		ulog(_ABEND_,	"getSessionInfo() failed. rc=%d", rc);
		rsof_resetFD(stidx, fd, _IGNORE);
		return;
	}
	ulog(_WARNING_,  "session accept fd(%d) stdix(%d)\n"
			"(%s.%d)->(%s.%d)"	
			, fd, stidx, peer_ip_str, peer_port, local_ip_str, local_port);

	STbl_AddNewSessionAct( peer_ip, peer_port, local_port, stidx);

    // Local Table 세션 할당
    // 해당 index영역에서 사용가능공간 검색
    // 초기값 setting ...
	// g_sessino_info 에서 앞 MAX_SESSION 만큼은 서버용 뒤 MAX_SESSION 은 클라이언트용으로 사용.
	l_sess_idx = 1;

	g_local_port = local_port;
	g_peer_port = peer_port;

	rc = rsof_setUserDefineValueSession( stidx, fd, l_sess_idx);
	if( rc < 0 ) {
		ulog(_ABEND_, "rsof_setUserDefineValueSession() failed rc=%d,  fd=%d, udvalue=%d",
						rc, fd, l_sess_idx);
		rsof_resetFD(_IGNORE, fd, _IGNORE);
		STbl_DelSessionCnxByStidx(stidx);
		return;
	}

	rc = rsof_asyncSelect( stidx, fd, _IGNORE, NULL, inet_Recv, inet_Close);
	if( rc < 0 ) {
		ulog(_ABEND_, "rsof_asyncSelect() failed. rc=%d  fd=%d ", rc, fd );
		rsof_resetFD(_IGNORE, fd, _IGNORE);
		STbl_DelSessionCnxByStidx(stidx);
		return;
	}
	return;
}


int inet_Connect()
{
	int	rc=0;
	int	localport=0;
	int	sockfd;
	size_t	len;
	struct sockaddr_in addr;
    struct sockaddr_in myaddr;
    struct timeval to;
    fd_set wrtfds;
    int 	on;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if( sockfd < 0 ) {
		ulog(_ERROR_, "socket create fail (%d)", errno );
		return -10;
	}

	//	bind...
	//	ip : g_sim_ip
	//	local ip : g_sim_bind_ip
	//	port : g_chidinfo[chid_idx].subport;

	memset((char*)&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(g_sim_bind_ip);

	rc = bind(sockfd, (const struct sockaddr*)&addr, sizeof(addr));
	if( rc < 0 ) {
		ulog(_ERROR_, "bind fail (%d:%s)!!!\n"
					"local ip (%s)"
					, errno, strerror(errno)
					, g_sim_bind_ip);
		return -20;
	}

	on = 1;
	rc = setsockopt(sockfd,SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
	if( rc < 0 ) {
		ulog(_WARNING_, "set socket option SO_REUSEADDR fail errno=%d",errno);
	}

	//	connect....
	addr.sin_family = AF_INET;
	addr.sin_port  = htons(g_sim_port);
	addr.sin_addr.s_addr  = inet_addr(g_sim_ip);
	ulog( 0, "시뮬레이터 접속 체크\n"
			 "대외MCA IP : [%s]\n"
			 "시뮬레이터 : [%s],[%d]"
			, g_sim_bind_ip, g_sim_ip, g_sim_port);

	while(1) {
		rc = connect(sockfd, (struct sockaddr *)&addr,sizeof(addr));
		if( rc < 0 ) {
			if( errno == EINTR ) {
				//	interrupt
				continue;
			}

			if( errno == EINPROGRESS ) {
				//	async connect
				break;
			}

			//	erroo
			ulog(_ERROR_,"시뮬레이터 접속 실패 rc:%d errno=%d (%s)\n"
					 	 "대외MCA IP : [%s]\n"
						 "시뮬레이터 : [%s],[%d]"
						 , rc, errno, strerror(errno)
						 , g_sim_bind_ip, g_sim_ip, g_sim_port);
			close(sockfd);
			return -30;
		}

		ulog( 1, "시뮬레이터 접속 성공\n"
				 "대외MCA IP : [%s]\n"
				 "시뮬레이터 : [%s],[%d]"
				, g_sim_bind_ip, g_sim_ip, g_sim_port);
		break;
	}

	FD_ZERO( &wrtfds );
	FD_SET( sockfd, &wrtfds );
	to.tv_sec  = 1;
	to.tv_usec = 0;

	//	select
	rc = select(sockfd+1,NULL,&wrtfds,NULL,&to);
	if(rc < 0) {
		ulog(_ERROR_,"select fail errno=%d",errno);
		close(sockfd);
		return -40;
	}

	if(rc==0) {
		// time out
		close(sockfd);
		return -50;
	}

	// Connect Check
	rc=connect(sockfd,(struct sockaddr *)&addr,sizeof(addr));
	if(rc < 0) {
		if( (errno != EISCONN) && (errno != EEXIST) )
		{
			// case : CON REFUSED
			ulog(_ERROR_, "connect fail errno=%d (%s)"
						, errno, strerror(errno));
			close(sockfd);
			return -60;
		}
		ulog(_WARNING_, "Connection Refused or EEXIST errno=%d (%s)"
					, errno, strerror(errno));
	}

	len = sizeof( myaddr);
	if( getsockname( sockfd, (struct sockaddr *)&myaddr, (int*)&len ) != 0 ) {
		ulog( _ERROR_, "error getsockname (%d)", errno );
		localport = -1;
	}

	return sockfd;
}


void    inet_Recv(int stidx, int fd, int udvalue)
{
	int		rc=0;
	int		l_sess_idx = -1;
	int		rcv_len=0;

	int		ifragcnt=0;
	int		nSndLen=0;
	long	nSndOption = TPNOREPLY | TPBLOCK | TPFUNC;

	char*	pSndData = NULL;
	char*	pDataBuf = NULL;

	char	recvlen[6+1];

	CFR_TDRV_FRAME		tdrv_frame;

	ulog(_FLOW_,	"Recv event. fd=%d, udvalue=%d  ", fd, udvalue);

	if(udvalue < MAX_SESSION) {
		l_sess_idx = udvalue ;
	} else {
		l_sess_idx = udvalue - MAX_SESSION ;
	}

	if( l_sess_idx < 0 || l_sess_idx > MAX_SESSION ) {
		ulog( _ERROR_, "rsof session index or udvalue error. - "
			   "l_sess_idx(%d), udvalue(%d), MAX_SESSION(%d)"
				, l_sess_idx, udvalue, MAX_SESSION);
		rsof_resetFD(_IGNORE, fd, _IGNORE);
		STbl_DelSessionCnxByStidx(stidx);
		return;
	}

	//	길이 수신
	ifragcnt = 0;
	memset(recvlen, 0x00, sizeof(recvlen));
	while(1) {
		rc = recv(fd, recvlen, 6, MSG_PEEK);
		if( rc < 0 ) {
			ulog(_ERROR_, "len recv error (%d:%s)", errno, strerror(errno));
			inet_Close(stidx, fd, udvalue);
			return;
		}

		if( rc == 6 ) {
			memset(recvlen, 0x00, sizeof(recvlen));
			rc = recv(fd, recvlen, 6, 0 );
			break;
		}

		//	fragmentation
		ifragcnt++;
		if( ifragcnt > 3 ) {
			ulog(_ERROR_, "len recv issue fragmentaion peerport(%d)!!", g_peer_port);
			inet_Close(stidx, fd, udvalue);
			return;
		}

		sleep(1);
	}

	rcv_len = atoi(recvlen); /* 시뮬레이터공통부의 데이터길이 */
	if( rcv_len < 0 ) {
		ulog(_ERROR_, "len string error (%s -> %d)", recvlen, rcv_len);
		inet_Close(stidx, fd, udvalue);

		//rsof_resetFD(_IGNORE, fd, _IGNORE);
		//STbl_DelSessionCnxByStidx(stidx);
		return;
	}

	//	데이터 버퍼 생성 
	pDataBuf = (char*)malloc(rcv_len);
	if( pDataBuf == NULL ) {
		ulog(_ERROR_, "RcvDataBuffer malloc error (%d:%s)", errno, strerror(errno));
		inet_Close(stidx, fd, udvalue);
		return;
	}
	memset(pDataBuf, 	0x00, 	rcv_len);

	//	Read 데이터
	ifragcnt = 0;
	while(1) {
		rc = recv(fd, pDataBuf, rcv_len, MSG_PEEK);
		if( rc < 0 ) {
			ulog(_ERROR_, " data recv error (%d:%s)", errno, strerror(errno));
			inet_Close(stidx, fd, udvalue);
			return;
		}

		if( rc == rcv_len ) {
			memset(pDataBuf, 0x00, rcv_len);
			rc = recv(fd, pDataBuf, rcv_len, 0 );
			break;
		}

		//	fragmentation
		ifragcnt++;
		if( ifragcnt > 3 ) {
			ulog(_ERROR_, " data recv issue fragmentaion !!!");
			inet_Close(stidx, fd, udvalue);
			return;
		}
		sleep(1);
	}

	roLog(_FLOW_,"[%s][%d] 시뮬레이터로 부터 개설요청 데이터 수신 Total(%d)byte", __FUNCTION__, __LINE__,  rcv_len);

	usertrace( rcv_len, pDataBuf, "RCV from Session [local:%d <-- %s:%d]", 
				g_local_listen_port, g_sim_ip, g_peer_port);

	STbl_AddRcvSndByStidx(stidx, SMT_RECV_INFO, rcv_len);

	 // 전문 생성하고 엔진에 tpcall
	memset((char*)&tdrv_frame, 0x00, sizeof(CFR_TDRV_FRAME));
	memcpy((char*)&tdrv_frame.InHead.FrameKind[0], "TDRV", 4);
	memcpy((char*)&tdrv_frame.InHead.Primitive, "indRcvDt", 8);

	// 법원 보관금 개설일 경우 설정
	// 20190827 YYK GA09 채널 추가.
	if( memcmp(pDataBuf, "GA01", 4) == 0 ||
		memcmp(pDataBuf, "GA05", 4) == 0 ||
		memcmp(pDataBuf, "GA09", 4) == 0 )
	{
		memcpy((char*)&tdrv_frame.InHead.DataKind, "B", 1);
		memcpy((char*)&tdrv_frame.PeerInfo.Protocol, "12", 2);

    	/* DealInfo Setting */
		struct tm*      pCur;
		struct timeb    st;
		char CurDate[16];

		/* 현재 시간 취득 */
		memset(CurDate, 0x00, sizeof(CurDate));

		ftime(&st);
		pCur = localtime(&st.time);
		sprintf(CurDate, "%.4d%.2d%.2d", pCur->tm_year + 1900, pCur->tm_mon + 1, pCur->tm_mday);
		memcpy((char*)&tdrv_frame.DealInfo.IssueDate, CurDate, 8);

		// DealSeq 개설이므로 0이기 때문에 R로 설정함.
		tdrv_frame.DealInfo.Rsv1[0] = 'R';
	}

	memcpy((char*)&tdrv_frame.InHead.SvcName[0], pDataBuf, 4);
	memcpy((char*)&tdrv_frame.PeerInfo.PeerIP[0], g_sim_ip, 15);
	sprintf((char*)&tdrv_frame.PeerInfo.PeerPort[0], "%d", g_peer_port);
	sprintf((char*)&tdrv_frame.PeerInfo.LocalPort[0], "%d", g_local_listen_port);
	memcpy((char*)&tdrv_frame.PeerInfo.PeerVanCode[0], pDataBuf, 4);
	
	nSndLen = sizeof(CFR_TDRV_FRAME) + rcv_len - 8;

	pSndData = tpalloc("CARRAY", NULL, nSndLen ); 	//	4 :chanid
	if( pSndData == NULL ) {
		ulog(_ERROR_, " tpalloc error (%d)", tperrno);
		exit(1);
	}

	memset(pSndData, 0x00, nSndLen);
	memcpy(pSndData, (char*)&tdrv_frame, sizeof(CFR_TDRV_FRAME)-4);
	memcpy(pSndData + (sizeof(CFR_TDRV_FRAME) - 4), (char*)pDataBuf+4, rcv_len-4); //	4 : len

	rc = tpacall("RRE1_1", pSndData, (long)nSndLen, (long)nSndOption);
	if(rc < 0) {
		ulog(_ERROR_, " tpacall error (%d)", tperrno);
		exit(1);
	}

	//roTrace('o', "RRE1_1", nSndLen, (unsigned char*)pSndData);
	roTrace('O', "RRE1_1", nSndLen, (unsigned char*)pSndData);
	ulog(_WARNING_, "채널[%.4s] : RRE1_1로 개설요청전문 전달", pDataBuf);
	
	if (pSndData) tpfree(pSndData);
	if( pDataBuf != NULL ) free(pDataBuf);

	return;
}

void    inet_Close(int stidx, int fd, int udvalue)
{
    int     l_sess_idx = -1;

	ulog(_FLOW_,	"Close event. fd=%d, udvalue=%d  ", fd, udvalue);

	if(udvalue < MAX_SESSION) {
		l_sess_idx = udvalue ;
	} else {
		l_sess_idx = udvalue - MAX_SESSION ;
	}

	if( l_sess_idx < 0 || l_sess_idx > MAX_SESSION ) {
		ulog( _ERROR_, "rsof session index or udvalue error. - "
			   "l_sess_idx(%d), udvalue(%d), MAX_SESSION(%d)"
				, l_sess_idx, udvalue, MAX_SESSION);
		rsof_resetFD(_IGNORE, fd, _IGNORE);
		STbl_DelSessionCnxByStidx(stidx);
		return;
	}

	STbl_DelSessionCnxByStidx( stidx );
	rsof_resetFD(_IGNORE, fd, _IGNORE);

	return;
}


int inet_Send(int fd, char *ptr, int nbyte, int leninfo, char* pchanid)
{
    int     rc=0;
    int     msglen=0;
    char    l_tmpbuf[32];
	char	sim_info[64];

    if( leninfo > 16 ) {
        return -10;
    }

    memset(l_tmpbuf, 0x00, sizeof(l_tmpbuf));

    /* 시뮬레이터 송신시 시뮬레이터 헤더의 길이부(6byte)를 제외한 길이를 세팅하여
        송신한다.  (전체전문길이 + VAN_CODE(4byte) => 전문길이부에 세팅 */
    snprintf(l_tmpbuf, sizeof(l_tmpbuf), "%0*d%.4s", leninfo, nbyte+4, pchanid);


    /* 송신데이터 버퍼 생성
        실전문길이 + 시뮬해더(길이부(6) + VAN_CODE(4)) */
	// 1. send length info
    msglen = leninfo+4;
    rc = rtp_sendn( fd, (char*)l_tmpbuf, msglen );
    if( rc < 0 ) {
        ulog(_ERROR_, "길이 정보(len:%d) 송신 실패!!(%d:%d)", msglen, rc, errno);
        return rc;
    }

	// 2. send messge
    msglen = nbyte;
    rc = rtp_sendn( fd, (char*)ptr, msglen );
    if( rc < 0 ) {
        ulog(_ERROR_, "데이터부분(len:%d) 송신 실패!!(%d:%d)", msglen, rc, errno);
        return rc;
    }

	memset (sim_info, 0x00, sizeof(sim_info));
	snprintf(sim_info, sizeof(sim_info), "%s:%d", g_sim_ip, g_sim_port);

    roTrace('O', sim_info, leninfo+4, (unsigned char*)l_tmpbuf);
    roTrace('O', sim_info, msglen, (unsigned char*)ptr);

    ulog(_FLOW_, "시뮬레이터로 데이터 데이터 송신 완료. 채널:(%.4s), Data(%d)byte !!", pchanid, msglen);

	return rc;
}


int SendN(int fd, char *ptr, int nbyte)
{
    int     nleft;
    int     nwritten;

    nleft = nbyte;

    while (nleft > 0 ) {
        nwritten = write(fd, ptr, nleft);

        if(nwritten <= 0 ) {
            ulog( _ABEND_, "<CHGW> write failed. rc=%d errno=%d", nwritten, errno);
            return(nwritten);
        }

        nleft -= nwritten;
        ptr   += nwritten;
    }

    return (nbyte - nleft);
}

int inet_RecvTrt(int fd, char* pchanid, int leninfo)
{
	int		rc = 0;
	int		iflagcnt = 0;
	int		iSndLen = 0;
	int		total_len = 0;

	char	lenbuf[24];
	char*	pDataBuf=NULL;
	char*	pSndBuf=NULL;

	char	sim_info[64];

	fd_set  readfds;
	struct  timeval to;

	CFR_TDRV_FRAME*		ptdrv_frame;


	FD_ZERO(&readfds);
	FD_SET( fd, &readfds);
	to.tv_sec  = 5;
	to.tv_usec = 0;

	ulog(_FLOW_, "시뮬레이터로부터 데이터 취급응답 대기 시작 (%dSec) !!!!", to.tv_sec);

	rc = select( fd+1, &readfds, NULL, NULL, &to );
	if( rc < 0 ) {
		//	Error
		ulog(_ERROR_, " select fail (%d)!!", errno );
		return -10;
	}

	if( rc == 0 ) {
		//	Error
		ulog(_ERROR_, " timeout close (%d)!!", errno );
		close(fd);
		return -20;
	}

	//	recv
	while(1) {
		if( iflagcnt >= 3 ) {
			ulog(_ERROR_, " Fragmentation 발생..Close fd");
			close(fd);
			return -30;
		}

		//	길이
		memset(lenbuf, 0x00, sizeof(lenbuf));
		rc = recv(fd, lenbuf, leninfo, MSG_PEEK);
		if(rc < 0) {
			ulog(_ERROR_, " Header read error (%d:%s)", errno, strerror(errno));
			close(fd);
			return -40;
		}

		if( rc == leninfo ) break;

		iflagcnt++;
		sleep(1);
		continue;
	}

	/* 시뮬레이터의 전문의 전문길이부가 전체길이-6byte(전문길이미포함)로 전문을
	 	수신하여 전문길이부의 길이 보다 + 6byte 추가 적으로 수신한다. */
	total_len = atoi(lenbuf) + leninfo; 

	pDataBuf = (char*)malloc(total_len);
	if( pDataBuf == NULL ) {
		ulog(_ERROR_, " malloc fail (%d:%s)", errno, strerror(errno));
		close(fd);
		return -50;
	}

	memset(pDataBuf, 0x00, total_len);

	// 데이터 수신
	while(1) {
		if( iflagcnt >= 3 ) {
			ulog(_ERROR_, " Fragmentation 발생..Close fd");
			free(pDataBuf);
			close(fd);
			return -60;
		}

		rc = recv(fd, pDataBuf, total_len, MSG_PEEK);
		if( rc < 0 ) {
			ulog(_ERROR_, " body read fail (%d:%s)", errno, strerror(errno));
			free(pDataBuf);
			close(fd);
			return -70;
		}

		/* lenbuf는 MSGPEEK으로 읽은 전문전체길이-6byte이기 때문에 수신데이터 비교
			 로직에 + 6byte를 추가하여 전체 길이를 수신 받는다. */
		if( rc == total_len ) break;

		iflagcnt++;
		sleep(1);

		continue;
	}

	//	close client
	close(fd);

	memset (sim_info, 0x00, sizeof(sim_info));
	snprintf(sim_info, sizeof(sim_info), "%s:%d", g_sim_ip, g_sim_port);
	roTrace('I', sim_info,  total_len, (unsigned char*)pDataBuf);

	ulog(_FLOW_, "시뮬레이터로 부터 취급응답 전문수신. 채널:(%.4s) data(%d)byte", pchanid, total_len);

	iSndLen = (total_len - 10) + sizeof(CFR_TDRV_FRAME) - 4 ;	// 6 + 4: data_lne + chanid

	pSndBuf = (char*)tpalloc("CARRAY", NULL, iSndLen);
	if( pSndBuf == NULL ) {
		ulog(_ERROR_, " tpalloc fail (%d)", tperrno);
		free(pDataBuf);
		return -100;
	}

	memset(pSndBuf, 0x00, iSndLen);
	ptdrv_frame = (CFR_TDRV_FRAME*)pSndBuf;

	memcpy(ptdrv_frame->InHead.FrameKind, "TDRV", 4);
	memcpy(ptdrv_frame->InHead.Primitive, "indRcvDt", 8);
	memcpy(ptdrv_frame->InHead.SvcName, pchanid, 4);
	memcpy(ptdrv_frame->PeerInfo.PeerIP, g_sim_ip, strlen(g_sim_ip));
	sprintf(ptdrv_frame->PeerInfo.PeerPort, "%d", g_sim_port);
	memcpy(ptdrv_frame->PeerInfo.PeerVanCode, pchanid, 4);

	// 법원 취급 전문 처리 
	if( memcmp(pchanid, "GA01", 4 ) == 0 ||
		memcmp(pchanid, "GA03", 4 ) == 0 ||
		memcmp(pchanid, "GA04", 4 ) == 0 )
	{
		memcpy(ptdrv_frame->InHead.Primitive, "indRcvRs", 8);
		memcpy(ptdrv_frame->InHead.DataKind, "B", 1);
		memcpy(ptdrv_frame->PeerInfo.Protocol, "12", 2);
		memcpy(ptdrv_frame->DealInfo.IssueDate, sDrvFrame.DealInfo.IssueDate, 8 );
		ptdrv_frame->DealInfo.DealSeq = sDrvFrame.DealInfo.DealSeq;
		ptdrv_frame->DealInfo.DealSvcIdx = sDrvFrame.DealInfo.DealSvcIdx;
	}

	//	데이터 복사 전문 전체 길이 - 시뮬레이터해더(길이(6byte)+CHANID(4byte)) 
	memcpy(pSndBuf + sizeof(CFR_TDRV_FRAME) - 4, pDataBuf+leninfo+4, total_len - 10); 

	rc = tpacall("RRE1_1", pSndBuf, (long)iSndLen, TPNOREPLY | TPBLOCK | TPFUNC);
	if(rc < 0) {
		ulog(_ERROR_, "tpsend error (RRE1_1) (%d)", tperrno);
		if( pDataBuf != NULL ) free(pDataBuf);
		if( pSndBuf != NULL ) tpfree(pSndBuf);
		return -110;
	}

	roTrace('O', "RRE1_1", iSndLen, (unsigned char*)pSndBuf);	

	if( pDataBuf != NULL ) free(pDataBuf);
	if( pSndBuf != NULL ) tpfree(pSndBuf);

	ulog(_FLOW_, "취급 응답전문 RRE1_1로 송신 완료 !!");

	return 0;
}
