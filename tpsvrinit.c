#include "tcp_iso.h"

void TCP_ISO(TPSVCINFO *msg);
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
    ulog(_ERROR_, "Config 취득 실패 : [Local] SvcName -> rc(%d)", rc);
    return -1;
  }

	// sequence file path
  memset(gc_seqFilePath, 0x00, sizeof(gc_seqFilePath));
  rc = roReadConfigString( NULL, "BOK_CONFIG", "SEQ_PATH", gc_seqFilePath );
  if( rc < 0 )
  {
    ulog(_WARNING_, "Sequence File Path 취득오류 : [BOK_CONFIG] SEQ_PATH -> Default Set : $ROME_HOME/log");
    sprintf(gc_seqFilePath, "%s/log", getenv("ROME_HOME"));
  }
  ulog(_FLOW_, "Sequence File Path[%s]", gc_seqFilePath);

  // Bizcode 취득
  strcpy( gc_BizCode, "FTP" );    // Set default : FTP (BSBANK, KNB)

  // 기관코드
  memset( gc_org_cd , 0x00, sizeof( gc_org_cd ));
  rc = roReadConfigString(NULL, "BOK_CONFIG", "OrgCode", gc_org_cd );
  if(rc < 0)
  {
    ulog(_ABEND_, "한국은행 참가기관 코드 취득 실패 : [BOK_CONFIG] OrgCode -> rc(%d)", rc);
    return -2;
  }

	// BOK-ISO 한국은행코드 고정 : 1016
  strcpy( gc_bok_cd , "1016");
  ulog( _WARNING_, "한국은행 코드 : 참가기관(%s) BOK(%s)", gc_org_cd, gc_bok_cd );

  // Encrypt 여부 (default : YES)
  sprintf( tmpstr, "YES");
  g_Encrypt_Flag = 1;
  rc = roReadConfigString(NULL, "BOK_CONFIG", "ENC_YN", tmpstr);
  if( strcasecmp( tmpstr, "NO" ) == 0 )
  {
    g_Encrypt_Flag = 0;
    ulog(_ERROR_, "Encryption flag is OFF !! : [BOK_CONFIG] ENC_YN -> %s", tmpstr );
  }
  ulog(_ERROR_, "Encryption flag is %d !! : [BOK_CONFIG] ENC_YN -> %s", g_Encrypt_Flag, tmpstr );

  memset( g_inisafe_conf, 0x00, sizeof(g_inisafe_conf));
  rc = roReadConfigString(NULL, "inisafe", "conf", g_inisafe_conf);
  if(rc < 0)
  {
    ulog(_ERROR_, "INISAFE Config 취득 실패 : [inisafe] conf -> rc(%d)", rc);
    return -3;
  }

  rc = tpadvertise(g_ServiceName,  TCP_ISO);
  ulog(_FLOW_, "Svr.Svc: %s.%s tpadvertise(rc:%d)", g_ServiceName, "TCP_ISO", rc);
  if( rc < 0 ) {
    ulog(_ABEND_, "tpadvertise failed rc(%d)", rc);
    return -6;
  }

  // User 초기화
  rc = UserInit();
  if( rc < 0 ) {
    ulog(_ABEND_, "UserInit failed rc(%d)", rc);
    return -7;
  }

  (void) xpSigInit();

  // Get ID/PSWD
  rc = dbGetIDPW( );
  if( rc < 0 ) { 
    ulog( _ABEND_, "BizCode[%s] : ID/PSWD 취득 오류 rc(%d)", gc_BizCode, rc );
    return -7;
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

#ifndef _SHB_
  cf_Disconnect();
#endif

  return 0;
}

