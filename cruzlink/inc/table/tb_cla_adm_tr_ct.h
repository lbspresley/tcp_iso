/******************************************************************************
 화일명     : tb_cla_adm_tr_ct.h
 내용설명   : TB_CLA_ADM_TR c용 Structure
 참고 사항  :
 변경이력   :
     일자             작성자                        내용
  ----------         --------     ---------------------------------------
  2012.04.12                  초기 작성
******************************************************************************/
#ifndef	__TB_CLA_ADM_TR_CT_H__
#define	__TB_CLA_ADM_TR_CT_H__

int  db_Insert_tb_cla_adm_tr(char *p_tstr);
int  db_Select_tb_cla_adm_tr(char *p_tstr);
int  db_Update_tb_cla_adm_tr(char *p_tstr);
void db_Disp_tb_cla_adm_tr(char *p_tstr);
void db_Init_tb_cla_adm_tr(char *p_tstr);

typedef	struct
{
	struct { unsigned short len; unsigned char arr[  8+1]; } amn_tgrm_tms_dt;
	struct { unsigned short len; unsigned char arr[  4+1]; } ext_chan_id;
	struct { unsigned short len; unsigned char arr[ 32+1]; } ap_code;
	struct { unsigned short len; unsigned char arr[  1+1]; } trt_op_dsc;
	int     amn_tgrm_rgno;
	struct { unsigned short len; unsigned char arr[  1+1]; } amn_tgrm_kdc;
	struct { unsigned short len; unsigned char arr[  9+1]; } amn_tgrm_tms_tm;
	struct { unsigned short len; unsigned char arr[2000+1]; } amn_tgrm_cntn;
} TB_CLA_ADM_TR_CT;

#endif
