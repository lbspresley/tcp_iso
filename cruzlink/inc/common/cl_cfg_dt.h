#ifndef __CL_CFG_DT_H__
#define __CL_CFG_DT_H__

#if 0
typedef struct  {
	char ymd            [8+1]; /* 년월일	*/
	char dt_dsc         [1+1]; /* 일자 구분코드	*/
								/* 'B' : 영업일	*/
								/* 'C' : 반영업일 ( 토요일등 )	*/
								/* 'H' : 공휴일	*/
								/**/
	char dow_dsc		[ 3+1];	/*	요일 상세구분코드	*/
	char dt_dtlc		[30+1];	/*	일자 상세구분코드	*/
} S_CL_CFG_DT;

#else

typedef struct  {
	char ymd            [8+1];
	char dt_dsc         [1+1];
	char dow_dsc		[ 3+1];	
	char dt_dtlc		[30+1];
} S_CL_CFG_DT;

#endif

#define CL_CFG_DT_LEN (sizeof(S_CL_CFG_DT))

#endif 
