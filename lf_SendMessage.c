#include "tcp_iso.h"

// Send Poll Messge
int lf_SendPollMessage(char *msgidr)
{
  int rc;
  char* pData = (char*) make_poll_request(0, msgidr);
  int data_len = strlen(pData);
  char bizmsgidr[35+1];

  strcpy (bizmsgidr, (char*)make_poll_request(1, msgidr) );
  
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
  int rc = lf_SendPollMessage(NULL);
  if( rc < 0 ) {
    //  do nothing
    ulog(_ERROR_, "POLLREQ 전문 송신 실패 !!");
  } else {
    ulog(_ERROR_, "[로그정보] POLLREQ SUCCESS. ");
  }

  if(g_UsePoll == 1) {
    // start poll timer again
    rdf_setTimer(TimerID, g_ReqPollInterval*1000, -1, 0, 0, TF_SendPollReq);
    ulog(_ERROR_, "[로그정보] Send Next POLLREQ after %d seconds.", g_ReqPollInterval);
  }

  return ;
}

int lf_GetLoginInfo()
{
  int rc;

  // Get ID/PSWD
  rc = dbGetIDPW( );
  if( rc < 0 ) {
    ulog( _ERROR_, "BizCode[%s] : ID/PSWD/OPN 취득 오류 rc(%d)", gc_BizCode, rc );
    return -1;
  }

  return 0;
}

int lf_SendMessage(char* pFrame, int len)
{
  int		rc;
  char* pData ;
  int data_len;

  char bizmsgidr[35+1];
  char msgtpcd[35+1];
  // char bizsvc[35+1];

  //1. FEP 헤더 처리
  BOK_HEADER *pBokHdr = (BOK_HEADER *)(pFrame + sizeof(S_CL_HEADER));

#if 1 // TEST
  // TRS TEST
  if (memcmp(pFrame, "TRSREQ", 6) == 0) {
	pData = pFrame+6;
    rc = send_to_core(pData, len);
    if( rc < 0 ) { 
	  ulog(_ERROR_, "send_to_core() error rc(%d)", rc);
    }

	return 0;
  }

  // POLL TEST
  if (memcmp(pFrame, "POLLREQ", 7) == 0) {
    rc = lf_SendPollMessage(NULL);
    if( rc < 0 ) {
      ulog(_ERROR_, "lf_SendPollMessage error rc(%d)", rc);
      return -1;
    }

    return 0;
  }
#endif

#ifdef _KSFC_
  S_CL_HEADER		*pFepHdr=(S_CL_HEADER*)pFrame;

  if (memcmp(pFepHdr->c_MsgDsc, "APMG", 4) != 0 ) {
    ulog(_ERROR_, "미정의 전문 수신 : MsgDsc(%.4s) --> NOT APMG", pFepHdr->c_MsgDsc );
    ulog(_FLOW_, "미정의 전문 수신 : 폐기 (%.15s)", pFrame );
	return -2;
  }

  // APCODE : OAL2_ISOMSG_O
  if (memcmp(pFepHdr->c_ApCode, APCODE_OUTBOUND, strlen(APCODE_OUTBOUND)) != 0 ) {
    ulog(_ERROR_, "미정의 전문 수신 : ApCode(%.4s) --> NOT %s", pFepHdr->c_ApCode, APCODE_OUTBOUND );
    ulog(_FLOW_, "미정의 전문 수신 : 폐기 (%.25s)", pFrame );
	return -3;
  }

  // 개시전문 : OAL1_081BKS20F010
  if (memcmp(pFepHdr->c_ApCode, "OAL1_081BK", 9) == 0 ) {
      ulog(_FLOW_, "개시전문 수신 : %.32s", pFepHdr->c_ApCode );
      rc = lf_GetLoginInfo();
      if( rc < 0 ) {
        ulog(_ERROR_, "lf_GetLoginInfo() error rc(%d)", rc);
        return -3;
      }

  	return 0;
  }
#endif


  memset(msgtpcd, 0, sizeof(msgtpcd));
  memset(bizmsgidr, 0, sizeof(bizmsgidr));

  memcpy(msgtpcd, pBokHdr->MsgTpCd, sizeof(pBokHdr->MsgTpCd));
  memcpy(bizmsgidr, pBokHdr->BizMsgIdr, sizeof(pBokHdr->BizMsgIdr));
  ulog(_FLOW_, "[로그정보] MsgTpCd: %s, BizMsgIdr: %s", msgtpcd, bizmsgidr);

  // remove trailing space
  //memset(bizsvc, 0, sizeof(bizsvc));
  //memcpy(bizsvc, pBokHdr->BizSvc, sizeof(pBokHdr->BizSvc));
  //ulog(_FLOW_, "[로그정보] BizMsgIdr: %s, MsgTpCd: %s, BizSvc: %s", bizmsgidr, msgtpcd, bizsvc);

  // POLLING : OAL2_ISOMSG_O
  if (memcmp(msgtpcd, "POLLREQ", 7) == 0 ) {
    ulog(_FLOW_, "POLL 요청 수신 ");
    rc = lf_SendPollMessage(bizmsgidr);
    if( rc < 0 ) {
      ulog(_ERROR_, "lf_SendPollMessage(msgidr:%s) error rc(%d)", bizmsgidr , rc);
      return -4;
    }

    ulog(_FLOW_, "POLL 요청 송신 성공 : msgidr(%s)", bizmsgidr);

  	return 0;
  }

  // check data length
  pData = pFrame + sizeof(S_CL_HEADER) + sizeof(BOK_HEADER);
  data_len = len - sizeof(S_CL_HEADER) - sizeof(BOK_HEADER);

  // 2. 전문변환 호출
  // 2.1 전문변환 호출
  char trs_data[1024*100];
  memset(trs_data, 0, sizeof(trs_data));
  ulog(0, "TRS FIX Data:len(%d)\n%s", data_len, pData); 

  // req_trs
  int trs_len = req_trs_fixed(msgtpcd, bizmsgidr, pData, data_len, trs_data);
  if( trs_len < 0 ) {
    ulog(_ERROR_, "[로그정보] 전문변환 실패 !!");
    return -1;
  }
  utrc(trs_len, trs_data, "전문변환 결과 : %s", trs_data);


  // 2.2 BokwireHeader 생성
  char* xml_data = (char*)make_header(msgtpcd, trs_data);
  data_len = strlen(xml_data);

#if 0
  char* encoded_data  = bokwire_header;
  data_len = strlen(encoded_data);

  // 3. 인코딩 변환 호출
  encoded_data = (char*)convert_to_utf8("EUC-KR", bokwire_header, data_len, &data_len);
  if( encoded_data == NULL ) {
    ulog(_ERROR_, "[로그정보] 인코딩 변환 실패 !!");
    return -1;
  }
  utrc(data_len, encoded_data, "인코딩 변환 결과 : %s", encoded_data);

  // compress xml
#ifdef __USE_XML_PARSER__
  encoded_data = trim_xml(bokwire_header, 0);
  data_len = strlen(encoded_data);

  utrc(data_len, encoded_data, "compress xml 결과 : %s", encoded_data);
#endif
#endif


  utrc(data_len, xml_data, "Send XML Data");
  ulog(0, "Send XML Data:len(%d)\n%s", data_len, xml_data); 


  // 4. 전문 송신
  rc = send_message(bizmsgidr, xml_data, data_len);
  if( rc < 0 ) {
    ulog(_ERROR_, "[Send] 업무 전문 송신 실패 !!");
    return -3;
  }

  ulog(_FLOW_, "[로그정보] 업무 전문 송신 성공!!");

  return 0;
}

