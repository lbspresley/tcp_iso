/*******************************************************************************
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
#ifndef __UC_APIDB_H
#define __UC_APIDB_H

#ifdef  __cplusplus
extern "C" {
#endif

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

/* DB 서버별 정보 정의 */
static dbinfo gstDbInfo[DB_SERVERCNT+1] = {
     { "", "" },
     { "11.1.1.105", "20300"},   /* DB 서버 1 */
     { "11.1.1.105", "20300"},   /* DB 서버 2 */
} ;

#ifdef  __cplusplus
}
#endif

#endif
