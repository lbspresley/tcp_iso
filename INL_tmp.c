#include <stdio.h>
#include "INL_external.h"

INISAFENET_INT_API INL_Version();
INISAFENET_CHAR_API	INL_ErrorString(int result) { return NULL; }
INISAFENET_INT_API INL_Init() { return 0; }
INISAFENET_INT_API INL_Cleanup() { return 0; }
INISAFENET_INT_API INL_CtxNew(net_ctx **ctx, int type, char* propertiespath) { return 0; }
INISAFENET_NETCTX_API INL_CtxNew_ex(int type, char *propertiespath, char *LicenseCertPath) { return NULL; }
INISAFENET_INT_API	INL_OutFree(unsigned char* p) { return 0; }
INISAFENET_INT_API	INL_InitHandShake(net_ctx* ctx, char* in, char** out) { return 0; }
INISAFENET_INT_API  INL_InitHandShake_ex(net_ctx *ctx, char *in, char **out, int* outl) { return 0; }
INISAFENET_INT_API	INL_UpdateHandShake(net_ctx* ctx, char* in, char** out) { return 0; }
INISAFENET_INT_API	INL_UpdateHandShake_ex(net_ctx* ctx, char* in, char** out, int* outl) { return 0; }
INISAFENET_INT_API	INL_FinalHandShake(net_ctx* ctx, char* in, char** out) { return 0; }
INISAFENET_INT_API	INL_FinalHandShake_ex(net_ctx* ctx, char* in, char** out, int* outl) { return 0; }


/* SET Functions */
INISAFENET_INT_API INL_SetEncFlag(net_ctx *ctx, char *encflag) { return 0; }
INISAFENET_INT_API INL_SetIV(net_ctx *ctx, unsigned char *iv, int iv_len ) { return 0; }
INISAFENET_INT_API INL_SetDigestAlg(net_ctx *ctx, char *DigestName) { return 0; }
INISAFENET_INT_API INL_SetKey(net_ctx *ctx, char *userkey, int keylen) { return 0; }
INISAFENET_INT_API INL_SetAlg(net_ctx *ctx, char *ciphername) { return 0; }

// ------------------------------------------------------------
INISAFENET_INT_API INL_New_Ctx(int type, net_ctx **ctx_st) { return 0; }
INISAFENET_VOID_API INL_Free_Buf(unsigned char *ctx_st) { return ; }
INISAFENET_INT_API INL_Initialize(int type, char *conf_path, char *license_path){return 0; }
INISAFENET_INT_API INL_CtxFree(net_ctx **ctx) { return 0; }
INISAFENET_INT_API INL_Encrypt(net_ctx *ctx, unsigned char *pt, int pt_len, unsigned char **ct, int *ct_len) { return 0; }
INISAFENET_INT_API INL_Decrypt(net_ctx *ctx, unsigned char *ct, int ct_len, unsigned char **pt, int *pt_len) { return 0; }
INISAFENET_INT_API INL_Handshake_Init(net_ctx *ctx, unsigned char *in, int in_len, unsigned char **out, int *out_len) { return 0; }
INISAFENET_INT_API INL_Handshake_Update(net_ctx *ctx, unsigned char *in, int in_len, unsigned char **out, int *out_len) { return 0; }
INISAFENET_INT_API INL_Handshake_Final(net_ctx *ctx, unsigned char *in, int in_len, unsigned char **out, int *out_len) { return 0; }

