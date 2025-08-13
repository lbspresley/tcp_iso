/*******************************************************************************
*  File name   : UC_chars.h                                                   *
*  Device      : AIX p615 3 5
*  Description : 공통util library - 문자함수        	       *
* **************************************************************************** *
*  Change Description.                                                         *
*  --------------------------------------------------------------------------- *
*  Date       Author   Ver    Description                                      *
*  +--------- +------  +----- +----------------------------------------------- *
*  2003.09.30 IBM-KR   1.09   Initial Release                                  *
*                                                                              *
*******************************************************************************/
#ifndef __UC_LIB_H
#define __UC_LIB_H

#ifdef  __cplusplus
extern "C" {
#endif

int UC_SubConvAscii(char* apInStr, int i_Len, char* apOutStr );
int UC_SconvChrToAscii (char acInChr, int *aiAscii);
int UC_SconvAsciiToChr (int aiInAscii, char *acChr);
int UC_SconvDblToStr (double adInNum, int aiWidth, char *apStrNum);
int UC_SconvIntToStr (int aiInNum, char *apStrNum);
int UC_SconvLongToStr (long alInNum, char *apStrNum);
int UC_SconvStrToInt (char *apInStrNum, int *aiNum);
int UC_SconvStrToLong (char *apInStrNum, long *alNum);
int UC_SconvStrToDouble (char *apInStrNum, double *adNum);
int UC_SconvNumToHangle (char *apInNum, int aiMode, char *apHangleNum);
int UC_SconcatTwoString (const char *apOneStr, const char *apOtherStr, char *apMergeStr);
int UC_SgetLowerStr (char *);
int UC_SgetUpperStr (char *);
int UC_SgetLeftPadStr (char *apInStr, int aiStrLen, char *apAddStr, char *apPaddedStr);
int UC_SgetRightPadStr (char *apInStr, int aiStrLen, char *apAddStr, char *apPaddedStr);
int UC_SgetLeftTrimStr (char *pc_Str, int i_Len);
int UC_SgetRightTrimStr (char *apInStr, char *apTrimmedStr);
int UC_SgetAllTrimStr (char *apInStr, char *apTrimmedStr);
int UC_SconvTwoSpaceToOneStr (char *apInStr, char *apConvStr);
int UC_SaddRightSpaceStr (char *apInStr, int aiStrLen, char *apAddedStr);
int UC_SaddLeftSpaceStr (char *apInStr, int aiStrLen, char *apAddedStr);
int UC_ScopyStrSpace (char *apInStr, int aiCopyLen, char *apCopyStr);
int UC_SaddLeftZeroStr (char *apInStr, int aiStrLen, char *apAddedStr);
int UC_SgetTokenStr (char *apInStr, char acDelimeter, char *apTokenStr);
int UC_SconvDblToMoney (double adNumber, char *apMoneyStr);
int UC_SconvLongToMoney (long alNumber, char *apMoneyStr);
int UC_SconvStrToMoney (char *apNumber, char *apMoneyStr);
int UC_SreplaceStr (char *apInStr, char *apFindStr, char *apChgStr, char *apConvStr);
int UC_SstuffStr (char *apOrgStr, int aiFromInx, int aiDelCnt, char *apIns, char *apConvStr);
int UC_SdelChrStr (char *apInStr, char acDelChr, char *apConvStr);
int UC_SsubStr (char *apInStr, int aiFromInx, int aiLen, char *apOutStr);
int UC_SgetLeftStr (char *apInStr, int aiLength, char *apOutStr);
int UC_SgetRightStr (char *apInStr, int aiLength, char *apOutStr);
int UC_SgetIndexFindChr (char *apInStr, char acFindChr);
int UC_SgetIndexRevFindChr (char *apInStr, char acFindChr);
int UC_SgetIndexFindStr (char *apInStr, char *apFindStr);
int UC_SgetStrLen (char *apInStr);
int UC_SisDigit (char *apInStr);
int UC_SisDigitAlpha (char *apInStr);
int UC_SshiftStr (char *apInStr, int aiShiftCnt, char *apOutStr);
int UC_SisExistSpace (char *apInStr, int aiSpaceCnt);
int UC_SisExistDigit (char *apInStr, int aiDigitCnt);
int UC_SisValid16BitChar1Byte (char *apHangleStr);
int UC_SisValid16BitCharSp1Byte (char *apHangleStr);
int UC_SisValid16BitCharSp (char *apHangleStr);
int UC_SisValid16BitChar (char *apHangleStr, int aiChkFlag,
                                   int *aiStatCode, char *apStatMsg);
int UC_SisKSC5601Char (char *apInStr);
int UC_SisHangleStr (char *apInStr);
int UC_SconvHangleStr (char *apHangleStr, char *apOutStr);
int UC_SconvInvalidChar (char *apHangleStr, int *aiConvBytes, char *apOutStr);
int UC_SconvMultiToSingleStr (char *apInStr, char *apOutStr);
int UC_SconvSingleToMultiStr (unsigned char *apInStr, char *apOutStr);
int UC_SgetTimeAfterSec (char *apOutTime, int aiBufSize, int aiAfterSec );


/*******************************************************************************
*                                                                              *
*                  (c) Copyright IBM Korea Corporation 2003                    *
*                             All Rights Reserved                              *
*                                                                              *
* **************************************************************************** *
*                                                                              *
*  File name   : UC_dates.h                                                   *
*                                                                              *
*  Device      : AIX ibmit1 1 5 000BF10D4C00                                   *
*                                                                              *
*  Description : 공통util library - 날짜함수        	       *
*                                                                              *
* **************************************************************************** *
*  Change Description.                                                         *
*  --------------------------------------------------------------------------- *
*  Date       Author   Ver    Description                                      *
*  +--------- +------  +----- +----------------------------------------------- *
*  2004.08.30 IBM-KR   1.0    Initial Release                                  *
*                                                                              *
*******************************************************************************/

/* 현재 시스템 날짜,시간  형태에 필요한 정의 */
#define YYYYMMDD             0
#define HHMISS               1
#define YYYYMMDDHHMISS       2
#define YYYYMMDDHHMISSMI     3
#define MMDDHHMISS           4
#define YMDFORM1             5      /* YYYYMMDD:HH:MI:SS */
#define YMDFORM2             6      /* MM/DD/YYYY HH:MI:SS */
#define YMDFORM3             7      /* YYYYMMDD-HH:MI:SS */
#define TIMEFORM1            8      /* HH:MI:SS */
#define YYYYMMDDHHMISSMIS    9

/* 입력 날짜를 변환하는 형태에 대한 정의 */
#define ADDMINUS_DT          1      /* YYYYMMDD -> YYYY-MM-DD */
#define DELMINUS_DT          2      /* YYYY-MM-DD -> YYYYMMDD */
#define ADDSLASH_DT          3      /* YYYYMMDD -> YYYY/MM/DD */
#define DELSLASH_DT          4      /* YYYY/MM/DD -> YYYYMMDD */
#define ADDMINUSYM_DT        5      /* YYYYMMDD -> YYYY-MM */
#define ADDDOT_DT            6      /* YYYYMMDD -> YYYY.MM.DD */

/* 입력 시간을 변환하는 형태에 대한 정의 */
#define ADDCOLON_TM          1      /* HHMISS -> HH:MI:SS */

/* 일정 기간에 대한 정보 요청시 입력 구조체 */
typedef struct _dtterm dtTerm, *dtTermPtr;
struct _dtterm {
   char stdt[9];                    /* 시작일자 */
   char enddt[9];                   /* 종료일자 */
} ;

/* 일정 기간의 월별 일수에 대한 정보 구조체 */
typedef struct _dtnum dtNum, *dtNumPtr;
struct _dtnum {
   int totdds;                      /* 총 일자수 */
   int tm_mncn;                     /* 기간내 개월수 */
   int rmd_dds;                     /* 나머지 일수 */
} ;

/* 일정 기간의 월과 월별 일자수 정보 구조체 */
typedef struct _dtmon dtMon, *dtMonPtr;
struct _dtmon {
   int mno;                         /* 해당월 */
   int bymn_dds;                    /* 월별 일수 */
};

/* Function Prototype */
int UC_SgetMonthLastDayInt (int aiYear, int aiMonth, int *aiLastDay,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetMonthLastDayStr (char *apInDate, int *aiLastDay,
                                              int *aiStatCode, char *apStatMsg);
int UC_SconvFromDateStrToInt (char *apInDate, int *aiYear, int *aiMonth,
                                  int *aiDay, int *aiStatCode, char *apStatMsg);
int UC_SisLeapYear (int aiInYear);
int UC_SisValidDateInt (int aiYear, int aiMonth, int aiDay,
                                              int *aiStatCode, char *apStatMsg);
int UC_SisValidDateStr (char *apInDate, int *aiStatCode, char *apStatMsg);
int UC_SgetPrevDate (char *apInDate, char *apPrevDate,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetNextDate (char *apInDate, char *apNextDate,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetPrevNextDate (char *apInDate, char *apPrevDate, char *apNextDate,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetYearToMonthNum (char *apInDate, int aiCountNum, char *apCountDate,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetCountedMonthInt (int *aiYear, int *aiMonth, int *aiDay,
                int aiCountNum, int aiOption, int *aiStatCode, char *apStatMsg);
int UC_SgetCountedMonth (char *apInDate, int aiCountNum, int aiOption,
                         char *apCountedDate, int *aiStatCode, char *apStatMsg);
int UC_SgetCountedDate (char *apInDate, int aiCountNum, char *apCountedDate,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetLastMonthInfo (char *apInDate, char *apFirstDay, char *apLastDay,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetWeekDayInx (int aiInYear,int aiInMonth,int aiInDay,int *aiDayInx,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetWeekDayName (char *apInDate, int aiIsFullName, char *apDayName,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetTimeMilliSec (int aiMode, char *apTimeStr, char *apMilliSec,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetSysDateTime (int aiMode, char *apDateStr,
                                              int *aiStatCode, char *apStatMsg);
int UC_SconvTimeFormat (int aiMode, char *apInTime, char *apConvTime,
                                              int *aiStatCode, char *apStatMsg);
int UC_SconvDateFormat (int aiMode, char *apInDate, char *apConvDate,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetFullAge (char *apBirthDate, int *aiFullAge,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetAge (char *apBirthDate, int *aiAge,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetTimeGapSecond (char *apOneTime, char *apOtherTime, long *alTimeGap,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetPassedDay (int aiStartYear, int aiInYear, int aiInMonth,
              int aiInDay, long *alPassedDay, int *aiStatCode, char *apStatMsg);
int UC_SgetIntervalDayNumber (char *apFromDate, char *apToDate, long *alDayNum,
                                              int *aiStatCode, char *apStatMsg);
int UC_SconvFromGregToJuliDay (char *apGregDay, char *apJulianDay,
                                              int *aiStatCode, char *apStatMsg);
int UC_SconvFromJuliToGregDay (char *apJulianDay, char *apGregDay,
                                              int *aiStatCode, char *apStatMsg);
int UC_SconvFromSolarToLunar (char *apSolarDate, char *apLunarDate,
                                              int *aiStatCode, char *apStatMsg);
int UC_SconvFromLunarToSolar (char *apLunarDate, char *apSolarDate,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetMonthName (int aiInMonth, int aiIsFullName, char *apMonthName,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetWeekCntInfo (char *apInDate, int *astOut,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetDdsCntInfo (dtTermPtr astIn, dtNumPtr astOut,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetByMnCntInfo (dtTermPtr astIn, dtMon astOut[],
                                              int *aiStatCode, char *apStatMsg);


/*******************************************************************************
*                                                                              *
*                  (c) Copyright IBM Korea Corporation 2003                    *
*                             All Rights Reserved                              *
*                                                                              *
* **************************************************************************** *
*                                                                              *
*  File name   : UC_debug.h                                                   *
*                                                                              *
*  Device      : AIX ibmit1 1 5 000BF10D4C00                                   *
*                                                                              *
*  Description : 공통library - define         	       *
*                                                                              *
* *****************************************************************************/


#define MAX_PROCNAME_LEN   32
#define MAX_PATHNAME_LEN  256
#define MAX_STATMSG_LEN   512

#define CONFHOME     "CONFHOME"

/* Logging 함수 */
void UC_IsetLogFileName (char *apLogFile, char *apLogPath);
void UC_RDebugLog (char *apFunctionName, int aiLine,
                                            int aiResultCode, char *apFmt, ...);
void UC_RDebugAnyDump (char *apFunctionName, int aiLine,
                                                int aiDataLen, char *apAnyData);


/*******************************************************************************
*                                                                              *
*                  (c) Copyright IBM Korea Corporation 2003                    *
*                             All Rights Reserved                              *
*                                                                              *
* **************************************************************************** *
*                                                                              *
*  File name   : UC_etc.h                                                     *
*                                                                              *
*  Device      : AIX ibmit1 1 5 000BF10D4C00                                   *
*                                                                              *
*  Description : 공통util library - 기타함수                *
*                                                                              *
* **************************************************************************** *
*  Change Description.                                                         *
*  --------------------------------------------------------------------------- *
*  Date       Author   Ver    Description                                      *
*  +--------- +------  +----- +----------------------------------------------- *
*  2004.08.31 IBM-KR   1.0    Initial Release                                  *
*                                                                              *
*******************************************************************************/

int UC_SvrfRrNo(char *apInRrNo, int *aiStatCode, char *apStatMsg);
int UC_SvrfBsNo(char *apInBsNo, int *aiStatCode, char *apStatMsg);
int UC_SvrfCorpNo(char *apInCorpNo, int *aiStatCode, char *apStatMsg);
int UC_SconvCorpNoToBsNo (char *apCorpNo, char *apBsNo);
int UC_SconvBsNoToCorpNo (char *apBsNo, char *apCorpNo);
int UC_SvrfFrnPeNo(char *apInFrnNo, int *aiStatCode, char *apStatMsg);
int UC_SvrfFrnRegNo(char *apInFrnRegNo, int *aiStatCode, char *apStatMsg);
int UC_SgetFileSize (char *apFileName, long *alFileSize,
                                         int *aiStatCode, char *apStatMsg);
int UC_SprintMsg (char *apMsg);
int UC_SgetRandNum (int aiWidth, int aiSeed, unsigned int *adRandNum);



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


/*******************************************************************************
*                                                                              *
*                  (c) Copyright PNPC      Corporation 2004                    *
*                             All Rights Reserved                              *
*                                                                              *
* **************************************************************************** *
*                                                                              *
*  File name   : UC_apidb.h                                                   *
*                                                                              *
*  Device      : AIX ibmit1 1 5 000BF10D4C00                                   *
*                                                                              *
*  Description : 공통정보 API - DB접속을 위한 헤더파일                 	       *
*                                                                              *
* **************************************************************************** *
*  Change Description.                                                         *
*  --------------------------------------------------------------------------- *
*  Date       Author   Ver    Description                                      *
*  +--------- +------  +----- +----------------------------------------------- *
*  2004.11.22 PNPC     1.0    Initial Release                                  *
*******************************************************************************/


/* ALTIBASE DB 접속 방식 */
#define RANDOM_ACCESS         1   /* 임의접근 */
#define ORDERBY_ACCESS        2    /* 순서대로 접근 */

/* ALTIBASE DB 접속 기본 값 정의 */
#define DB_SERVERCNT          2         /* MMDB 서버 개수 */
#define DB_ACCESSTYPE         "RANDOM"  /* MMDB 서버 접근방식 (random/order) */

/* ALTIBASE DB 접속 계정 */
#define DB_USERID             "conf_sel"
#define DB_PASSWD             "conf_sel"

/* MMDB 접속을 위한 환경변수 명 */
#define ALTIBASE_SVRCNT       "CONFDB_SVRCNT"     /* 서버 개수 */
#define ALTIBASE_CONNTYPE     "CONFDB_ACCESSTYPE" /* 서버 접근방식 */

/*
  MMDB 접속을 위한 서버별 환경변수 명
- 접근IP   : CONFDB#n_IPADDR
- 접근Port : CONFDB#n_PORTNO
*/

typedef struct _dbinfo {
   char ipaddr[64];
   char portno[8];
} dbinfo, *dbinfoPtr;


/*******************************************************************************
*                                                                              *
*                  (c) Copyright PNPC      Corporation 2004                    *
*                             All Rights Reserved                              *
*                                                                              *
* **************************************************************************** *
*                                                                              *
*  File name   : UC_apistruct.h                                               *
*                                                                              *
*  Device      : AIX ibmit1 1 5 000BF10D4C00                                   *
*                                                                              *
*  Description : 공통정보 API - 공통정의 api 구조체정의 파일           	       *
*                                                                              *
* **************************************************************************** *
*  Change Description.                                                         *
*  --------------------------------------------------------------------------- *
*  Date       Author   Ver    Description                                      *
*  +--------- +------  +----- +----------------------------------------------- *
*  2004.10.06 PNPC     1.0    Initial Release                                  *
*******************************************************************************/


/* 일자정보 요청시 입력 구조체 */
typedef struct _dtinfo dtInfo, *dtInfoPtr;
struct _dtinfo {
   int discd;                            /* 구분코드 */
   int tm;                               /* 계산 기간(+,-) */
   char inpdt[DT_LEN+1];                 /* 입력일자 */
} ;

/* 영업일 일수 산출시 입력 구조체 */
typedef struct _cntin cntIn, *cntInPtr;
struct _cntin {
   int discd;                            /* 구분코드 */
   char stdt[DT_LEN+1];                  /* 시작일자 */
   char enddt[DT_LEN+1];                 /* 종료일자 */
} ;

/* 영업일 일수 산출시 출력 구조체 */
typedef struct _cntout cntOut, *cntOutPtr;
struct _cntout {
   int bizdt;                            /* 영업일수 */
   int hldydt;                           /* 휴일수 */
   int total;                            /* 전체일수*/
} ;

/* 자금화시간 출력 구조체 */
typedef struct _captiz captIz, *captIzPtr;
struct _captiz {
   char crt_dt[DT_LEN+1];                /* 생성일자 */
   char at_capt_iz_tm1[TM_LEN+1];        /* 평일자동자금화시각 */
   char at_capt_iz_tm2[TM_LEN+1];        /* 토요자동자금화시각 */
} ;

/* 연장시각 구조체 */
typedef struct _xtntm xtnTm, *xtnTmPtr;
struct _xtntm {
   char cd[YNFLAG_LEN+1];                /* 기준코드 */
   char dis_c;                           /* 연장구분코드 */
   char xtn_tm[TM_LEN+1];                /* 연장시각 */
} ;

/* 연장시각 출력 구조체 */
typedef struct _xtnout xtn, *xtnPtr;
struct _xtnout {
   char crt_dt[DT_LEN+1];                /* 생성일자 */
   int srch_cnt;                         /* 검색수 */
   xtnTm astXtn[MAX_XTNCNT];             /* 연장시각 구조체 */
};

/* 기준일자일테이블 요청시 입력 구조체 */
typedef struct _bscdtin bscdtIn;
struct _bscdtin {
   char crt_dt[DT_LEN+1];                /* 생성일자 */
   int dis_c;                            /* 구분코드 */
} ;

/* 기준일자일테이블 요청시 출력 구조체 */
typedef struct _bscdtout bscdt, *bscdtPtr;
struct _bscdtout {
   char crt_dt[DT_LEN+1];                /* 생성일자 */
   char dt_dis_c;                        /* 일자구분코드         */
   char nd5_dt[DT_LEN+1];                /* 5익일일자            */
   int  nd5_ned_dds;                     /* 5익일소요일수        */
   char nd5_dow_c;                       /* 5익일요일코드        */
   char nd5_dow_eabr_nm[EABR_NM_LEN+1];  /* 5익일요일영문약어명  */
   char nd5_hldy_dis_c;                  /* 5익일휴일구분코드    */
   char nd4_dt[DT_LEN+1];                /* 4익일일자            */
   int  nd4_ned_dds;                     /* 4익일소요일수        */
   char nd4_dow_c;                       /* 4익일요일코드        */
   char nd4_dow_eabr_nm[EABR_NM_LEN+1];  /* 4익일요일영문약어명  */
   char nd4_hldy_dis_c;                  /* 4익일휴일구분코드    */
   char nd3_dt[DT_LEN+1];                /* 3익일일자            */
   int  nd3_ned_dds;                     /* 3익일소요일수        */
   char nd3_dow_c;                       /* 3익일요일코드        */
   char nd3_dow_eabr_nm[EABR_NM_LEN+1];  /* 3익일요일영문약어명  */
   char nd3_hldy_dis_c;                  /* 3익일휴일구분코드    */
   char nd2_dt[DT_LEN+1];                /* 2익일일자            */
   int  nd2_ned_dds;                     /* 2익일소요일수        */
   char nd2_dow_c;                       /* 2익일요일코드        */
   char nd2_dow_eabr_nm[EABR_NM_LEN+1];  /* 2익일요일영문약어명  */
   char nd2_hldy_dis_c;                  /* 2익일휴일구분코드    */
   char nd_dt[DT_LEN+1];                 /* 1익일일자            */
   int  nd_ned_dds;                      /* 1익일소요일수        */
   char nd_dow_c;                        /* 1익일요일코드        */
   char nd_dow_eabr_nm[EABR_NM_LEN+1];   /* 1익일요일영문약어명  */
   char nd_hldy_dis_c;                   /* 1익일휴일구분코드    */
   char td_dt[DT_LEN+1];                 /* 당일일자             */
   int  td_ned_dds;                      /* 당일소요일수         */
   char td_dow_c;                        /* 당일요일코드         */
   char td_dow_eabr_nm[EABR_NM_LEN+1];   /* 당일일요일영문약어명 */
   char td_hldy_dis_c;                   /* 당일휴일구분코드     */
   char td_ldd_dis_c;                    /* 당일말일구분코드     */
   char bd_dt[DT_LEN+1];                 /* 1전일일자            */
   int  bd_ned_dds;                      /* 1전일소요일수        */
   char bd_dow_c;                        /* 1전일요일코드        */
   char bd_dow_eabr_nm[EABR_NM_LEN+1];   /* 1전일요일영문약어명  */
   char bd_hldy_dis_c;                   /* 1전일휴일구분코드    */
   char bd2_dt[DT_LEN+1];                /* 2전일일자            */
   int  bd2_ned_dds;                     /* 2전일소요일수        */
   char bd2_dow_c;                       /* 2전일요일코드        */
   char bd2_dow_eabr_nm[EABR_NM_LEN+1];  /* 2전일요일영문약어명  */
   char bd2_hldy_dis_c;                  /* 2전일휴일구분코드    */
   char bd3_dt[DT_LEN+1];                /* 3전일일자            */
   int  bd3_ned_dds;                     /* 3전일소요일수        */
   char bd3_dow_c;                       /* 3전일요일코드        */
   char bd3_dow_eabr_nm[EABR_NM_LEN+1];  /* 3전일요일영문약어명  */
   char bd3_hldy_dis_c;                  /* 3전일휴일구분코드    */
   char bd4_dt[DT_LEN+1];                /* 4전일일자            */
   int  bd4_ned_dds;                     /* 4전일소요일수        */
   char bd4_dow_c;                       /* 4전일요일코드        */
   char bd4_dow_eabr_nm[EABR_NM_LEN+1];  /* 4전일요일영문약어명  */
   char bd4_hldy_dis_c;                  /* 4전일휴일구분코드    */
   char bd5_dt[DT_LEN+1];                /* 5전일일자            */
   int  bd5_ned_dds;                     /* 5전일소요일수        */
   char bd5_dow_c;                       /* 5전일요일코드        */
   char bd5_dow_eabr_nm[EABR_NM_LEN+1];  /* 5전일요일영문약어명  */
   char bd5_hldy_dis_c;                  /* 5전일휴일구분코드    */
   char bd6_dt[DT_LEN+1];                /* 6전일일자            */
   int  bd6_ned_dds;                     /* 6전일소요일수        */
   char bd6_dow_c;                       /* 6전일요일코드        */
   char bd6_dow_eabr_nm[EABR_NM_LEN+1];  /* 6전일요일영문약어명  */
   char bd6_hldy_dis_c;                  /* 6전일휴일구분코드    */
   char bd7_dt[DT_LEN+1];                /* 7전일일자            */
   int  bd7_ned_dds;                     /* 7전일소요일수        */
   char bd7_dow_c;                       /* 7전일요일코드        */
   char bd7_dow_eabr_nm[EABR_NM_LEN+1];  /* 7전일요일영문약어명  */
   char bd7_hldy_dis_c;                  /* 7전일휴일구분코드    */
   char bd8_dt[DT_LEN+1];                /* 8전일일자            */
   int  bd8_ned_dds;                     /* 8전일소요일수        */
   char bd8_dow_c;                       /* 8전일요일코드        */
   char bd8_dow_eabr_nm[EABR_NM_LEN+1];  /* 8전일요일영문약어명  */
   char bd8_hldy_dis_c;                  /* 8전일휴일구분코드    */
   char bd9_dt[DT_LEN+1];                /* 9전일일자            */
   int  bd9_ned_dds;                     /* 9전일소요일수        */
   char bd9_dow_c;                       /* 9전일요일코드        */
   char bd9_dow_eabr_nm[EABR_NM_LEN+1];  /* 9전일요일영문약어명  */
   char bd9_hldy_dis_c;                  /* 9전일휴일구분코드    */
   char bd10_dt[DT_LEN+1];               /* 10전일일자           */
   int  bd10_ned_dds;                    /* 10전일소요일수       */
   char bd10_dow_c;                      /* 10전일요일코드       */
   char bd10_dow_eabr_nm[EABR_NM_LEN+1]; /* 10전일요일영문약어명 */
   char bd10_hldy_dis_c;                 /* 10전일휴일구분코드   */
   char bd11_dt[DT_LEN+1];               /* 11전일일자           */
   int  bd11_ned_dds;                    /* 11전일소요일수       */
   char bd11_dow_c;                      /* 11전일요일코드       */
   char bd11_dow_eabr_nm[EABR_NM_LEN+1]; /* 11전일요일영문약어명 */
   char bd11_hldy_dis_c;                 /* 11전일휴일구분코드   */
   char bd12_dt[DT_LEN+1];               /* 12전일일자           */
   int  bd12_ned_dds;                    /* 12전일소요일수       */
   char bd12_dow_c;                      /* 12전일요일코드       */
   char bd12_dow_eabr_nm[EABR_NM_LEN+1]; /* 12전일요일영문약어명 */
   char bd12_hldy_dis_c;                 /* 12전일휴일구분코드   */
   char bd13_dt[DT_LEN+1];               /* 13전일일자           */
   int  bd13_ned_dds;                    /* 13전일소요일수       */
   char bd13_dow_c;                      /* 13전일요일코드       */
   char bd13_dow_eabr_nm[EABR_NM_LEN+1]; /* 13전일요일영문약어명 */
   char bd13_hldy_dis_c;                 /* 13전일휴일구분코드   */
   char bd14_dt[DT_LEN+1];               /* 14전일일자           */
   int  bd14_ned_dds;                    /* 14전일소요일수       */
   char bd14_dow_c;                      /* 14전일요일코드       */
   char bd14_dow_eabr_nm[EABR_NM_LEN+1]; /* 14전일요일영문약어명 */
   char bd14_hldy_dis_c;                 /* 14전일휴일구분코드   */
   char bd15_dt[DT_LEN+1];               /* 15전일일자           */
   int  bd15_ned_dds;                    /* 15전일소요일수       */
   char bd15_dow_c;                      /* 15전일요일코드       */
   char bd15_dow_eabr_nm[EABR_NM_LEN+1]; /* 15전일요일영문약어명 */
   char bd15_hldy_dis_c;                 /* 15전일휴일구분코드   */
} ;

/* 기준일자기타일테이블 요청시 출력 구조체 */
typedef struct _bscdtetc bscdtEtc, *bscdtEtcPtr;
struct _bscdtetc {
   char crt_dt[DT_LEN+1];                /* 생성일자                     */
   char aco_isu_fexmp_yn[YNFLAG_LEN+1];  /* 조합발행수수료면제여부       */
   char aco_isu_fexmp_st_dt[DT_LEN+1];   /* 조합발행수수료면제종료일자   */
   char aco_isu_fexmp_end_dt[DT_LEN+1];  /* 조합발행수수료면제여부       */
   char naf_isu_fexmp_yn[YNFLAG_LEN+1];  /* 중앙회발행수수료면제여부     */
   char naf_isu_fexmp_st_dt[DT_LEN+1];   /* 중앙회발행수수료면제종료일자 */
   char naf_isu_fexmp_end_dt[DT_LEN+1];  /* 중앙회발행수수료면제여부     */
   int  pb_reisu_fee;                    /* 통장재발행수수료             */
   int  blcf_isu_fee;                    /* 잔액증명서발급수수료         */
   int  blcf_add_isu_fee;                /* 잔액증명서추가발급수수료     */
   int  here_fee;                        /* 당지수수료                   */
   char hanaro_acd_reg_yn;               /* 하나로사고등록여부           */
   char hldy_afts_cmpl_yn;               /* 휴일자동이체작업여부         */
   char sys_sts_c;                       /* 시스템상황코드               */
   char acc_1m_frst_biz_dt[DT_LEN+1];    /* 계리1월처음영업일자          */
   char acc_6m_lst_biz_dt[DT_LEN+1];     /* 계리6월마지막영업일자        */
   char acc_7m_frst_biz_dt[DT_LEN+1];    /* 계리7월처음영업일자          */
   char acc_12m_lst_biz_dt[DT_LEN+1];    /* 계리12월마지막영업일자       */
   char capt_iz_td_dt[DT_LEN+1];         /* 자금화당일자                 */
   char capt_iz_bd_dt[DT_LEN+1];         /* 자금화전일자                 */
} ;

/* 기산일 검증 요청시 입력 구조체 */
typedef struct _dtvalid dtValid, *dtValidPtr;
struct _dtvalid {
   int clsyn;                            /* 마감 여부 */
   int hldy_yn;                          /* 금융휴무 처리여부 */
   char brcd[BR_C_LEN+1];                /* 사무소코드 */
   char sbjcd[SBJ_C_LEN+1];              /* 과목코드 */
   char mgrid[IDCD_LEN+1];               /* 책임자 ID */
   char optrid[IDCD_LEN+1];              /* 조작자 ID */
   char rckdt[DT_LEN+1];                 /* 기산일 */
} ;

/* 일자정보 요청에 대한 출력 구조체 */
typedef struct _dtbasic dtBasic, *dtBasicPtr;
struct _dtbasic {
   int dowcd;                            /* 요일코드 */
   int leapyn;                           /* 윤년 여부 : 0/1 */
   int hldyyn;                           /* 휴일 여부 : 0/1/2 */
   int bfned_dds;                        /* 전 영업 소요일수 */
   int afned_dds;                        /* 익 영업 소요일수 */
   char basdt[DT_LEN+1];                 /* 기준일 */
   char bfdt[DT_LEN+1];                  /* 기준일의 전일 */
   char afdt[DT_LEN+1];                  /* 기준일의 익일 */
   char bf1bzdt[DT_LEN+1];               /* 전영업일 */
   char af1bzdt[DT_LEN+1];               /* 익영업일 */
} ;

/* 농협 계좌 정보 구조체 */
typedef struct _acct nafacct, *nafacctPtr;
struct _acct {
   char brcd [BR_C_LEN +1];              /* 사무소코드 */
   char sbjcd[SBJ_C_LEN+1];              /* 과목코드 */
   char seqno[ACCT_SEQNO_LEN+1];         /* 일련번호 */
};

/* 사무소 정보 구조체 */
typedef struct _brc brc, *brcPtr;
struct _brc {
   char onl_c[BR_C_LEN+1];               /* 온라인 코드 */
   char giro_c[GIRO_C_LEN+1];            /* 지로코드 */
   char nafaco_c[NAFACO_DIS_LEN+1];      /* 중조구분코드 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char brnm_chg_dt[DT_LEN+1];           /* 사무소명 변경일자 */
   char brnm_chg_psno[PSNO_LEN+1];       /* 사무소명 변경 개인번호 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char org_form[ORG_FORM_LEN+1];        /* 조직형태 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
   char cus_tel[TEL_LEN+1];              /* 고객용 전화 */
   char emp_tel[TEL_LEN+1];              /* 직원용 전화 */
   char xuse_tel[XUSE_TEL_LEN+1];        /* 전용 전화 */
   char rep_fax[TEL_LEN+1];              /* 대표 FAX */
   char crdt_fax[TEL_LEN+1];             /* 신용 FAX */
   char rbno[RBNO_LEN+1];                /* 사업자 등록번호 */
   char genmgr_nm[GENMGR_NM_LEN+1];      /* 사무소장명 */
   char eng_brnm[BR_ENM_LEN+1];          /* 영문 사무소명 */
   char addr[BR_ADDR_LEN+1];             /* 주소 */
   char addr2[BLW_ADDR_LEN+1];           /* 읍면동 이하 주소 */
   char postno[POSTNO_LEN+1];            /* 우편번호 */
   char redc_bil_mo_br_c[BR_C_LEN+1];    /* 재할인어음 모점 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관 구분 */
   char rcv_br_c[BR_C_LEN+1];            /* 수관사무소코드 */
   char rcv_onl_c[BR_C_LEN+1];           /* 수관온라인코드 */
   char fx_c[FX_C_LEN+1];                /* 외환코드 */
   char fx_mo_br_c[BR_C_LEN+1];          /* 외환 모점코드 */
   char fx_type[FX_TP_C_LEN+1];          /* 외환 type */
   char mo_br_c[BR_C_LEN+1];             /* 모점사무소코드 */
   char mo_br_onl_c[BR_C_LEN+1];         /* 모점 온라인 */
   char nlf_onl_c[BR_C_LEN+1];           /* 구축협 온라인 코드 */
   char br_loc_inf[BR_LOCINF_LEN+1];     /* 사무소 위치정보 */
   char opn_dt[DT_LEN+1];                /* 신규일 */
   char cls_dt[DT_LEN+1];                /* 폐쇄일 */
   char acc_cls_dt[DT_LEN+1];            /* 계정폐쇄일 */
   char lst_chg_dt[DT_LEN+1];            /* 사무소정보 최종변경일 */
   char clrhs_c[CLRHS_C_LEN+1];          /* 교환소 코드 */
   char clrhs_idx[CLRHS_IDX_LEN+1];      /* 교환 idx */
   char net1[CLRHS_C_LEN+1];             /* 관내교환소 코드 */
   char net2[CLRHS_C_LEN+1];             /* 상호교환소 코드 */
   char aud_mphon[TEL_LEN+1];            /* 감사 휴대폰 */
   char aud_mphon_chg_psno[PSNO_LEN+1];  /* 감사 휴대폰 변경 개인번호 */
   char chk_fee_yn[YNFLAG_LEN+1];        /* 수표발행 수수료 면제여부 */
   char coff_c[COFF_ONLC_LEN+1];         /* 시군지부 코드 */
   char loc_tp[LOC_TP_C_LEN+1];          /* 입지유형 */
   char dvlp_tp_c[DVLP_TP_LEN+1];        /* 발전형태 코드 */
   char rgn_form_c[RGN_FORM_LEN+1];      /* 지역형태 코드 */
   char aco_dis[ACO_DIS_C_LEN+1];        /* 조합구분 */
   char lntrt_avl_yn[YNFLAG_LEN+1];      /* 여신취급 가능여부 */
   char biz_stp_yn[YNFLAG_LEN+1];        /* 업무정지 여부 */
};

/* 사무소정보 기타 COUNT 정보 구조체 */
typedef struct _brcnt brcnt, *brcntPtr;
struct _brcnt {
   int  dist1_cnt;                       /* 직하위 사무소수 */
   int  dist2_cnt;                       /* 관할 사무소수 */
   int  rcvin_cnt;                       /* 수관 사무소수(폐쇄점) */
   int  mrg_cnt;                         /* 합병 사무소수 */
} ;

/* 온라인코드를 이용한 사무소 조회 결과 구조체 */
typedef struct _onbr onbr, *onbrPtr;
struct _onbr {
   char hwan_c[BR_C_LEN+1];              /* 환코드 */
   char giro_c[BR_C_LEN+1];              /* 지로코드 */
   char nafaco_dis_c[NAFACO_DIS_LEN+1];  /* 중조구분 */
   char org_frm_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관구분 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
};

/* 환코드를 이용한 사무소 조회 결과 구조체 */
typedef struct _hwbr hwbr, *hwbrPtr;
struct _hwbr {
   char onl_c[BR_C_LEN+1];               /* 온라인코드 */
   char giro_c[BR_C_LEN+1];              /* 지로코드 */
   char nafaco_dis_c[NAFACO_DIS_LEN+1];  /* 중조구분 */
   char org_frm_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관구분 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
};

/* 지로코드를 이용한 사무소 조회 결과 구조체 */
typedef struct _girobr girobr, *girobrPtr;
struct _girobr {
   char onl_c[BR_C_LEN+1];               /* 온라인코드 */
   char hwan_c[BR_C_LEN+1];              /* 환코드 */
   char nafaco_dis_c[NAFACO_DIS_LEN+1];  /* 중조구분 */
   char org_frm_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관구분 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
};

/* 사무소코드를 이용한 모점 조회 결과 구조체 */
typedef struct _mobr mobr, *mobrPtr;
struct _mobr {
   char br_c[BR_C_LEN+1];                /* 사무소코드 */
   char onl_c[BR_C_LEN+1];               /* 온라인코드 */
   char giro_c[BR_C_LEN+1];              /* 지로코드 */
   char nafaco_dis_c[NAFACO_DIS_LEN+1];  /* 중조구분 */
   char org_frm_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관구분 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
};

/* 사무소명을 이용한 조회 결과 구조체 */
typedef struct _brnm brname, *brnmPtr;
struct _brnm {
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char nafaco_dis_c[NAFACO_DIS_LEN+1];  /* 중조구분 */
   char br_c[BR_C_LEN+1];                /* 사무소코드 */
   char onl_c[BR_C_LEN+1];               /* 온라인코드 */
   char giro_c[GIRO_C_LEN+1];            /* 지로코드 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
   char emp_tel[TEL_LEN+1];              /* 직원용 전화 */
};

/* 시군지부 관할 조합 사무소정보 */
typedef struct _coffhdr coffhdr, *coffhdrPtr;
struct _coffhdr {
   int  jurdbr_cnt;                      /* 관할사무소수 */
   int  jurdhoff_cnt;                    /* 관할 본부수 */
   int  jurdhdrbr_cnt;                   /* 관할 본소수 */
   int  jurdsubbr_cnt;                   /* 관할 지소수 */
   int  jurdclsbr_cnt;                   /* 관할 폐쇄점 수 */
   char coff_c[COFF_ONLC_LEN+1];         /* 시군지부코드 */
   char coff_nm[BRNM_LEN+1];             /* 시군지부 명 */
} ;

/* 조합 사무소 정보 */
typedef struct _jurdbr jurdbr, *jurdbrPtr;
struct _jurdbr {
   int  jurdbr_cnt;                      /* 관할 사무소수 */
   char br_c[BR_C_LEN+1];                /* 사무소코드 */
   char onl_c[BR_C_LEN+1];               /* 온라인코드 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
   char orgform_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관 구분 */
};

/* 시도코드별 사무소 정보조회 헤더 */
typedef struct _provhdr provhdr, *provhdrPtr;
struct _provhdr {
   int  br_cnt;                          /* 사무소 수 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
   char prov_nm[PROV_NM_LEN+1];           /* 시도명 */
} ;

/* 시도코드별 사무소 정보조회 데이터 */
typedef struct _provc provbr, *provbrPtr;
struct _provc {
   char br_c[BR_C_LEN+1];                /* 사무소코드 */
   char onl_c[BR_C_LEN+1];               /* 온라인 코드 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char orgform_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관 구분 */
   char coff_c[COFF_ONLC_LEN+1];         /* 시군지부코드 */
} ;

/* 수관점 정보 */
typedef struct _rcvinf rcvinf;
struct _rcvinf {
   char br_c[BR_C_LEN+1];                /* 폐쇄사무소 코드 */
   char cls_dt[DT_LEN+1];                /* 폐쇄일자 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관 구분 */
} ;

/* 하위정보 */
typedef struct _distbr {
   char br_c[BR_C_LEN+1];                /* 관할 사무소코드 */
   char orgform_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관 구분 */
} distinf;

/* 합병 정보 */
typedef struct _mrginf {
   char ohbr_c[BR_C_LEN+1];              /* 구본소 사무소코드 */
   char mrg_dt[DT_LEN+1];                /* 합병 일자 */
   char orgform_c[ORG_FORM_LEN+1];       /* 구 조직형태 */
} mrginf ;

/* 업무정지 정보 */
typedef struct _stpinf {
   char ohbr_c[BR_C_LEN+1];              /* 구본소 사무소코드 */
   char stp_dt[DT_LEN+1];                /* 업무정지 일자 */
   char ctrmv_dt[DT_LEN+1];              /* 계약이전 일자 */
   char orgform_c[ORG_FORM_LEN+1];       /* 구 조직형태 */
} stpinf, *stpinfPtr ;

/* 우편번호, 주소 정보 */
typedef struct _pinf {
   char postno[POSTNO_LEN+1];            /* 우편번호 */
   int  seqno;
   char addr[ADDR_LEN+1];                /* 주소 */
} postaddr;

/* 우편번호 입력 정보 */
typedef struct _postin {
   int  addrmode;                        /* 한글,영문주소 선택 */
   char postno[POSTNO_LEN+1];            /* 우편번호 */
   int  seqno;
   char inaddr[INADDR_LEN+1];            /* 입력 주소 */
} postin, *postPtr;

/* 우편번호 입력시 주소 출력 정보 */
typedef struct _postout {
   int  seqno;
   char addr[ADDR_LEN+1];                /* 주소 */
} postnoaddr;

/* 통합계정수관점 사무소정보 */
typedef struct _itginf {
   char br_c[BR_C_LEN+1];                /* 사무소코드 */
   char onl_c[BR_C_LEN+1];               /* 온라인 코드 */
   char giro_c[GIRO_C_LEN+1];            /* 지로코드 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
   char orgform_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관 구분 */
   char rcvin_br_c[BR_C_LEN+1];          /* 수관사무소코드 */
} itginf;

/* 축협 사무소 정보 및 이수관점 정보 */
typedef struct _nlfinf nlfinf, *nlfinfPtr;
struct _nlfinf {
   char br_c[BR_C_LEN+1];                /* 축협사무소코드 */
   char giro_c[GIRO_C_LEN+1];            /* 축협 지로코드 */
   char brnm[BRNM_LEN+1];                /* 축협사무소명 */
   char prov_c[PROV_C_LEN+1];            /* 축협시도코드 */
   char orgform_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char opn_dt[DT_LEN+1];                /* 축협 개점일 */
   char cls_dt[DT_LEN+1];                /* 축협 폐점일 */
   char cls_dis_c[CLS_DIS_LEN+1];        /* 폐쇄구분 */
   char nlf_rcvin[BR_C_LEN+1];           /* 축협수관점 코드 */
   char naf_rcvin[BR_C_LEN+1];           /* 농협수관점 코드 */
   char itg_rcvin[BR_C_LEN+1];           /* 통합계정 수관점코드 */
   struct _itginf itginf;                /* 통합사무점 정보 */
} ;

/* ID 카드 정보 */
typedef struct _idlist {
   int id_knd;                           /* ID카드 취급자 구분 */
   char idno[IDCD_LEN+1];                /* ID 카드번호 */
   char reg_name[REGNM_LEN+1];           /* 등록자 명 */
} idcd_inf;

/* ID 카드 검증 입력정보 */
typedef struct _idcd {
   int  trm_knd;                         /* 단말기 종류 */
   char brcd[BR_C_LEN+1];                /* 사무소 코드 */
   char optr_idcd[IDCD_LEN+1];           /* 조작자 ID카드 */
   char mgr_idcd[IDCD_LEN+1];            /* 책임자 ID카드 */
} idcdVrf, *idcdVrfPtr;

/* ID 카드 검증 출력정보 */
typedef struct _emp empinf, *empInfPtr;
struct _emp {
   char optr_idcd[IDCD_LEN+1];           /* 조작자 ID카드 */
   char mgr_idcd[IDCD_LEN+1];            /* 책임자 ID카드 */
   char optr_nm[REGNM_LEN+1];            /* 조작자 성명 */
   char mgr_nm[REGNM_LEN+1];             /* 책임자 성명 */
   char optr_psno[PSNO_LEN+1];           /* 조작자 개인번호 */
   char mgr_psno[PSNO_LEN+1];            /* 책임자 개인번호 */
   char nslip_useyn[NSLIP_USE_YN_LEN+1]; /* 무전표 사용여부 */
} ;

/* 점정보 요청 정보 */
typedef struct _ininf {
   char trnbiz_dis[TRNDIS_LEN+1];        /* 거래업무구분 */
   char trnftrn_dis;                     /* 거래이체구분 */
   char hldy_dis;                        /* 거래휴일구분 */
   char trbr_c[BR_C_LEN+1];              /* 취급점 */
   char trm_no[TRMNO_LEN+1];             /* 취급단말기번 */
   char acctno[ACCTNO_LEN+1];            /* 계좌번호 */
   char acd_cnf_xcp;                     /* 하나로사고체크 제외 */
   char bizstp_cnf_xcp;                  /* 업무정지 체크 제외 */
   char aclstrn_imp;                     /* HTH 마감후 거래불가 */
   char acls_key;                        /* 마감후 키 */
   char svr_rollback;                    /* 서버 rollback */
   char xcftrn_cmpl;                     /* 환처리완료 Bit */
} ininf;

typedef struct _clsinf {
   char cls_br_c[BR_C_LEN+1];            /* 폐쇄점 코드 */
   char trre_dis_c[TRRE_DISC_LEN+1];     /* 이수관 코드 */
} clsinf;

/* 취급점/계좌점 정보 */
typedef struct _vbr {
   char br_c[BR_C_LEN+1];                /* 사무소코드 */
   char onl_c[BR_C_LEN+1];               /* 온라인코드 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char nafaco_dis_c[NAFACO_DIS_LEN+1];  /* 중조구분 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char orgform_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관 구분 */
   char rcv_br_c[BR_C_LEN+1];            /* 수관점 */
   char tel_no[TEL_LEN+1];               /* 전화번호 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
   char aco_dis[ACO_DIS_C_LEN+1];        /* 조합구분 코드 */
   char lntrt_imp_yn[YNFLAG_LEN];        /* 여신취급불가 여부 */
   char giro_c[GIRO_C_LEN+1];            /* 지로코드 */
   char chk_fee_yn[YNFLAG_LEN];          /* 수표발행 수수료 bit */
   char nlf_onl_c[BR_C_LEN+1];           /* 구축협 온라인 코드 */
   char mo_br_c[BR_C_LEN+1];             /* 모점 코드 */
   char bizstp_yn[YNFLAG_LEN];           /* 업무정지 bit */
   char fx_c[FX_C_LEN+1];                /* 외환코드 */
   char fx_mo_br_c[BR_C_LEN+1];          /* 외환 모점코드 */
   char fx_type[FX_TP_C_LEN+1];          /* 외환 type */
   char clrhs_c[CLRHS_C_LEN+1];          /* 교환소 코드 */
   char clrhs_idx[CLRHS_IDX_LEN+1];      /* 교환 idx */
   char net1[CLRHS_C_LEN+1];             /* 관내교환소 코드 */
   char net2[CLRHS_C_LEN+1];             /* 상호교환소 코드 */
   int  mrg_cnt;                         /* 합병 건수 */
   char dtch_trm_knd[TRMKND_LEN+1];      /* 파출단말 종류코드 */
   char rnt_br_c[BR_C_LEN+1];            /* 타소등록점 */
   int  clsbr_cnt;                       /* 폐점 수 */
   clsinf clsInf[MAX_CLSBR_CNT];         /* 폐쇄점 정보 */
   char acccls_yn;                       /* 계리마감 여부 */
} vbr;

/* 점정보 결과 정보 */
typedef struct _vrfinf vrfinf, *vrfinfPtr;
struct _vrfinf {
   char trn_dis[TRNDIS_LEN+1];           /* 거래구분 */
   char capt_iz_dt[DT_LEN+1];            /* 자금화 일 */
   char opn_dt[DT_LEN+1];                /* 개국일 */
   vbr  tr_brinf;                        /* 취급점 정보 */
   vbr  acct_brinf;                      /* 계좌점 정보 */
} ;

/* 구축/삼협 계좌의 이관계좌 정보 */
typedef struct _acctinf acctinf, *acctinfPtr;
struct _acctinf {
   char nlf_acct_no[ACCTNO_LEN+1];       /* 구축협 계좌번호 */
   char acct_no[ACCTNO_LEN+1];           /* 계좌번호 */
   char rrno_dis_c[TRNDIS_LEN+1];        /* 실명 구분 */
   char rrno[RRNO_LEN+1];                /* 실명번호 */
   char gus_nm[GUSNM_LEN+1];             /* 예금주명 */
   char opn_dt[DT_LEN+1];                /* 신규일 */
   char cls_yn[YNFLAG_LEN+1];            /* 해지여부 */
   char hanaro_yn[YNFLAG_LEN];           /* 하나로 여부 */
} ;

/* DB handle function prototype */
int UC_SmmdbConnect (int *aiStatCode, char *apStatMsg);
int UC_SmmdbDisconn (int *aiStatCode, char *apStatMsg);
int UC_SmmdbChkError (int *aiStatCode, char *apStatMsg);

/* 일자 함수 ProtoType */
int UC_SisHoliday (char *apSvcNm, char *apInDate,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetTrnDtInfo (char *apSvcNm, dtInfoPtr astIn, dtBasicPtr astOut,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetBzDtInfo (char *apSvcNm, dtInfoPtr astIn, dtBasicPtr astOut,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetDowDtInfo (char *apSvcNm, dtInfoPtr astIn, dtBasicPtr astOut,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetBzDtCntInfo (char *apSvcNm, cntInPtr astIn, cntOutPtr astOut,
                                              int *aiStatCode, char *apStatMsg);
int UC_SvldRckDtInfo (char *apSvcNm, dtValidPtr astIn,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetBscDtInfo (char *apSvcNm, int iDisC, bscdtPtr astBizDt,
                 bscdtPtr astTrnDt, bscdtPtr astHbizDt, bscdtEtcPtr astBscDtEtc,
                                              int *aiStatCode, char *apStatMsg);
int UC_RgetCaptIzInfo (char *apSvcNm, captIzPtr astCaptIz,
                                              int *aiStatCode, char *apStatMsg);
int UC_RgetExtensionInfo (char *apSvcNm, int aiMode, xtnPtr astXtn,
                                              int *aiStatCode, char *apStatMsg);

/* 사무소 정보 조회 Prototype */
int UC_SconvHwanCToOtherC (char *apFileNm, char *apHwanC, hwbrPtr astBrInf,
                                              int *aiStatCode, char *apStatMsg);
int UC_SconvOnlCToOtherC (char *apSvcNm, char *apOnlC, onbrPtr astBrInf,
                                              int *aiStatCode, char *apStatMsg);
int UC_SconvGiroCToOtherC (char *apSvcNm, char *apGiroC, girobrPtr astBrInf,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetBrCToMoBrC (char *apSvcNm, char *apBrC, int aiLevel, int *aiSrchCnt,
                  mobr astBrInf[MAX_MOBRCNT], int *aiStatCode, char *apStatMsg);
int UC_SgetBrInfByBrNm (char *apSvcNm, char *apBrNm, int *aiSrchCnt,
                  brname astBrInf[MAX_BRCNT], int *aiStatCode, char *apStatMsg);
int UC_SgetBrInfByBrC (char *apSvcNm, char *apBrC, brcPtr astBrInf,
                             brcntPtr astBrCnt, distinf astDistInf1[MAX_BRLIST],
                  distinf astDistInf2[MAX_BRLIST], rcvinf astRcvInf[MAX_BRLIST],
                              mrginf astMrgInf[MAX_BRLIST], stpinfPtr astStpInf,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetBrInfByCoffC (char *apSvcNm, char *apCoffC, coffhdr *astHdrInf,
                  jurdbr astBrInf[MAX_BRCNT], int *aiStatCode, char *apStatMsg);
int UC_SgetBrInfByProvC (char *apSvcNm, int aiSortMode, char *apProvC,
                                 provhdr *astHdrInf, provbr astBrInf[MAX_BRCNT],
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetNlfBrInf (char *apSvcNm, char *apBrC, nlfinf *astNlfBrInf,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetRcvinInfByBrC (char *apSvcNm, char *apBrC, int *aiSrchCnt,
                 rcvinf astBrInf[MAX_BRLIST], int *aiStatCode, char *apStatMsg);
int UC_SgetMrgInfOfAco (char *apSvcNm, char *apBrC, int *aiSrchCnt,
                 mrginf astBrInf[MAX_BRLIST], int *aiStatCode, char *apStatMsg);
int UC_SgetBizStpInfOfAco (char *apSvcNm, char *apBrC, stpinfPtr astBrInf,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetDistBrByBrC (char *apSvcNm, char *apBrC, int aiLevel,
                                   int *aiSrchCnt, distinf astBrInf[MAX_BRLIST],
                                              int *aiStatCode, char *apStatMsg);
int UC_SvrfBrInf (char *apSvcNm, ininf astInf,  vrfinf *astBrInf,
                                              int *aiStatCode, char *apStatMsg);

/* 기타 정보 조회 Prototype */
int UC_SgetBizctgTp (char *apSvcNm, char *apBizC, char *apBizNm,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetCusNm (char *apSvcNm, char *apCusC, char *apCusNm,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetAddrByPostNo (char *apSvcNm, postin astPost, int *aiSrchCnt,
            postnoaddr astAddr[MAX_ADDRLIST], int *aiStatCode, char *apStatMsg);
int UC_SgetPostNoByAddr (char *apSvcNm, char *apAddr,
                                 int *aiSrchCnt, postaddr astPost[MAX_ADDRLIST],
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetIdcdByPsnNo (char *apSvcNm, char *apBrC, char *apPsnNo,
                                  int *aiSrchCnt, idcd_inf astIdInf[MAX_IDLIST],
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetEmpInfByIdcd (char *apSvcNm, idcdVrfPtr astIdcdInf,
                         empInfPtr astEmpInf, int *aiStatCode, char *apStatMsg);
int UC_SvrfAcctNo (char *apSvcNm, char *apAcctNo,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetAcctChkDigit (char *apSvcNm, char *apAcctNo,
                                              int *aiStatCode, char *apStatMsg);


/******************************************************************************
* Function Name : UC_ConvBin2Char
* Input Parameter
*       char *apInStr  : 바이너리문자
*       int  i_Len     : 바이너리 문자열 길이
* Output Parameter
*       char *apOutStr : 0x로 치환한 문자열
*       int  *i_OLen   : 치환한 문자열 길이
* Return Value
*       int :   0 ( 정상 )
* Description
*   바이너리문자열을 Hex값으로 표현함.
*****************************************************************************/
int UC_ConvBin2Char(char* apInStr, int i_Len, char* apOutStr, int* i_OLen );

#ifdef  __cplusplus
}
#endif

#endif
