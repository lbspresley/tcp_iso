#include "tcp_iso.h"

// ACK 전문 송신
int send_ack_response(char* outbuf)
{
  char* ack_msg = (char*)make_ack_msg(outbuf);
  int ack_msg_len = strlen(ack_msg);

  // send message without ack-retry
  return send_message(NULL, ack_msg, ack_msg_len);
}

void ack_info_init()
{
  int i;
  for(i = 0; i < MAX_ACK_MSG_CNT; i++) {
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

  int i;
  for(i = 0; i < MAX_ACK_MSG_CNT; i++) {
    if( g_ack_info[i].use_flag == 0 ) {
      g_ack_info[i].use_flag = 1;
      strcpy(g_ack_info[i].msgidr, msgidr);
      g_ack_info[i].msg = (char*)malloc(msg_len+1);
      if( g_ack_info[i].msg == NULL ) {
        ulog( _ERROR_, "Failed to allocate memory for ack message" );
        return NULL;
      }
      g_ack_info[i].msg[msg_len] = '\0';
      memcpy(g_ack_info[i].msg, msg, msg_len);
      g_ack_info[i].msg_len = msg_len;
      g_ack_info[i].retry_count = ACK_RETRY_CNT;
      return &g_ack_info[i];
    }
  }
  return NULL;
}

ACK_INFO* get_ack_info(int timer_id)
{
  int i;
  for(i = 0; i < MAX_ACK_MSG_CNT; i++) {
    if( g_ack_info[i].use_flag == 1 && g_ack_info[i].retry_timer_id == timer_id ) {
      return &g_ack_info[i];
    }
  }
  return NULL;
}

ACK_INFO* get_ack_info_with_msgidr(char msgidr[35])
{
  int i;
  for(i = 0; i < MAX_ACK_MSG_CNT; i++) {
    if( g_ack_info[i].use_flag == 1 && strcmp(g_ack_info[i].msgidr, msgidr) == 0 ) {
      return &g_ack_info[i];
    }
  }
  return NULL;
}

void remove_ack_info(int timer_id)
{
  int i;
  for(i = 0; i < MAX_ACK_MSG_CNT; i++) {
    if( g_ack_info[i].use_flag == 1 && g_ack_info[i].retry_timer_id == timer_id ) {
      g_ack_info[i].use_flag = 0;
      g_ack_info[i].msg_len = 0;
      if( g_ack_info[i].msg != NULL ) {
        free(g_ack_info[i].msg);
      }
      g_ack_info[i].msg = NULL;
      rdf_killTimer(timer_id);
      break;
    }
  }
  ulog( _ERROR_, "remove_ack_info(timer_id:%d) Fail. !!!!! ", timer_id );
}

int process_ack_response(char* msg)
{
  char* value = NULL;
  char msgidr[35+1];

  // 1. check msgidr
  value = (char *)get_tag_value(msg, "BizMsgIdr");
  if( value == NULL ) {
    ulog( _ERROR_, "BizMsgIdr 추출 실패 !!");
    return -1;
  }
  strcpy(msgidr, value);

  // 2. get ack_info
  ACK_INFO* ack_info = get_ack_info_with_msgidr(msgidr);
  if( ack_info == NULL ) {
    ulog( _ERROR_, "ACK 응답메시지 수신. msgidr(%s) 없음 !!!!! ", msgidr );
    return -2;
  }

  // 3. remove ack_info
  remove_ack_info(ack_info->retry_timer_id);

  return 0;
}

int ack_retry(ACK_INFO* ack_info)
{
  int rc = 0;

  if( ack_info->retry_count > 0 ) {
    // re-send message
    strcpy(g_rmpSvcName, "SNDMSG_ISO");
    rc = rmp_MessageProc(g_rmpSvcName, 0, (unsigned char*)ack_info->msg, ack_info->msg_len, 0, 0);
    if (rc < 0)
    {
      ulog(_ERROR_, "ACK Retry : RMP error(%d) msgIdr(%s) len(%d)", rc, ack_info->msgidr, ack_info->msg_len);
      return -1;
    }

    // decrease retry count
    ack_info->retry_count--;
    ulog(_ERROR_, "Retry count is %d. msgIdr(%s)", ack_info->retry_count, ack_info->msgidr);

    // set timer
    rdf_setTimer( ack_info->retry_timer_id, ACK_RETRY_INTERVAL*1000, -1, 0, 0, TF_Ack_Timeout);

    return ack_info->retry_count;
  }

  // retry count is 0
  ulog(_ERROR_, "Retry count is 0. msgIdr(%s)", ack_info->msgidr);
  return -2;
}

int send_message(char* msgidr, char* msg, int msg_len)
{
  static unsigned char _send_msg[MAX_MSG_LEN];
  int rc;
  char* _encrypt_msg = (char*)NULL;
  int encrypt_msg_len = 0;

  // encrypt message
  rc = inl_encrypt(msg, msg_len, &_encrypt_msg, &encrypt_msg_len);
  if( rc < 0 ) {
    ulog( _ERROR_, "Error in encrypting message. !!!!! " );
    return -1;
  }

  // make send message
  sprintf((char*)_send_msg, "%05d", encrypt_msg_len);
  memcpy((char*)_send_msg + 5, _encrypt_msg, encrypt_msg_len);
  int send_msg_len = encrypt_msg_len + 5;

  /* call rmp action */
  strcpy(g_rmpSvcName, "SNDMSG_ISO");
  rc = rmp_MessageProc( g_rmpSvcName, 0, _send_msg, send_msg_len, 0, 0 );
  if( rc < 0 )
  {
    ulog( _ERROR_, "Send message : RMP error(%d) msgIdr(%s) len(%d)", rc, msgidr==NULL ? "NULL" : msgidr, msg_len );
    return -1;
  }

  // send message without ack-retry
  if( msgidr == NULL ) {
    return 0;
  }

  // save message
  ACK_INFO* ack_info = add_ack_info(msgidr, (char*)_send_msg, send_msg_len);
  if( ack_info == NULL ) {
    ulog( _ERROR_, "Error in Getting ACK info. msgIdr(%s) len(%d)", msgidr==NULL ? "NULL" : msgidr, msg_len );
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
    ulog( _ERROR_, "TIMEOUT : No TIMERID(%d) Waiting ACK-Response message. !!!!! ", TimerID );
    return;
  }

  int rc = ack_retry(ack_info);
  if( rc < 0 ) {
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
  int i;
  for(i = 0; i < MAX_ACK_MSG_CNT; i++) {
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
    ulog(_ERROR_, "Close all sessions : RMP error(%d) len(%d)", rc, Len);
  }
  return;
}
