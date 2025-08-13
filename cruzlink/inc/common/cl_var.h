#ifndef __CL_VAR_H__
#define __CL_VAR_H__

#include "common/cl_common.h"

int 	gi_SvcMstCnt;
int		gi_ClmSvcMstCnt;

int 	gi_CoreHdrSz;				/*	Core header size	*/
int 	gi_EaiHdrSz;				/*	Eai header size		*/

int     gi_NodeNo;                  /* system node number */
int     gi_AllocSize;               /* tpalloc size */
int     gi_SndLen;                  /* send length */

char    gc_SndSvc[16+1];            /* send service name */
char    gc_MySvrName[16+1];         /* my server name */

char    gc_CmnCfg[256];             /* config file */
char    gc_NodeYn[1+1];             /* Node 구분    */
char    gc_LogDsc[1+1];             /* Log 구분     */

char    gc_CoreLenVar[1+1];			/* Core Header Length variable	*/
int		gi_CoreLenPos;				/* Core Header Length position	*/
int		gi_CoreLenLen;				/* Core Header Length length	*/

char    gc_ChkFileDir[256];			/* Check File Directory			*/
char    gc_DtFileDir[256];			/* Data File Directory			*/
char    gc_WkFileDir[256];			/* Work File Directory			*/
char    gc_CmpFileDir[256];			/* Complete File Directory		*/
char    gc_RztFileDir[256];			/* Result File Directory		*/

#endif
