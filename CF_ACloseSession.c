#include "tcp_iso.h"

int func_ASearchEmptyTbl();
void func_AClearTable(int);
int  func_NacfGetMaxSessC(char *strAdtName);

int func_ASearchSessTbl(int LocalPort, int PeerPort);
int CF_StopPoll(int Type, long* pInfo);

int CF_ACloseSession(int Type, long* pInfo)
{
  TGL_RESULT*  pResult;

  char    strIP[16];
  char    LocalPort[32];
  char    PeerPort[32];
  int		idx;


  idx=-1;
  pResult = (TGL_RESULT*)*pInfo;

  memset(strIP, 0x00, sizeof(strIP));
  rsof_inetNtoA(pResult->PeerIP, strIP);

  memset(LocalPort, 0x00, sizeof(LocalPort));
  sprintf(LocalPort, "%d", pResult->LocalPort);

  memset(PeerPort, 0x00, sizeof(PeerPort));
  sprintf(PeerPort, "%d", pResult->PeerPort);


  // table 할당 및 설정
  idx = func_ASearchSessTbl( pResult->LocalPort, pResult->PeerPort);
  if(idx < 0)
  {
    ulog(_WARNING_, "[로그정보] 미관리세션 \n" 
        "[상세정보] \n"
        "stidx [%d]\n" 
        "PeerIP [%s\\n" 
        "PeerPort [%d]\n" 
        "LocalPort [%d]"
        , pResult->stidx
        , strIP, pResult->PeerPort, pResult->LocalPort);

    //       	return RC_DROP_ALL;
  }	
  else
  {
    // 실제로 연결된 세션수 변경
    if(g_RCntCount != 0)
    {
      g_RCntCount--;
    }
    if(g_DnSessLimit < g_RCntCount)
    {
      if (g_SessStat != 1) 
      {
        g_SessStat = 1;
      }
    } 
    else 
    { 
      if (g_SessStat == 1) 
      { 
        g_SessStat = 0;
      }
      ulog(_FLOW_, "[로그정보] 송신 세션 정보\n" 
          "[상세정보]\n"
          "stidx [%d]\n" 
          "PeerIP [%s]\n" 
          "PeerPort [%d]\n" 
          "LocalPort [%d]\n" 
          "Fd [%d]\n" 
          "idx [%d]\n"
          , pResult->stidx
          , strIP, pResult->PeerPort, pResult->LocalPort
          , pResult->fd, idx);


      g_TermTable[idx].cnt_stat = -1;
      //			func_AClearTable(idx);
    }
  }

#if 1
  (void)CF_StopPoll(Type, pInfo);
  rdf_killTimer( TIMERID_RSP_POLL );
#else
  // 모든 TIMER를 종료한다.
  rdf_killTimer(TIMERID_DISCNT + pResult->stidx);
  rdf_killTimer(TIMERID_COMMON + pResult->stidx);
  rdf_killTimer(TIMERID_REQ_POLL + pResult->stidx);
  rdf_killTimer(TIMERID_RSP_POLL + pResult->stidx);
#endif

  return RC_NEXT_ACTION;
}


/*  MAX SESSTION COUNT 를 구한다 */
int  func_NacfGetMaxSessC(char *strAdtName)
{
  int      nLen=0, ii=0;
  int      nRc =0 ;
  char     strTmp[256];
  char     strBaseDir[256];
  char     strTGLName[256];
  char     strConfigName[300];

  char     strSectionName[80];
  char     strActionType [80];
  int      nSectionCount = 0;
  int      nLocalPortCount = 0;
  int      nPortCount = 0;

  char     *ptrBase = NULL;

  /* Base Dir 설정 */
  ptrBase = getenv("ROME_HOME");
  if(ptrBase == NULL) {
    return(-1);
  }

  memset(strBaseDir, 0x00, sizeof(strBaseDir));
  strcpy(strBaseDir, ptrBase);
  nLen = strlen(strBaseDir);
  if(strBaseDir[nLen-1] == '/') {
    strBaseDir[nLen-1] = 0x00;
  }


  /* Configuration File명 */
  memset(strConfigName, 0x00, sizeof(strConfigName));
  sprintf(strConfigName, "%s/config/upconfig/%s.ini", strBaseDir, strAdtName);


  memset(strTGLName, 0x00, sizeof(strTGLName));
  roReadConfigString(strConfigName, "Local", "TGLRuleFile" , strTGLName);



  /* fopen해서 파일을 Search하는 것이 나을까   */
  /* roReadConfigString() 함수를 쓰는게 나을까 */

  roReadConfigInt(strTGLName, "TGLinfo"
      , "SectionCount"
      , &nSectionCount);

  memset(strTmp, 0x00, sizeof(strTmp));

  for (ii=0 ; ii < nSectionCount ; ii++)
  {
    sprintf(strTmp, "Section%d", (ii+1));
    memset(strSectionName, 0x00, sizeof(strSectionName));
    roReadConfigString(strTGLName, "TGLinfo"
        , strTmp
        , strSectionName);

    roReadConfigString(strTGLName, strSectionName
        , "ActionType"
        , strActionType);

    if (memcmp(strActionType, "ConnectPort", 11) != 0) {
      continue;
    }

    nLocalPortCount = 0;
    nRc = roReadConfigInt(strTGLName, strSectionName
        , "LocalPortCount"
        , &nLocalPortCount);


    if (nRc != 0) {
      nPortCount = nPortCount + 1;
    }
    else {
      nPortCount = nPortCount + nLocalPortCount;
    }
  } /* end of for */

  return nPortCount;
}
