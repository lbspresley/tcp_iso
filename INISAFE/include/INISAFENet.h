/**
 *	@file	: INISAFENet.h
 *	@brief	: header file for external old functions
 *	@section  CREATEINFO	Create
 *   - author	:   Myungkyu Jung (myungkyu.jung@initech.com)
 *   - create	:   2009/02/26
 *	@section  MODIFYINFO	History
 *   - 2009.2.26/Myungkyu Jung	: create functions
 */


#ifndef INISAFENET_H_
#define INISAFENET_H_

#ifdef  __cplusplus
extern "C" {
#endif /*#ifdef  __cplusplus*/

/*** Include files ***/
#include <stdio.h>
#include "INL_external.h"


/*** Function Declaration ***/
/* Base Functions */
INISAFENET_INT_API NET_Version();
INISAFENET_INT_API INL_Version();
INISAFENET_INT_API	NET_GetLastError();
INISAFENET_CHAR_API	NET_ErrorString(int result);
INISAFENET_CHAR_API	INL_ErrorString(int result);
INISAFENET_VOID_API NET_Init();
#ifdef _OLD_INL_
INISAFENET_VOID_API INL_Init();
#else
INISAFENET_INT_API INL_Init();
#endif
INISAFENET_INT_API NET_Init_exp(int type, char *propertiespath, char *LicenseCertPath );
INISAFENET_VOID_API NET_Cleanup();
#ifdef _OLD_INL_
INISAFENET_VOID_API INL_Cleanup();
#else
INISAFENET_INT_API INL_Cleanup();
#endif
INISAFENET_NETCTX_API NET_CtxNew(int type, char* propertiespath);
INISAFENET_NETCTX_API NET_CtxNew_ex(int type, char* propertiespath, char *LicenseCertPath);
#ifdef _OLD_INL_
INISAFENET_NETCTX_API INL_CtxNew(int type, char* propertiespath);
#else
INISAFENET_INT_API INL_CtxNew(net_ctx **ctx, int type, char* propertiespath);
#endif
INISAFENET_NETCTX_API INL_CtxNew_ex(int type, char *propertiespath, char *LicenseCertPath);
INISAFENET_NETCTX_API NET_CtxNew_exp(int type);
INISAFENET_INT_API NET_CtxFree(net_ctx* ctx);
INISAFENET_INT_API INL_CtxFree(net_ctx* ctx);
INISAFENET_VOID_API	NET_OutFree(unsigned char* p);
#ifdef _OLD_INL_
INISAFENET_VOID_API	INL_OutFree(unsigned char* p);
#else
INISAFENET_INT_API	INL_OutFree(unsigned char* p);
#endif
INISAFENET_INT_API NET_Encrypt(net_ctx *ctx, unsigned char *in, int inl, unsigned char **out, int *outl);
INISAFENET_INT_API NET_Decrypt(net_ctx *ctx, unsigned char *in, int inl, unsigned char **out, int *outl);
INISAFENET_INT_API NET_maskEncrypt(net_ctx *ctx, unsigned char *in, int inl, unsigned char **out, int *outl);
INISAFENET_INT_API NET_maskDecrypt(net_ctx *ctx, unsigned char *in, int inl, unsigned char **out, int *outl);
INISAFENET_INT_API	NET_InitHandShake(net_ctx* ctx, char* in, char** out);
INISAFENET_INT_API  NET_InitHandShake_ex(net_ctx *ctx, char *in, char **out, int* outl);
INISAFENET_INT_API	NET_UpdateHandShake(net_ctx* ctx, char* in, char** out);
INISAFENET_INT_API	NET_UpdateHandShake_ex(net_ctx* ctx, char* in, char** out, int* outl);
INISAFENET_INT_API	NET_FinalHandShake(net_ctx* ctx, char* in, char** out);
INISAFENET_INT_API	NET_FinalHandShake_ex(net_ctx* ctx, char* in, char** out, int* outl);
INISAFENET_INT_API	INL_InitHandShake(net_ctx* ctx, char* in, char** out);
INISAFENET_INT_API  INL_InitHandShake_ex(net_ctx *ctx, char *in, char **out, int* outl);
INISAFENET_INT_API	INL_UpdateHandShake(net_ctx* ctx, char* in, char** out);
INISAFENET_INT_API	INL_UpdateHandShake_ex(net_ctx* ctx, char* in, char** out, int* outl);
INISAFENET_INT_API	INL_FinalHandShake(net_ctx* ctx, char* in, char** out);
INISAFENET_INT_API	INL_FinalHandShake_ex(net_ctx* ctx, char* in, char** out, int* outl);


/* SET Functions */
INISAFENET_INT_API NET_SetEncFlag(net_ctx *ctx, char *encflag);
INISAFENET_INT_API INL_SetEncFlag(net_ctx *ctx, char *encflag);
INISAFENET_INT_API NET_SetIV(net_ctx *ctx, unsigned char *iv, int iv_len);
INISAFENET_INT_API INL_SetIV(net_ctx *ctx, unsigned char *iv, int iv_len );
INISAFENET_INT_API NET_SetDigestAlg(net_ctx *ctx, char *DigestName);
INISAFENET_INT_API INL_SetDigestAlg(net_ctx *ctx, char *DigestName);
INISAFENET_INT_API NET_SetKey(net_ctx *ctx, char *userkey, int keylen);
INISAFENET_INT_API INL_SetKey(net_ctx *ctx, char *userkey, int keylen);
INISAFENET_INT_API NET_SetAlg(net_ctx *ctx, char *ciphername);
INISAFENET_INT_API INL_SetAlg(net_ctx *ctx, char *ciphername);
INISAFENET_INT_API NET_SetClientCert(net_ctx *ctx, char *cli_cert, int certlen);
INISAFENET_INT_API NET_SetClientCertFile(net_ctx *ctx, char *cli_cert_path);
INISAFENET_INT_API NET_SetServerCert(net_ctx *ctx, char *svr_cert, int certlen);
INISAFENET_INT_API NET_SetServerCertFile(net_ctx *ctx, char *svr_cert_path);
INISAFENET_INT_API NET_SetPrivKey(net_ctx *ctx, char *privkey, int keylen);
INISAFENET_INT_API NET_SetPrivKeyFile(net_ctx *ctx, char *privkey_path);
INISAFENET_INT_API NET_SetPrivKeyPass(net_ctx *ctx, char *privkeyPass, int passlen);
INISAFENET_INT_API NET_LoadEncryptedSKey(net_ctx *ctx, char *EncryptedSkeyFile, char *password);

/* Extend Functions */
INISAFENET_INT_API NET_I_Sign(net_ctx *ctx, unsigned char *in, int inl, unsigned char** out, int *outl);
INISAFENET_INT_API NET_I_VerifySign(net_ctx *ctx, unsigned char *org_data, int org_data_len, unsigned char *sig_data, int sig_data_len);
INISAFENET_VOID_API NET_gen_sessionkey(unsigned char *sessionkey);
INISAFENET_INT_API NET_Encrypt_Skey(net_ctx *ctx, unsigned char** encskey, int *encskeylen);
INISAFENET_INT_API NET_Decrypt_Skey(net_ctx *ctx, unsigned char *encskey);
INISAFENET_INT_API NET_Encrypt_Data(net_ctx *ctx, unsigned char *in, int inl, unsigned char** out, int *outl);
INISAFENET_INT_API NET_Decrypt_Data(net_ctx *ctx, unsigned char *in, int inl, unsigned char** out, int *outl);
INISAFENET_INT_API NET_Encrypt_Ext(net_ctx *ctx, unsigned char *in, int inl, unsigned char** out, int *outl);
INISAFENET_INT_API NET_Decrypt_Ext(net_ctx *ctx, unsigned char *in, int inl, unsigned char** out, int *outl);
INISAFENET_INT_API NET_Encrypt_Skey_FTP(net_ctx* ctx, int datalen, unsigned char** encskey, int* encskeylen);
INISAFENET_INT_API NET_Decrypt_Skey_FTP(net_ctx* ctx, unsigned char* encskey, int encskeylen);
INISAFENET_INT_API NET_Encrypt_FTP(net_ctx *ctx, char *infile, char *outfile);
INISAFENET_INT_API NET_Decrypt_FTP(net_ctx *ctx, char *infile, char *outfile);

/**
 * @brief	: Ecnrypt data with public-key(cert or pkcs1 format)
 * @param	: (char *) pub_key		: String of read cert_file or string of read pkcs1_file(PEM format)
 * @param	: (int) pubk_len		: Length of pub_key string
 * @param	: (int) pubk_flag		: Certificate=1, PKCS#1 format=2
 * @param	: (unsigned char *) pt	: plaintext
 * @parma	: (int) pt_len 			: Length of plaintext
 * @param	: (unsigned char *) ct	: ciphertext (return)
 * @param	: (int *) ct_len		: Length of ciphertext (return)
 * @return	: (int) Length of ciphertext
 */
INISAFENET_INT_API NET_EXT_RSA_Public_Encrypt(char *pub_key, int pubk_len, int pubk_flag, unsigned char *pt, int pt_len, unsigned char *ct, int *ct_len);
/**
 * @brief	: Decrypt data with private-key (only PKCS#1 format)
 * @param	: (char *) priv_key		: String of read Encrypted private-key file or string of read PKCS#1 file(PEM format)
 * @param	: (int) privk_len		: Length of priv_key string
 * @param	: (unsigned char *) ct	: ciphertext
 * @parma	: (int) ct_len 			: Length of ciphertext
 * @param	: (unsigned char *) pt	: plaintext (return)
 * @param	: (int *) pt_len		: Length of plaintext (return)
 * @return	: (int) Length of plaintext
 */
INISAFENET_INT_API NET_EXT_RSA_Private_Decrypt(char *priv_key, int privk_len, unsigned char *ct, int ct_len, unsigned char *pt, int *pt_len);





#ifdef  __cplusplus
}
#endif /*#ifdef  __cplusplus*/


#endif /* INISAFENET_H_ */
