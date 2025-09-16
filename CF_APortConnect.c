#include "tcp_iso.h"

int func_ASearchSessTbl(int LocalPort, int PeerPort);
int func_ASearchEmptyTbl();
void funbc_AClearTable(int);
int	func_GetSGFirstIdx(char* SGName);
int	func_SendChannelStat(int stat);
int func_AGetFd(int , int *);

void CF_DisCntSession(int timerID,int lParam,int rParam);
//void CF_SendPollReq(int timerID,int lParam,int rParam);


int CF_APortConnect(int Type, long* pInfo)
{
  TGL_RESULT*  pResult;

  char    strIP[16];
  char    LocalPort[32];
  char    PeerPort[32];

  int timerID;
  long lParam = 0;
  long rParam = 0;

  int idx;
  int SessCnt;
  int i;
  int	RCntCount = 0;


  idx=-1;
  pResult = (TGL_RESULT*)*pInfo;
  SessCnt = pResult->Count;

  idx = func_GetSGFirstIdx(pResult->SrcSvc);
  if(idx <= -1)
  {
    return RC_NEXT_ACTION;
  }

  i = idx;
  for( ; i<SessCnt+idx; i++ )
  {
#ifdef _DEBUG_
    ulog(_ERROR_, "[로그정보] 회선연결정보\n" 
        "[로그상세] [%d] pNext : %x\n" 
        "ActType(%d), Count(%d), udValue(%d), stidx(%d)\n" 
        "Result(%d), Reason(%d), fd(%d)\n" 
        , i, pResult->pNext 
        , pResult->ActType, pResult->Count 
        , pResult->udValue, pResult->stidx 
        , pResult->Result, pResult->Reason, pResult->fd);
    ulog(_ERROR_, "PIP/PPORT/LPORT: [%x/%d/%d]\n" 
        "TotalSessionC(%d), TotalValidSessionC(%d)\n" 
        "PeerSessionC(%d), PeerValidSessionC(%d)\n" 
        , pResult->PeerIP 
        , pResult->PeerPort, pResult->LocalPort 
        , pResult->TotalSessionCount 
        , pResult->TotalValidSessionCount 
        , pResult->PeerSessionCount 
        , pResult->PeerValidSessionCount );

#endif

#if 1
    if( (pResult->Result > -1) ) {
      if(pResult->Reason == 7) {
        // 기연결
        ulog(_ERROR_, "[로그정보] 기연결 회선 연결" );
        g_TermTable[i].cnt_stat = 7;
      } else {
        // 연결
        ulog(_ERROR_, "[로그정보] 신규회선 연결" );
        g_TermTable[i].cnt_stat = 1;
      }
    } else {
      // 접속실패
      ulog(_ERROR_, "[로그정보] 회선연결 실패" );
      g_TermTable[i].cnt_stat = -1;

      /* 접속 오류시 return */
      return RC_NEXT_ACTION;
    }
#endif

    memset(strIP, 0x00, sizeof(strIP)); 
    rsof_inetNtoA(pResult->PeerIP, strIP);

    memset(LocalPort, 0x00, sizeof(LocalPort));
    sprintf(LocalPort, "%d", pResult->LocalPort);

    memset(PeerPort, 0x00, sizeof(PeerPort));
    sprintf(PeerPort, "%d", pResult->PeerPort);


    memset( g_TermTable[i].SGName, 0x00, sizeof(g_TermTable[i].SGName));
    strncpy( g_TermTable[i].SGName, pResult->SrcSvc, strlen(pResult->SrcSvc) );
    g_TermTable[i].onuse      = 1;
    g_TermTable[i].stidx      = pResult->stidx; 
    g_TermTable[i].PeerIP     = pResult->PeerIP;
    g_TermTable[i].PeerPort   = pResult->PeerPort;
    g_TermTable[i].LocalPort  = pResult->LocalPort;	

    pResult++;

  } // for


  for( i=0; i<g_maxterm_cnt; i++ )
  {
    if( g_TermTable[i].cnt_stat > -1) {
      RCntCount++;

      if( (g_AutoDisCnt == 1) && (g_TermTable[i].cnt_stat == 1) ) {
        // On Timer
        lParam = g_TermTable[i].stidx;
        // timerID = TIMERID_DISCNT + lParam;
        timerID = 0;
        rdf_setTimer( timerID, g_DisCntInterval*1000, -1, lParam, rParam, CF_DisCntSession ); 
#ifdef _DEBUG_ 
        ulog(_FLOW_, "[로그정보] TIMERID for auto disconnect\n" 
            "[TIMER_ID:%d][lParam:%d]"
            , timerID, lParam); 
#endif
      } else {
#ifdef _DEBUG_
        ulog(_FLOW_, "[로그정보] [stidx:%d] [cnt_stat:%d]" 
            , g_TermTable[i].stidx, g_TermTable[i].cnt_stat);
#endif
      }
    }
  }

#ifdef _DEBUG_ 
  // 회선상태 공유 서비스 테스트이후 삭제예정
  ulog(_WARNING_, "[로그정보] Before Channel Stat\n" 
      "[로그상세] RCntCount[%d] g_SessStat[%d]" 
      , RCntCount, g_SessStat);
#endif

  // 실제로 연결된 세션 수 변경
  if(g_UpSessLimit > RCntCount) {
    if (g_SessStat != 0) {
      g_SessStat = 0;
      func_SendChannelStat(0);
    }
  } else {
    if (g_SessStat == 0) {
      g_SessStat = 1;
      func_SendChannelStat(1);
    }
  }

#ifdef _DEBUG_ 
  // 회선상태 공유 서비스 테스트이후 삭제예정
  ulog(_WARNING_, "[로그정보] After Channel Stat\n" 
      "[로그상세] RCntCount[%d] g_SessStat[%d]" 
      , RCntCount, g_SessStat);
#endif

  ulog(_FLOW_, "Max Session Count     : %d\n"
      "SG Session Count      : %d\n"
      "Connect Session Count : %d\n"
      "Session Stat          : %d"
      , g_maxterm_cnt, SessCnt, RCntCount, g_SessStat);

  /* CHANGE SESSION KEY : START  */
  cli_send_1(strIP, PeerPort, LocalPort);

  return RC_NEXT_ACTION;
}


