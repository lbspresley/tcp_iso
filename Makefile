# ROME+ Application Make Property include
include $(ROME_HOME)/work/cruztp.mkconf
include $(CL_HOME)/work/cl.mkconf

# EUC-KR 인코딩 확인을 위한 설정
# 기본적으로 -finput-charset=EUC-KR 옵션을 비활성화하고, 
# 필요시 AUTO_CHARSET=1로 설정하여 자동 감지 활성화
ifeq ($(AUTO_CHARSET),1)
    CHARSET_FLAGS = -finput-charset=auto
else
    # 수동으로 EUC-KR 파일만 지정하는 방법
    EUC_KR_FILES = 
    # 예시: EUC_KR_FILES = korean_file1.c korean_file2.c
    
    # EUC-KR 파일에만 charset 옵션 적용하는 함수
    define get_charset_option
    $(if $(filter $(1),$(EUC_KR_FILES)),-finput-charset=EUC-KR,)
    endef
endif

SRCS1	= tcp_bok.c \
		tpsvrinit.c \
		UserInit.c \
		usermain.c \
		CF_APortConnect.c \
		CF_ACloseSession.c \
		CF_DisCntSession.c \
		CF_UpdateSendCnt.c \
		CF_UpdateRecvCnt.c \
		CF_Encrypt.c \
		CF_Decrypt.c	\
		CF_ProcLogErr.c \
		CF_ImgLogRecv.c \
		CF_ImgLogSend.c \
		$(SVCTAB1)
SRCS1+= CF_StopPoll.c

#SRCS1+= lf_Rcv_000000001_NF.c lf_Rcv_000000002_NF.c lf_Rcv_000000003_NF.c \
		#lf_Rcv_000000004_NF.c lf_Rcv_000000005_NF.c lf_Snd_000000001_NF.c 

#SRCS1+= CF_GetPassWd_NF.c CF_RcvSKeyMsg_NF.c
#SRCS1+= Polling.c lf_Snd_Poll.c CF_RcvPoll.c CF_StopPoll.c
#SRCS1+= Polling_NF.c lf_Snd_Poll_NF.c CF_RcvPoll_NF.c CF_DecSndRMP.c

#PRCS1	= db_Get_BOK_Inf.pc
SRCS1	+= db_tmp.c

SRCS1	+= INL_tmp.c
SRCS1	+= trs_req.c
SRCS1	+= cli_session_key.c iso_utils.c

# Module Name 
DEST1	= tcp_iso
SVC1	= TCP_ISO

SRCS2	= test_iso.c iso_xml.c
DEST2	= test_iso

SRCS3	= validate_xml.c parson.c
DEST3	= validate_xml

SRCS4	= test_regex.c
DEST4	= test_regex

include $(ROME_HOME)/work/rome.mkrule

# 인코딩을 확인하여 조건부로 컴파일하는 규칙 (UTF-8이 아니면 EUC-KR로 간주)
%.o: %.c
	@echo "Checking encoding for $<..."
	@ENCODING=$$(file -bi $< 2>/dev/null | grep -o 'charset=[^;]*' | cut -d= -f2 | tr '[:upper:]' '[:lower:]'); \
	echo "File: $< - Encoding: $$ENCODING"; \
	case "$$ENCODING" in \
		utf-8|utf8|us-ascii|ascii) \
			echo "UTF-8 compatible encoding - using default"; \
			CHARSET_FLAG=""; \
			;; \
		*) \
			echo "Non-UTF-8 encoding detected - assuming EUC-KR, adding -finput-charset=EUC-KR"; \
			CHARSET_FLAG="-finput-charset=EUC-KR"; \
			;; \
	esac; \
	echo "Compiling $< with charset flag: $$CHARSET_FLAG"; \
	`which gcc` -m64 -g -Wall -fcommon $(INCS) $(DEFINES) $$CHARSET_FLAG -c $< -o $@

# 테스트용 인코딩 확인 규칙 (UTF-8이 아니면 EUC-KR로 간주)
test-encoding:
	@echo "Testing encoding detection (UTF-8이 아니면 EUC-KR로 간주)..."
	@for src in $(SRCS1); do \
		if [ -f "$$src" ]; then \
			ENCODING=$$(file -bi $$src 2>/dev/null | grep -o 'charset=[^;]*' | cut -d= -f2 | tr '[:upper:]' '[:lower:]'); \
			case "$$ENCODING" in \
				utf-8|utf8|us-ascii|ascii) \
					echo "$$src: $$ENCODING -> UTF-8 compatible (default encoding)"; \
					;; \
				*) \
					echo "$$src: $$ENCODING -> Non-UTF-8 (WILL USE -finput-charset=EUC-KR)"; \
					;; \
			esac; \
		fi; \
	done


# Include Path
#INISAFENET_HOME=$(HOME)/INITEC/INISAFE_HP
INCS	+= -I$(CL_HOME)/inc
INCS	+= -I$(CL_HOME)/work/inc/adaptor/tcp_type/tcp_com
INCS  += -I$(INISAFENET_HOME)/include 
INCS  += -I$(INISAFENET_HOME)/include 

#PROC_INC+= include=$(ROME_HOME)/work/inc/usrinc/rsof
#PROC_INC+= include=$(CL_HOME)/src/inc
#PROC_INC+= include=$(INISAFENET_HOME)/include 
PROC_INC += $(INCS:-I%=include=%)


# Library Link
#COMMON_LIB += $(XMLLIB) -lxmlcfg
#COMMON_LIB += $(XMLLIB)
COMMON_LIB += -lrmpst -lrmvc -lrdf -lrsof
COMMON_LIB += -ltgl_s_nh
COMMON_LIB += -lsmt
COMMON_LIB += -ltpucs -ltxnon
COMMON_LIB += -lxml2
COMMON_LIB += -lcurl
#COMMON_LIB += -L$(INISAFENET_HOME)/lib -linisafeNet -liniCore -liniPKI
#COMMON_LIB += -lccl
#COMMON_LIB += -L$(CL_HOME)/lib -lclcmn -ldbcmn -lucmn -lclcfg
#COMMON_LIB += -L$(CL_HOME)/lib -ldbcmn -ldb_cl_init -ldb_cl_insert -ldb_cl_select -ldb_cl_update
#COMMON_LIB += -L$(INISAFENET_HOME)/lib -linisafeNet -liniCore -liniPKI


# Compile Option
#DEFINES	+= -D_DEBUG_
DEFINES	+= -D_CRYPT_		#	암복호화

install: all bininstall
clobber: clean binclobber
