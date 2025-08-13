#ifndef __CL_CFG_SVCDSC_H__
#define __CL_CFG_SVCDSC_H__

typedef struct
{
    char    c_apcode    [32];
    char    c_qadsc     [1];
    char    rsv1        [15];
} S_SVC_DSC_CFG;

#define SZ_SVC_DSC_CFG (sizeof(S_SVC_DSC_CFG))

#endif
