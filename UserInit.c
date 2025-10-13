#include "tcp_iso.h"

// extern int  func_NacfGetMaxSessC(char *strAdtName);

int UserInit()
{
  char	ServerName[64];
  int		rc;
  int		i = 0;
  
  memset(ServerName, 0x00, sizeof(ServerName));
  roGetSvcName(ServerName);

#ifdef _CCL_
  // CruzChannel Log 초기화
  ccl_InitLog(ServerName, "TCPC", NULL);
#endif

#ifdef _SHB_
	/* BOK LOGIN INF ini filename 취득 */
	memset(gc_login_file, 0x00, sizeof(gc_login_file));
	rc = roReadConfigString( NULL, "BOK_CONFIG", "LOGIN_INF_FILE", gc_login_file);
	if(rc != 0) 
	{ 
		ulog(_ABEND_, "한국은행 로그인 정보 파일 경로 취득 실패 : [BOK_CONFIG] LOGIN_INF_FILE -> rc(%d)", rc);
		return -1; 
	}
	ulog(_FLOW_, "한국은행 로그인 정보 파일 경로 [%s]" , gc_login_file);
#else
  /* DB 연결 */
  rc = cf_dbcnx();
  if( rc != 0 )
  {
    ulog(_ABEND_, "[%s] db connect error [%d]", FF, rc);
    return -2;
  }
#endif

  rc = roReadConfigInt(  NULL, "SessionInfo", "DownSessCnt", &g_DnSessLimit);
  if ( rc < 0 )
  {
    ulog(_ERROR_,  "Read Down Session Cnt failed rc = %d", rc);

    // default 0
    g_DnSessLimit= 0;
  }
  ulog(_FLOW_, "Down Session Count : %d", g_DnSessLimit);


  rc = roReadConfigInt(  NULL, "SessionInfo", "UpSessCnt", &g_UpSessLimit);
  if ( rc < 0 )
  {
    ulog(_ERROR_,  "Read Up Session Cnt failed rc = %d", rc);

    // default 1
    g_UpSessLimit= 1;
  }
  ulog(_FLOW_, "Up Session Count : %d", g_UpSessLimit);


  g_maxterm_cnt = func_NacfGetMaxSessC(ServerName);
  if(g_maxterm_cnt <= 0 )
  {
    ulog(_ERROR_,  "Get Max Session failed g_maxterm_cnt = %d", g_maxterm_cnt);

    g_maxterm_cnt = 0;
  }
  ulog(_FLOW_, "Max Session Count : %d", g_maxterm_cnt);


  // Init TermTbl
  g_TermTable = NULL;
  g_TermTable = (TERM_TABLE*)malloc(sizeof(TERM_TABLE)*(g_maxterm_cnt+1));
  if( g_TermTable == NULL)
  {
    ulog(_ERROR_,  "malloc() failed : Agent Local Table : errno = %d", errno);
    return -3;
  }

  memset(g_TermTable, 0x00, sizeof(TERM_TABLE)*(g_maxterm_cnt));
  for(i=0; i<g_maxterm_cnt; i++)
  {
    func_AClearTable(i);
  }


  // Poll 정보 취득 : PollInfo - UsePoll
  g_UsePoll = 0; 	// default 미사용 : 0
  rc = roReadConfigInt(	NULL, "PollInfo", "UsePoll", &g_UsePoll);
  if ( rc < 0 )
  {
    // default 미사용 : 0
    g_UsePoll = 0;
  }

  ulog(_FLOW_, "Poll 사용여부(0:미사용, 1:사용) => [%d]", g_UsePoll);

  if(g_UsePoll == 1)
  {
    // Get PollInfo - PollInterval
    g_ReqPollInterval = 0;
    rc = roReadConfigInt(  NULL, "PollInfo", "PollInterval", &g_ReqPollInterval    );
    if ( rc < 0 ||  g_ReqPollInterval < 1)
    { 
      ulog(_WARNING_, "Config 취득 실패 : [PollInfo] PollInterval -> default 30분으로 설정", rc);

      // PollSInterval의 기본값 - 30분
      g_ReqPollInterval = 30*60;
    }

    ulog(_FLOW_, "POLL 주기 : %d", g_ReqPollInterval);


    // Get PollInfo - PollTimeOut 
    rc = roReadConfigInt(  NULL, "PollInfo", "PollTimeOut", &g_RspPollInterval    );
    if ( rc < 0 || g_RspPollInterval < 1)
    {
      ulog(_WARNING_, "Config 취득 실패 : [PollInfo] PollTimeOut -> default 30 sec로 설정");

      // Poll 응답 타이머 기본값 - 30초
      g_RspPollInterval = 30;
    }

    ulog(_FLOW_, "POLL 응답 대기 IMMER : %d", g_RspPollInterval);
  }


  // Get SessionInfo - SessMoniter/SessMonitor
  g_SessMonitor = 0;
  rc = roReadConfigInt(  NULL, "SessionInfo", "SessMoniter", &g_SessMonitor);
  if ( rc < 0 )
  {
    rc = roReadConfigInt(  NULL, "SessionInfo", "SessMonitor", &g_SessMonitor);
    if (rc < 0) {
      ulog(_WARNING_, "Config 취득 실패 : [SessionInfo] SessMoniter/SessMonitor -> default 0(미사용) 설정");

      //  기본값 - 0
      g_SessMonitor = 0;
    }
  }
  ulog(_FLOW_, "세션관리 : %d", g_SessMonitor);


  //Get Session Mgr Service
  memset( g_APSvc, 0x00, sizeof(g_APSvc) );
  rc = roReadConfigString( NULL, "SessionInfo", "SessMgrSvc", g_APSvc);
  if( (rc != 0) && (g_SessMonitor==1) )
  {
    ulog(_ABEND_, "세션관리서비스명 취득 실패 : [SessionInfo] SessMgrSvc -> rc(%d)", rc);
    return -4;
  }

  memset( g_VANCode, 0, sizeof(g_VANCode) );
  memset( g_ChanID, 0, sizeof(g_ChanID) );
  memcpy( g_VANCode, g_ServiceName, strlen(g_ServiceName) );
  memcpy( g_ChanID, g_ServiceName, strlen(g_ServiceName) );


  gi_ApDataBufAllocSize = MAX_MSG_LEN;
  ulog(_WARNING_, "Common Max Message Length set default [%d]", MAX_MSG_LEN );

  memset(gc_LogYn, 0x00, sizeof(gc_LogYn));
  rc = roReadConfigString( gc_CmnCfg, "ImageLog", "DB_LOG", gc_LogYn );
  if( rc != 0 )
  {
    ulog(_WARNING_, "Image Logging 여부 취득오류 : [ImageLog] DB_LOG --> Set default to N");
    gc_LogYn[0] = 'N';
  }
  ulog(_FLOW_, "Image Logging 여부[%c]", gc_LogYn[0]);

  /*  Proc 5. ap data *-----------------------------------------------------*/
  g_EncryptBuf = NULL;
  g_EncryptBuf = (char*)malloc(gi_ApDataBufAllocSize);
  if(g_EncryptBuf == (char*)NULL)
  {
    ulog(_ABEND_,  "Initial g_EncryptBuf malloc error [%d]" , errno);
    return -5;
  }
  memset(g_EncryptBuf, 0x00, gi_ApDataBufAllocSize);

  g_DecryptBuf = NULL;
  g_DecryptBuf = (char*)malloc(gi_ApDataBufAllocSize);
  if(g_DecryptBuf == (char*)NULL)
  {
    ulog(_ABEND_,  "Initial g_DecryptBuf malloc error [%d]" , errno);
    return -6;
  }
  memset(g_DecryptBuf, 0x00, gi_ApDataBufAllocSize);


  // 실제 연결된 세션수
  g_RCntCount = 0;

  // 마지막 송신한 세션
  g_SndIdx = 0;

  // Poll off 상태
  //	g_OnPolling = 0; 

  // DOWN:0  UP:1
  g_SessStat = 0;

  return 0;
}
