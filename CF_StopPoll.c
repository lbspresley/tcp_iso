#include "tcp_iso.h"

int CF_StopPoll(int Type, long* pInfo)
{ 
  ulog(_ERROR_, "[로그정보] Stop Timer for Poll Request status(%d --> 0 )", g_poll_started ); 

  // Stop Poll Timer 
  g_poll_started = 0;

  rdf_killTimer( TIMERID_REQ_POLL );

  return RC_NEXT_ACTION;
}