int func_ASearchSndTbl( int idx )
{
  int i = idx+1;
  int srch_cnt = 0;

  if(i == g_maxterm_cnt) {
    i = 0;
  }

RESEARCH:
  for(; i<g_maxterm_cnt; i++)
  {
    if(g_TermTable[i].onuse == 0) {
      if(i == idx) {
        // 한번 씩 확인후는 오류처리
        return -1;
      }

      if(i == g_maxterm_cnt) {
        i = 0;
        if(srch_cnt > 1) {
          return -1;
        }
        srch_cnt++;

        goto RESEARCH;
      }
      continue;
    } else {
      return i;
    }
  }

  return -1;
}

int	func_GetSGFirstIdx(char* SGName)
{
  int i;

  for(i=0; i<g_maxterm_cnt; i++)
  {
    if( strcmp(g_TermTable[i].SGName, SGName) == 0) {
      return i;
    }
  }

  for(i=0; i<g_maxterm_cnt; i++)
  {
    if(g_TermTable[i].onuse == 0) {
      return i;
    }
  }

  return -1;
}

int func_SearchIdxByStidx(int stidx)
{
  int i;
  for(i=0; i<g_maxterm_cnt; i++)
  {
    if(g_TermTable[i].stidx == stidx) {
      return i;
    }
  }

  return -1;
}


int func_ASearchEmptyTbl()
{
  int i;

  for(i=0; i<g_maxterm_cnt; i++)
  {
    if(g_TermTable[i].onuse == 0) {
      return i;
    }
  }

  return -1;
}


int func_ASearchSessTbl(int LocalPort, int PeerPort)
{
  int i = 0;

  for(i=0; i<g_maxterm_cnt; i++)
  {
    if( (g_TermTable[i].PeerPort == PeerPort) &&
        (g_TermTable[i].LocalPort == LocalPort) )
    {
      return i;
    }
  }

  return -1;
}



void func_AClearTable(int idx)
{
  // table clear
  g_TermTable[idx].stidx		= -1;
  g_TermTable[idx].onuse		= 0;
  g_TermTable[idx].cnt_stat	= 0;

  g_TermTable[idx].PeerIP		= 0;
  g_TermTable[idx].PeerPort	= 0;
  g_TermTable[idx].LocalPort	= 0;

  memset( g_TermTable[idx].SGName, 0x00, sizeof(g_TermTable[idx].SGName) );

  return;
}


int func_AGetFd(int idx, int* Fd)
{
  int Len, nRc;
  int stidx = g_TermTable[idx].stidx;

  if (stidx < 0) {
    ulog(_WARNING_, "[로그정보] stidx 값이 0보다 작음" );
    return -1;
  }

  Len = sizeof(int);
  nRc = rsof_getSessionInfo(stidx, _IGNORE, _IGNORE, RSOF_FDNUM, Fd, &Len);
  if( nRc < 0 ) {
    ulog(_WARNING_, "[로그정보] FD 값이 취득 실패" );
    return -3;
  }

  return 0;
}



int	func_SendChannelStat(int stat)
{
  int				nRc;
  S_CL_HEADER		*pHdr=NULL;
  char*	pSndMsg=NULL;
  int		SndMsgLen=0;

  if(g_SessMonitor == 0 ) {
    //		ulog(_FLOW_, "회선관리 대상이 아님" ); 
    return 0;
  }

  SndMsgLen = sizeof(S_CL_HEADER);
  pSndMsg = tpalloc("CARRAY", NULL, SndMsgLen);
  if(pSndMsg == NULL) {
    ulog(_ERROR_, "[로그정보] tpalloc fail (size:%d))" , SndMsgLen);
    return -1;
  }

  /* TDrv 정보 입력 */
  memset(pSndMsg, 0x00, SndMsgLen);
  pHdr = (S_CL_HEADER *)pSndMsg;

  /*InHead 설정 */
  if(stat == 1) {
    memcpy( pHdr->c_MsgDsc, DEF_MSG_DSC_UPCHANNEL, strlen(DEF_MSG_DSC_UPCHANNEL));
  } else {
    memcpy( pHdr->c_MsgDsc, DEF_MSG_DSC_DOWNCHANNEL, strlen(DEF_MSG_DSC_DOWNCHANNEL));
  }
  memcpy( pHdr->c_BeChanID, g_VANCode, strlen(g_VANCode) );
  memcpy( pHdr->c_ExChanID, g_VANCode, strlen(g_VANCode) );

  /* 파일 수신 처리 서비스로 전송 */
  nRc = tpacall(g_APSvc, pSndMsg, SndMsgLen, TPNOREPLY | TPBLOCK);
  if(nRc < 0) {
    tpfree(pSndMsg);
    ulog(_ERROR_, "[로그정보] 송신 실패 to [%s] (nRc:%d)", g_APSvc, nRc);
    return -1;
  } 

  roTrace('O', g_APSvc, SndMsgLen, (unsigned char*)pSndMsg);
  tpfree(pSndMsg);
  ulog(_FLOW_, "[로그정보] 송신 성공 to %s", g_APSvc);

  return 0;
}
