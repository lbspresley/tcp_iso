#ifndef __TCP_BOK_STR_H__
#define __TCP_BOK_STR_H__

typedef struct { 
	char	SGName[16];
	int		stidx;                           
	int		onuse;                           
	int		cnt_stat; 				/* Session연결 상태 */
									/* 1:on, -1:off, 7:기연결 */
	in_addr_t PeerIP;                    
	unsigned short PeerPort;             
	unsigned short LocalPort;            
} TERM_TABLE;


typedef struct {
	char            command    [ 5];   /* 명령어 : REQ/RSP/ACK */
	char            rsp        [ 5];   /* 응답 : TRUE/SUCCESS(0000) */
	char            msgtpcd    [30];   /* 메시지 유형코드 : admi.004.001.01  */
	char            bizsvc     [30];   /* 업무서비스 : bok.rtgs.gtr.01 */
	char            bizmsgidr  [30];   /* 메시지 고유번호 : YYYYMMDD + ORGID(4) + TYPE(S/T) + SERIAL(8:00000000) + SEQ(6) */
} ISO_FEP_HEADER;
#define SIZE_ISO_FEP_HEADER (sizeof(ISO_FEP_HEADER))

#if 1
typedef struct {
	char ApCode   [32];  // CORE -> BOK  : OAL2_ISOMSG_O
	                     // BOK  -> CORE : OAL2_ISOMSG_I
	char MsgTpCd  [35];  // MsgTpCd : pacs.009.CORE ==> pacs_009_CORE 
	char BizMsgIdr[35];  // BizMsgIdr
} BOK_HEADER;
#else
typedef struct {
	char RespCd   [7];   // REQ(O),RSP(O) (REQ:SPACE, RSP:SUCCESS/FAIL)
	char MsgTpCd  [35];  // REQ(O),RSP(O) (Max 27)
	char BizSvc   [35];  // REQ(X),RSP(O)
	char BizMsgIdr[35];  // REQ(X),RSP(O)
	char Id       [16];  // REQ(O),RSP(X)
	char Password [16];  // REQ(O),RSP(X)
} BOK_HEADER;
#endif
#define SIZE_BOK_HEADER (sizeof(BOK_HEADER))

#endif
