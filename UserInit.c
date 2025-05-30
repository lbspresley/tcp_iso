#include "tcp_bok.h"

extern int  func_NacfGetMaxSessC(char *strAdtName);

void UserInit()
{
  /*	var	*----------------------------------------------------------------*/
  char	ServerName[64];
  int		rc;
  int		i = 0;
  //char	TmpStr[64];

  /*	init	*------------------------------------------------------------*/
  memset(ServerName, 0x00, sizeof(ServerName));
  roGetSvcName(ServerName);

#ifdef _CCL_
  // CruzChannel Log 초기화
  ccl_InitLog(ServerName, "TCPC", NULL);
#endif

  /* DB 연결 */
  rc = cf_dbcnx();
  if( rc != 0 )
  {
    ulog(_ABEND_, "[%s] db connect error [%d]", FF, rc);
    //return -1;
    exit(-1);
  }


  /*	proc	*------------------------------------------------------------*/
  rc = roReadConfigInt(  NULL, "SessionInfo", "DownSessCnt", &g_DnSessLimit);
  if ( rc < 0 )
  {
    ulog(_ERROR_,  "[%s] Read Down Session Cnt failed rc = %d", __FUNCTION__, rc);

    // default 0
    g_DnSessLimit= 0;
  }
  ulog(_FLOW_, "[%s] Down Session Count : %d", __FUNCTION__, g_DnSessLimit);


  rc = roReadConfigInt(  NULL, "SessionInfo", "UpSessCnt", &g_UpSessLimit);
  if ( rc < 0 )
  {
    ulog(_ERROR_,  "[%s] Read Up Session Cnt failed rc = %d", __FUNCTION__, rc);

    // default 1
    g_UpSessLimit= 1;
  }
  ulog(_FLOW_, "[%s] Up Session Count : %d", __FUNCTION__, g_UpSessLimit);


  g_maxterm_cnt = func_NacfGetMaxSessC(ServerName);
  if(g_maxterm_cnt <= 0 )
  {
    ulog(_ERROR_,  "[%s] Get Max Session failed g_maxterm_cnt = %d", __FUNCTION__, g_maxterm_cnt);

    g_maxterm_cnt = 0;
  }

  ulog(_FLOW_, "[%s] Max Session Count : %d", __FUNCTION__, g_maxterm_cnt);


  // Init TermTbl
  g_TermTable = NULL;
  g_TermTable = (TERM_TABLE*)malloc(sizeof(TERM_TABLE)*(g_maxterm_cnt+1));
  if( g_TermTable == NULL)
  {
    ulog(_ERROR_,  "[%s] malloc() failed : Agent Local Table : errno = %d", __FUNCTION__, errno);
    exit(-1);
  }
  memset(g_TermTable, 0x00, sizeof(TERM_TABLE)*(g_maxterm_cnt));
  for(i=0; i<g_maxterm_cnt; i++)
  {
    func_AClearTable(i);
  }


  // Get SessionInfo - AutoDisCnt
  rc = roReadConfigInt(  NULL, "SessionInfo", "AutoDisCnt", &g_AutoDisCnt);
  if ( rc < 0 )
  {
    // default 미사용 : 0
    g_AutoDisCnt = 0;
  }
  ulog(_FLOW_, "[%s] 세션 종료 사용여부(0:미사용, 1:사용) => [%d]", __FUNCTION__, g_AutoDisCnt);

  if( g_AutoDisCnt == 1)
  {
    // Get SessionInfo - DisCntInterval
    rc = roReadConfigInt(	NULL, "SessionInfo", "DisCntInterval", &g_DisCntInterval);
    if ( rc < 0 ) 
    {
      ulog(_WARNING_, "[%s] Config 취득 실패(rc:%d)\n"
          "[SessionInfo] DisCntInterval -> default 60 sec로 설정", __FUNCTION__, rc);

      // TimerInterval의 기본값 - 1분
      g_DisCntInterval = 60; 
    }
    if(g_DisCntInterval < 1) 
    {
      ulog(_WARNING_, "[%s] Config 설정 오류(value:%d)\n"
          "[SessionInfo] DisCntInterval -> default 60 sec로 설정", __FUNCTION__, g_DisCntInterval);

      // TimerInterval의 기본값 - 1분
      g_DisCntInterval = 600; 
    }
    ulog(_FLOW_, "[%s] 세션 종료 주기 => [%d]", __FUNCTION__, g_DisCntInterval);
  }


  // Poll 정보 취득 : PollInfo - UsePoll
  g_UsePoll = 0; 	// default 미사용 : 0

  rc = roReadConfigInt(	NULL, "PollInfo", "UsePoll", &g_UsePoll);
  if ( rc < 0 )
  {
    // default 미사용 : 0
    g_UsePoll = 0;
  }

  ulog(_FLOW_, "[%s] Poll 사용여부(0:미사용, 1:사용) => [%d]", __FUNCTION__, g_UsePoll);

  if(g_UsePoll == 1)
  {
    // Get PollInfo - PollInterval
    rc = roReadConfigInt(  NULL, "PollInfo", "PollInterval", &g_ReqPollInterval    );
    if ( rc < 0 ) 
    { 
      ulog(_WARNING_, "[%s] Config 취득 실패(rc:%d)\n" 
          "[PollInfo] PollSInterval -> default 60 sec로 설정", __FUNCTION__, rc);

      // TimerInterval의 기본값 - 1분
      g_ReqPollInterval = 300;
    }
    if(g_ReqPollInterval < 1)
    {
      ulog(_WARNING_, "[%s] Config 설정 오류(value:%d)\n" 
          "[PollInfo] PollSInterval -> default 60 sec로 설정", __FUNCTION__, g_ReqPollInterval);

      // PollSInterval의 기본값 - 1분
      g_ReqPollInterval = 60;
    }
    ulog(_FLOW_, "[%s] POLL 주기 : %d", __FUNCTION__, g_ReqPollInterval);


    // Get PollInfo - PollTimeOut 
    rc = roReadConfigInt(  NULL, "PollInfo", "PollTimeOut", &g_RspPollInterval    );
    if ( rc < 0 )
    {
      ulog(_WARNING_, "[%s] Config 취득 실패(rc:%d)\n"
          "[PollInfo] PollWInterval -> default 60 sec로 설정", __FUNCTION__, rc);

      // TimerInterval의 기본값 - 1분
      g_RspPollInterval = 60;
    }
    if(g_RspPollInterval < 1)
    {
      ulog(_WARNING_, "[%s] Config 설정 오류(value:%d)\n" 
          "[PollInfo] PollWInterval -> default 60 sec로 설정", __FUNCTION__, g_RspPollInterval);

      // PollWInterval의 기본값 - 1분
      g_RspPollInterval = 60;
    }
    ulog(_FLOW_, "[%s] POLL 응답 대기 IMMER : %d", __FUNCTION__, g_RspPollInterval);
  }


  // Get PollInfo - PollTimeOut
  g_SessMonitor = 0;
  rc = roReadConfigInt(  NULL, "SessionInfo", "SessMoniter", &g_SessMonitor);
  if ( rc < 0 )
  {
    ulog(_WARNING_, "[%s] Config 취득 실패(rc:%d)\n"
        "[SessInfo] 세션관리 여부 -> default 1(사용함) 설정", __FUNCTION__, rc);

    //  기본값 - 1
    g_SessMonitor=1;
  }
  else
  {
    ulog(_FLOW_, "[%s] 세션관리 사용함");
  }


  //Get Session Mgr Service
  memset( g_APSvc, 0x00, sizeof(g_APSvc) );
  rc = roReadConfigString( NULL, "SessionInfo", "SessMgrSvc", g_APSvc);
  if( (rc != 0) && (g_SessMonitor==1) )
  {
    ulog(_ABEND_, "[UserInit] [%s] %s 취득 실패 rc=%d",
        "Local", "세션관리서비스명", rc);
    exit(-1);
  }


  // Get VanCode
  memset( g_VANCode, 0x00, sizeof(g_VANCode) );
  rc = roReadConfigString( NULL, "SessionInfo", "VanCode", g_VANCode );
  if(rc != 0)
  {
    ulog(_ABEND_, "[UserInit] [%s] %s 취득 실패 rc=%d",
        "Local", "채널코드", rc);
    exit(-1);
  }
  memcpy( g_ChanID, g_VANCode, strlen(g_VANCode) );


  /*  Proc 4. gi_ApDataBufAllocSize   *-------------------------------------*/
  gi_ApDataBufAllocSize = 0;
  rc = roReadConfigInt( gc_CmnCfg, "Common", GI_ALLOCSZ, &gi_ApDataBufAllocSize );
  if( rc != 0 )
  {
    ulog(_ABEND_, " roReadConfigInt Common error [%d] default 15000", rc );
    gi_ApDataBufAllocSize = 15000;
  }

  memset(gc_LogYn, 0x00, sizeof(gc_LogYn));
  rc = roReadConfigString( gc_CmnCfg, "ImageLog", "DB_LOG", gc_LogYn );
  if( rc != 0 )
  {
    ulog(_ABEND_, "[%s] Image Logging 여부 취득오류\n" 
        "[ImageLog/DB_LOG][%d]\n"
        "Default N Set"
        , FF, rc );
    gc_LogYn[0] = 'N';
  }
  ulog(_FLOW_, "[%s] Image Logging 여부[%c]", FF, gc_LogYn[0]);

  /*  Proc 5. ap data *-----------------------------------------------------*/
  g_EncryptBuf = NULL;
  g_EncryptBuf = (char*)malloc(gi_ApDataBufAllocSize);
  if(g_EncryptBuf == (char*)NULL)
  {
    ulog(_ABEND_,  "[%s] Initial malloc g_EncryptBuf error [%d]\n"
        , FF, errno);
    exit(-1);
  }
  memset(g_EncryptBuf, 0x00, gi_ApDataBufAllocSize);

  g_DecryptBuf = NULL;
  g_DecryptBuf = (char*)malloc(gi_ApDataBufAllocSize);
  if(g_DecryptBuf == (char*)NULL)
  {
    ulog(_ABEND_,  "Initial malloc g_DecryptBuf error [%d]\n", errno);
    exit(-1);
  }
  memset(g_DecryptBuf, 0x00, gi_ApDataBufAllocSize);


  if((g_UsePoll==1) && (g_AutoDisCnt==1) )
  {
    g_UsePoll = 0;
    ulog(_FLOW_, "Poll과 자동세션Close는 함께 사용할수 없음\n", 
        "자동세션Close 사용으로 강제설정" );
  }

  // 실제 연결된 세션수
  g_RCntCount = 0;

  // 마지막 송신한 세션
  g_SndIdx = 0;

  // Poll off 상태
  //	g_OnPolling = 0; 

  // DOWN:0  UP:1
  g_SessStat = 0;

}
