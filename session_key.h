//Server 세션키 교환 요구(1) 수신
int svr_recv_1(char* msg, int len);

//Server 세션키 교환 통보(3) 수신
int svr_recv_3(char* msg, int len);

//Server 세션키 교환 통보(5) 수신
int svr_recv_5(char* msg, int len);

//Client 세션키 교환 요구(1) 송신
int cli_send_1(char* PeerIP, char* PeerPort, char* LocalPort);

//Client 세션키 교환 통보(2) 수신
int cli_recv_2(char* msg, int len);

//Client 세션키 교환 통보(4) 수신
int cli_recv_4(char* msg, int len);

// Timeout Callback
void TF_Key_Timeout(int TimerID, int lParam, int rParam);

// Client Session Key
int lf_Client_SessionKey(char* msg, int len, char* tr_cd);

// Server Session Key
int lf_Server_SessionKey(char* msg, int len, char* tr_cd);