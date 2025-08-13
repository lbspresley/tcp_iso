/*******************************************************************************
*  File name   : UC_debug.h                                                   *
*  Device      : AIX ibmit1 1 5 000BF10D4C00                                   *
*  Description : 공통library - define         	       *
* *****************************************************************************/
#ifndef __UC_DEBUG_H
#define __UC_DEBUG_H

#ifdef  __cplusplus
extern "C" {
#endif

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
                            
#ifdef  __cplusplus
}
#endif

#endif
