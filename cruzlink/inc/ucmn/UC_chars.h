/*******************************************************************************
*  File name   : UC_chars.h                                                   *
*                                                                              *
*  Device      : AIX ibmit1 1 5 000BF10D4C00                                   *
*                                                                              *
*  Description : 공통util library - 문자함수        	       *
*                                                                              *
* **************************************************************************** *
*  Change Description.                                                         *
*  --------------------------------------------------------------------------- *
*  Date       Author   Ver    Description                                      *
*  +--------- +------  +----- +----------------------------------------------- *
*  2003.09.30 IBM-KR   1.09   Initial Release                                  *
*                                                                              *
*******************************************************************************/
#ifndef __UC_CHARS_H
#define __UC_CHARS_H

#ifdef  __cplusplus
extern "C" {
#endif

int UC_SubConvAscii(char* apInStr, int i_Len, char* apOutStr );
int UC_SconvChrToAscii (char acInChr, int *aiAscii);
int UC_SconvAsciiToChr (int aiInAscii, char *acChr);
int UC_SconvDblToStr (double adInNum, int aiWidth, char *apStrNum);
int UC_SconvIntToStr (int aiInNum, char *apStrNum);
int UC_SconvLongToStr (long alInNum, char *apStrNum);
int UC_SconvStrToInt (char *apInStrNum, int *aiNum);
int UC_SconvStrToLong (char *apInStrNum, long *alNum);
int UC_SconvStrToDouble (char *apInStrNum, double *adNum);
int UC_SconvNumToHangle (char *apInNum, int aiMode, char *apHangleNum);
int UC_SconcatTwoString (const char *apOneStr, const char *apOtherStr, char *apMergeStr);
int UC_SgetLowerStr (char *);
int UC_SgetUpperStr (char *);
int UC_SgetLeftPadStr (char *apInStr, int aiStrLen, char *apAddStr, char *apPaddedStr);
int UC_SgetRightPadStr (char *apInStr, int aiStrLen, char *apAddStr, char *apPaddedStr);
int UC_SgetLeftTrimStr (char *pc_Str, int i_Len);
int UC_SgetRightTrimStr (char *apInStr, char *apTrimmedStr);
int UC_SgetAllTrimStr (char *apInStr, char *apTrimmedStr);
int UC_SconvTwoSpaceToOneStr (char *apInStr, char *apConvStr);
int UC_SaddRightSpaceStr (char *apInStr, int aiStrLen, char *apAddedStr);
int UC_SaddLeftSpaceStr (char *apInStr, int aiStrLen, char *apAddedStr);
int UC_ScopyStrSpace (char *apInStr, int aiCopyLen, char *apCopyStr);
int UC_SaddLeftZeroStr (char *apInStr, int aiStrLen, char *apAddedStr);
int UC_SgetTokenStr (char *apInStr, char acDelimeter, char *apTokenStr);
int UC_SconvDblToMoney (double adNumber, char *apMoneyStr);
int UC_SconvLongToMoney (long alNumber, char *apMoneyStr);
int UC_SconvStrToMoney (char *apNumber, char *apMoneyStr);
int UC_SreplaceStr (char *apInStr, char *apFindStr, char *apChgStr, char *apConvStr);
int UC_SstuffStr (char *apOrgStr, int aiFromInx, int aiDelCnt, char *apIns, char *apConvStr);
int UC_SdelChrStr (char *apInStr, char acDelChr, char *apConvStr);
int UC_SsubStr (char *apInStr, int aiFromInx, int aiLen, char *apOutStr);
int UC_SgetLeftStr (char *apInStr, int aiLength, char *apOutStr);
int UC_SgetRightStr (char *apInStr, int aiLength, char *apOutStr);
int UC_SgetIndexFindChr (char *apInStr, char acFindChr);
int UC_SgetIndexRevFindChr (char *apInStr, char acFindChr);
int UC_SgetIndexFindStr (char *apInStr, char *apFindStr);
int UC_SgetStrLen (char *apInStr);
int UC_SisDigit (char *apInStr);
int UC_SisDigitAlpha (char *apInStr);
int UC_SshiftStr (char *apInStr, int aiShiftCnt, char *apOutStr);
int UC_SisExistSpace (char *apInStr, int aiSpaceCnt);
int UC_SisExistDigit (char *apInStr, int aiDigitCnt);
int UC_SisValid16BitChar1Byte (char *apHangleStr);
int UC_SisValid16BitCharSp1Byte (char *apHangleStr);
int UC_SisValid16BitCharSp (char *apHangleStr);
int UC_SisValid16BitChar (char *apHangleStr, int aiChkFlag,
                                   int *aiStatCode, char *apStatMsg);
int UC_SisKSC5601Char (char *apInStr);
int UC_SisHangleStr (char *apInStr);
int UC_SconvHangleStr (char *apHangleStr, char *apOutStr);
int UC_SconvInvalidChar (char *apHangleStr, int *aiConvBytes, char *apOutStr);
int UC_SconvMultiToSingleStr (char *apInStr, char *apOutStr);
int UC_SconvSingleToMultiStr (unsigned char *apInStr, char *apOutStr);


#ifdef  __cplusplus
}
#endif

#endif
