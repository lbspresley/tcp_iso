//Client 세션키 교환 요구(1) 송신
int cli_send_1(char* PeerIP, char* PeerPort, char* LocalPort);

//Client 세션키 교환 통보(2) 수신
int cli_recv_2(char* msg, int len);

//Client 세션키 교환 통보(4) 수신
int cli_recv_4(char* msg, int len);

