#ifndef __CL_ADT_STR_H__
#define __CL_ADT_STR_H__

typedef struct {
	char	c_Len    	[6];	/*	길이							*/
	char	c_ChanID 	[4];	/*	채널ID							*/
	char	c_Sts	 	[1];	/*	ONE(O)/ALL(A)					*/
	char	c_RunYN	 	[1];	/*	Die(D)/Recover(R)				*/
	char	c_ModKind	[1];	/*	Adaptor(A)/Session(S)/Module(M)	*/
} S_CL_ADT_MSG;
#define SZ_S_CL_ADT_MSG	(sizeof(S_CL_ADT_MSG))

#endif
