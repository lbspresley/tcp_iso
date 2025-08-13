/*******************************************************************************
*                                                                              *
*                  (c) Copyright PNPC      Corporation 2004                    *
*                             All Rights Reserved                              *
*                                                                              *
* **************************************************************************** *
*                                                                              *
*  File name   : UC_api.h                                                     *
*                                                                              *
*  Device      : AIX ibmit1 1 5 000BF10D4C00                                   *
*                                                                              *
*  Description : 공통정보 API - 공통정의 헤더파일                      	       *
*                                                                              *
* **************************************************************************** *
*  Change Description.                                                         *
*  --------------------------------------------------------------------------- *
*  Date       Author   Ver    Description                                      *
*  +--------- +------  +----- +----------------------------------------------- *
*  2004.10.06 PNPC     1.0    Initial Release                                  *
*******************************************************************************/
#ifndef __UC_API_H
#define __UC_API_H

#ifdef  __cplusplus
extern "C" {
#endif

/* 각 상수 정의 */
#define UC_OK                 1 
#define UC_ERR               -1
#define UC_CHECK              0
#define UC_SKIP               2
 
#define UC_YES                1
#define UC_NO                -1

#define MAX_STATMSG_LEN      512

#define MAX_ADDRLIST         100     /* 주소정보 최대 갯수 */
#define MAX_BRCNT            512     /* 최대 사무소갯수 */
#define MAX_MNCNT             12     /* 최대 월 갯수 */
#define MAX_BRLIST            50     /* 단순 조회 사무소 갯수 */
#define MAX_IDLIST            10     /* ID카드정보 갯수 */
#define MAX_CLSBR_CNT         15     /* 폐쇄점 갯수 */
#define MAX_MOBRCNT            5     /* 모점 사무소 갯수 */
#define MAX_BSCDTCNT           3     /* 기준일자 레코드 갯수 */
#define MAX_XTNCNT            99     /* 연장내역 레코드 갯수 */
 
/* 기준일자 계산하는 기준구분코드 */
#define BASDT_INF              0     /* 기준일 */
#define BMN_INF                1     /* 월초 */
#define EMN_INF                2     /* 월말 */
#define DDS_INF                3     /* N 일 전후 */
#define NMN_INF                4     /* N 개월 전후 */
#define BZDT_INF               5     /* N 영업일 전후 */

/* 금융휴무 적용시 일자정보의 구분코드 */
#define HBASDT_INF             10    /* 기준일 */ 
#define HBMN_INF               11    /* 월초 */
#define HEMN_INF               12    /* 월말 */
#define HDDS_INF               13    /* N 일 전후 */
#define HNMN_INF               14    /* N 개월 전후 */
#define HBZDT_INF              15    /* N 영업일 전후 */

/* 사무소정보 코드 구분코드 */
#define NAF_ONLC                1    /* 중앙회 온라인 코드 */
#define ACO_HWANC               2    /* 조합 환 코드 */
#define ACO_ONLC                3    /* 조합 온라인 코드 */
 
/* 연장 내역 조회 구분코드 */
#define BK_XTN                  1    /* 은행별 연장내역 */
#define BCHK_XTN                2    /* 지역별 자기앞 연장내역 */
#define CHK_XTN                 3    /* 지역별 기타 연장내역*/
 
/* 기준일자정보 구분코드 */
#define ALL                     0    
#define BZDT                    1    /* 영업일 기준 */
#define TRNDT                   2    /* 거래일 기준 */
#define HBZDT                   3    /* 금융영업일 기준 */
#define DTETC                   4    /* 기준일자 기타 정보 */
 
/* 개국 상태 코드 */
#define TDOPN_STS               0    /* 당일 개별 개국 상태 */
#define BFOPN_STS               1    /* 전일자 개별 개국 상태 */
#define BF2OPN_STS              2    /* 전전일자 개별 개국 상태 */

/* 책임자 단말 여부 */
#define MGR_TRM                 1    /* 책임자 단말 */

/* 콜센터 여부 */
#define CALLCENTER              1    /* 콜센터 */

/* ID카드 등록 여부 */
#define IDCD_REG                1    /* ID카드 등록 */

/* 시도코드별 사무소정보 조회 정렬 Type */
#define NAF_MOBRC_SORT          1    /* 중앙회 모점코드순 */
#define NAF_BRC_SORT            2    /* 중앙회 사무소코드순 */ 
#define NAF_BRNM_SORT           3    /* 중앙회 한글 사무소명 순 */
#define ACO_COFF_SORT          11    /* 조합 시군지부 코드순 */
#define ACO_BRC_SORT           12    /* 조합 사무소코드순 */ 
#define ACO_BRNM_SORT          13    /* 조합 한글 사무소명 순 */

/* 하위정보 관할단계 Level 정의 */
#define FIRST_LEVEL             1    /* 직하위 정보 조회 */
#define ALL_LEVEL               2    /* 모든 하위정보 조회 */

/* 주소검색 구분코드 */
#define KOR_ADDR                1    /* 한글주소 */
#define ENG_ADDR                2    /* 영문주소 */

/* ID카드 취급자 Level 정의 */
#define MGR_LEVEL               1    /* 책임자 */
#define OPTR_LEVEL              2    /* 조작자 */

/* 정보 길이 정의 */
#define DT_LEN                  8    /* 일자 길이 */
#define IDCD_LEN                2    /* ID카드 코드 길이 */
#define SBJ_C_LEN               3    /* 과목코드 길이 */
#define BR_C_LEN                6    /* 사무소 코드 길이 */
#define GIRO_C_LEN              6    /* 지로코드 길이 */
#define NAFACO_DIS_LEN          1    /* 중조 구분 코드 */
#define ORG_FORM_LEN            3    /* 조직형태 길이 */
#define PROV_C_LEN              2    /* 시도코드 길이 */
#define BIZ_DIS_LEN             2    /* 영업구분 코드 길이 */
#define LOC_TP_C_LEN            2    /* 입지유형 코드 길이 */
#define DVLP_TP_LEN             2    /* 발전형태 코드 길이 */
#define RGN_FORM_LEN            2    /* 지역형태 코드 길이 */
#define ACO_DIS_C_LEN           2    /* 조합구분 코드 길이 */
#define BRNM_LEN               40    /* 사무소명 길이 */
#define BR_ENM_LEN             24    /* 영문 사무소명 길이 */
#define BR_ADDR_LEN            52    /* 사무소 주소 */
#define COFF_ONLC_LEN           6    /* 시군지부 코드 길이 */
#define TRRE_DISC_LEN           2    /* 이수관 구분코드 길이 */
#define CLRHS_C_LEN             2    /* 교환소 코드 길이 */
#define CLRHS_IDX_LEN           2    /* 교환소 인덱스 */
#define FX_C_LEN                2    /* 외환코드 길이 */
#define FX_TP_C_LEN             2    /* 외환코드 type */
#define POSTNO_LEN              6    /* 우편번호 길이 */
#define TEL_LEN                14    /* 전화번호 길이 */
#define XUSE_TEL_LEN            9    /* 전용전화번호 길이 */
#define RBNO_LEN               10    /* 사업자 등록번호 길이 */
#define GENMGR_NM_LEN           8    /* 사무소장 명 길이 */
#define BLW_ADDR_LEN           20    /* 읍,면 단위이하 주소길이 */
#define BR_LOCINF_LEN          40    /* 사무소 위치정보 */
#define YNFLAG_LEN              2    /* 여부 Flag 길이 */
#define HLDY_DIS_C_LEN          1    /* 휴일 구분코드 길이 */
#define DOW_C_LEN               1    /* 요일코드 길이 */
#define BIZCTG_LEN              5    /* 업종분류코드 길이 */
#define BIZCTG_TXT_LEN         60    /* 업종분류내용 길이 */ 
#define CUS_DIS_C_LEN           4    /* 고객구분코드 길이 */           
#define CUS_DIS_TXT_LEN        60    /* 고객구분설명 길이 */
#define STAT_C_LEN              2    /* 상태코드 길이 */
#define ACCT_CALC_DIS_C_LEN     1    /* 계좌번호산출 구분코드 길이 */
#define NLFACCT_BR_C_LEN        3    /* 축협계좌 사무소코드 길이 */
#define ACCT_SEQNO_LEN          6    /* 계좌 일련번호 길이 */
#define ACCT_SEQNO1_LEN         5    /* 축협계좌 일련번호 길이1 */
#define ACCT_SEQNO2_LEN         3    /* 축협계좌 일련번호 길이2 */
#define DISTSTG_LEN             1    /* 관할단계 코드 길이 */
#define POSTNO_LEN              6    /* 우편번호 길이 */
#define ADDR_LEN              200    /* 주소 길이 */
#define SEQ_NO_LEN              5    /* 일련번호 길이 */
#define PROV_NM_LEN            10    /* 시도명 길이 */
#define CCW_NM_LEN             15    /* 시군구 길이 */
#define TTV_NM_LEN             17    /* 읍면동명 길이 */
#define INADDR_LEN             52    /* 입력주소 길이 */
#define VILG_NM_LEN            20    /* 번지아파트호수명 길이 */
#define PO_BOX_NM_LEN          36    /* 대량배달처 길이 */
#define PROV_ENM_LEN           25    /* 영문시도명 길이 */
#define CCW_ENM_LEN            35    /* 영문시군구 길이 */
#define TTV_ENM_LEN            35    /* 읍면동명 길이 */
#define PO_BOX_ENM_LEN         85    /* 대량배달처 길이 */
#define CLS_DIS_LEN             1    /* 폐쇄구분 코드 길이 */
#define PSNO_LEN                9    /* ID카드 개인번호 길이 */
#define REGNM_LEN              20    /* ID카드 등록성명 길이 */
#define NSLIP_USE_YN_LEN        1    /* 무전표 사용 여부 길이 */
#define IDCD_REG_YN_LEN         1    /* ID카드 등록 여부 길이 */ 
#define TRMNO_LEN               3    /* 단말기 번호길이 */
#define ACCTNO_LEN             15    /* 계좌번호 길이 */
#define TRNDIS_LEN              2    /* 거래구분 길이 */
#define TRMKND_LEN              2    /* 단말종류 코드 길이 */
#define RRNO_LEN               13    /* 실명번호 길이 */
#define GUSNM_LEN              24    /* 예금주명 */
#define EABR_NM_LEN             3    /* 요일영문약어명 */
#define TM_LEN                  6    /* 시각 길이 */  

/* 점정보 체크 : 001 - 100 */
#define UC_ERR_TRN_ACCTBR_BEFOREOPN      2 
#define UC_ERR_TRN_TRNBR_BEFOREOPN       5 
#define UC_ERR_TRN_BDOPN_ACCCLS          6 
#define UC_ERR_TRN_ACCTBR_ACLS2          7 
#define UC_ERR_TRN_BOTH_ACLS_REGN        8
#define UC_ERR_TRN_ACLS_HWANFTRN        10
#define UC_ERR_TRN_CLS_REGN             11
#define UC_ERR_TRN_ACCTBR_ACLS1         13
#define UC_ERR_TRN_YEARLDD_ACLS         14
#define UC_ERR_TRN_BDOPN_TRMLINK        42
#define UC_ERR_TRN_BDOPN_ACLS           43
#define UC_ERR_TRN_NAF_NETTRN           45
#define UC_ERR_TRN_BIZSTP               49
#define UC_ERR_TRN_ONLC                 51
#define UC_ERR_TRN_BRC                  52
#define UC_ERR_TRN_OPN                  54
#define UC_ERR_TRN_CLS                  56
#define UC_ERR_TRN_TRMNO                61
#define UC_ERR_TRN_ACLS_REG             63
#define UC_ERR_TRN_ACCTNO               71
#define UC_ERR_TRN_SBJCD                80
#define UC_ERR_TRN_BIZDIS               81
#define UC_ERR_TRN_HLDYDIS              82
#define UC_ERR_TRN_HANARO_ACDREG        83
#define UC_ERR_TRN_HLDY_CC              84
#define UC_ERR_TRN_CHKCD_24365          85
#define UC_ERR_TRN_INDATA_NULL          91
#define UC_ERR_TRN_NOTFOUND_DATA        92

/* 사무소 조회 API : 101 - 120 */
#define UC_ERR_BR_INDATA_NULL          101
#define UC_ERR_BR_NOTFOUND_DATA        102
#define UC_ERR_BR_INDATA_LENGTH        103
#define UC_ERR_BR_INDATA_OUTOFRANGE    104
#define UC_ERR_BR_UNKNOWN_TYPE         105

/* 날짜 API : 111 - 110 */
#define UC_ERR_DT_INDATA_NULL          111
#define UC_ERR_DT_NOTFOUND_DATA        112
#define UC_ERR_DT_INDATA_TERM          113
#define UC_ERR_DT_INDATA_VALUE         114
#define UC_ERR_DT_INDATA_OUTOFRANGE    115
#define UC_ERR_DT_UNKNOWN_TYPE         116
#define UC_ERR_DT_RCKVALID             117

/* ID카드 API  : 121 - 130 */
#define UC_ERR_ID_INDATA_NULL          121
#define UC_ERR_ID_NOTFOUND_DATA        122
#define UC_ERR_ID_INDATA_VALUE         123
#define UC_ERR_ID_NOTREGIST_NO         124
#define UC_ERR_ID_SAME_PSNO            125

/* 코드 조회 API : 131 - 140 */
#define UC_ERR_CD_INDATA_NULL          131
#define UC_ERR_CD_NOTFOUND_DATA        132
#define UC_ERR_CD_INDATA_LENGTH        133
#define UC_ERR_CD_INVALID              134
#define UC_ERR_CD_UNKNOWN_TYPE         135

/* 계좌 API    : 141 - 150 */
#define UC_ERR_ACT_INDATA_NULL         141
#define UC_ERR_ACT_NOTFOUND_DATA       142
#define UC_ERR_ACT_INDATA_LENGTH       143
#define UC_ERR_ACT_CHKDIGIT            144
#define UC_ERR_ACT_UNKNOWN_TYPE        145

/* Util API Error : 151 - 170 */
#define UC_ERR_INDATA_DATEFORM         151
#define UC_ERR_INDATA_TIMEFORM         152
#define UC_ERR_INDATA_LENGTH           153
#define UC_ERR_INDATA_OUTOFRANGE       154
#define UC_ERR_INDATA_UNKNOWN_TYPE     155
#define UC_ERR_INDATA_VALUE            156
#define UC_ERR_INDATA_CHKDIGIT         157
#define UC_ERR_OUTPUT_DAYINX           158
#define UC_ERR_FILESTAT                159

/* MMDB Handle Error Code : 211 ~ 230 */
#define	UC_ERR_MMDB_CONNECT					   211
#define	UC_ERR_MMDB_DISCONN						 212
#define UC_ERR_MMDB_NODATA             213
#define UC_ERR_MMDB_SELECT             214
#define UC_ERR_MMDB_INSERT             215
#define UC_ERR_MMDB_UPDATE             216
#define UC_ERR_MMDB_DELETE             217
#define	UC_ERR_MMDB_AUTOCOMMIT_OFF		 218
#define	UC_ERR_MMDB_COMMIT						 219
#define	UC_ERR_MMDB_ROLLBACK					 220
#define UC_ERR_MMDB_HANDLE             221
#define UC_ERR_MMDB_OTHER              222
#define UC_ERR_MMDB_BUFFERLEN					 223
#define UC_ERR_MMDB_CONNENV            224

#ifdef  __cplusplus
}
#endif


#endif 
