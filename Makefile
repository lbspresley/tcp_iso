# ROME+ Application Make Property include
include $(ROME_HOME)/work/cruztp.mkconf
include $(CL_HOME)/work/cl.mkconf

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
		CF_GetPassWd.c \
		CF_ImgLogRecv.c \
		CF_ImgLogSend.c \
		$(SVCTAB1)

#SRCS1+= lf_Rcv_000000001_NF.c lf_Rcv_000000002_NF.c lf_Rcv_000000003_NF.c \
		#lf_Rcv_000000004_NF.c lf_Rcv_000000005_NF.c lf_Snd_000000001_NF.c 

#SRCS1+= CF_GetPassWd_NF.c CF_RcvSKeyMsg_NF.c
#SRCS1+= Polling.c lf_Snd_Poll.c CF_RcvPoll.c CF_StopPoll.c
#SRCS1+= Polling_NF.c lf_Snd_Poll_NF.c CF_RcvPoll_NF.c CF_DecSndRMP.c

#PRCS1	= db_Get_BOK_Inf.pc
SRCS1	+= db_tmp.c

SRCS1	+= INL_tmp.c
SRCS1	+= trs_req.c


# Module Name 
DEST1	= tcp_iso
SVC1	= TCP_ISO

SRCS2	= test_iso.c iso_xml.c
DEST2	= test_iso

include $(ROME_HOME)/work/rome.mkrule


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
COMMON_LIB += -lxml2 -liconv
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
