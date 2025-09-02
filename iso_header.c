#include "tcp_iso.h"

/*
 * 메시지 유형코드 체크
 * 정의된 메시지 유형코드 목록에 있는지 체크
*/
int check_msg_tp_cd(char* msg_tp_cd)
{
  static char* msg_tp_cd_list[] = {
    "admi.002", "admi.004.ConnectionCheck", "admi.004.SystemNotification",
    "admi.006", "admi.007", "admi.011",
    "camt.005", "camt.006", "camt.007",
    "camt.025", "camt.029",
    "camt.052", "camt.053", "camt.054", "camt.056",
    "camt.060", "camt.110", "camt.111",
    "pacs.002.CLS", "pacs.002.CORE",
    "pacs.004.CLS", "pacs.004.CORE",
    "pacs.008.CORE",
    "pacs.009.CLS", "pacs.009.CORE",
    "pacs.028",
  };

  int i;
  for(i = 0; i < sizeof(msg_tp_cd_list)/sizeof(msg_tp_cd_list[0]); i++) {
    if( strcmp(msg_tp_cd, msg_tp_cd_list[i]) == 0 ) {
      return 1;
    }
  }

    return 0;
}

/* 
 * 표준 전문(XML) 송신
 */
int send_standard_msg(char* msg, int msg_len)
{
  // timer id with bizMsgIdr
  char* bizMsgIdr = (char*)get_tag_value(msg, "BizMsgIdr");
  if( bizMsgIdr == NULL ) {
    return -1;
  }

  int rc = send_message(bizMsgIdr, msg, msg_len);
  if( rc < 0 ) {
    return -2;
  }

  return 0;
}


/* 
 * POLL 요청 메시지 수신후 응답 송신처리
 */
int process_poll_request(char* msg)
{
  int rc;
  char* resp_msg = (char*)make_poll_response(msg);
  if( resp_msg == NULL ) {
    return -1;
  }

  rc = send_standard_msg(resp_msg, strlen(resp_msg));
  if( rc < 0 ) {
    return -2;
  }

  return 0;
}
