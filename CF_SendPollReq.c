#include "tcp_bok.h"



int func_SearchIdxByStidx(int stidx);
int func_AGetFd(int idx, int* Fd);

void CF_SendPollReq(int TimerID, int lParam, int rParam)
{
  int nRc;

  char    Msg[64];
  char	PeerIP[32];
  int     Len;
  int idx = -1;

  //    int SndPollTimerID;
  int WaitRspTimerID;

  struct  tm*      pCur;
  struct  timeb    st;
  char    CurDate[16];
  long    Info1 = 0;
  long    Info2 = 0;

  void CF_PollTimeout(int timerID,int lParam,int rParam);
  void CF_SendPollMsg(int timerID,int lParam,int rParam);


  /* Timer ID */
  idx = lParam;


  // Timer Off
  rdf_killTimer(TimerID);


  // TermTable의 Index 취득
  nRc = func_SearchIdxByStidx(idx);
  if(nRc == -1)
  {
    ulog(_ERROR_, "[장애로그] 미관리 세션으로 강제 Close하지 않는다" );
    return ;
  }
  else
  {
    idx = nRc;
  }


  // String IP 취득
  memset(PeerIP, 0x00, sizeof(PeerIP));
  rsof_inetNtoA(g_TermTable[idx].PeerIP, PeerIP);

  // Make PollMsg
  /* 현재 시간 취득 : mmddhhmmss */
  memset(CurDate, 0x00, sizeof(CurDate));
  ftime(&st);
  pCur = localtime(&st.time);
  sprintf(CurDate, "%.2d%.2d%.2d%.2d%.2d",
      pCur->tm_mon + 1, pCur->tm_mday,
      pCur->tm_hour, pCur->tm_min, pCur->tm_sec);

  memset(Msg, 0x20, sizeof(Msg));
  // Make Poll Msg
  //    sprintf(Msg, "0020HDRREQPOLL%s", CurDate );
  memcpy(Msg, PeerIP, strlen(PeerIP));
  sprintf(&Msg[15], "%5d%5d0020HDRREQPOLL%s", 
      g_TermTable[idx].PeerPort, g_TermTable[idx].LocalPort, CurDate );
  Len = strlen(Msg);

  ulog(_FLOW_, "[로그정보] MAKE POLL MSG" );

#if 1
  // PollMsg 전달
  strcpy(g_rmpSvcName, "POLLMSG");
  nRc = rmp_MessageProc(g_rmpSvcName, 0, (unsigned char*)Msg, Len, &Info1, &Info2);
  if(nRc < 0)
  {
    ulog(_ERROR_, "rmp_MessageProc(%s) Fail. RMP 호출 실패 (rc:%d/len:%d)", g_rmpSvcName, nRc, Len);
  }

  // Poll응답 Timer 기동
  WaitRspTimerID = TIMERID_RSP_POLL + lParam;
  rParam = WaitRspTimerID;
  rdf_setTimer(WaitRspTimerID, g_RspPollInterval* 1000, 1,
      lParam, WaitRspTimerID,
      CF_PollTimeout);
#endif
  return;
}
