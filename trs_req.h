#ifndef __TRS_REQ_H__
#define __TRS_REQ_H__

int init_trs_req(char *trs_ip, int trs_port);
int close_trs_req();
int tcp_connect(const char* ip, int port);
int req_trs_xml(char *trs_id, char *req, int len, char *resp);
int req_trs_fixed(char *trs_id, char *req, int len, char *resp);
int req_trs(int type, char *trs_id, char *req, int len, char *resp);

#define REQ_LEN_LEN 5   // 5 bytes for request length. < 100MB
#define TRS_ID_LEN 35   // 35 bytes for transaction ID
#define RESULT_MSG_LEN 60   // 60 bytes for result message length
#define MAX_TRS_DATA_LEN 1024*100 // 100KB
#define PRE_LEN (REQ_LEN_LEN+TRS_ID_LEN+RESULT_MSG_LEN)

struct trs_req_t {
    char len[REQ_LEN_LEN]; // 요청 길이
    char trs_id[TRS_ID_LEN]; // 전문 ID
    char result_msg[RESULT_MSG_LEN]; // 결과 메시지
    char *data; // 요청 데이터
};

#endif