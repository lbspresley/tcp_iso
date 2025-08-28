#include "tcp_iso.h"

void ack_info_init()
{
  for(int i = 0; i < MAX_ACK_MSG_CNT; i++) {
    g_ack_info[i].use_flag = 0;
    g_ack_info[i].retry_timer_id = TIMERID_REQ_ACK + i;
  }
}

ACK_INFO* add_ack_info(char* msgidr, char* msg, int msg_len)
{
  ACK_INFO* ack_info = get_ack_info_with_msgidr(msgidr);
  if( ack_info != NULL ) {
    return ack_info;
  }

  for(int i = 0; i < MAX_ACK_MSG_CNT; i++) {
    if( g_ack_info[i].use_flag == 0 ) {
      g_ack_info[i].use_flag = 1;
      strcpy(g_ack_info[i].msgidr, msgidr);
      strcpy(g_ack_info[i].msg, msg);
      g_ack_info[i].msg_len = msg_len;
      g_ack_info[i].retry_count = ACK_RETRY_CNT;
      return &g_ack_info[i];
    }
  }
  return NULL;
}

ACK_INFO* get_ack_info(int timer_id)
{
  for(int i = 0; i < MAX_ACK_MSG_CNT; i++) {
    if( g_ack_info[i].use_flag == 1 && g_ack_info[i].retry_timer_id == timer_id ) {
      return &g_ack_info[i];
    }
  }
  return NULL;
}

ACK_INFO* get_ack_info_with_msgidr(char msgidr[35])
{
  for(int i = 0; i < MAX_ACK_MSG_CNT; i++) {
    if( g_ack_info[i].use_flag == 1 && memcmp(g_ack_info[i].msgidr, msgidr, 35) == 0 ) {
      return &g_ack_info[i];
    }
  }
  return NULL;
}

void remove_ack_info(int timer_id)
{
  for(int i = 0; i < MAX_ACK_MSG_CNT; i++) {
    if( g_ack_info[i].retry_timer_id == timer_id ) {
      g_ack_info[i].use_flag = 0;
    }
  }
  rdf_killTimer(timer_id);
}

int ack_retry(ACK_INFO* ack_info)
{
  if( ack_info->retry_count > 0 ) {
    // re-send message
    int rc = send_message(ack_info->msgidr, ack_info->msg, ack_info->msg_len);
    if( rc < 0 ) {
      ulog( _ERROR_, "Error in Re-Sending ACK message. !!!!! " );
      return -1;
    }

    // set timer
    rdf_setTimer( ack_info->retry_timer_id, ACK_RETRY_INTERVAL*1000, -1, 0, 0, TF_Ack_Timeout);
    return 0;
  }
  return -1;
}

int send_message(char* msgidr, char* msg, int msg_len)
{
  int rc;

  /* call rmp action */
  strcpy(g_rmpSvcName, "SNDMSG_ISO");
  rc = rmp_MessageProc( g_rmpSvcName, 0, (unsigned char*)msg, msg_len, 0, 0 );
  if( rc < 0 )
  {
    ulog( _ERROR_, "rmp_MessageProc(%s) Fail. RMP 호출 실패 (rc:%d/len:%d)", g_rmpSvcName, rc, msg_len );
    return -1;
  }

  // save message
  ACK_INFO* ack_info = add_ack_info(msgidr, msg, msg_len);
  if( ack_info == NULL ) {
    ulog( _ERROR_, "Error in Getting ACK info. !!!!! " );
    return -1;
  }

  // decrease retry count
  ack_info->retry_count--;

  // set timer
  rdf_setTimer( ack_info->retry_timer_id, ACK_RETRY_INTERVAL*1000, -1, 0, 0, TF_Ack_Timeout);

  return 0;
}

// Timer callback
void TF_Ack_Timeout(int TimerID, int lParam, int rParam)
{
  // find ack_info
  ACK_INFO* ack_info = get_ack_info(TimerID);
  if( ack_info == NULL ) {
    ulog( _ERROR_, "TIMEOUT : Waiting ACK-Response message. !!!!! " );
    return;
  }

  int rc = ack_retry(ack_info);
  if( rc == 0 ) {
    // timeout
    ulog( _ERROR_, "TIMEOUT : End-of-Retry for msgIdr(%s). !!!!! ", ack_info->msgidr );

    // Close all sessions
    close_all_sessions();
    return;
  }

  return;
}

void kill_all_timers()
{
  // Kill all ACK timers
  for(int i = 0; i < MAX_ACK_MSG_CNT; i++) {
    if( g_ack_info[i].use_flag == 1 ) {
      rdf_killTimer(g_ack_info[i].retry_timer_id);
    }
  }

  // Kill POLL timers
  rdf_killTimer(TIMERID_REQ_POLL);

  // Kill KEY timers
  rdf_killTimer(TIMERID_KEY_CLI);
  rdf_killTimer(TIMERID_KEY_SVR);
}

void close_all_sessions()
{
  ulog(_ERROR_, "Close all sessions. !!!!! ");

  // Kill all ACK timers
  kill_all_timers();

  // kill all sessions
  // 강제로 세션이 끊어진 이벤트를 위해서 메세지 발송
  char Msg[1024];
  sprintf(Msg, "CLOSE_ALL_SESSIONS");
  int Len = strlen(Msg);

  strcpy(g_rmpSvcName, "CLOSE_ALL");
  int rc = rmp_MessageProc(g_rmpSvcName, 0, (unsigned char*)Msg, Len, 0, 0);
  if(rc < 0)
  {
    ulog(_ERROR_, "rmp_MessageProc(%s) Fail. RMP 호출 실패 (rc:%d/len:%d)", g_rmpSvcName, rc, Len);
  }
  return;
}

/*
rmp config

[Rule6]
RuleName=ACK_TIMEOUT
DisableRule=false

SrcCnt=1
SrcSvc1=CLOSE_ALL

FieldCount=0

ProcCnt=1

Proc1Disable=false
Proc1Replace=no
Proc1ActionCnt=2

Proc1Action1Kind=TGLaction
Proc1Action1DisableAc=false
Proc1Action1TGLaction=CLS_CLI_SG1
Proc1Action1TCPinfoInput=frame
Proc1Action1TCPinfoOutput=succession
Proc1Action1FailMethod=procnoreplace
Proc1Action1SuccessJumpProc=-1
Proc1Action1FailJumpProc=-1
Proc1Action2Kind=TGLaction
Proc1Action2DisableAc=false
Proc1Action2TGLaction=CLS_SVR_SG1
Proc1Action2TCPinfoInput=frame
Proc1Action2TCPinfoOutput=succession
Proc1Action2FailMethod=procnoreplace
Proc1Action2SuccessJumpProc=-1
Proc1Action2FailJumpProc=-1

Proc1Comment=""

Comment="ACK TIMEOUT 발생"
*/