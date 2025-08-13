/*******************************************************************************
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
#ifndef __UC_DATES_H
#define __UC_DATES_H

#ifdef  __cplusplus
extern "C" {
#endif

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
int UC_SgetTimeAfterSec (char *apOutTime, int aiBufSize, int aiAfterSec ); 

#ifdef  __cplusplus
}
#endif

#endif 
