#include "tcp_iso.h"


void func_AClearTable(int);
int func_AGetFd(int idx, int* Fd);
int	func_SearchIdxByStidx(int index);

void CF_DisCntSession(int TimerID, int lParam, int rParam)
{
  int nRc;

  //    char* Msg = "DisCntTimeout";
  char Msg[32]; 
  int Len;
  long Info1 = 0;
  long Info2 = 0;

  int idx = lParam;
  TGL_RESULT* pResult;


  ulog(_ERROR_, "[로그정보] %d sec동안 거래 없음\n"
      "[상세정보] TIMER_ID : %d"
      , g_DisCntInterval, TimerID);

  // Timeout된 시점에는 Timer는 Off 
  rdf_killTimer(TimerID);

  // 이곳에서 세션을 끊는다
  nRc = func_SearchIdxByStidx(idx);
  if(nRc == -1)
  {
    ulog(_ERROR_, "[로그정보] 미관리 세션으로 강제 Close하지 않는다" );

    return ;
  }
  else
  {
    idx = nRc;
  }

  // Result Struct 생성
  pResult = (TGL_RESULT*) malloc(sizeof(TGL_RESULT));
  memset((char*)pResult, 0x00, sizeof(TGL_RESULT));
  pResult[0].ActType = ACT_CLOSEEVT;
  pResult[0].Count = 1;
  //	Result[0].udValue = -1;
  pResult[0].stidx = g_TermTable[idx].stidx;

  pResult[0].LocalPort = g_TermTable[idx].LocalPort;
  pResult[0].PeerPort = g_TermTable[idx].PeerPort;
  pResult[0].PeerIP = g_TermTable[idx].PeerIP;
  pResult[0].Result = TGL_RC_SUCCESS;


  // Close Session 
  rsof_resetFD( lParam, _IGNORE, _IGNORE );

  // Clear SG
  tglf_SetSG(g_TermTable[idx].SGName, pResult);




  // 강제로 세션이 끊어진 이벤트를 위해서 메세지 발송
  memset(Msg, 0x00, sizeof(Msg));
  sprintf(Msg, "PeerPort:%05d", g_TermTable[idx].PeerPort); 
  Len = strlen(Msg);

  strcpy(g_rmpSvcName, "DISCONNT");
  nRc = rmp_MessageProc(g_rmpSvcName, 0, (unsigned char*)Msg, Len, &Info1, &Info2);
  if(nRc < 0)
  {
    ulog(_ERROR_, "rmp_MessageProc(%s) Fail. RMP 호출 실패 (rc:%d/len:%d)", g_rmpSvcName, nRc, Len);
  }

  if(pResult != NULL)
  {
    free(pResult);
  }			

  return;
}

