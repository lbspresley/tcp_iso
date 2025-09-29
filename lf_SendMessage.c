#include "tcp_iso.h"

// Send Poll Messge
int lf_SendPollMessage()
{
  int rc;
  char* pData = (char*) make_poll_request(0);
  int data_len = strlen(pData);
  char bizmsgidr[35+1];

  strcpy (bizmsgidr, (char*)make_poll_request(1) );
  
  utrc (data_len, pData, "Send Poll Message : bizmsgidr(%s)", bizmsgidr);

  rc = send_message(bizmsgidr, pData, data_len);
  if( rc < 0 ) {
    ulog(_ERROR_, "[로그정보] POLLREQ 전문 송신 실패 !!");
    return -1;
  }

  ulog(_FLOW_, "[로그정보] POLLREQ 전문 송신 성공!!");

  return 0;
}

// Polling callback function
void TF_SendPollReq(int TimerID, int lParam, int rParam)
{
  int rc = lf_SendPollMessage();
  if( rc < 0 ) {
    ulog(_ERROR_, "[로그정보] POLLREQ 전문 송신 실패 !!");
    //  do nothing
  }

  // start poll timer again
  rdf_setTimer(TimerID, g_ReqPollInterval, -1, 0, 0, TF_SendPollReq);

  return ;
}

int lf_SendMessage(char* pFrame, int len)
{
  int		rc;
  char* pData ;
  int data_len;

  char bizmsgidr[35+1];
  char msgtpcd[35+1];
  char bizsvc[35+1];


  if (memcmp(pFrame, "POLLREQ", 7) == 0) {
    ulog(1, "POLLREQ 전문 송신 처리 !!");
    pData = (char*)make_poll_request(0);
    strcpy (bizmsgidr, (char*)make_poll_request(1) );
    data_len = strlen(pData);

    rc = send_message(bizmsgidr, pData, data_len);
    if( rc < 0 ) {
      ulog(_ERROR_, "[로그정보] POLLREQ 전문 송신 실패 !!");
      return -1;
    }

    return 0;
  }

  //1. FEP 헤더 처리
  S_CL_HEADER		*pFepHdr=(S_CL_HEADER*)pFrame;
  BOK_HEADER *pBokHdr = (BOK_HEADER *)pFepHdr + sizeof(S_CL_HEADER);

  memset(bizmsgidr, 0, sizeof(bizmsgidr));
  memset(msgtpcd, 0, sizeof(msgtpcd));
  memset(bizsvc, 0, sizeof(bizsvc));

  memcpy(bizmsgidr, pBokHdr->BizMsgIdr, sizeof(pBokHdr->BizMsgIdr));
  memcpy(msgtpcd, pBokHdr->MsgTpCd, sizeof(pBokHdr->MsgTpCd));
  memcpy(bizsvc, pBokHdr->BizSvc, sizeof(pBokHdr->BizSvc));
  ulog(_FLOW_, "[로그정보] BizMsgIdr: %s, MsgTpCd: %s, BizSvc: %s", bizmsgidr, msgtpcd, bizsvc);

  // check data length
  pData = pFrame + sizeof(S_CL_HEADER) + sizeof(BOK_HEADER);
  data_len = len - sizeof(S_CL_HEADER) - sizeof(BOK_HEADER);

  // check data length
  char data_len_str[6+1];
  sprintf(data_len_str, "%06d", data_len);
  if( memcmp(data_len_str, pFepHdr->c_Len, 6) != 0 ) {
    ulog(_ERROR_, "[로그정보] 전문 길이 체크 실패 !!");
    return -1;
  }

  // 2. 전문변환 호출
  // TODO: 전문변환 결과 확인

  // 3. 인코딩 변환 호출
  // TODO: 인코딩 변환 결과 확인

  // 4. 전문 송신
  rc = send_message(bizmsgidr, pData, data_len);
  if( rc < 0 ) {
    ulog(_ERROR_, "[로그정보] 업무 전문 송신 실패 !!");
    return -3;
  }

  ulog(_FLOW_, "[로그정보] 업무 전문 송신 성공!!");

  return 0;
}
