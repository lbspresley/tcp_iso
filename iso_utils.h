#include "tcp_iso.h"

#if 1
#define SKEY_TEMPLATE "<bwh:BokwireEnvelope xmlns:bwh=\"urn:bok:std:iso:20022:xsd:001\"><bwh:BokwireHeader><SecurityHandshake><TrCd>%09d</TrCd><Key>%s</Key></SecurityHandshake></bwh:BokwireHeader></bwh:BokwireEnvelope>"

#define ACK_TEMPLATE "<bwh:BokwireEnvelope xmlns:bwh=\"urn:bok:std:iso:20022:xsd:001\"><bwh:BokwireHeader><Response><RespCd>%s</RespCd><MsgTpCd>%s</MsgTpCd><BizSvc>%s</BizSvc><BizMsgIdr>%s</BizMsgIdr></Response></bwh:BokwireHeader></bwh:BokwireEnvelope>"

#define BOKWIRE_HEADER_TEMPLATE "<bwh:BokwireEnvelope xmlns:bwh=\"urn:bok:std:iso:20022:xsd:001\"><bwh:BokwireHeader><Request><MsgTpCd>%s</MsgTpCd><Id>%s</Id><Password>%s</Password></Request></bwh:BokwireHeader><bwh:BokwireBody>%s</bwh:BokwireBody></bwh:BokwireEnvelope>"
#else
#define SKEY_TEMPLATE "<bwh:BokwireEnvelope xmlns:bwh=\"urn:bok:std:iso:20022:xsd:001\">\
     <bwh:BokwireHeader>\
         <SecurityHandshake>\
             <TrCd>%09d</TrCd>\
             <Key>%s</Key>\
        </SecurityHandshake>\
    </bwh:BokwireHeader>\
</bwh:BokwireEnvelope>"

#define ACK_TEMPLATE "<bwh:BokwireEnvelope xmlns:bwh=\"urn:bok:std:iso:20022:xsd:001\">\
     <bwh:BokwireHeader>\
        <Response>\
            <RespCd>%s</RespCd>\
            <MsgTpCd>%s</MsgTpCd>\
            <BizSvc>%s</BizSvc>\
            <BizMsgIdr>%s</BizMsgIdr>\
        </Response>\
    </bwh:BokwireHeader>\
</bwh:BokwireEnvelope>"

#define BOKWIRE_HEADER_TEMPLATE "<bwh:BokwireEnvelope xmlns:bwh=\"urn:bok:std:iso:20022:xsd:001\">\
     <bwh:BokwireHeader>\
        <Request>\
            <MsgTpCd>%s</MsgTpCd>\
            <Id>%s</Id>\
            <Password>%s</Password>\
        </Request>\
    </bwh:BokwireHeader>\
    <bwh:BokwireBody>%s</bwh:BokwireBody>\
</bwh:BokwireEnvelope>"
#endif

// Setting variables
// 1. BizMsgIdr(request 복사)
// 2. MmbId(자신의 은행 코드)
// 3. BizMsgIdr (신규발행)
// 4. CreDt (현재시간)
// 5. BizPrcgDt (개시 시간 : 현재날짜+9시 고정)
// 6. MsgId (3번항목 동일)
// 7. OrgtrRef (1번항목 동일)
// 8. EvtTm (request 복사)
#if 1
#define POLL_RSP_TEMPLATE "<bwh:BokwireEnvelope xmlns:bwh=\"urn:bok:std:iso:20022:xsd:001\"><bwh:BokwireHeader><Request><MsgTpCd>admi.011</MsgTpCd><Id>%s</Id><Password>%s</Password></Request></bwh:BokwireHeader><bwh:BokwireBody><AppHdr xmlns=\"urn:iso:std:iso:20022:tech:xsd:head.001.001.03\"><Fr><FIId><FinInstnId><ClrSysMmbId><ClrSysId><Cd>KRBOK</Cd></ClrSysId><MmbId>%s</MmbId></ClrSysMmbId></FinInstnId></FIId></Fr><To><FIId><FinInstnId><ClrSysMmbId><ClrSysId><Cd>KRBOK</Cd></ClrSysId><MmbId>1016</MmbId></ClrSysMmbId></FinInstnId></FIId></To><BizMsgIdr>%s</BizMsgIdr><MsgDefIdr>admi.011.001.01</MsgDefIdr><BizSvc>bok.rtgs.ping.01</BizSvc><CreDt>%s</CreDt><BizPrcgDt>%s</BizPrcgDt></AppHdr><Document xmlns=\"urn:iso:std:iso:20022:tech:xsd:admi.011.001.01\"><SysEvtAck><MsgId>%s</MsgId><OrgtrRef>%s</OrgtrRef><AckDtls><EvtCd>PING</EvtCd><EvtParam>1016</EvtParam><EvtTm>%s</EvtTm></AckDtls></SysEvtAck></Document></bwh:BokwireBody></bwh:BokwireEnvelope>"

