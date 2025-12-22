include $(ROME_HOME)/work/cruztp.mkconf

SRCS1	=	simadt_init.c \
			simadt_rrdf.c \
			simadt.c \
			tcp_action.c \
			$(SVCTAB1)

PRCS1	=	lf_UpdateDealLog.pc

DEST1	= simadt3.bin
SVC1	= SIMADT2

INCS    += -I.
INCS    += -I$(CFR_HOME)/inc/engine/adaptor	##########	20140926 add
INCS    += -I$(CFR_HOME)/inc	# 20190827 YYK Ãß°¡

UPBIN_DIR=$(CFR_HOME)/bin

PROC_INC +=include=$(ROME_HOME)/work/inc/usrinc
PROC_INC +=include=$(ROME_HOME)/work/inc/usrinc/rsof
PROC_INC +=include=$(ROME_HOME)/work/inc/usrinc/smt
PROC_INC +=include=$(ROME_HOME)/work/inc/usrinc/tplib
PROC_INC +=include=$(ROME_HOME)/work/inc
PROC_INC +=include=$(CFR_HOME)/inc
PROC_INC +=include=$(CFR_HOME)/src/adaptor/simadt/inc	##########	20141013 add
PROC_INC +=include=$(CFR_HOME)/inc/engine/adaptor		##########	20140926 add

COMMON_LIB += $(XMLLIB)
COMMON_LIB += -lrmtl -lrmta -lrmrl -lrmra -ldmap
COMMON_LIB += -lrdf -lrsof -lsmt
COMMON_LIB  += -L$(CFR_HOME)/lib
COMMON_LIB  += -lcfr_DBCNX
COMMON_LIB  += -L/OraDBConnect_lib -lora_dbconnect
COMMON_LIB  += -ltxnon -ltpucs


include $(ROME_HOME)/work/rome.mkrule

CFLAGS +=  -D_DEBUG_

install: bininstall

clobber: binclobber
