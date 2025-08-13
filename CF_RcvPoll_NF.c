#include "tcp_iso.h"

int CF_RcvPoll_NF(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2)
{
  int		rc;
  BOK_NF_COMMON_STR* 	pCommon = (BOK_NF_COMMON_STR*)*ppFrame;

  ulog(_FLOW_, "[로그정보] 전문ID : [%.9s]", pCommon->bz_no );

  // 20200408 : send to host when NOT use POLL in FEP
  if(g_UsePoll != 1) {
    // Send to Host
    strcpy(g_rmpSvcName, "SEND_TO_HOST");
    rc = rmp_MessageProc( g_rmpSvcName, 0, *ppFrame, *pFrameLen, 0, 0 );
    if( rc < 0 )
    {
      ulog( _ERROR_, "rmp_MessageProc(%s) Fail. RMP 호출 실패 (rc:%d/len:%d)", g_rmpSvcName, rc, *pFrameLen );
      return RC_DROP_PROC_NOREPLACE;
    }

    return RC_NEXT_ACTION;
  }

#if 1 // 20200410 : 자체 송신한 Polling 의 응답일 경우만 처리.
      // 자체 송신한 일련번호 여부 검사
  if( ( memcmp(pCommon->bz_no, "TEJG00013", 9) == 0 ) &&
      ( memcmp( pCommon->filler1 , "90", 2 ) == 0 )   // polling prefix : 90
    ) {
    // 회선시험 응답처리 (BOK response)
    rc = lf_Rcv_PollRsp_NF( (char*)*ppFrame, *pFrameLen );
    if( rc < 0 ) {
      ulog( _ERROR_, "전문ID : [%.9s] 처리오류 rc(%d)", pCommon->bz_no, rc );
      return RC_DROP_PROC_NOREPLACE;
    }

    return RC_NEXT_ACTION;
  }

  // 자체 송신 외 회선전문 ==> 호스트로 송신
  strcpy(g_rmpSvcName, "SEND_TO_HOST");
  rc = rmp_MessageProc( g_rmpSvcName, 0, *ppFrame, *pFrameLen, 0, 0 );
  if( rc < 0 )
  {
    ulog( _ERROR_, "rmp_MessageProc(%s) Fail. RMP 호출 실패 (rc:%d/len:%d)", g_rmpSvcName, rc, *pFrameLen );
    return RC_DROP_PROC_NOREPLACE;
  }

  return RC_NEXT_ACTION;

#else

  if( memcmp(pCommon->bz_no, "TEJG00012", 9) == 0 ) {
    // 회선시험 요청 처리 (BOK --> BS)
    rc = lf_Rcv_PollReq_NF( (char*)*ppFrame, *pFrameLen );
  } 
  else if( memcmp(pCommon->bz_no, "TEJG00013", 9) == 0 ) {
    // 회선시험 응답처리
    rc = lf_Rcv_PollRsp_NF( (char*)*ppFrame, *pFrameLen );
  } else {
    // Unknown biz no
    ulog( _ERROR_, "Unknown  Biz_no" );
    rc = -2;
  }

  if( rc < 0 ) {
    ulog( _ERROR_, "전문ID : [%.9s] 처리오류 rc(%d)", pCommon->bz_no, rc );
    return RC_DROP_PROC_NOREPLACE;
  }

  return RC_NEXT_ACTION;
#endif
}
