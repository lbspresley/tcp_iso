#include "tcp_iso.h"
#include "trs_req.h"
#ifdef USE_CURL
#include <curl/curl.h>
#endif

char* g_trs_ip = "127.0.0.1";
int g_trs_port = 58110;
int g_tcp_fd = -1;
struct trs_req_t *g_trs_req;
struct trs_req_t *g_trs_rsp;

int init_trs_req(char *trs_ip, int trs_port) 
{
    g_trs_ip = trs_ip;
    g_trs_port = trs_port;
    g_tcp_fd = tcp_connect(g_trs_ip, g_trs_port);
    if (g_tcp_fd == -1) {
        printf("Failed to connect to TRS: %s:%d\n", g_trs_ip, g_trs_port);
        return -1;
    }
    printf("Connected to TRS: %s:%d\n", g_trs_ip, g_trs_port);

    g_trs_req = (struct trs_req_t*) malloc(MAX_TRS_DATA_LEN);
    g_trs_rsp = (struct trs_req_t*) malloc(MAX_TRS_DATA_LEN);
    if (g_trs_req == NULL || g_trs_rsp == NULL) {
        printf("Failed to allocate memory for TRS request\n");
        return -1;
    }
    memset(g_trs_req, 0, MAX_TRS_DATA_LEN);
    memset(g_trs_rsp, 0, MAX_TRS_DATA_LEN);

    return 0;
}

int close_trs_req() 
{
    if (g_tcp_fd != -1) {
        close(g_tcp_fd);
        g_tcp_fd = -1;
    }
    return 0;
}

int req_trs(char *trs_id, char *req, int len, char *resp, int resp_len) 
{
    char len_str[10];
    int req_len = 0;

    if (g_tcp_fd == -1) {
        printf("TRS is not connected\n");
        return -1;
    }

    // send request
    req_len = len + PRE_LEN;
    snprintf(len_str, sizeof(len_str), "%05d", req_len);
    
    memset(g_trs_req, 0x20, PRE_LEN);
    memcpy(g_trs_req->req_len, len_str, REQ_LEN_LEN);
    memcpy(g_trs_req->req_id, trs_id, TRS_ID_LEN);
    memcpy(g_trs_req->master_id, trs_id, TRS_ID_LEN);
    memcpy(g_trs_req->req_data, req, len);
    
    // 000 : transform request
    // 001 : data field display
    // 100 : transform response
    memcpy(g_trs_req->req_type, "000", REQ_TYPE_LEN);

    // send request
    int nRc = send(g_tcp_fd, (char*) g_trs_req, req_len, 0);
    if (nRc != req_len) {
        printf("Failed to send request to TRS: %s:%d\n", g_trs_ip, g_trs_port);
        return -1;
    }

    memset(g_trs_rsp, 0x20, PRE_LEN);

    // receive response
    nRc = recv(g_tcp_fd, (char*) g_trs_rsp, PRE_LEN, 0);
    if (nRc != PRE_LEN) {
        printf("Failed to receive response from TRS: %s:%d\n", g_trs_ip, g_trs_port);
        return -1;
    }

    // parse response
    memcpy(len_str, g_trs_rsp->req_len, REQ_LEN_LEN);
    int rsp_len = atoi(len_str);
    if (rsp_len <= 0) {
        printf("Response length is invalid: (%s) --> %d\n", len_str, rsp_len);
        return -1;
    }

    // receive response
    nRc = recv(g_tcp_fd, (char*) g_trs_rsp->req_data, rsp_len, 0);
    if (nRc != rsp_len) {
        printf("Failed to receive response from TRS: %s:%d\n", g_trs_ip, g_trs_port);
        return -1;
    }

    return 0;
}

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
        return -1;
    }
    
    // 수신 타임아웃 설정
    if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        ulog( _ERROR_, "Set receive timeout failed");
        close(sock_fd);
        return -1;
    }

    // 서버에 연결
    ret = connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (ret < 0) {
        ulog( _ERROR_, "Connection failed");
        close(sock_fd);
        return -1;
    }

    ulog( _FLOW_, "Connected to server %s:%d", ip, port);
    return sock_fd;
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