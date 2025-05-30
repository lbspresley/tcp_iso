#include "tcp_bok.h"


//void TCP_BOK(TPSVCINFO *msg)
void TCP_ISO(TPSVCINFO *msg)
{
  int     rc;
  char    SndStationName[64];
  int     SndStationNo = 0;


  ulog( _FLOW_, "[%s] from TPmsg (msg->len : %d)", FF, msg->len );

  memset( SndStationName, 0x00, sizeof(SndStationName) );
  tpgetsndsvc( SndStationName, NULL );

  roTrace( 'I', SndStationName, msg->len, (unsigned char*)msg->data );

  /*	proc	*-----------------------------------------------------------------*/
  rc = rmp_MessageProc( "fromSvc", SndStationNo, (unsigned char*)(msg->data), msg->len, 0, 0 );
  if(rc < 0)
  {
    ulog( _ERROR_, "[%s] Message 수신 처리 오류 rc:%d", __FUNCTION__, rc );
    roDiscardTrace( 'I', SndStationName, msg->len, (unsigned char*)msg->data,
        "Message 수신 처리 장애 반환 rc: %d", rc );

    tpreturn_r( TPFAIL, -1, NULL, 0, 0 );
    return;
  }

  tpreturn_r( TPSUCCESS, 0, NULL, 0, 0 );

  return;
}

