#include "tcp_iso.h"

int CF_ProcessMessage(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int SrcPidx,
    char* callback_name,
    long* info1, long* info2)
{
  // TODO: implement real message processing. For now, no-op.
  // Return next action to keep flow.
  return RC_NEXT_ACTION;
}
