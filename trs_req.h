#ifndef __TRS_REQ_H__
#define __TRS_REQ_H__

int init_trs_req(char *trs_ip, int trs_port);
int close_trs_req();
int tcp_connect(const char* ip, int port);
void msgtpcd_to_trsid(int type, char* msgtpcd ); // MsgTpCd를 TRSID로 변환
int req_trs_xml(char *msgtpcd, char* msg_idr, char *req, int len, char *resp);
int req_trs_fixed(char *msgtpcd, char* msg_idr, char *req, int len, char *resp);
int req_trs(int type, char *msgtpcd, char* msg_idr, char *req, int len, char *resp);

#define REQ_LEN_LEN 5   // 5 bytes for request length. < 100MB
#define TRS_ID_LEN 35   // 35 bytes for transaction ID
#define RESULT_MSG_LEN 60   // 60 bytes for result message length
#define MAX_TRS_DATA_LEN 1024*100 // 100KB
#define PRE_LEN (REQ_LEN_LEN+TRS_ID_LEN+RESULT_MSG_LEN)

struct trs_req_t {
    char len[REQ_LEN_LEN]; // 요청 길이
    char trs_id[TRS_ID_LEN]; // 전문 ID : admi.004.001.01 ==> admi_004_001_01_I1 / admi_004_001_01_I3 
    char msg_id[TRS_ID_LEN]; // 메시지 ID
    char result_msg[RESULT_MSG_LEN]; // 결과 메시지
    char *data; // 요청 데이터
};

// error
// 00130[TRSID   ][MSGID   ][ERRMSG     ]

// success
// 00630[TRSID   ][MSGID   ][SPACE     ][DATA(500)      ]
#endif