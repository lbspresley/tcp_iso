#ifndef __TRS_REQ_H__
#define __TRS_REQ_H__


int init_trs_req(char *trs_ip, int trs_port);
int close_trs_req();
int tcp_connect(const char* ip, int port);
int req_trs(char *trs_id, char *req, int req_len, char *resp, int resp_len);

#define TRS_ID_LEN 32
#define REQ_TYPE_LEN 3
#define REQ_LEN_LEN 8   // 8 bytes for request length. < 100MB
#define MAX_TRS_DATA_LEN 1024*1024*100 // 100MB
#define PRE_LEN (REQ_TYPE_LEN+REQ_LEN_LEN+TRS_ID_LEN+TRS_ID_LEN)


struct trs_req_t {
    char req_type[TRS_ID_LEN]; // 요청 타입
    char req_id[TRS_ID_LEN]; // 요청 아이디
    char master_id[TRS_ID_LEN]; // 대표 요청 아이디
    char req_len[REQ_LEN_LEN]; // 요청 길이
    char *req_data; // 요청 데이터
};


#endif