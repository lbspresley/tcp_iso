#ifndef __CL_BULK_STR_H__
#define __CL_BULK_STR_H__

/*------------------------------------------------------------------------------
	BULK TGRM
*/

typedef struct {
	char c_Len		[ 6];	/*	전체길이	*/
	char c_MsgDsc	[ 4];	/*	MSG 구분	*/
	char pApMsg		[ 1];	/*	Msg			*/	
} S_BULK_FRAME;
#define SZ_S_BULK_FRAME  (sizeof(S_BULK_FRAME)-1)

#endif
