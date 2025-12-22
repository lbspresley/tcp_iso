/*------------------------------------------------------------------------------
                       columns = 80          tabstop = 4                        
----------------------------------------------------------------------------  
	FILE NAME    : sv_sr_init.c 
	DESCRIPTIOIN : 

	DATA & NAME  : 2014/02/10 (이영근)
------------------------------------------------------------------------------*/
#include "simadt.h"
#include "tplib/ulog.h"


char* GWLINK_VERSION_NUM = "###### GW Link Module ver 1.0 (2014/02/17) ######"; 


extern void SIMADT2( TPSVCINFO *msg );

/*------------------------------------------------------------------------------
 MOUDLE  NAME  : tpsvrinit
 DESCRIPTIOIN  : TP 서버 초기화 함수  

 INPUT  VALUE  : int argc, char* argv[] 
 OUTPUT VALUE  : 
 RETURN VALUE  : 0 

 DATA &  NAME  : 2014-02-10  
------------------------------------------------------------------------------*/

int tpsvrinit(int argc, char* argv[])
{
	int 	rc;
	char	*pSvcname;
	extern int tpcfg_getsvclst(char *p_svrname, char **svclist);

	tpgetmysvr( g_name_mysvr );

	rc = tpcfg_getsvclst( g_name_mysvr, &pSvcname );
	if( rc < 0 ) {
		ulog(_ERROR_,	"[장애내용] 서비스 이름 취득 실패 : tpcfg.m 내용을 확인하세요" );
		return -1;
	}

	ulog( 0, "count(%d) SVC(%s)", rc, pSvcname );
	memset( g_name_mysvc, 0x00, sizeof(g_name_mysvc) );
	strcpy( g_name_mysvc, pSvcname );
	free( pSvcname );

	/*-------------------------------------*
	| 서비스명 셋팅                        |
	*-------------------------------------*/
	rc  = tpadvertise( g_name_mysvc, SIMADT2 );
	if( rc < 0 ) {
		ulog(_ERROR_, "[장애내용] tpadvertise tperrno(%d)", tperrno);
		exit(-1);
	}
	ulog(_FLOW_,	"[상세내용] Advertise SIMADT2->%s " , g_name_mysvc);


	/*-------------------------------------*
	| TCP/IP 정보 취득                     |
	*-------------------------------------*/
	/* 환경 파일에서 정보 취득 */
	if( ( rc = Read_FILE_Info() ) < 0 ) {
		ulog(_ERROR_, "[장애내용] 환경파일 취득 실패 rc(%d)", rc);
		return -1;
	}

	/*-------------------------------------*
	| TCP/IP 정보 table 초기화             |
	*-------------------------------------*/
	if( g_my_mode != 'M') {
		memset(g_session_info, 0x00, sizeof(g_session_info));
		rc = STbl_init( 0, NULL, 0, 0 );
    	if( rc < 0 ) {
			ulog( _ERROR_, "STbl_init() rc=%d", rc );
		}
	}


	/*-------------------------------------*
	| DB Connect						   |
	*-------------------------------------*/
	rc = cfrf_DBCNX();
	if( rc < 0 ) {
		ulog(_ERROR_, "[장애내용] DB Connect Fail (%d)", rc );
		return -1;
	}

	if ( g_my_mode == 'M' ) {
		roLog(_ERROR_, "[%s][%d] 시뮬레이터 실제 소켓프로그램으로 tpacall만 한다.\n"
						"취급요청, 개설응답에만 관여한다."
						, __FUNCTION__, __LINE__);

	} else {
		roLog(_ERROR_, "[%s][%d] 시뮬레이터와 연계하는 실제 TCP 소켓\n"
						"1. TEST_SIMX로부터 취급요청을 받아 시뮬레이터로 전송 후 취급응답을 RRE1_1로 전송(SYNC)\n"
						"2. 시뮬레이터로부터 개설요청을 받아 RRE1_1로 전송\n"
						"3. TEST_SIMX로부터 개설응답을 받아 개설요청을 받은 세션을 찾아 시뮬레이터로 전송"
						, __FUNCTION__, __LINE__);
	}

	return 0;
}


