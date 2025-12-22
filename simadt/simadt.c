#include "simadt.h"
#include "tplib/ulog.h"

CFR_TDRV_FRAME sDrvFrame;

void SIMADT2(TPSVCINFO* msg)
{
	unsigned short	sSteps;

	int				rc = 0;  
	int				fd = 0;; 
	int				fdlen = 0;; 
	int				stidx = 0;;
	int				ipeerport = 0;
	int             idx_srcsvc = 0;

	long			nSndOption = TPNOREPLY | TPBLOCK | TPFUNC;

	//char*			pSndData = NULL; 
	CFR_TDRV_FRAME*	p_tdrv_frame = NULL;

	char			l_chid_svc_name[16];
	char            name_srcsvc[MAX_SVC_NAME+1];
	char            cpeerip[15+1];
	char            cpeerport[5+1];

	in_addr_t		inaddr;


	/*-------------------------------------*
	|   source정보 GET ...                 |
	| -----------------------------------  |
	|   1. src NAME                        |
	|   2. src PIDX                        |
	*-------------------------------------*/
	memset(name_srcsvc, 0x00, sizeof(name_srcsvc));
	tpgetsndsvc(name_srcsvc, &idx_srcsvc);

	// 20190827 YYK 추가
	if ( memcmp( msg->data, "RCOM", 4) == 0 ) {
		roLog(_WARNING_, "[%s][%d] 수신데이터는 처리하지 않습니다.rreldcfg 전문", __FUNCTION__, __LINE__);
		return -1;
	}

	ulog(_WARNING_,   "[부가정보] 서비스 start. src=%s:%02d. msg_len=%d",
				name_srcsvc, idx_srcsvc, msg->len);

	roTrace(TL_TRACEINPUT, name_srcsvc, msg->len, (unsigned char*)msg->data);

	//	길이 검증
	if( msg->len < sizeof(CFR_TDRV_FRAME)) {
		ulog(_ERROR_," 해당 전문은 TDRV길이보다 작습니다. ");
		tpreturn(TPFAIL, 0, NULL, 0, 0);
	}

	p_tdrv_frame = (CFR_TDRV_FRAME *)msg->data;

	/*-------------------------------------*
	|   CHID GET ...  		               |
	| -----------------------------------  |
	|   g_my_mode == 'M' 이면
	|	chid 에 해당하는 서비스로 호출만 한다.
	|
	|   g_my_mode != 'M' 이면
	|	chid index를 구하고
	|	inet_Connect 호출하고 전문 전송.
	*-------------------------------------*/

	ulog(_FLOW_, "CHID PeerInfo [%.4s] dealinfo CHID [%.4s]", 
		, p_tdrv_frame->PeerInfo.PeerVanCode, p_tdrv_frame->DealInfo.VanCode);

	memset(l_chid_svc_name, 0x00, sizeof(l_chid_svc_name));
	memcpy(l_chid_svc_name, (char*)&p_tdrv_frame->DealInfo.VanCode[0], 4);

	if( g_my_mode == 'M' ) { //TEST_SIMX 일 때
		//	Child 로 송신
		//	group_svcname 재설정.
		ulog(_FLOW_, "group_svcname [%s] [%d]", g_groupinfo[g_my_group_idx].group_svcname, g_my_group_idx);
		ulog(_FLOW_, "chid_name [%s]", l_chid_svc_name);

		rc = tpacall( g_groupinfo[g_my_group_idx].group_svcname, msg->data, msg->len, (long)nSndOption );
		if( rc < 0 ) {
			ulog(_ERROR_, "SIMADT 서비스로  tpcall failed rc(%d) ", rc);
			tpreturn(TPFAIL, 0, NULL, 0, 0);
		}

		//20190827 YYK 로그 수정
		roTrace(TL_TRACEOUTPUT, g_groupinfo[g_my_group_idx].group_svcname, msg->len, (unsigned char*)msg->data);
		ulog(_ERROR_, "SIMADT 서비스로  tpcall 성공");
		tpreturn(TPSUCCESS, 0, NULL, 0, 0);
	}

	///////////////////////////////
	//	취급 / 개설 구분
	///////////////////////////////
	if( g_my_mode == 'S' || g_my_mode == 'G' ) { //	취급 
		if( p_tdrv_frame->DealInfo.Rsv1[0] == 'R'
		|| p_tdrv_frame->DealInfo.Rsv1[0] == 'I' )
		{
			ulog(_WARNING_, "취급 요청 거래 to 시뮬레이터");
			//	connect
			fd = inet_Connect();
			if ( fd < 0 ) {
				ulog(_ERROR_, "시뮬레이터 서버 Connect 실패..");
				tpreturn(TPFAIL, 0, NULL, 0, 0);
			}

			ulog(_FLOW_, "시뮬레이터 서버 connect [%s]", l_chid_svc_name);
			
			//	Send
			rc = inet_Send( fd, msg->data+(sizeof(CFR_TDRV_FRAME)-4), msg->len-(sizeof(CFR_TDRV_FRAME)-4), 6, l_chid_svc_name );
			if ( rc < 0 ) {
				ulog(_ERROR_, " 전문 송신 실패(%d)", rc );
				tpreturn(TPFAIL, 0, NULL, 0, 0);
			}

			//	법원어뎁터 (보관금, 집행관 공탁금(취급))
			if( memcmp( l_chid_svc_name, "GA01", 4 ) == 0 ||
				memcmp( l_chid_svc_name, "GA03", 4 ) == 0 ||
				memcmp( l_chid_svc_name, "GA04", 4 ) == 0 )
			{
				char* p = (char*)&sDrvFrame;

				memset(p, 0x00, sizeof(CFR_TDRV_FRAME));
				memcpy(p, p_tdrv_frame, sizeof(CFR_TDRV_FRAME));
			}

			//	RSET_1에 송신
			//	tdrv 수정 ..  p_tdrv_frame = (CFR_TDRV_FRAME *)msg->data;
			memcpy(p_tdrv_frame->InHead.Primitive, "rspSndDt", 8 );
			memset(p_tdrv_frame->InHead.SvcName, 0x00, sizeof(p_tdrv_frame->InHead.SvcName));
			memcpy(p_tdrv_frame->InHead.SvcName, l_chid_svc_name, strlen(l_chid_svc_name));
			sSteps = p_tdrv_frame->DealInfo.Steps;
			sSteps = sSteps & 0xFF00;
			sSteps += 3;
			p_tdrv_frame->DealInfo.Steps = sSteps;
			memcpy(p_tdrv_frame->InHead.RsltCode, "0000", 4 );

			rc = tpacall( "RSET1_1", msg->data, msg->len, (long)nSndOption );
			if( rc < 0 ) {
				ulog(_ERROR_, " tpacall error to RSET !!(%d)", tperrno);
				tpreturn(TPFAIL, 0, NULL, 0, 0);
			}

			roTrace(TL_TRACEOUTPUT, "RSET1_1", msg->len, (unsigned char*)msg->data);

			//	전문 수신
			rc = inet_RecvTrt(fd, l_chid_svc_name, 6);
			if( rc < 0 ) {
				ulog(_ERROR_, " 전문 수신 실패(%d)", rc );
				tpreturn(TPFAIL, 0, NULL, 0, 0);
			}
		}
		else //	개설
		{
			ulog(_WARNING_, "개설 응답 거래 to 시뮬레이터");
			//	fd 찾기..
			memset(cpeerip, 0x00, sizeof(cpeerip));
			memset(cpeerport, 0x00, sizeof(cpeerport));

			//	TODO : DB에서 찾기
			ulog(_FLOW_, "[%s][%d] 거래로그에서 PEER_IP, PEER_PORT 정보를 취득하여 응답할 세션을 찾는다\n"
					"거래로그 조회 시작" );
			
			rc = lf_SelectDealMaster(p_tdrv_frame, cpeerip, &ipeerport);
			if( rc < 0 ) {
				ulog(_ERROR_, "해당 개설 로그가 없어서 fd취득오류... (%d)\n"
						"채널 : [%.4s] 일자 : [%.8s] DEAL_SEQ : [%d]", rc
						, p_tdrv_frame->DealInfo.VanCode, p_tdrv_frame->DealInfo.IssueDate, p_tdrv_frame->DealInfo.DealSeq);
				tpreturn(TPFAIL, 0, NULL, 0, 0);
			}

			memcpy(cpeerip, cpeerip, strlen(cpeerip));
			sprintf(cpeerport, "%d", ipeerport);

			ulog(_FLOW_, "PEER IP:PORT [%s:%s]", cpeerip, cpeerport);

			inaddr = inet_addr(cpeerip);
			stidx = rsof_findStidx(TYPE_PEER, 1, (in_addr_t)inaddr, (unsigned short)atoi(cpeerport));
			if( stidx < 0 ) {
				ulog(_ERROR_, "대외MCA 세션테이블에 Session 없음... (%d)\n"
						"PEER IP:PORT [%s:%s]", stidx, cpeerip, cpeerport);
				tpreturn(TPFAIL, 0, NULL, 0, 0);
			}

			fdlen = sizeof(fd); 
			rc = rsof_getSessionInfo(stidx, _IGNORE, _IGNORE, RSOF_FDNUM, &fd, &fdlen);
			if( rc < 0 ) {
				ulog(_ERROR_, "해당 fd  없음... (%d)", rc);
				tpreturn(TPFAIL, 0, NULL, 0, 0);
			}

			//	Send
			ulog(_FLOW_, "connect [%s]", l_chid_svc_name);
			rc = inet_Send( fd, msg->data+(sizeof(CFR_TDRV_FRAME)-4)
								  , msg->len-(sizeof(CFR_TDRV_FRAME)-4)
								  , 6 , l_chid_svc_name );
			if ( rc < 0 ) {
				ulog(_ERROR_, " 전문 송신 실패(%d)", rc );
				tpreturn(TPFAIL, 0, NULL, 0, 0);
			}

			//	close
			ulog(_FLOW_, "해당 fd  Close !! --> BADFD로 나올수 있음...");
			STbl_DelSessionCnxByStidx( stidx );
			close(fd);

			//	tdrv 수정 ..  p_tdrv_frame = (CFR_TDRV_FRAME *)msg->data;
			memcpy(p_tdrv_frame->InHead.Primitive, "rspSndDt", 8 );
			memset(p_tdrv_frame->InHead.SvcName, 0x00, sizeof(p_tdrv_frame->InHead.SvcName));
			memcpy(p_tdrv_frame->InHead.SvcName, l_chid_svc_name, strlen(l_chid_svc_name));
			sSteps = p_tdrv_frame->DealInfo.Steps;
			sSteps = sSteps & 0xFF00;
			sSteps += 3;
			p_tdrv_frame->DealInfo.Steps = sSteps;
			memcpy(p_tdrv_frame->InHead.RsltCode, "0000", 4 );

			//	RSET_1에 송신
			rc = tpacall( "RSET1_1", msg->data, msg->len, (long)nSndOption );
			if( rc < 0 ) {
				ulog(_ERROR_, " tpacall error to RSET !!(%d)", tperrno);
				tpreturn(TPFAIL, 0, NULL, 0, 0);
			}

			ulog(_FLOW_, "RSET1_1로 송신");
			roTrace(TL_TRACEOUTPUT, "RSET1_1", msg->len, (unsigned char*)msg->data);
		}
	}

	tpreturn(TPSUCCESS, 0, NULL, 0, 0);
}
