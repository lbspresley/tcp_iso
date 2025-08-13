#ifndef __CL_STR_H__
#define __CL_STR_H__

#include "common/cl_fep_hdr.h"
#include "common/cl_fep_err.h"
#include "common/cl_adm_hdr.h"
#include "common/cl_batch.h"
#include "common/cl_fep_err.h"
#include "common/cl_fep_hdr.h"
#include "common/cl_sts.h"
#include "common/cl_cfg_aplist.h"
#include "common/cl_cfg_bed_tgrm.h"
#include "common/cl_cfg_ext_tgrm.h"
#include "common/cl_cfg_str.h"
#include "common/cl_cfg_svc_mst.h"
#include "common/cl_img_str.h"
#include "common/cl_bulk_str.h"
#include "common/cl_sys_log.h"

typedef struct {
	S_CL_HEADER		s_ClHead;
	char			pc_ApData[1];
} S_CL_FRAME, *P_CL_FRAME;
#define SZ_S_CL_FRAME	(sizeof(S_CL_FRAME)-1)

typedef struct {
	S_CL_ERR_MSG	s_Err;
	char			pc_ApData[1];
} S_CL_ERR_FRAME, *P_CL_ERR_FRAME;
#define SZ_S_CL_ERR_FRAME	(sizeof(S_CL_ERR_FRAME)-1)


#endif
