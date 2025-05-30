#include "tcp_bok.h"


int CF_ProcLogErr(int bufkind, unsigned char** ppFrame,
    int* pBufLen, int* pFrameLen,
    char SrcSvc[64],int Srcpidx,
    char* callback_name,
    long* info1, long* info2)
{
  int rc;

  //unsigned char* in = (char*) *ppFrame;
  //unsigned char* tmpbuf;

  S_CL_ERR_MSG	sErrMsg;
  S_CL_HEADER*	pHdr;

  char*	pApData;
  int		ApDataLen;

  int	inlen = *pFrameLen;
  //int	outlen = 0;

  /* APData용 버퍼를 따로 할당하지 않고.. 암복호에서 사용하는 버퍼를 이용*/
  pApData = g_EncryptBuf;

  memset( (char*)&sErrMsg, 0x00, sizeof(S_CL_ERR_MSG));
  memset( pApData, 0x00, gi_ApDataBufAllocSize); 

#if 1
  if( inlen < sizeof(S_CL_HEADER) ){
    ulog(_ERROR_, "[상세내역] Making S_CL_HEADER : inlen(%d), 대외해더길이(%d) ", inlen, sizeof(S_CL_HEADER));
    memcpy( pApData + sizeof(S_CL_HEADER), *ppFrame, inlen );
    inlen += sizeof(S_CL_HEADER);
  } else {
    memcpy( pApData, *ppFrame, inlen );
  }

  pHdr = (S_CL_HEADER*)pApData;
  ApDataLen = inlen - sizeof(S_CL_HEADER);

#else

  if( inlen < sizeof(S_CL_HEADER) )
  {
    ulog(_ERROR_, "[장애로그] 전문길이 오류\n"
        "[상세내역] inlen(%d), 대외해더길이(%d)"
        , inlen, sizeof(S_CL_HEADER));

    return RC_DROP_PROC;
  }

  pHdr = (S_CL_HEADER*)*ppFrame;
  ApDataLen = inlen - sizeof(S_CL_HEADER);

  if(ApDataLen > gi_ApDataBufAllocSize)
  {
    ulog(_WARNING_,  "[로그정보] 할당된 버퍼길이 확인" 
        "[상세정보] 할당버퍼(%d), 전문사이즈(%d)\n"
        "로깅용임으로 전문길이 조정"
        , gi_ApDataBufAllocSize, ApDataLen);

    ApDataLen = gi_ApDataBufAllocSize - sizeof(S_CL_HEADER);	
  }
  memcpy(pApData, (char*)*ppFrame + sizeof(S_CL_HEADER), ApDataLen);
#endif


  /* 에러 전문 생성 */
  rc = lf_SetErrStr(pHdr, &sErrMsg);

  /* 에러발생 서비스 */
  memcpy(sErrMsg.c_ErrSvcName, g_ServiceName, strlen(g_ServiceName));


  memcpy( (char*)*ppFrame, (char*)&sErrMsg, sizeof(S_CL_ERR_MSG) );
  memcpy( (char*)*ppFrame+sizeof(S_CL_ERR_MSG), pApData, ApDataLen);
  *pFrameLen = sizeof(S_CL_ERR_MSG) + ApDataLen;

  return RC_NEXT_ACTION;
}


/* 
   대외헤더를 사용해 대외 에러 전문생성
   */
int	lf_SetErrStr(S_CL_HEADER* pHdr, S_CL_ERR_MSG* pErrMsg)
{
  int rc = 0;

  if((pHdr == NULL) || (pErrMsg == NULL))
  {
    rc = -1;
  }

  /* 메시지 구분 */
  memcpy(pErrMsg->c_MsgDsc, pHdr->c_MsgDsc, sizeof(pErrMsg->c_MsgDsc));
  /* 대표 APCODE */
  memcpy(pErrMsg->c_FstApCode, pHdr->c_RpstApCode
      , sizeof(pErrMsg->c_FstApCode) );
  /* 대외계 APCODE */
  memcpy(pErrMsg->c_ApCode, pHdr->c_ApCode
      , sizeof(pErrMsg->c_ApCode));
  /* 취급/개설 구분 */
  memcpy(pErrMsg->c_TrtOpDsc, pHdr->c_TrtOpDsc
      , sizeof(pErrMsg->c_TrtOpDsc));
  /* 요청/응답 구분 */
  memcpy(pErrMsg->c_QADsc, pHdr->c_QADsc
      , sizeof(pErrMsg->c_QADsc));
  /* 업무 채널 ID */
  memcpy(pErrMsg->c_BeChanID, pHdr->c_BeChanID
      , sizeof(pErrMsg->c_BeChanID));
  /* 기관 채널 ID */
  memcpy(pErrMsg->c_ExChanID, pHdr->c_ExChanID
      , sizeof(pErrMsg->c_ExChanID));
  /* 업무거래 고유번호 */
  memcpy(pErrMsg->c_BeSeqNo, pHdr->c_BeSeqNo, sizeof(pErrMsg->c_BeSeqNo));
  /* 대외거래 고유번호 */
  memcpy(pErrMsg->c_ExSeqNo, pHdr->c_ExSeqNo, sizeof(pErrMsg->c_ExSeqNo));
  /* 대외계 시스템 번호 */
  memcpy(pErrMsg->c_ExSysNo, pHdr->c_ExSysNo, sizeof(pErrMsg->c_ExSysNo));
  /* 마스터 거래고유번호 */
  memcpy(pErrMsg->c_MstTrxNo, pHdr->c_MstTrxNo
      , sizeof(pErrMsg->c_MstTrxNo));
  /* 현재데이터로그번호 */
  memcpy(pErrMsg->c_PstTrxNo, pHdr->c_PstTrxNo
      , sizeof(pErrMsg->c_PstTrxNo));
  /* 백엔드 헤더 구성구분코드 */ 
  memcpy(pErrMsg->c_BizHdrTrDsc, pHdr->c_CurHdrTypeCode
      , sizeof(pErrMsg->c_BizHdrTrDsc));



  return 0;	
}
