#include "tcp_bok.h"
#include "table/tb_clc_code_dtl_ct.h"

typedef struct {
  BOK_COMMON_STR common;
  char			chgpswd[16];
  char			rsv[16];
} TGRM;

int CF_GetPassWd(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2)
{
  TGRM*	pMsg = (TGRM*) *ppFrame;

  if( memcmp(pMsg->common.tlg_tp, "0800", 4 ) == 0 )
  {
    /*	요청	*/

    /*  pass    */
    memset( gc_plain_id, 0x00, sizeof(gc_plain_id));
    memcpy( gc_plain_id, pMsg->common.enc_org_id, sizeof(pMsg->common.enc_org_id));

    ulog(_ERROR_, "요청전문 : ID[%.*s] PSWD[%.*s]", 
        sizeof(pMsg->common.enc_org_id), gc_plain_id, 
        sizeof(pMsg->common.enc_org_pwd), pMsg->common.enc_org_pwd );
    return RC_NEXT_ACTION;
  }

  /* 응답코드 확인 */
  if(memcmp(pMsg->common.rsp_cd, "0000", 4) != 0)
  {
    ulog(_ERROR_, "ID, 비밀번호 변경 오류 입니다.[%.4s] \n"
        "ID,비밀번호를 변경 하지 않습니다."
        , pMsg->common.rsp_cd);
    return RC_NEXT_ACTION;
  }


  /*  pass    */
  memset( gc_plain_pw, 0x00, sizeof(gc_plain_pw));
  memcpy( gc_plain_pw, pMsg->chgpswd, sizeof(pMsg->chgpswd));

  (void)dbUpdateIDPW(gc_plain_id, gc_plain_pw);

  ulog(_ERROR_, "응답전문 : ID[%.*s] PSWD[%.*s]", 
      sizeof(pMsg->common.enc_org_id), gc_plain_id, 
      sizeof(pMsg->common.enc_org_pwd), gc_plain_pw );

  return RC_NEXT_ACTION;
}
