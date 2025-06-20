
#include "tcp_bok.h"

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

#define MAX_MSG_LEN 200*1024

char* make_sess_key_msg(int step, char* key); // 세션키 메시지 생성
char* get_tag_value(char* msg, char* tag); // 태그값 추출
char* get_sess_key(char* msg); // 세션키를 추출
char* get_tr_cd(char* msg); // 트랜잭션코드를 추출
char* make_network_msg(); // 네트워크 체크 메시지 생성
size_t charset_convert(int encode_type, char* msg, size_t msg_len, char* out_msg, size_t *out_msg_len ); // 문자셋 변환
char* convert_to_utf8(char* msg, size_t msg_len, size_t *out_msg_len ); // UTF-8로 변환
char* convert_to_euc_kr(char* msg, size_t msg_len, size_t *out_msg_len ); // EUC-KR로 변환
