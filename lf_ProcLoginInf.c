#include "tcp_iso.h"

// 0 : BOK (국고)
// 1 : FTP (신한은망)
#ifdef _SHB_
int dbGetIDPW()
{
	int rc = lf_Get_BOK_ID();
	if (rc < 0)
	{
		return -1;
	}

	rc = lf_Get_BOK_PW();
	if (rc < 0)
	{
		return -2;
	}

	return 0;
}

int lf_Get_BOK_PW()
{
	memset(gc_plain_pw, 0x00, sizeof(gc_plain_pw));
	int rc = roReadConfigString(gc_login_file, "ID_PW_INFO1", "BOK_PW", gc_plain_pw);
	if (rc < 0)
	{
		ulog(_ERROR_, "[장애로그] 한국은행 PASSWD 취득 오류 [rc:%d]", rc);
		return -1;
	}
	ulog(_FLOW_, "한국은행 PASSWD : [%s]", gc_plain_pw);

	return 0;
}

int lf_Get_BOK_ID()
{
	memset(gc_plain_id, 0x00, sizeof(gc_plain_id));
	int rc = roReadConfigString(gc_login_file, "ID_PW_INFO1", "BOK_ID", gc_plain_id);
	if (rc < 0)
	{
		ulog(_ERROR_, "[장애로그] 한국은행 ID 취득 오류 [rc:%d]", rc);

		return -1;
	}
	ulog(_FLOW_, "한국은행 ID : [%s]", gc_plain_id);

	return 0;
}

int dbUpdateIDPW(char *pID, char *pPass)
{
	int rc = 0;
	int l_nMsgLen = 0;
	FILE *fp = NULL;

	char l_CurDt4Tm[32];
	char l_BakFile[1024];
	char l_TmpStr[512];

	ulog(_FLOW_, "ID/PW : %s/%s", pID, pPass);

	time_t tm;
	struct tm *calptr, strtm;

	time(&tm);

	calptr = localtime_r(&tm, &strtm);
	calptr = &strtm;

	memset(l_CurDt4Tm, 0x00, sizeof(l_CurDt4Tm));
	strftime(l_CurDt4Tm, 15, "%Y%m%d%H%M%S", calptr);

	memset(l_BakFile, 0x00, sizeof(l_BakFile));
	snprintf(l_BakFile, sizeof(l_BakFile), "%s_%s", gc_login_file, l_CurDt4Tm);

	ulog(_FLOW_, "[로그정보] 한국은행 로그인 정보 파일 백업\n"
				 "[%s->%s]",
		 gc_login_file, l_BakFile);

	// system() 대신 직접 파일 백업 수행
	rc = lf_BackupFile(gc_login_file, l_BakFile);
	if (rc != 0)
	{
		ulog(_ERROR_, "로그인 파일 백업 오류. 파일 복사 실패. rc=%d", rc);
		return -1;
	}

	fp = fopen(gc_login_file, "w");
	if (fp == NULL)
	{
		int Errno = errno;
		ulog(_ERROR_, "로그인 파일 백업 오류. File Open 오류"
					  "FileName : [%s]"
					  "error : (%d)(%s)",
			 gc_login_file, Errno, strerror(Errno));

		return -1;
	}

	/* Make Login Info File */
	memset(l_TmpStr, 0x00, sizeof(l_TmpStr));
	snprintf(l_TmpStr, sizeof(l_TmpStr), "[ID_PW_INFO1]\nBOK_ID=\"%s\"\nBOK_PW=\"%s\"", pID, pPass);
	l_nMsgLen = strlen(l_TmpStr);

	rc = fwrite(l_TmpStr, 1, l_nMsgLen, fp);
	if (rc != l_nMsgLen)
	{
		int Errno = errno;
		ulog(_ERROR_, "로그인 파일 백업 오류. File Write 오류"
					  "FileName : [%s]"
					  "error : (%d)(%s)",
			 gc_login_file, Errno, strerror(Errno));
		fclose(fp);

		return -1;
	}

	/* 파일 저장 성공 */
	fclose(fp);

	return 0;
}

/**
 * 파일을 안전하게 백업하는 함수
 * @param src_file 원본 파일 경로
 * @param dst_file 백업 파일 경로
 * @return 0: 성공, -1: 실패
 */
int lf_BackupFile(const char *src_file, const char *dst_file)
{
	FILE *src_fp = NULL, *dst_fp = NULL;
	char buffer[4096];
	size_t bytes_read, bytes_written;
	struct stat src_stat;
	int rc = 0;

	// 원본 파일 존재 여부 확인
	if (access(src_file, F_OK) != 0)
	{
		ulog(_ERROR_, "백업할 원본 파일이 존재하지 않습니다: %s", src_file);
		return -1;
	}

	// 원본 파일 정보 가져오기
	if (stat(src_file, &src_stat) != 0)
	{
		ulog(_ERROR_, "원본 파일 정보를 가져올 수 없습니다: %s", src_file);
		return -1;
	}

	// 원본 파일 열기
	src_fp = fopen(src_file, "rb");
	if (src_fp == NULL)
	{
		int errno_val = errno;
		ulog(_ERROR_, "원본 파일을 열 수 없습니다: %s, 오류: %d (%s)",
			 src_file, errno_val, strerror(errno_val));
		return -1;
	}

	// 백업 파일 열기
	dst_fp = fopen(dst_file, "wb");
	if (dst_fp == NULL)
	{
		int errno_val = errno;
		ulog(_ERROR_, "백업 파일을 생성할 수 없습니다: %s, 오류: %d (%s)",
			 dst_file, errno_val, strerror(errno_val));
		fclose(src_fp);
		return -1;
	}

	// 파일 내용 복사
	while ((bytes_read = fread(buffer, 1, sizeof(buffer), src_fp)) > 0)
	{
		bytes_written = fwrite(buffer, 1, bytes_read, dst_fp);
		if (bytes_written != bytes_read)
		{
			int errno_val = errno;
			ulog(_ERROR_, "파일 복사 중 오류 발생: %d (%s)", errno_val, strerror(errno_val));
			rc = -1;
			break;
		}
	}

	// 파일 핸들 닫기
	fclose(src_fp);
	fclose(dst_fp);

	if (rc != 0)
	{
		// 백업 실패 시 생성된 백업 파일 삭제
		unlink(dst_file);
		return -1;
	}

	// 백업 파일의 권한을 원본과 동일하게 설정
	if (chmod(dst_file, src_stat.st_mode) != 0)
	{
		int errno_val = errno;
		ulog(_WARNING_, "백업 파일 권한 설정 실패: %s, 오류: %d (%s)",
			 dst_file, errno_val, strerror(errno_val));
		// 권한 설정 실패는 치명적이지 않으므로 경고만 출력
	}

	ulog(_FLOW_, "파일 백업 완료: %s -> %s", src_file, dst_file);
	return 0;
}
#endif