#ifndef __CLM_CFG_FL_SVC_DSC_H__
#define __CLM_CFG_FL_SVC_DSC_H__

typedef struct
{
	char    c_clm_ap_code       [32];
	char    rsv1                [12];
} S_CLM_SVC_DSC_CFG;

#define SZ_CLM_SVC_DSC_CFG (sizeof(S_CLM_SVC_DSC_CFG))

#endif
