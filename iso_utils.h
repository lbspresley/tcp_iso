#include "tcp_iso.h"

#define SKEY_TEMPLATE "<bwh:BokwireEnvelope xmlns:bwh=\"urn:bok:std:iso:20022:xsd:001\">\
     <bwh:BokwireHeader>\
         <SecurityHandshake>\
             <TrCd>%09d</TrCd>\
             <Key>%s</Key>\
        </SecurityHandshake>\
    </bwh:BokwireHeader>\
</bwh:BokwireEnvelope>"

#define NETWORK_TEMPLATE "<bwh:BokwireEnvelope xmlns:bwh=\"urn:bok:std:iso:20022:xsd:001\">\
     <bwh:BokwireHeader>\
        <admi.004.001.01>\
            <EvtInf>\
                <EvtCd>PING</EvtCd>\
                <EvtParam>%s</EvtParam>\
                <EvtTm>%s</EvtTm>\
            </EvtInf>\
        </admi.004.001.01>\
    </bwh:BokwireHeader>\
</bwh:BokwireEnvelope>"

#define ACK_TEMPLATE "<bwh:BokwireEnvelope xmlns:bwh=\"urn:bok:std:iso:20022:xsd:001\">\
     <bwh:BokwireHeader>\
        <Response>\
            <RespCd>%s</RespCd>\
            <MsgTpCd>%s</MsgTpCd>\
            <BizSvc>%s</BizSvc>\
            <BizMsgIdr>%s</MsgIdr>\
        </Response>\
    </bwh:BokwireHeader>\
</bwh:BokwireEnvelope>"

#define POLL_REQ_TEMPLATE "<bwh:BokwireEnvelope xmlns:bwh=\"urn:bok:std:iso:20022:xsd:001\">\
     <bwh:BokwireHeader>\
        <Request>\
            <MsgTpCd>pacs.002.GTR</MsgTpCd>\
            <Id>%s</Id>\
            <Password>%s</Password>\
        </Request>\
    </bwh:BokwireHeader>\
    <AppHdr xmlns=\"urn:iso:std:iso:20022:tech:xsd:head.001.001.03\">\
        <Fr>\
            <FIId>\
                <FinInstnId>\
                    <ClrSysMmbId>\
                        <ClrSysId>\
                            <Cd>KRBOK</Cd>\
                        </ClrSysId>\
                        <MmbId>%s</MmbId>\
                    </ClrSysMmbId>\
                </FinInstnId>\
            </FIId>\
        </Fr>\
        <To>\
            <FIId>\
                <FinInstnId>\
                    <ClrSysMmbId>\
                        <ClrSysId>\
                            <Cd>KRBOK</Cd>\
                        </ClrSysId>\
                        <MmbId>1016</MmbId>\
                    </ClrSysMmbId>\
                </FinInstnId>\
            </FIId>\
        </To>\
        <BizMsgIdr>%s</BizMsgIdr>\
        <MsgDefIdr>admi.004.001.01</MsgDefIdr>\
        <BizSvc>bok.rtgs.ping.01</BizSvc>\
        <CreDt>%s</CreDt>\
        <BizPrcgDt>%s</BizPrcgDt>\
    </AppHdr>\
    <Document xmlns=\"urn:iso:std:iso:20022:tech:xsd:admi.004.001.01\">\
        <admi.004.001.01>\
            <EvtInf>\
                <EvtCd>PING</EvtCd>\
                <EvtParam>%s</EvtParam>\
                <EvtTm>%s</EvtTm>\
            </EvtInf>\
        </admi.004.001.01>\
    </Document>\
</bwh:BokwireEnvelope>"

#define MAX_MSG_LEN 200*1024

void get_iso_datetime(char timestr[32]);
void get_msg_idr(char msgidr[35]); // 메시지 고유번호 생성

unsigned char* make_sess_key_msg(int step, char* key); // 세션키 메시지 생성
unsigned char* get_tag_value(char* msg, char* tag); // 태그값 추출
unsigned char* get_sess_key(char* msg); // 세션키를 추출
unsigned char* get_tr_cd(char* msg); // 트랜잭션코드를 추출

size_t charset_convert(int encode_type, char* msg, size_t msg_len, unsigned char* out_msg, size_t *out_msg_len ); // 문자셋 변환
unsigned char* convert_to_utf8(char* kr_encoding, char* msg, size_t msg_len, size_t *out_msg_len ); // UTF-8로 변환
unsigned char* convert_to_kr(char* kr_encoding, char* msg, size_t msg_len, size_t *out_msg_len ); // EUC-KR로 변환

unsigned char* make_network_msg(); // 네트워크 체크 메시지 생성
unsigned char* make_ack_msg(char* reqxml); // ACK 메시지 생성
int is_ack_response_msg(char* msg); // ACK 응답메시지 여부 체크
int is_need_ack_msg(char* msg); // ACK 필요 여부 체크
int send_standard_msg(char* msg, int msg_len); // 표준 메시지 전송

int inl_decrypt(char* in, int inlen, char** out, int* outlen); // 복호화
int inl_encrypt(char* in, int inlen, char** out, int* outlen); // 암호화


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

int CF_ProcessMessage(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2);

int CF_ProcessSessionKey(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2);