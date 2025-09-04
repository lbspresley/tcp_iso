#include "tcp_iso.h"

void tgmCallbackResiter();
void UserInit();

#if 1
  /* TGL Callback Function Register */
int CF_APortConnect(int Type, long* pInfo);
int	CF_ACloseSession(int Type, long* pInfo);
int	CF_DisCntSession(int Type, long* pInfo);
int CF_UpdateRecvCnt(int Type, long* pInfo);
int CF_UpdateSendCnt(int Type, long* pInfo);

  /* RMP Callback Function Register */
int	CF_ReceiveMessage(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen, 
    char SrcSvc[64],int Srcpidx, 
    char* callback_name, 
    long* info1, long* info2);

int CF_ImgLogSend(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2);
int CF_ImgLogRecv(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2);
#endif

int usermain(int argc, char* argv[])
{
#if (1) 
  int defval;
  int rcvq=1;
#endif

  // tgl 초기화
  tgl_init();


  // TGM callback 등록
  tgl_CallbackRegistration(tgmCallbackResiter);

#if (1) 
  defval = 1;
  (void) cfg_getInt( NULL, "RDFsetup","RCVQ",
      "SERVER", NULL, "RDF_RCVQ", 
      &rcvq, &defval );
  ulog(_FLOW_, " RCVQ = (%d)", rcvq );
  if( rcvq == 0 )
  {
    (void) rdf_StopRcvQ();
  }
#endif

  // tpuschedule에 대한 Loop 처리가 내장되어 있다
  tgl_main(0);

  return 0;
}

void tgmCallbackResiter()
{

  /* TGL Callback Function Register */
#if 1
  tgl_SetupCallback("CF_APortConnect", CF_APortConnect);
  tgl_SetupCallback("CF_ACloseSession", CF_ACloseSession);
  tgl_SetupCallback("CF_DisCntSession", CF_DisCntSession);


  /* RMP Callback Function Register */
  rmp_SetupCallback("CF_ReceiveMessage", CF_ReceiveMessage);
  rmp_SetupCallback("CF_ImgLogSend", CF_ImgLogSend);
  rmp_SetupCallback("CF_ImgLogRecv", CF_ImgLogRecv);
  //rmp_SetupCallback("CF_ProcLogErr", CF_ProcLogErr);
  
#endif

  return;
}