#define POLL_REQ_TEMPLATE "<bwh:BokwireEnvelope xmlns:bwh=\"urn:bok:std:iso:20022:xsd:001\"><bwh:BokwireHeader><Request><MsgTpCd>admi.004.ConnectionCheck</MsgTpCd><Id>%s</Id><Password>%s</Password></Request></bwh:BokwireHeader><bwh:BokwireBody><AppHdr xmlns=\"urn:iso:std:iso:20022:tech:xsd:head.001.001.03\"><Fr><FIId><FinInstnId><ClrSysMmbId><ClrSysId><Cd>KRBOK</Cd></ClrSysId><MmbId>%s</MmbId></ClrSysMmbId></FinInstnId></FIId></Fr><To><FIId><FinInstnId><ClrSysMmbId><ClrSysId><Cd>KRBOK</Cd></ClrSysId><MmbId>1016</MmbId></ClrSysMmbId></FinInstnId></FIId></To><BizMsgIdr>%s</BizMsgIdr><MsgDefIdr>admi.004.001.01</MsgDefIdr><BizSvc>bok.rtgs.ping.01</BizSvc><CreDt>%s</CreDt><BizPrcgDt>%s</BizPrcgDt></AppHdr><Document xmlns=\"urn:iso:std:iso:20022:tech:xsd:admi.004.001.01\"><admi.004.001.01><EvtInf><EvtCd>PING</EvtCd><EvtParam>%s</EvtParam><EvtTm>%s</EvtTm></EvtInf></admi.004.001.01></Document></bwh:BokwireBody></bwh:BokwireEnvelope>"

#else

#define POLL_RSP_TEMPLATE "<bwh:BokwireEnvelope xmlns:bwh=\"urn:bok:std:iso:20022:xsd:001\">\
    <bwh:BokwireHeader>\
        <Request>\
            <MsgTpCd>admi.011</MsgTpCd>\
            <Id>%s</Id>\
            <Password>%s</Password>\
        </Request>\
    </bwh:BokwireHeader>\
    <bwh:BokwireBody>\
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
            <MsgDefIdr>admi.011.001.01</MsgDefIdr>\
            <BizSvc>bok.rtgs.ping.01</BizSvc>\
            <CreDt>%s</CreDt>\
            <BizPrcgDt>%s</BizPrcgDt>\
        </AppHdr>\
        <Document xmlns=\"urn:iso:std:iso:20022:tech:xsd:admi.011.001.01\">\
            <SysEvtAck>\
                <MsgId>%s</MsgId>\
                <OrgtrRef>%s</OrgtrRef>\
                <AckDtls>\
                    <EvtCd>PING</EvtCd>\
                    <EvtParam>1016</EvtParam>\
                    <EvtTm>%s</EvtTm>\
                </AckDtls>\
            </SysEvtAck>\
        </Document>\
    </bwh:BokwireBody>\
</bwh:BokwireEnvelope>"

#define POLL_REQ_TEMPLATE "<bwh:BokwireEnvelope xmlns:bwh=\"urn:bok:std:iso:20022:xsd:001\">\
     <bwh:BokwireHeader>\
        <Request>\
            <MsgTpCd>admi.004.ConnectionCheck</MsgTpCd>\
            <Id>%s</Id>\
            <Password>%s</Password>\
        </Request>\
    </bwh:BokwireHeader>\
    <bwh:BokwireBody>\
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
    </bwh:BokwireBody>\
</bwh:BokwireEnvelope>"

#endif

#define MAX_MSG_LEN 100*1024

void get_iso_datetime(char timestr[32]);
void get_iso_date(char datestr[32], char timestr[9]);
void get_today(char date[32]);
void get_seq(char seq[7], char date[32]);
void get_msg_idr(char msgidr[35]); // 메시지 고유번호 생성

unsigned char* make_sess_key_msg(int step, char* key); // 세션키 메시지 생성
unsigned char* get_tag_value(char* msg, char* tag); // 태그값 추출
unsigned char* get_sess_key(char* msg); // 세션키를 추출
unsigned char* get_tr_cd(char* msg); // 트랜잭션코드를 추출

int charset_convert(int encode_type, char* msg, size_t msg_len, unsigned char* out_msg, size_t *out_msg_len ); // 문자셋 변환
unsigned char* convert_to_utf8(char* kr_encoding, char* msg, size_t msg_len, size_t *out_msg_len ); // UTF-8로 변환
unsigned char* convert_to_kr(char* kr_encoding, char* msg, size_t msg_len, size_t *out_msg_len ); // EUC-KR로 변환

unsigned char* make_network_msg(); // 네트워크 체크 메시지 생성
unsigned char* make_ack_msg(char* reqxml); // ACK 메시지 생성
int is_poll_msg(char* msg); // POLL 요청메시지 여부 체크
int is_ack_response_msg(char* msg); // ACK 응답메시지 여부 체크
int is_need_ack_msg(char* msg); // ACK 필요 여부 체크
int send_standard_msg(char* msg, int msg_len); // 표준 메시지 전송

int process_poll_request(char* msg); // POLL 요청메시지 처리
int process_ack_response(char* msg); // ACK 응답메시지 처리

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

int process_message(char* in, int inlen);
int process_session_key(char* SrcSvc, char* in, int inlen);

// iso_header.c
int check_msg_tp_cd(char* msg_tp_cd);

unsigned char* make_poll_response(char* reqxml);
//unsigned char* make_poll_request(int get_msg_idr_flag);
unsigned char* make_poll_request(int flag, char* msgidr);
unsigned char* _make_poll_request(char* msgidr);
unsigned char* make_header(char* msg_tp_cd, char* body);
unsigned char* get_body(char* msg);
unsigned char* strip_xml_message(char* msg);
unsigned char* make_escaped_value(char* msg);
unsigned char* make_unescaped_value(char* msg);
