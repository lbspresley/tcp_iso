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
		CF_ReceiveMessage.c \
		CF_UpdateSendCnt.c \
		CF_UpdateRecvCnt.c \
		lf_SendMessage.c \
		trs_req.c \
		session_key_cli.c \
		session_key_svr.c \
		process_message.c \
		process_skey_message.c \
		iso_ack.c \
		iso_utils.c \
		iso_xml.c \
		iso_header.c \
		inl_utils.c \
		$(SVCTAB1)

ifeq ($(shell uname -s), Linux)
SRCS1	+= db_tmp.c INL_tmp.c
else
PRCS1	= db_Get_BOK_Inf.pc
endif

# Module Name 
DEST1	= tcp_iso
SVC1	= TCP_ISO

SRCS2	= test_iso.c iso_xml.c iso_utils.c 
#DEST2	= test_iso

SRCS3	= validate_xml.c parson.c
#DEST3	= validate_xml

SRCS4	= validate_xml_complex.c parson.c
#DEST4	= validate_xml2

include $(ROME_HOME)/work/rome.mkrule

# Include Path
#INISAFENET_HOME=$(HOME)/INITEC/INISAFE_HP
INCS	+= -I$(CL_HOME)/inc
INCS  += -I$(INISAFENET_HOME)/include 

PROC_INC += $(INCS:-I%=include=%)


# Library Link
COMMON_LIB += -lrmpst -lrmvc -lrdf -lrsof
COMMON_LIB += -ltgl_s_nh -lsmt
COMMON_LIB += -ltpucs -ltxnon
COMMON_LIB += $(XMLLIB)
#COMMON_LIB += -lcurl
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