/*------------------------------------------------------------------------------
 MOUDLE  NAME  : usermain 
 DATA &  NAME  : 2014-02-10 
------------------------------------------------------------------------------*/
int usermain(int argc,char** argv)
{ 
	int     rc;

	rc = rdf_init();
	if(rc != 0) {
		ulog(_ERROR_,  "rdf_init() failed. rc=%d" , rc);
		exit(-1);
	}

	if( g_my_mode != 'M') {
		rdf_setUserInitCF(rrdf_UserInit);
		rdf_setThreadProcCF(rrdf_ProcSock);
	}

	rdf_main();

	return 0;
}

/*------------------------------------------------------------------------------
 MOUDLE  NAME  : Read_FILE_Info 
 DATA &  NAME  : 2014-02-10 
------------------------------------------------------------------------------*/
int	Read_FILE_Info()
{
	int			rc;
// 20161027 유예근. 전환 영업점 테스트시 여러개 기동을 위해 컨피그명 수정
//	snprintf( g_commoncfg, sizeof(g_commoncfg), "%s/config/upconfig/simadt2.ini", getenv( "ROME_HOME" ) );
	snprintf( g_commoncfg, sizeof(g_commoncfg), "%s/config/upconfig/%s.ini",getenv( "ROME_HOME" ), g_name_mysvr );

	rc = read_common_info( );
	if( rc < 0 ) {
		return -1;
	}

	memset(g_groupinfo, 0x00, sizeof(g_groupinfo));
	rc = read_group_info( );	//	mode 취득
	if( rc < 0 ) {
		return -2;
	}

	return 0;
}

int read_common_info( )
{
	int rc;

	/*-------------------------------------*
	| 1. COMMON 정보 취득     
	| 1-1. 최대 GROUP 갯수 (default:1) GROUP당 채널
	| 1-2. GROUP당 최대 수용 채널 갯수 (max & default:100)
	| 1-3. 읽을 총 CHID 갯수
	| 1-4. Simulator IP 
	| 1-5. 접속용 BIND IP 
	*-------------------------------------*/
	rc = roReadConfigInt( NULL, "COMMON", "max_group_count", &max_group_count );
	if( rc < 0 )
	{
		max_group_count = 1;
		rc = roReadConfigInt( g_commoncfg, "COMMON", "max_group_count", &max_group_count );
		if( rc < 0 )
		{
			ulog( _WARNING_, "[COMMON]-max_group_count --> %d. by default", max_group_count );
		}
		else
		{
			ulog( _WARNING_, "[COMMON]-max_group_count --> %d. by common config(%s)", max_group_count, g_commoncfg );
		}
	}

	rc = roReadConfigInt( NULL, "COMMON", "max_group_per_ch", &max_group_per_ch );
	if( rc < 0 )
	{
		max_group_per_ch = 100;
		rc = roReadConfigInt( g_commoncfg, "COMMON", "max_group_per_ch", &max_group_per_ch );
		if( rc < 0 )
		{
			ulog( _WARNING_, "[COMMON]-max_group_per_ch --> %d. by default", max_group_per_ch );
		}
		else
		{
			ulog( _WARNING_, "[COMMON]-max_group_per_ch --> %d. by common config(%s)", max_group_per_ch, g_commoncfg );
		}
	}

	rc = roReadConfigInt( NULL, "COMMON", "max_chid_count", &max_chid_count );
	if( rc < 0 )
	{
		rc = roReadConfigInt( g_commoncfg, "COMMON", "max_chid_count", &max_chid_count );
		if( rc < 0 )
		{
			ulog( _WARNING_, "[COMMON]-max_chid_count --> Not Found by common config(%s)", g_commoncfg );
			return -1;
		}
		else
		{
			ulog( _WARNING_, "[COMMON]-max_chid_count --> %d. by common config(%s)", max_chid_count, g_commoncfg );
		}
	}

	memset(g_sim_ip, 0x00, sizeof(g_sim_ip));
	memset(g_sim_bind_ip, 0x00, sizeof(g_sim_bind_ip));

	rc = roReadConfigString( NULL, "COMMON", "sim_ip", g_sim_ip);
	if( rc < 0 )
	{
		strcpy( g_sim_ip, "127.0.0.1" );
		rc = roReadConfigString( g_commoncfg, "COMMON", "sim_ip", g_sim_ip);
		if( rc < 0 )
		{
			ulog( _WARNING_, "[COMMON]-sim_ip --> %s by default", g_sim_ip );
		}
		else
		{
			ulog( _WARNING_, "[COMMON]-sim_ip --> %s by common config(%s)", g_sim_ip, g_commoncfg );
		}
	}

	rc = roReadConfigString( NULL, "COMMON", "bind_ip", g_sim_bind_ip);
	if( rc < 0 )
	{
		strcpy( g_sim_bind_ip, "127.0.0.1" );
		rc = roReadConfigString( g_commoncfg, "COMMON", "bind_ip", g_sim_bind_ip);
		if( rc < 0 )
		{
			ulog( _WARNING_, "[COMMON]-bind_ip --> %s by default", g_sim_bind_ip );
		}
		else
		{
			ulog( _WARNING_, "[COMMON]-bind_ip --> %s by common config(%s)", g_sim_bind_ip, g_commoncfg );
		}
	}

	rc = roReadConfigInt( NULL, "COMMON", "port", &g_sim_port);
	if( rc < 0 )
	{
		ulog( _ERROR_, "[COMMON]-port --> %d 취득에러", rc);
		return -1;
	}

	rc = roReadConfigInt( NULL, "COMMON", "listen", &g_local_listen_port);
	if( rc < 0 )
	{
		ulog( _ERROR_, "[COMMON]-listen --> %d 취득에러", rc);
		return -1;
	}

	ulog( _FLOW_, "SIMNULATOR IP INFO : ip(%s) bind_ip(%s) port(%d)", g_sim_ip, g_sim_bind_ip, g_sim_port );


	return 0;
}


