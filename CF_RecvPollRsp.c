#include "tcp_bok.h"

int func_ASearchEmptyTbl();
int func_SearchIdxByStidx(int stidx);
void func_AClearTable(int);


int func_ASearchSessTbl(int LocalPort, int PeerPort);

int CF_RecvPollRsp(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2)
{
  int		nRc;
  TGL_RESULT*  pResult;

  //    char    strIP[16];
  //    char    LocalPort[32];
  //    char    PeerPort[32];

  int	timerID;
  long lParam = 0;
  long rParam = 0;

  int		idx;

  void CF_DisCntSession(int timerID,int lParam,int rParam);
  void CF_SendPollReq(int timerID,int lParam,int rParam);

  pResult = (TGL_RESULT*)*info1;
#if 0
  memset(strIP, 0x00, sizeof(strIP));
  rsof_inetNtoA(pResult->PeerIP, strIP);

  memset(LocalPort, 0x00, sizeof(LocalPort));
  sprintf(LocalPort, "%d", pResult->LocalPort);

  memset(PeerPort, 0x00, sizeof(PeerPort));
  sprintf(PeerPort, "%d", pResult->PeerPort);


  // table 할당 및 설정
  idx = func_ASearchSessTbl( pResult->LocalPort, pResult->PeerPort );
  if(idx < 0)
  {
    // 장애 처리 -> Session 강제 해제
    ulog(_WARNING_, "[로그정보] 미관리세션 \n"
        "[상세정보] \n" 
        "stidx [%d]\n" 
        "PeerIP [%s]\n" 
        "PeerPort [%d]\n" 
        "LocalPort [%d]"
        , pResult->stidx
        , strIP,  pResult->PeerPort, pResult->LocalPort);

    return RC_DROP_ALL;
  }	
#endif
  idx = pResult->stidx;
  nRc = func_SearchIdxByStidx(idx);
  if(nRc == -1)
  {
    ulog(_ERROR_, "[로그정보] 미관리 세션으로 Poll 처리 하지 않는다" );

    return RC_NEXT_ACTION;
  }
  else
  {
    idx = nRc;
  }

  // 응답대기 Timer Off
  timerID = TIMERID_RSP_POLL + g_TermTable[idx].stidx;
  rdf_killTimer(timerID);

  // On Timer
  lParam = g_TermTable[idx].stidx;
  timerID = TIMERID_REQ_POLL + lParam;
  rdf_setTimer(	timerID, g_ReqPollInterval*1000, -1, 
      lParam, rParam, 
      CF_SendPollReq);
  ulog(_FLOW_, "[로그정보] USE POLL \n" 
      "[상세정보] [TIMER_ID:%d][lParam:%d]"
      , timerID, lParam);

#if 0
  ulog(_FLOW_, "[%s] 수신 세션 정보\n"
      "stidx    : %d\n"
      "PeerIP   : %s\n"
      "PeerPort : %d\n"
      "LocalPort: %d\n"
      "Fd       : %d\n"
      "idx      : %d\n"
      "Rcv Count: %d",
      __FUNCTION__,
      pResult->stidx, strIP,  pResult->PeerPort, pResult->LocalPort,
      pResult->fd, idx, g_TermTable[idx].rcvcnt);
#endif


  return RC_NEXT_ACTION;
}

