#include "tcp_iso.h"
#ifdef USE_CURL
#include <curl/curl.h>
#endif


int tcp_connect(const char* ip, int port)
{
    int sock_fd;
    struct sockaddr_in server_addr;
    struct timeval timeout;
    int ret;

    // 소켓 생성
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        ulog( _ERROR_, "Socket creation failed");
        return -1;
    }

    // 서버 주소 구조체 초기화
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    
    // IP 주소 변환
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        ulog( _ERROR_, "Invalid address");
        close(sock_fd);
        return -1;
    }

    // 연결 타임아웃 설정 (5초)
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    
    // 송신 타임아웃 설정
    if (setsockopt(sock_fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0) {
        ulog( _ERROR_, "Set send timeout failed");
        close(sock_fd);
        return -2;
    }
    
    // 수신 타임아웃 설정
    if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        ulog( _ERROR_, "Set receive timeout failed");
        close(sock_fd);
        return -3;
    }

    // 서버에 연결
    ret = connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (ret < 0) {
        ulog( _ERROR_, "Connection failed");
        close(sock_fd);
        return -4;
    }

    return sock_fd;
}

int init_trs_req(char *trs_ip, int trs_port) 
{
    int fd = tcp_connect(trs_ip, trs_port);
    if (fd < 0) {
        ulog(_ERROR_, "Failed to connect to TRS: %s:%d", trs_ip, trs_port);
        return -1;
    }
    ulog(_FLOW_, "Connected to TRS: %s:%d fd(%d)", trs_ip, trs_port, fd);

    return fd;
}

int close_trs_req(int fd) 
{
    if (fd != -1) {
        close(fd);
    }
    return 0;
}

void msgtpcd_to_trsid(int type, char* msgtpcd )
{
  char tpidr[36];

  strcpy(tpidr, msgtpcd);
  replaceString(tpidr, ".", "_" );

  if (type == 0) {
  	strcpy(msgtpcd, "I1");
  } else {
    strcpy(msgtpcd, "I3");
  }
  strcat(msgtpcd, tpidr);

  return;
}

int req_trs_xml(char *msg_tp_cd, char* msg_idr, char *req, int len, char *resp ) 
{
    return req_trs(0, msg_tp_cd, msg_idr, req, len, resp );
}

int req_trs_fixed(char *msg_tp_cd, char* msg_idr, char *req, int len, char *resp ) 
{
    return req_trs(1, msg_tp_cd, msg_idr, req, len, resp );
}

int req_trs(int type, char *msg_tp_cd, char* msg_idr, char *req, int len, char *resp ) 
{
    static char _trs_req[MAX_TRS_DATA_LEN];
    static char _trs_rsp[MAX_TRS_DATA_LEN];
    struct trs_req_t *trs_req = (struct trs_req_t *)_trs_req;
    struct trs_req_t *trs_rsp = (struct trs_req_t *)_trs_rsp;

    char len_str[10];
    int req_len = 0;

    int port = 0;
    if (type == 0) {
        port = g_trs_xml_port;
    } else {
        port = g_trs_fixed_port;
    }

    int fd = -1;
    fd = init_trs_req(g_trs_ip, port);
    if (fd < 0) {
        ulog( _ERROR_, "TRS connect failed (type:%s)-(%s:%d)", (type == 0) ? "XML" : "FIXED", g_trs_ip, port);
        return -1;
    }

    // MsgTpCd를 TRSID로 변환
    char trs_id[36];
    strcpy(trs_id, msg_tp_cd);
    msgtpcd_to_trsid(type, trs_id);

	ulog(0, "msgtp(%s) trsid(%s)", msg_tp_cd, trs_id);

    memset(_trs_req, 0, PRE_LEN);
    memset(_trs_rsp, 0, PRE_LEN);

    // send request
    req_len = len + PRE_LEN;
    snprintf(len_str, sizeof(len_str), "%05d", (unsigned short)(req_len-REQ_LEN_LEN) );
    
    memset((char*)trs_req, 0x20, PRE_LEN);
    memcpy(trs_req->len, len_str, REQ_LEN_LEN);
    //memcpy(trs_req->trs_id, trs_id, TRS_ID_LEN);
    //memcpy(trs_req->msg_id, msg_idr, TRS_ID_LEN);
    memcpy(trs_req->trs_id, trs_id, strlen(trs_id));
    memcpy(trs_req->msg_id, msg_idr, strlen(msg_idr));
    memcpy(trs_req->data, req, len);

	utrc( req_len, _trs_req, "REQ DATA");
    
    // send request
    int rc = send(fd, (char*) trs_req, req_len, 0);
    if (rc != req_len) {
        ulog( _ERROR_, "Failed to send request to TRS: %s:%d\n", g_trs_ip, port);
        close_trs_req(fd);
        return -2;
    }
	ulog( 0, "TRS send ok (%d)", rc );

    memset(trs_rsp, 0x20, PRE_LEN);

    // receive response
	memset( len_str, 0, sizeof(len_str));

    rc = recv(fd, (char*) len_str, REQ_LEN_LEN, 0);
    if (rc != REQ_LEN_LEN) {
        ulog( _ERROR_, "Failed to receive response from TRS: %s:%d\n", g_trs_ip, port);
        close_trs_req(fd);
        return -3;
    }

    int rsp_len = atoi(len_str);
    if (rsp_len <= 0) {
        ulog( _ERROR_, "Response length is invalid: (%s) --> %d\n", len_str, rsp_len);
        close_trs_req(fd);
        return -4;
    }

    // receive response
	int total_len = 0;
	int rcv_len = rsp_len;
	char *pRcv = (char*)_trs_rsp;

	while(total_len<rsp_len){
      rc = recv(fd, (char*) (pRcv+total_len), rcv_len, 0);
      if (rc < 0){
          ulog( _ERROR_, "Failed to receive response from TRS: %s:%d\n", g_trs_ip, port);
          close_trs_req(fd);
          return -5;
      }
	  total_len += rc;
	  rcv_len -= rc;
	}

    memcpy(resp, _trs_rsp, rsp_len);

	ulog( 0, "TRS recv ok (%d) data_len :%d", rc, rsp_len );

    close_trs_req(fd);
    return rsp_len;
}