int read_group_info( )
{
	int 		rc = 0;
	int			i = 0;
	int			l_count = 0;
	char		key[64];

	char		tmpbuf[24];

	/*-------------------------------------*
	| 1. GROUP 정보 취득     
	|    group 이 0 이면 main 에서 모두 처리하고 CHID 에서 group 선언하지 않아도 되도록 구현...--> 나중에
	| 1-1. group_main 취득
	| 1-2. group 갯수만큼 취득
	*-------------------------------------*/
	memset( g_group_main, 0x00, sizeof(g_group_main));
	rc = roReadConfigString(g_commoncfg, "GROUP", "group_main", g_group_main);
	if( rc < 0 ) {
		return -1;
	}

#if _DEBUG_
		ulog( _FLOW_, "[GROUP]\n" "group_main=%s", g_group_main);
#endif

	if( max_group_count == 0 ) {
		g_my_mode = 'S';	/* Single Mode	*/
	} else if( memcmp(g_name_mysvc, g_group_main, sizeof(g_name_mysvc)) == 0) {
		g_my_mode = 'M';	/* Main Mode	*/
	} else {
		g_my_mode = 'G';	/* Group Mode	*/
	}

	g_groupinfo[0].onuse	= 1;
	g_groupinfo[0].group_idx= 0;
	memcpy((char*)&g_groupinfo[0].group_svcname[0], g_group_main, strlen(g_group_main));

	l_count = 0;
	g_my_group_idx = 0;

	for( i=0 ; i < max_group_count ; i++)
	{
		memset(key, 0x00, sizeof(key));
		sprintf(key, "group_%d", i+1);

		memset(tmpbuf, 0x00, sizeof(tmpbuf));
		rc = roReadConfigString(g_commoncfg, "GROUP", key, tmpbuf);
		if( rc < 0 ) {
			continue;
		}

		/* 그룹은 무조건 idx 맞추어야 됨. */
		l_count++;
		g_groupinfo[l_count].onuse	= 1;
		g_groupinfo[l_count].group_idx= i;
		memcpy((char*)&g_groupinfo[l_count].group_svcname[0], tmpbuf, strlen(tmpbuf));
		g_my_group_idx = l_count;
	}

	if( (g_my_mode == 'G') && (g_my_group_idx == 0) ) {
		ulog( _ERROR_, "GROUP SERVICE NAME NOT FOUND.(my_svcname:%s)", g_name_mysvc);
		return -2;
	}

	ulog( _FLOW_, "MAX_GROUP_COUNT(%d), 취득 GROUP_COUNT(%d)", max_group_count, l_count );
	ulog( _FLOW_, "MY_MODE(%s), MY_GROUP_ID(%d)", 
			(g_my_mode=='M')?"Main":(g_my_mode=='S')?"Single":"Group", g_my_group_idx );

	ulog( _FLOW_, "group_svcname[%s][%d]", g_groupinfo[g_my_group_idx].group_svcname, g_my_group_idx);

	return 0;
}


