#include "tcp_iso.h"

//void TCP_BOK(TPSVCINFO *msg);
void TCP_ISO(TPSVCINFO *msg);
void UserInit();
extern void xpSigInit();

int tpsvrinit(int argc, char* argv[])
{
  int rc;
  char tmpstr[64];

  ulog(_FLOW_, "tpsvrinit start ");


  // Svc name 취득
  memset(g_ServiceName, 0x00, sizeof(g_ServiceName));
  rc = roReadConfigString(NULL, "Local", "SvcName", g_ServiceName);
  if(rc < 0)
  {
    ulog(_ERROR_, "[%s/%s] Config 취득 실패\n"
        "-> rc : %d\n",
        "Local", "SvcName", rc);
    return(-1);
  }

	// sequence file path
  memset(gc_seqFilePath, 0x00, sizeof(gc_seqFilePath));
  rc = roReadConfigString( NULL, "Local", "SEQ_PATH", gc_seqFilePath );
  if( rc != 0 )
  {
    ulog(_WARNING_, "[Local/SEQ_PATH] Sequence File Path 취득오류\n" 
        "--> Default Set : $ROME_HOME/log");
    sprintf(gc_seqFilePath, "%s/log", getenv("ROME_HOME"));
  }
  ulog(_FLOW_, "Sequence File Path[%s]", gc_seqFilePath);

#ifdef _KSFC_
  // Bizcode 취득
  strcpy( gc_BizCode, "FTP" );    // 신한은망, ISO :FTP 
  strcpy( gc_org_cd, "8070" );    // 증권금융
#else
  // Bizcode 취득
  strcpy( gc_BizCode, "BOK" );    // 국고:BOK, 신한은망:FTP
  memset(tmpstr, 0x00, sizeof(tmpstr));
  rc = roReadConfigString(NULL, "Local", "BizCode", tmpstr);
  if(rc != 0)
  {
    ulog(_ABEND_, "[%s] %s 취득 실패 rc=%d ==> Set default : BOK # 국고", "Local", "BizCode", rc);
    //exit(-1);
  }
  memcpy(gc_BizCode, tmpstr, strlen(tmpstr));

  // 송수신기관코드
  memset( gc_org_cd , 0x00, sizeof( gc_org_cd ));
  rc = roReadConfigString(NULL, "Local", "OrgCode", gc_org_cd );
  if(rc != 0)
  {
    ulog(_ABEND_, "[%s] %s 취득 실패 rc=%d : 한국은행 참가기관 코드", "Local", "OrgCode", rc);
    return(-2);
  }
#endif

#if 1
	// BOK-ISO 한국은행코드 고정 : 1016
  strcpy( gc_bok_cd , "1016");
#else
  memset( gc_bok_cd , 0x00, sizeof( gc_bok_cd ));
  rc = roReadConfigString(NULL, "Local", "BokCode", gc_bok_cd );
  if(rc != 0)
  {
    if( strcmp( gc_BizCode, "BOK" ) != 0 ) { // 국고:BOK, 신한은망:FTP
      ulog(_ERROR_, "[%s] %s 취득 실패 rc=%d ==> Set Default : 001", "Local", "BokCode", rc);
      sprintf( gc_bok_cd, "001" ); // 국고 한국은행 코드(001)
    } else {
      ulog(_ERROR_, "[%s] %s 취득 실패 rc=%d ==> Set Default : 1016", "Local", "BokCode", rc);
      sprintf( gc_bok_cd, "1016" ); // 신-한은망용 한국은행 코드(1016)
    }
  }
#endif
  ulog( _WARNING_, "한국은행 코드 : 참가기관(%s) BOK(%s)", gc_org_cd, gc_bok_cd );

  // Encrypt 여부 (default : YES)
  sprintf( tmpstr, "YES");
  g_Encrypt_Flag = 1;
  rc = roReadConfigString(NULL, "BOK_CONFIG", "ENC_YN", tmpstr);
  if( strcasecmp( tmpstr, "NO" ) == 0 )
  {
    g_Encrypt_Flag = 0;
    ulog(_ERROR_, "[%s] %s : %s ==> Encryption flag is OFF !!", "BOK_CONFIG", "ENC_YN", tmpstr );
  }
  ulog(_ERROR_, "Encryption flag is %d !!", g_Encrypt_Flag );


  memset( g_inisafe_conf, 0x00, sizeof(g_inisafe_conf));
  rc = roReadConfigString(NULL, "inisafe", "conf", g_inisafe_conf);
  if(rc < 0)
  {
    ulog(_ERROR_, "[%s/%s] Config 취득 실패 -> rc : %d"
        "\n==> Set default : /app/mcx/initech/INISAFE_Net_for_C/conf/INISAFENet_PSB.cnf"
        "inisafe", "conf", rc);
    strcpy( g_inisafe_conf, "/app/mcx/initech/INISAFE_Net_for_C/conf/INISAFENet_PSB.cnf" );
  }

  // 20200408 : Encrypt 안 할 경우
  /* ctx 포인터 변수에 대한 메모리 할당 */
  g_server_ctx = NULL;

  if( g_Encrypt_Flag != 0 ) {
    rc = INL_Initialize( SERVER_CTX, g_inisafe_conf, NULL );
    if( rc != 0 )
    {
      ulog(_ABEND_, "Server INL_Initialize(%d:%s)", rc, INL_ErrorString(rc) );
      return(-4);
    }

    rc = INL_New_Ctx( SERVER_CTX, &g_server_ctx );
    if( rc != 0 )
    {
      /* ret 가 0 이면 정상*/
      ulog(_ERROR_, "INL_New_Ctx SERVER Failed. code=%d\n", rc);
      return -5;
    }
  }

  rc = tpadvertise(g_ServiceName,  TCP_ISO);
  ulog(_FLOW_, "Svr.Svc: %s.%s tpadvertise(rc:%d)",
      g_ServiceName, "TCP_ISO", rc);

  // User 초기화
  UserInit();

  (void) xpSigInit();

  // Get ID/PSWD
  rc = dbGetIDPW( );
  if( rc < 0 ) { 
    // 국고:BOK, 신한은망:FTP
    ulog( _ABEND_, "BizCode[%s] : ID/PSWD 취득 오류 rc(%d)", gc_BizCode, rc );
    return -3;
  }

  return 0;
}


int tpsvrdone()
{
  ulog( _ABEND_,	"tpsvrdone" );

  /* Free : 암호화 관련 */
  INL_CtxFree(g_client_ctx);
  INL_CtxFree(g_server_ctx);

  INL_Cleanup();

  cf_Disconnect();

  return 0;
}