#ifdef USE_CURL
// HTTP 응답 데이터를 저장할 구조체
struct http_response {
    char *data;
    size_t size;
};

// HTTP 응답 데이터를 저장하는 콜백 함수
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) 
{
    size_t realsize = size * nmemb;
    struct http_response *resp = (struct http_response *)userp;

    char *ptr = realloc(resp->data, resp->size + realsize + 1);
    if (!ptr) {
        ulog(_ERROR_, "Memory allocation failed");
        return 0;
    }

    resp->data = ptr;
    memcpy(&(resp->data[resp->size]), contents, realsize);
    resp->size += realsize;
    resp->data[resp->size] = 0;

    return realsize;
}

int http_request(const char *url, const char *method, const char *headers[], 
                const char *body, char *response, int response_size) 
{
    CURL *curl;
    CURLcode res;
    struct http_response resp = {0};
    struct curl_slist *header_list = NULL;
    int i;

    // 응답 버퍼 초기화
    resp.data = malloc(1);
    resp.size = 0;

    // CURL 초기화
    curl = curl_easy_init();
    if (!curl) {
        ulog(_ERROR_, "Failed to initialize CURL");
        free(resp.data);
        return -1;
    }

    // URL 설정
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // HTTP 메소드 설정
    if (strcmp(method, "POST") == 0) {
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        if (body) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
        }
    } else if (strcmp(method, "PUT") == 0) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        if (body) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
        }
    } else if (strcmp(method, "DELETE") == 0) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    }

    // 헤더 설정
    if (headers) {
        for (i = 0; headers[i] != NULL; i++) {
            header_list = curl_slist_append(header_list, headers[i]);
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);
    }

    // 응답 콜백 설정
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&resp);

    // SSL 인증서 검증 비활성화 (개발 환경용)
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    // 타임아웃 설정
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);

    // HTTP 요청 실행
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        ulog(_ERROR_, "HTTP request failed: %s", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        if (header_list) {
            curl_slist_free_all(header_list);
        }
        free(resp.data);
        return -1;
    }

    // 응답 코드 확인
    long response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    if (response_code != 200) {
        ulog(_ERROR_, "HTTP request failed with status code: %ld", response_code);
        curl_easy_cleanup(curl);
        if (header_list) {
            curl_slist_free_all(header_list);
        }
        free(resp.data);
        return -1;
    }

    // 응답 데이터 복사
    if (response && response_size > 0) {
        strncpy(response, resp.data, response_size - 1);
        response[response_size - 1] = '\0';
    }

    // 리소스 정리
    curl_easy_cleanup(curl);
    if (header_list) {
        curl_slist_free_all(header_list);
    }
    free(resp.data);

    return 0;
}

// HTTP 요청 초기화 함수
int init_http_request() 
{
    CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
    if (res != CURLE_OK) {
        ulog(_ERROR_, "Failed to initialize CURL global: %s", curl_easy_strerror(res));
        return -1;
    }
    return 0;
}

// HTTP 요청 정리 함수
void cleanup_http_request() 
{
    curl_global_cleanup();
}
#endif

