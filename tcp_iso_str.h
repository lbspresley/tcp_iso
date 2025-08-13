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
	char            MsgTpCd    [16];   /* 메시지 유형코드 : admi.004.001.01  */
	char            BizMsgIdr  [64];   /* 메시지 고유번호           */
	char            prc_org_cd [ 3];   /* 처리기관코드     */
} ISO_FEP_HEADER;
#define SIZE_ISO_FEP_HEADER (sizeof(ISO_FEP_HEADER))

#endif
