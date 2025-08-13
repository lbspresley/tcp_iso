#include "tcp_iso.h"

int CF_GetPassWd_NF(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2)
{
  BOK_NF_PASSWD_STR*	pMsg = (BOK_NF_PASSWD_STR*)*ppFrame;
  static char _req_id[32];
  static char _req_pw[32];
  static char _chg_flag = '0'; // 20200410 : 비밀번호 변경 여부 복사

  if( memcmp( pMsg->Common.bz_no, "TEJG00010", 9) != 0 ) // 비밀번호 변경 전문 아니면
  {
    // SKIP ..
    ulog(_ERROR_, "비밀번호 변경 전문 아님 : 전문ID [%.9s]", pMsg->Common.bz_no);
    return RC_NEXT_ACTION;
  }

  if( pMsg->Common.rs_flag == 'Q' )
  {
    /*	요청	*/
    ulog(_ERROR_, "요청전문 : ID[%.*s] PSWD[%.*s] CHGFLG[%c]", 
        sizeof(pMsg->NewID), pMsg->NewID, sizeof(pMsg->NewPasswd), pMsg->NewPasswd, pMsg->chg_flag );

#if 1	// 국고의 경우 응답전문에 id/pswd 안들어옴
    /*	id		*/
    memset( _req_id, 0x00, sizeof(_req_id));
    memcpy( _req_id, pMsg->NewID, sizeof(pMsg->NewID) );

    /*  pass    */
    memset( _req_pw, 0x00, sizeof(_req_pw));
    memcpy( _req_pw, pMsg->NewPasswd, sizeof(pMsg->NewPasswd));
#endif

    // 20200410 : 비밀번호 변경 여부 복사
    _chg_flag = pMsg->chg_flag ;
    ulog(_ERROR_, "[요청] 비밀번호 변경 Flag(%c)" , pMsg->chg_flag);

    return RC_NEXT_ACTION;
  }

  /* 변경 여부 : 요청시 저장한 값 비교 */
  if( _chg_flag != '1' )
  {
    ulog(_ERROR_, "ID, 비밀번호 변경 진행하지 않습니다. (%c)" , pMsg->chg_flag);

    return RC_NEXT_ACTION;
  }

  // 20200410 : 비밀번호 변경 여부 리셋
  _chg_flag = '0';

  /* 응답코드 확인 */
  if(memcmp(pMsg->Common.prc_res_cd, "0000", 4) != 0)
  {
    ulog(_ERROR_, "ID, 비밀번호 변경 오류 입니다.[%.4s] \n"
        "ID,비밀번호를 변경 하지 않습니다."
        , pMsg->Common.prc_res_cd);
    return RC_NEXT_ACTION;
  }

  if( pMsg->Common.rs_flag == 'R' )
  {
#if 1	// 국고의 경우 응답전문에 id/pswd 안들어옴
    /*	id		*/
    memset( gc_plain_id, 0x00, sizeof(gc_plain_id));
    memcpy( gc_plain_id, _req_id, sizeof(pMsg->NewID) );

    /*  pass    */
    memset( gc_plain_pw, 0x00, sizeof(gc_plain_pw));
    memcpy( gc_plain_pw, _req_pw, sizeof(pMsg->NewPasswd));
#endif

    (void)dbUpdateIDPW(gc_plain_id, gc_plain_pw);

    ulog(_ERROR_, "응답전문 : ID[%.*s] PSWD[%.*s]", sizeof(pMsg->NewID), gc_plain_id, sizeof(pMsg->NewPasswd), gc_plain_pw );
  }
  else
  {
    ulog(_ERROR_, "요청/응답 구분 오류");
  }

  return RC_NEXT_ACTION;
}
