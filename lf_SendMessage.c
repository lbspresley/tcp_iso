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

#if 0 // 중복 삭제
int lf_SendPollRequest()
{
  char* pData ;
  int data_len;
  int rc;
  char bizmsgidr[35+1];

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
#endif

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
  char bizsvc[35+1];

  //1. FEP 헤더 처리
  S_CL_HEADER		*pFepHdr=(S_CL_HEADER*)pFrame;
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
    rc = lf_SendPollMessage();
    if( rc < 0 ) {
      ulog(_ERROR_, "lf_SendPollMessage error rc(%d)", rc);
      return -1;
    }

    return 0;
  }
#endif

  if (memcmp(pFepHdr->c_MsgDsc, "APMG", 4) != 0 ) {
    ulog(_ERROR_, "미정의 전문 수신 : MsgDsc(%.4s) --> 폐기 (%.15s)", pFepHdr->c_MsgDsc, pFrame );
    ulog(_FLOW_, "미정의 전문 수신 : 폐기 (%.15s)", pFrame );
	return -2;
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


  memset(msgtpcd, 0, sizeof(msgtpcd));
  memset(bizmsgidr, 0, sizeof(bizmsgidr));

  memcpy(msgtpcd, pBokHdr->MsgTpCd, sizeof(pBokHdr->MsgTpCd));
  memcpy(bizmsgidr, pBokHdr->BizMsgIdr, sizeof(pBokHdr->BizMsgIdr));
  ulog(_FLOW_, "[로그정보] MsgTpCd: %s, BizMsgIdr: %s", msgtpcd, bizmsgidr);
  //memset(bizsvc, 0, sizeof(bizsvc));
  //memcpy(bizsvc, pBokHdr->BizSvc, sizeof(pBokHdr->BizSvc));

  // POLLING : OAL2_POLLREQ
  if (memcmp(pBokHdr->MsgTpCd, "admi.004.ConnectionCheck", 25) == 0 ) {
      ulog(_FLOW_, "POLL 수신 : %.32s", msgtpcd );
      rc = lf_SendPollMessage();
      if( rc < 0 ) {
        ulog(_ERROR_, "lf_SendPollMessage() error rc(%d)", rc);
        return -4;
      }

  	return 0;
  }

  // check data length
  pData = pFrame + sizeof(S_CL_HEADER) + sizeof(BOK_HEADER);
  data_len = len - sizeof(S_CL_HEADER) - sizeof(BOK_HEADER);

  // 2. 전문변환 호출
  // 2.1 전문변환 호출
  char trs_data[1024*100];
  memset(trs_data, 0, sizeof(trs_data));

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


#if 0
  char* outbuf;
  int outlen;
  if( g_Encrypt_Flag == 0 ) {
    outbuf = encoded_data;
    outlen = data_len;
  } else {
    rc = inl_encrypt(encoded_data, data_len, &outbuf, &outlen);
    if( rc < 0 ) {
      ulog(_ERROR_, "[Encrypt] 데이터 전문 암호화 실패. rc(%d)", rc);
      return -1;
    }
  }

  ulog(_FLOW_, "[Encrypt] 데이터 전문 암호화 성공. len(%d)", outlen);
#endif

  utrc(data_len, xml_data, "Send XML Data");

  // 4. 전문 송신
  rc = send_message(bizmsgidr, xml_data, data_len);
  if( rc < 0 ) {
    ulog(_ERROR_, "[Send] 업무 전문 송신 실패 !!");
    return -3;
  }

  ulog(_FLOW_, "[로그정보] 업무 전문 송신 성공!!");

  return 0;
}