int read_chid_info( )
{
	int 		rc;
	int 		i;
	int			l_port;
	int			l_subport;
	int			l_idx;
	int			l_group_idx;

	char		section[80];
	char		chid_buf[80];
	char		group_buf[80];
	char		group_svc[16+1];

	/*-------------------------------------*
	| 1. 'S' : group 선언이 없어나 같은 것만 읽는다. 최대 수용 채널 체크 필수
	| 1. 'M' : 전 채널을 읽는다. GROUP별 최대 수용 채널 체크는 일단 하지 않는다.
	| 2. 'G' : group 이 같은 것만 읽는다. 최대 수용 채널 체크 필수
	*-------------------------------------*/

	gi_chid_count = 0;
	for( i=0 ; i < max_chid_count ; i++) {
		memset(section, 0x00, sizeof(section));
		sprintf(section, "CHID_%d", i+1);

		memset(chid_buf, 0x00, sizeof(chid_buf));
		rc = roReadConfigString(g_commoncfg, section, "chid", chid_buf);
		if( rc < 0 ) {
			continue;
		}

		l_port = 0;
		rc = roReadConfigInt(g_commoncfg, section, "port", &l_port);
		if( rc < 0 ) {
			continue;
		}
		if( l_port < 1024 || l_port > 65535 ) {
			ulog( _WARNING_, "CHID_%d : Invalid PORT(%d)", i+1, l_port );
			continue;
		}

		rc = roReadConfigInt(g_commoncfg, section, "subport", &l_subport);
		if( rc < 0 ) {
			l_subport = l_port;
		}

		if( l_subport < 1024 || l_subport > 65535 ) {
			ulog( _WARNING_, "CHID_%d : Invalid SUB-PORT(%d)", i+1, l_subport );
			continue;
		}

		memset(group_buf, 0x00, sizeof(group_buf));
		rc = roReadConfigString(g_commoncfg, section, "group", group_buf);
		if( rc < 0 ) {
			continue;
		}

		l_group_idx = atoi((char*)&group_buf[6]);

		ulog( _FLOW_, "CHID[%s] Mode(%c) MyGroup(idx:%d), cfg(idx:%d)", chid_buf, g_my_mode, g_my_group_idx, l_group_idx);

		if( (g_my_mode == 'G') && (g_my_group_idx == l_group_idx) ) {
			ulog( _FLOW_, "[%s] : Mode(%c), Group(idx:%d)", chid_buf, g_my_mode, g_my_group_idx );
		} else if( g_my_mode == 'M' || g_my_mode == 'S' ) {
			ulog( _FLOW_, "Main or Single Mode : %c", g_my_mode );
		} else {
			ulog( _WARNING_, "[%s] is other group", chid_buf);
			continue;
		}

		if( g_my_mode != 'M' ) {
			if( gi_chid_count >= max_group_per_ch ) {
				ulog( _ERROR_, "MAX_GROUP_PER_CH(%d) OVER.", max_group_per_ch );
				break;
			}
		}

		gi_chid_count++;
		l_idx = gi_chid_count;
		g_chidinfo[l_idx].onuse    = 1;
		g_chidinfo[l_idx].chid_idx = l_idx;
		g_chidinfo[l_idx].port     = (short)l_port;
		g_chidinfo[l_idx].subport  = (short)l_subport;
		memcpy((char*)&g_chidinfo[l_idx].chid_name[0], chid_buf, strlen(chid_buf));

		memset(group_svc, 0x00, sizeof(group_svc));
		rc = roReadConfigString(g_commoncfg, "GROUP", group_buf, group_svc);
		if( rc < 0 ) {
			ulog( _ERROR_, "그룹ID[%s] : 해당 그룹 서비스명이 설정 되어 있지 않습니다.", group_buf);
			break;
		}

		memcpy((char*)&g_chidinfo[l_idx].group_svcname[0], group_svc, strlen(group_svc));

#if _DEBUG_
		ulog( 1, "[%s]\n"
				 "chid=%s\n"
				 "port=%d\n"
				 "subport=%d\n"
				 "group=%s"
				 , section, chid_buf, l_port, l_subport, group_buf);
		ulog( 1, "idx(%d), port(%d), subport(%d), chid_name(%s), group(%s)"
				, g_chidinfo[l_idx].chid_idx 
				, g_chidinfo[l_idx].port
				, g_chidinfo[l_idx].subport
				, g_chidinfo[l_idx].chid_name
				, g_chidinfo[l_idx].group_svcname );
#endif
	}

	ulog( 0, "MAX_CHID_COUNT(%d), 취득 CHID_COUNT(%d)", max_chid_count, gi_chid_count );

	return 0;
}
