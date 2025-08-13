#ifndef __CL_BATCH_H__
#define __CL_BATCH_H__

#include "table/tb_clc_bat_inf_ct.h"

/*	batch	*-----------------------------------------------------------------*/
typedef struct {
	char    c_Len       [ 6];   /*  전체길이 N 대외계헤더길이 + 데이타길이  */ 
	char    c_MsgDsc    [ 4];   /*  Msg구분  A APMG : APmsg                 * 
								*              RCFG : ReConfig              */
	char	c_tr_dt		[ 8];

	TB_CLC_BAT_INF_CT	sTbBat;

} S_BAT_FRAME;

typedef struct {
	char    c_Len       [ 6];   /*  전체길이 N 대외계헤더길이 + 데이타길이  */ 
	char    c_MsgDsc    [ 4];   /*  Msg구분  A APMG : APmsg                 * 
								*              RCFG : ReConfig              */
	char	c_tr_dt		[ 8];
	char	c_batmsg	[256+1];	/*	명령어/전문	*/
} S_BAT_MSG;

#endif
