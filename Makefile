# ROME+ Application Make Property include
include $(ROME_HOME)/work/cruztp.mkconf
include $(CL_HOME)/work/cl.mkconf

SRCS1	= tcp_iso.c \
		tpsvrinit.c \
		UserInit.c \
		usermain.c \
		CF_APortConnect.c \
		CF_ACloseSession.c \
		CF_DisCntSession.c \
		CF_Encrypt.c \
		CF_Decrypt.c	\
		CF_ProcLogErr.c \
		CF_ImgLogRecv.c \
		CF_ImgLogSend.c \
		CF_StopPoll.c \
		CF_ReceiveMessage.c \
		CF_ProcessSessionKey.c \
		CF_ProcessMessage.c \
		CF_UpdateSendCnt.c \
		CF_UpdateRecvCnt.c \
		trs_req.c \
		session_key_cli.c \
		session_key_svr.c \
		iso_utils.c \
		iso_xml.c \
		$(SVCTAB1)

#PRCS1	= db_Get_BOK_Inf.pc
SRCS1	+= db_tmp.c INL_tmp.c inl_utils.c

# Module Name 
DEST1	= tcp_iso
SVC1	= TCP_ISO

SRCS2	= test_iso.c iso_xml.c iso_utils.c
DEST2	= test_iso

SRCS3	= validate_xml.c parson.c
DEST3	= validate_xml

SRCS4	= validate_xml_complex.c parson.c
DEST4	= validate_xml2

include $(ROME_HOME)/work/rome.mkrule

# Include Path
#INISAFENET_HOME=$(HOME)/INITEC/INISAFE_HP
INCS	+= -I$(CL_HOME)/inc
INCS	+= -I$(CL_HOME)/work/inc/adaptor/tcp_type/tcp_com
INCS  += -I$(INISAFENET_HOME)/include 

PROC_INC += $(INCS:-I%=include=%)


# Library Link
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


# Compile Option
#DEFINES	+= -D_DEBUG_
#	암복호화
DEFINES	+= -D_CRYPT_

install: all bininstall
clobber: clean binclobber
