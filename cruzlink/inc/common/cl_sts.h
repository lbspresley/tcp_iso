#ifndef __CL_STS_H__
#define __CL_STS_H__

/*	statistics *-----------------------------------------------------------------*/

struct statistics_info{
	char	c_trt_year		[ 4];	/* 贸府斥档		*/
	char	c_trt_month		[ 2];	/* 贸府岿		*/
	char	c_trt_day		[ 2];	/* 贸府老		*/
	char	c_trt_hour		[ 2];	/* 贸府矫埃		*/
	char	c_trt_min		[ 2];	/* 贸府盒		*/
	char	c_rsv			[ 2];	
};
typedef struct statistics_info S_STS_INFO;

typedef struct{
	char		c_Len		[ 6];	/* 傈眉辨捞				N	单捞磐辨捞    */
	char		c_MsgDsc	[ 4];	/* Msg备盒				A	APMG : APmsg , RCFG : ReConfig, BATF : Batch Msg */
	char		c_Primitive	[ 8];	/* Statistics Job Name									   */
	char		c_tr_dt		[ 8];
	char		c_rsv		[ 2];
	int			i_sts_dsc		;	/* 贸府备盒 	*/
	S_STS_INFO	s_StsInf		;
}S_STS_FRAME;
	

#endif
