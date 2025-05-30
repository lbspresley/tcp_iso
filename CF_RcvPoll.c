#include "tcp_bok.h"

int CF_RcvPoll(int bufkind, unsigned char** ppFrame,
                    int* pBufLen, int* pFrameLen,
                    char SrcSvc[64],int Srcpidx,
                    char* callback_name,
                    long* info1, long* info2)
{
	int		rc;
	BOK_COMMON_STR* 	pCommon = (BOK_COMMON_STR*)*ppFrame;

	ulog(_FLOW_, "[로그정보] 전문ID : [%.9s] - [%.4s]", pCommon->bz_dst_cd, pCommon->tlg_tp );

	// 20200408 : send to host when NOT use POLL in FEP
	if(g_UsePoll != 1) {
		// Send to Host
		rc = rmp_MessageProc( "SEND_TO_HOST", 0, *ppFrame, *pFrameLen, 0, 0 );
		if( rc < 0 )
		{
			ulog( _ERROR_, "Fail to Send POLLING message for SEND_TO_HOST. (rc:%d/len:%d)", rc, *pFrameLen );
			return RC_DROP_PROC_NOREPLACE;
		}

		return RC_NEXT_ACTION;
	}

#if 1 // 20200410 : 자체 송신한 Polling 의 응답일 경우만 처리.
	// 관리번호체계 : 영업일자(8) + 참가기관(4) + 일련번호(8)
	// 자체 송신한 일련번호 여부 검사
	if( ( memcmp(pCommon->bz_dst_cd, "000000008", 9) == 0 ) &&
		( memcmp(pCommon->tlg_tp, "0810", 4) == 0 ) &&
		( memcmp( pCommon->tlg_mgm_no + 12 , "90", 2 ) == 0 )   // polling prefix : 90
	  ) {
		// 회선시험 응답처리 (BOK response)
		rc = lf_Rcv_PollRsp( (char*)*ppFrame, *pFrameLen );
    	if( rc < 0 ) {
			ulog( _ERROR_, "전문ID : [%.9s] - [%.4s] 처리오류 rc(%d)", pCommon->bz_dst_cd, pCommon->tlg_tp, rc ); 
			return RC_DROP_PROC_NOREPLACE;
		}

		return RC_NEXT_ACTION;
	} 

	// 자체 송신 외 회선전문 ==> 호스트로 송신
	rc = rmp_MessageProc( "SEND_TO_HOST", 0, *ppFrame, *pFrameLen, 0, 0 );
	if( rc < 0 )
	{
		ulog( _ERROR_, "Fail to Send POLLING message for SEND_TO_HOST. (rc:%d/len:%d)", rc, *pFrameLen );
		return RC_DROP_PROC_NOREPLACE;
	}

	return RC_NEXT_ACTION;

#else

	if( ( memcmp(pCommon->bz_dst_cd, "000000009", 9) == 0 ) &&
		( memcmp(pCommon->tlg_tp, "0800", 4) == 0 ) ) {
		// 회선시험 요청 처리 (BOK Request)
		rc = lf_Rcv_PollReq( (char*)*ppFrame, *pFrameLen );
	} 
	else 
	if( ( memcmp(pCommon->bz_dst_cd, "000000008", 9) == 0 ) &&
		( memcmp(pCommon->tlg_tp, "0810", 4) == 0 ) ) {
		// 회선시험 응답처리 (BOK response)
		rc = lf_Rcv_PollRsp( (char*)*ppFrame, *pFrameLen );
	} else {
		// Unknown biz no
		ulog( _ERROR_, "Unknown  Biz_no" );
		rc = -2;
	}

    if( rc < 0 ) {
		ulog( _ERROR_, "전문ID : [%.9s] - [%.4s] 처리오류 rc(%d)", pCommon->bz_dst_cd, pCommon->tlg_tp, rc ); 
		return RC_DROP_PROC_NOREPLACE;
	}

	return RC_NEXT_ACTION;
#endif
}
