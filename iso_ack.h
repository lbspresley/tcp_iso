#include "tcp_iso.h"

#ifndef __ISO_ACK_H__
#define __ISO_ACK_H__

#define MAX_ACK_MSG_CNT 500
#define ACK_RETRY_CNT 3		// 3번 재전송
#define ACK_RETRY_INTERVAL 30		// 30초 간격으로 재전송

typedef struct {
  int use_flag;
  int retry_timer_id;
  int retry_count;
  int msg_len;
  char msgidr[35];
  char *msg;
} ACK_INFO;

ACK_INFO g_ack_info[MAX_ACK_MSG_CNT];

int send_ack_response(char* outbuf);

void ack_info_init();
ACK_INFO* add_ack_info(char* msgidr, char* msg, int msg_len);
ACK_INFO* get_ack_info(int timer_id);
ACK_INFO* get_ack_info_with_msgidr(char msgidr[35]);
void remove_ack_info(int timer_id);
int ack_retry(ACK_INFO* ack_info);
void kill_all_timers();
void close_all_sessions();
int send_message(char* msgidr, char* msg, int msg_len);
void TF_Ack_Timeout(int TimerID, int lParam, int rParam);

#endif