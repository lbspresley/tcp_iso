/*******************************************************************************
*  File name   : UC_etc.h                                                     *
*  Device      : AIX ibmit1 1 5 000BF10D4C00                                   *
*  Description : 공통util library - 기타함수                *
* **************************************************************************** *
*  Change Description.                                                         *
*  --------------------------------------------------------------------------- *
*  Date       Author   Ver    Description                                      *
*  +--------- +------  +----- +----------------------------------------------- *
*******************************************************************************/
#ifndef __UC_ETC_H
#define __UC_ETC_H

#ifdef  __cplusplus
extern "C" {
#endif

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

#ifdef  __cplusplus
}
#endif

#endif
