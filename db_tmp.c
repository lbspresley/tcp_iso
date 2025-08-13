#include "tcp_iso.h"

int cf_dbcnx() { return 0; }
void cf_Disconnect() { return ; }
int cf_GoImgLog(char *svc, char *dir, char *title, char* msg, int len) { return 0; }


// 0 : BOK (국고)
// 1 : FTP (신한은망)
int dbGetIDPW( )
{
  char tmp_id[32]="tmp-id";
  char tmp_pw[32]="tmp-pw";

  memset( gc_plain_id, 0x00, sizeof( gc_plain_id ) );
  memcpy( gc_plain_id, tmp_id, strlen(tmp_id));

  memset( gc_plain_pw, 0x00, sizeof( gc_plain_pw ) );
  memcpy( gc_plain_pw, tmp_pw, strlen(tmp_pw));

  return 0;
}

int dbUpdateIDPW(char* pID, char* pPass)
{
  ulog(_FLOW_, "BIZ/ID/PW :%s/%s/%s", gc_BizCode, pID, pPass );

  return 0;
}

int getEncIdPw( )
{
  int inlen=0;
  int outlen=0;
  int rc;
  int offset;
  unsigned char* pOut = NULL;

  memset(gc_EncIdPswd, 0x0, sizeof( gc_EncIdPswd ) );
  memset(gc_PlainIdPswd, 0x20, sizeof( gc_PlainIdPswd ) );
  gc_PlainIdPswd[32] = 0;

  if( strcmp( gc_BizCode, "BOK" ) == 0 ) {    
    // 0 : BOK     (국고)
    offset = 20;
    inlen = 28;
  } else {
    // 1 : NEW BOK (신한은망)
    offset = 16;
    inlen = 32;
  }

  // copy id, pswd
  memcpy( gc_PlainIdPswd, 	   gc_plain_id, strlen( gc_plain_id ) );
  memcpy( gc_PlainIdPswd+offset, gc_plain_pw, strlen( gc_plain_pw ) );

  // 20200408 : Encrypt 안 할 경우
  if( g_Encrypt_Flag == 0 ) {
    memcpy( gc_EncIdPswd, gc_PlainIdPswd, strlen( gc_PlainIdPswd ) );
    return 0;
  }

  rc = INL_Encrypt(g_client_ctx, (unsigned char*)gc_PlainIdPswd, inlen, &pOut, &outlen);
  if( (rc < 0) || (inlen != outlen ) )
  {
    ulog(_ERROR_, "[장애로그] : ID/PSWD Encrypt 오류 BIZ[%s] [%d]", gc_BizCode, rc);
    return -2;
  }

  // copy encrypted id, pswd
  memcpy( gc_EncIdPswd, pOut, outlen );

  if( pOut != NULL ) INL_Free_Buf( pOut );

  return 0;
}

int getPlainIdPw( )
{
  int outlen=0;
  int inlen=0;
  int rc;
  int offset;
  unsigned char* pOut;

  if( strcmp( gc_BizCode, "BOK" ) == 0 ) {    
    // 0 : BOK     (국고)
    offset = 20;
    inlen = 28;
  } else {
    // 1 : NEW BOK (신한은망)
    offset = 16;
    inlen = 32;
  }

  memset(gc_PlainIdPswd, 0x0, sizeof( gc_PlainIdPswd ) );

  // 20200408 : Encrypt 안 할 경우
  if( g_Encrypt_Flag == 0 ) {
    memcpy( gc_PlainIdPswd, gc_EncIdPswd, strlen( gc_EncIdPswd ) );

    // copy id, pswd
    memset( gc_plain_id, 0, 	    sizeof( gc_plain_id ) );
    memset( gc_plain_pw, 0, 	    sizeof( gc_plain_pw ) );

    memcpy( gc_plain_id, gc_PlainIdPswd, 	    offset );
    memcpy( gc_plain_pw, gc_PlainIdPswd+offset, inlen-offset );

    return 0;
  }

  rc = INL_Decrypt(g_server_ctx, (unsigned char*)gc_EncIdPswd, inlen, &pOut, &outlen);
  if( (rc < 0) || (inlen != outlen ) )
  {
    ulog(_ERROR_, "[장애로그] : ID/PSWD Decrypt 오류 BIZ[%s] [%d]", gc_BizCode, rc);
    return -2;
  }

  // copy encrypted id, pswd
  memcpy( gc_PlainIdPswd, pOut, outlen );

  if( pOut != NULL ) INL_Free_Buf( pOut );

  // copy id, pswd
  memset( gc_plain_id, 0, 	    sizeof( gc_plain_id ) );
  memset( gc_plain_pw, 0, 	    sizeof( gc_plain_pw ) );

  memcpy( gc_plain_id, gc_PlainIdPswd, 	    offset );
  memcpy( gc_plain_pw, gc_PlainIdPswd+offset, inlen-offset );

  return 0;
}

int UC_SgetSysDateTime (int aiMode, char *apDateStr, int *aiStatCode, char *apStatMsg)
{
  time_t tm;
  struct tm *calptr, strtm;

  time(&tm);

  calptr = localtime_r(&tm, &strtm);
  calptr = &strtm;

  switch (aiMode)
  {
    case YYYYMMDD:
      strftime(apDateStr, 9, "%Y%m%d", calptr);
      break;
    case HHMISS:
      strftime(apDateStr, 7, "%H%M%S", calptr);
      break;
    case YYYYMMDDHHMISS:
      strftime(apDateStr, 15, "%Y%m%d%H%M%S", calptr);
      break;
    case YYYYMMDDHHMISSMI:
      {
        struct timeval currtime;
        char sDateTime[15];

        gettimeofday(&currtime, NULL);
        strftime(sDateTime, 15, "%Y%m%d%H%M%S", calptr);

        sprintf(apDateStr, "%s%02d", sDateTime, (int)(currtime.tv_usec / 10000));
        break;
      }
    case YYYYMMDDHHMISSMIS:
      {
        struct timeval currtime;
        char sDateTime[16];

        gettimeofday(&currtime, NULL);
        strftime(sDateTime, 16, "%Y%m%d%H%M%S", calptr);

        sprintf(apDateStr, "%s%03d", sDateTime, (int)(currtime.tv_usec / 1000));
        break;
      }
    case MMDDHHMISS:
      strftime(apDateStr, 11, "%m%d%H%M%S", calptr);
      break;
    case YMDFORM1:
      strftime(apDateStr, 18, "%Y%m%d:%H:%M:%S", calptr);
      break;
    case YMDFORM2:
      strftime(apDateStr, 20, "%m/%d/%Y %H:%M:%S", calptr);
      break;
    case YMDFORM3:
      strftime(apDateStr, 18, "%Y%m%d-%H:%M:%S", calptr);
      break;
    case TIMEFORM1:
      strftime(apDateStr, 9, "%H:%M:%S", calptr);
      break;
    default:
      *aiStatCode = UC_ERR_INDATA_UNKNOWN_TYPE;
      sprintf(apStatMsg, "구분코드[%d] 오류입니다", aiMode);
      return -1;

  } /* end of switch */

  return 0;

} /* end of UC_SgetSysDateTime() */
