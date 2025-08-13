#ifndef __CL_CFG_SVC_MST_H__
#define __CL_CFG_SVC_MST_H__

/*	업무정보 (SVC_MASTER)가
*	DB와 Config File을 같이 쓰기 위해서 Config 정의를 한다.	*/
typedef struct  {
	char svc_mst_dsc             [33+1]; /* 구분코드                      */
	char ap_code                 [32+1];  /* 업무코드                      */
	char trt_op_dsc              [1+1];   /* 취급개설구분코드              */
	char fst_ap_code             [32+1];  /* 대표업무코드                  */
	char re_rs_dsc               [1+1];   /* 요청응답구분코드              */
	char ext_chan_id             [4+1];   /* 대외채널코드                  */
	char bed_chan_id             [4+1];   /* 백엔드채널코드                */
	char svc_flow_mst_dsc        [20+1];  /* 서비스플로우마스터코드        */
	char err_svcnm               [16+1];  /* 장애서비스명                  */
	char to_svcnm                [16+1];  /* 타임아웃서비스명              */
	char to_err_svcnm            [16+1];  /* 타임아웃장애서비스명          */
	char node_no                 [4+1];   /* 노드번호                      */
	char rel_ap_code             [32+1];  /* 상대대표업무코드              */
	char crypt_dsc               [1+1];   /* 암복호화구분코드              */
	char crypt_mdlnm             [16+1];  /* 암복호화모듈명                */
	char crypt_key_flnm          [64+1];  /* 암복호화키파일명              */
	int  crypt_pos               ;        /* 암복호화위치                  */
	int  crypt_len               ;        /* 암호화길이                    */
	int  decrypt_len             ;        /* 복호화길이                    */
	char dup_trtc                [1+1];   /* 중복처리코드                  */
	char tgrm_asodsc             [1+1];   /* 전문구성형식코드              */
	char seq_reg_dsc             [1+1];   /* Seq채번구분코드               */
	char seq_nm                  [32+1];  /* 채번Seq명                     */
	int  biz_seq_pos             ;        /* 업무팀Seq번호위치             */
	int  biz_seq_len             ;        /* 업무팀Seq번호길이             */
	int  ext_seq_pos             ;        /* 대외기관Seq번호위치           */
	int  ext_seq_len             ;        /* 대외기관Seq번호길이           */
	int  biz_dtl_dsc_pos         ;        /* 업무상세구분코드위치          */
	int  biz_dtl_dsc_len         ;        /* 업무상세구분코드길이          */
	char to_tm                   [6+1];   /* 타임아웃시간(초)              */
	char to_tr_c                 [1+1];   /* 타임아웃처리코드              */
	int  to_rty_cn               ;        /* 타임아웃재시도횟수            */
	char to_bed_hdr_comp_dsc     [2+1];   /* 타임아웃백엔드헤더구성구분코드*/
	char app_snd_tp_yn           [1+1];   /* 지정송신방식여부              */
	char x25_line_nm             [8+1];   /* 지정_LINE_명                  */
	char x25_lu_no               [8+1];   /* 지정_LU_명                    */
	char peer_ip                 [16+1];  /* 지정상대_IP                   */
	char peer_port               [5+1];   /* 지정상대_PORT                 */
	char local_port              [5+1];   /* 지정자기_PORT                 */
	char bed_svc_nm              [16+1];  /* 백엔드수신서비스명            */
	char snd_err_bed_rtn_yn      [1+1];   /* 송신실패백엔드리턴여부        */
	char snd_err_hdr_comp_dsc    [2+1];   /* 송신실패백엔드헤더구성구분코드*/
	char snd_err_bed_svc_nm      [16+1];  /* 송신실패백엔드수신서비스명    */
	char tgrm_log_dsc            [1+1];   /* 전문로그구분코드              */
	char eaiid                   [32+1];  /* EAIID                         */
	char bed_hdr_comp_dsc        [2+1];   /* 백엔드헤더구성구분코드        */
	char ext_hdr_comp_dsc        [2+1];   /* 대외헤더구성구분코드          */
	char bed_chan_tgrm_id        [30+1];  /* 백엔드채널전문ID              */
	char bed_snr_dsc             [1+1];   /* 백엔드송수신구분코드          */
	char ext_chan_tgrm_id        [30+1];  /* 대외채널전문ID                */
	char ext_snr_dsc             [1+1];   /* 대외송수신구분코드            */
	char tgrm_mrl_id             [50+1];  /* 전문매핑룰ID                  */
	char hdr_rec_yn              [1+1];   /* 헤더복구여부                  */
	char opn_dt                  [8+1];   /* 적용일자                      */
	char chan_bsn_dept_c         [6+1];   /* 관리업무팀코드                */
} S_CL_CFG_SVCMST, *P_CL_CFG_SVCMST;
#define CL_CFG_SVCMST_LEN (sizeof(S_CL_CFG_SVCMST))


#endif
