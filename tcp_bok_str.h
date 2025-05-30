#ifndef __TCP_BOK_STR_H__
#define __TCP_BOK_STR_H__

//#ifdef TERM_TABLE 
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
//#endif


typedef struct {
	char	snd_len		[5];	/* 전문송신 Byte 수		*/
	char	bz_dst_cd	[9];	/* 거래구분 코드		*/
	char	sys_id		[3];	/* System ID			*/
	char	tlg_tp		[4];	/* 전문종별 코드		*/
	char	bz_date		[8];	/* 영업일자				*/
	char	bz_sts		[4];	/* STATUS				*/
	char	rsp_cd		[4];	/* 응답코드				*/
	char	tlg_mgm_no	[20];	/* 전문관리번호			*/
	char	tlg_snd_tm	[14];	/* 전문전송시간			*/
	char	rfr_no		[20];	/* 참조번호				*/
	char	snd_org_cd	[4];	/* 송신기관				*/
	char	rcv_org_cd	[4];	/* 수신기관				*/
	char	enc_yn			;	/* 암호화 여부			*/	
	char	snd_nft		[3];	/* 전송횟수				*/
	char	filler		[65];	/* 공란					*/
	char	enc_org_id	[16];	/* 참가기관 ID			*/
	char	enc_org_pwd	[16];	/* 참가기관 비밀번호	*/
} BOK_COMMON_STR;
#define SIZE_BOK_COMMON_STR 200 

typedef struct {
	BOK_COMMON_STR	Common	;			/* 공통부		*/

	char			indv_pt_len	[ 4];	/* 개별부 길이	*/
	/* 개별부 존재 */
} BOK_SKEY_STR;
#define SIZE_BOK_SKEY_STR (SIZE_BOK_COMMON_STR + 4) 


typedef struct {
	BOK_COMMON_STR  Common		;		/* 공통부			*/

	char			new_pw	[16];		/* 비밀번호 변경	*/
	char			filler	[16];		/* space			*/
} BOK_CHNG_PW_STR;
#define SIZE_BOK_CHNG_PW_STR (SIZE_BOK_COMMON_STR + 32) 


/* LHY 국고망 구조체 ----------------------------------------------*/

typedef struct {
	char	snd_len		[4];	/* 전문송신 Byte 수		*/
	char    bz_no       [9];    /* 거래번호             */
	char    apcode      [2];    /* 업무코드             */
	char    bz_kind_cd  [2];    /* 거래종류코드         */
	char    rs_flag;            /* 요청/응답 구분       */
	char    snd_org_cd  [3];    /* 송신기관             */
	char    rcv_org_cd  [3];    /* 수신기관             */
	char    bz_date     [8];    /* 거래일자             */
	char    bz_time     [6];    /* 거래시각             */
	char    tlg_mgm_no  [7];    /* 전문관리번호         */
	char    prc_org_cd  [3];    /* 처리기관코드         */
	char    prc_res_cd  [4];    /* 처리결과코드         */
	char    cd_chg_dst;         /* 코드변환구분         */
	char    filler1     [61];   /* 공란                 */
	char    enc_org_id  [20];   /* 사용자ID             */
	char    enc_org_pwd [8];    /* 비밀번호             */
} BOK_NF_COMMON_STR;
#define SIZE_BOK_NF_COMMON_STR (sizeof(BOK_NF_COMMON_STR)) 

/* 암호변경 전문 : TEJG00011 */
/* 회선시험 전문 : TEJG00012(한국은행 요청), TEJG00013(참가기관 요청) : chg_flag 부터 filler2까지 모두 공란임. */
typedef struct {
	BOK_NF_COMMON_STR  Common;

	char            chg_flag;           /* 변경여부         */
	char            NewID       [20];   /* 변경 ID          */
	char            NewPasswd   [ 8];   /* 변경 PASSWORD    */ /* 20200406 : fix for length 16 --> 8 */
	char            filler2     [292];  /* 공란             */
	char            end;                /* 종료표시         */
} BOK_NF_PASSWD_STR;
#define SIZE_BOK_NF_PASSWD_STR (sizeof(BOK_NF_PASSWD_STR))


/* 세션키 교환 전문 */
typedef struct {
	BOK_NF_COMMON_STR  Common  ;        /* 공통부       */

	char            indv_pt_len [ 4];   /* 개별부 길이  */
	/* 개별부 존재 */
} BOK_NF_SKEY_STR;
#define SIZE_BOK_NF_SKEY_STR (SIZE_BOK_NF_COMMON_STR + 4)

#endif
