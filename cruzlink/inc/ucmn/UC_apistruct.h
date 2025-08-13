/*******************************************************************************
*                                                                              *
*  File name   : UC_apistruct.h                                               *
*                                                                              *
*  Device      : AIX ibmit1 1 5 000BF10D4C00                                   *
*                                                                              *
*  Description : 공통정보 API - 공통정의 api 구조체정의 파일           	       *
*                                                                              *
* **************************************************************************** *
*  Change Description.                                                         *
*  --------------------------------------------------------------------------- *
*  Date       Author   Ver    Description                                      *
*  +--------- +------  +----- +----------------------------------------------- *
*  2004.10.06 PNPC     1.0    Initial Release                                  *
*******************************************************************************/
#ifndef __UC_APISTRUCT_H
#define __UC_APISTRUCT_H

#ifdef  __cplusplus
extern "C" {
#endif

/* 일자정보 요청시 입력 구조체 */
typedef struct _dtinfo dtInfo, *dtInfoPtr;
struct _dtinfo {
   int discd;                            /* 구분코드 */
   int tm;                               /* 계산 기간(+,-) */
   char inpdt[DT_LEN+1];                 /* 입력일자 */
} ;
                                                             
/* 영업일 일수 산출시 입력 구조체 */
typedef struct _cntin cntIn, *cntInPtr;
struct _cntin {
   int discd;                            /* 구분코드 */
   char stdt[DT_LEN+1];                  /* 시작일자 */
   char enddt[DT_LEN+1];                 /* 종료일자 */
} ;

/* 영업일 일수 산출시 출력 구조체 */
typedef struct _cntout cntOut, *cntOutPtr;
struct _cntout {
   int bizdt;                            /* 영업일수 */
   int hldydt;                           /* 휴일수 */
   int total;                            /* 전체일수*/
} ;

/* 자금화시간 출력 구조체 */                               
typedef struct _captiz captIz, *captIzPtr;                      
struct _captiz {  
   char crt_dt[DT_LEN+1];                /* 생성일자 */     	                                              
   char at_capt_iz_tm1[TM_LEN+1];        /* 평일자동자금화시각 */     	                                              
   char at_capt_iz_tm2[TM_LEN+1];        /* 토요자동자금화시각 */     	                                              
} ;                                                             
         
/* 연장시각 구조체 */                               
typedef struct _xtntm xtnTm, *xtnTmPtr;                      
struct _xtntm {  
   char cd[YNFLAG_LEN+1];                /* 기준코드 */ 
   char dis_c;                           /* 연장구분코드 */     	                                              
   char xtn_tm[TM_LEN+1];                /* 연장시각 */     	                                              
} ;                                                             
         
/* 연장시각 출력 구조체 */                               
typedef struct _xtnout xtn, *xtnPtr;                      
struct _xtnout {  
   char crt_dt[DT_LEN+1];                /* 생성일자 */ 
   int srch_cnt;                         /* 검색수 */ 
   xtnTm astXtn[MAX_XTNCNT];             /* 연장시각 구조체 */
};

/* 기준일자일테이블 요청시 입력 구조체 */                               
typedef struct _bscdtin bscdtIn;                      
struct _bscdtin {  
   char crt_dt[DT_LEN+1];                /* 생성일자 */     	                                              
   int dis_c;                            /* 구분코드 */   
} ;                                                             
         
/* 기준일자일테이블 요청시 출력 구조체 */                               
typedef struct _bscdtout bscdt, *bscdtPtr;                      
struct _bscdtout {  
   char crt_dt[DT_LEN+1];                /* 생성일자 */               
   char dt_dis_c;                        /* 일자구분코드         */   
   char nd5_dt[DT_LEN+1];                /* 5익일일자            */     
   int  nd5_ned_dds;                     /* 5익일소요일수        */      
   char nd5_dow_c;                       /* 5익일요일코드        */ 
   char nd5_dow_eabr_nm[EABR_NM_LEN+1];  /* 5익일요일영문약어명  */ 
   char nd5_hldy_dis_c;                  /* 5익일휴일구분코드    */  
   char nd4_dt[DT_LEN+1];                /* 4익일일자            */    
   int  nd4_ned_dds;                     /* 4익일소요일수        */    
   char nd4_dow_c;                       /* 4익일요일코드        */    
   char nd4_dow_eabr_nm[EABR_NM_LEN+1];  /* 4익일요일영문약어명  */    
   char nd4_hldy_dis_c;                  /* 4익일휴일구분코드    */    
   char nd3_dt[DT_LEN+1];                /* 3익일일자            */   
   int  nd3_ned_dds;                     /* 3익일소요일수        */   
   char nd3_dow_c;                       /* 3익일요일코드        */ 
   char nd3_dow_eabr_nm[EABR_NM_LEN+1];  /* 3익일요일영문약어명  */ 
   char nd3_hldy_dis_c;                  /* 3익일휴일구분코드    */ 
   char nd2_dt[DT_LEN+1];                /* 2익일일자            */ 
   int  nd2_ned_dds;                     /* 2익일소요일수        */ 
   char nd2_dow_c;                       /* 2익일요일코드        */ 
   char nd2_dow_eabr_nm[EABR_NM_LEN+1];  /* 2익일요일영문약어명  */ 
   char nd2_hldy_dis_c;                  /* 2익일휴일구분코드    */ 
   char nd_dt[DT_LEN+1];                 /* 1익일일자            */ 
   int  nd_ned_dds;                      /* 1익일소요일수        */ 
   char nd_dow_c;                        /* 1익일요일코드        */ 
   char nd_dow_eabr_nm[EABR_NM_LEN+1];   /* 1익일요일영문약어명  */ 
   char nd_hldy_dis_c;                   /* 1익일휴일구분코드    */ 
   char td_dt[DT_LEN+1];                 /* 당일일자             */  
   int  td_ned_dds;                      /* 당일소요일수         */  
   char td_dow_c;                        /* 당일요일코드         */  
   char td_dow_eabr_nm[EABR_NM_LEN+1];   /* 당일일요일영문약어명 */  
   char td_hldy_dis_c;                   /* 당일휴일구분코드     */  
   char td_ldd_dis_c;                    /* 당일말일구분코드     */ 
   char bd_dt[DT_LEN+1];                 /* 1전일일자            */  
   int  bd_ned_dds;                      /* 1전일소요일수        */  
   char bd_dow_c;                        /* 1전일요일코드        */  
   char bd_dow_eabr_nm[EABR_NM_LEN+1];   /* 1전일요일영문약어명  */  
   char bd_hldy_dis_c;                   /* 1전일휴일구분코드    */  
   char bd2_dt[DT_LEN+1];                /* 2전일일자            */ 
   int  bd2_ned_dds;                     /* 2전일소요일수        */ 
   char bd2_dow_c;                       /* 2전일요일코드        */ 
   char bd2_dow_eabr_nm[EABR_NM_LEN+1];  /* 2전일요일영문약어명  */ 
   char bd2_hldy_dis_c;                  /* 2전일휴일구분코드    */ 
   char bd3_dt[DT_LEN+1];                /* 3전일일자            */  
   int  bd3_ned_dds;                     /* 3전일소요일수        */  
   char bd3_dow_c;                       /* 3전일요일코드        */  
   char bd3_dow_eabr_nm[EABR_NM_LEN+1];  /* 3전일요일영문약어명  */  
   char bd3_hldy_dis_c;                  /* 3전일휴일구분코드    */  
   char bd4_dt[DT_LEN+1];                /* 4전일일자            */  
   int  bd4_ned_dds;                     /* 4전일소요일수        */  
   char bd4_dow_c;                       /* 4전일요일코드        */  
   char bd4_dow_eabr_nm[EABR_NM_LEN+1];  /* 4전일요일영문약어명  */  
   char bd4_hldy_dis_c;                  /* 4전일휴일구분코드    */  
   char bd5_dt[DT_LEN+1];                /* 5전일일자            */  
   int  bd5_ned_dds;                     /* 5전일소요일수        */  
   char bd5_dow_c;                       /* 5전일요일코드        */  
   char bd5_dow_eabr_nm[EABR_NM_LEN+1];  /* 5전일요일영문약어명  */  
   char bd5_hldy_dis_c;                  /* 5전일휴일구분코드    */  
   char bd6_dt[DT_LEN+1];                /* 6전일일자            */  
   int  bd6_ned_dds;                     /* 6전일소요일수        */  
   char bd6_dow_c;                       /* 6전일요일코드        */  
   char bd6_dow_eabr_nm[EABR_NM_LEN+1];  /* 6전일요일영문약어명  */  
   char bd6_hldy_dis_c;                  /* 6전일휴일구분코드    */  
   char bd7_dt[DT_LEN+1];                /* 7전일일자            */  
   int  bd7_ned_dds;                     /* 7전일소요일수        */  
   char bd7_dow_c;                       /* 7전일요일코드        */  
   char bd7_dow_eabr_nm[EABR_NM_LEN+1];  /* 7전일요일영문약어명  */  
   char bd7_hldy_dis_c;                  /* 7전일휴일구분코드    */  
   char bd8_dt[DT_LEN+1];                /* 8전일일자            */  
   int  bd8_ned_dds;                     /* 8전일소요일수        */  
   char bd8_dow_c;                       /* 8전일요일코드        */  
   char bd8_dow_eabr_nm[EABR_NM_LEN+1];  /* 8전일요일영문약어명  */  
   char bd8_hldy_dis_c;                  /* 8전일휴일구분코드    */  
   char bd9_dt[DT_LEN+1];                /* 9전일일자            */  
   int  bd9_ned_dds;                     /* 9전일소요일수        */  
   char bd9_dow_c;                       /* 9전일요일코드        */  
   char bd9_dow_eabr_nm[EABR_NM_LEN+1];  /* 9전일요일영문약어명  */  
   char bd9_hldy_dis_c;                  /* 9전일휴일구분코드    */  
   char bd10_dt[DT_LEN+1];               /* 10전일일자           */  
   int  bd10_ned_dds;                    /* 10전일소요일수       */  
   char bd10_dow_c;                      /* 10전일요일코드       */  
   char bd10_dow_eabr_nm[EABR_NM_LEN+1]; /* 10전일요일영문약어명 */  
   char bd10_hldy_dis_c;                 /* 10전일휴일구분코드   */  
   char bd11_dt[DT_LEN+1];               /* 11전일일자           */ 
   int  bd11_ned_dds;                    /* 11전일소요일수       */ 
   char bd11_dow_c;                      /* 11전일요일코드       */ 
   char bd11_dow_eabr_nm[EABR_NM_LEN+1]; /* 11전일요일영문약어명 */ 
   char bd11_hldy_dis_c;                 /* 11전일휴일구분코드   */ 
   char bd12_dt[DT_LEN+1];               /* 12전일일자           */ 
   int  bd12_ned_dds;                    /* 12전일소요일수       */ 
   char bd12_dow_c;                      /* 12전일요일코드       */ 
   char bd12_dow_eabr_nm[EABR_NM_LEN+1]; /* 12전일요일영문약어명 */ 
   char bd12_hldy_dis_c;                 /* 12전일휴일구분코드   */ 
   char bd13_dt[DT_LEN+1];               /* 13전일일자           */ 
   int  bd13_ned_dds;                    /* 13전일소요일수       */ 
   char bd13_dow_c;                      /* 13전일요일코드       */ 
   char bd13_dow_eabr_nm[EABR_NM_LEN+1]; /* 13전일요일영문약어명 */ 
   char bd13_hldy_dis_c;                 /* 13전일휴일구분코드   */ 
   char bd14_dt[DT_LEN+1];               /* 14전일일자           */ 
   int  bd14_ned_dds;                    /* 14전일소요일수       */ 
   char bd14_dow_c;                      /* 14전일요일코드       */ 
   char bd14_dow_eabr_nm[EABR_NM_LEN+1]; /* 14전일요일영문약어명 */ 
   char bd14_hldy_dis_c;                 /* 14전일휴일구분코드   */ 
   char bd15_dt[DT_LEN+1];               /* 15전일일자           */ 
   int  bd15_ned_dds;                    /* 15전일소요일수       */ 
   char bd15_dow_c;                      /* 15전일요일코드       */ 
   char bd15_dow_eabr_nm[EABR_NM_LEN+1]; /* 15전일요일영문약어명 */ 
   char bd15_hldy_dis_c;                 /* 15전일휴일구분코드   */
} ;                                                             
                                  
/* 기준일자기타일테이블 요청시 출력 구조체 */     
typedef struct _bscdtetc bscdtEtc, *bscdtEtcPtr;    
struct _bscdtetc {                          
   char crt_dt[DT_LEN+1];                /* 생성일자                     */
   char aco_isu_fexmp_yn[YNFLAG_LEN+1];  /* 조합발행수수료면제여부       */     
   char aco_isu_fexmp_st_dt[DT_LEN+1];   /* 조합발행수수료면제종료일자   */ 
   char aco_isu_fexmp_end_dt[DT_LEN+1];  /* 조합발행수수료면제여부       */
   char naf_isu_fexmp_yn[YNFLAG_LEN+1];  /* 중앙회발행수수료면제여부     */
   char naf_isu_fexmp_st_dt[DT_LEN+1];   /* 중앙회발행수수료면제종료일자 */
   char naf_isu_fexmp_end_dt[DT_LEN+1];  /* 중앙회발행수수료면제여부     */
   int  pb_reisu_fee;                    /* 통장재발행수수료             */
   int  blcf_isu_fee;                    /* 잔액증명서발급수수료         */
   int  blcf_add_isu_fee;                /* 잔액증명서추가발급수수료     */
   int  here_fee;                        /* 당지수수료                   */
   char hanaro_acd_reg_yn;               /* 하나로사고등록여부           */
   char hldy_afts_cmpl_yn;               /* 휴일자동이체작업여부         */
   char sys_sts_c;                       /* 시스템상황코드               */
   char acc_1m_frst_biz_dt[DT_LEN+1];    /* 계리1월처음영업일자          */
   char acc_6m_lst_biz_dt[DT_LEN+1];     /* 계리6월마지막영업일자        */
   char acc_7m_frst_biz_dt[DT_LEN+1];    /* 계리7월처음영업일자          */
   char acc_12m_lst_biz_dt[DT_LEN+1];    /* 계리12월마지막영업일자       */
   char capt_iz_td_dt[DT_LEN+1];         /* 자금화당일자                 */
   char capt_iz_bd_dt[DT_LEN+1];         /* 자금화전일자                 */
} ;                        
                                         
/* 기산일 검증 요청시 입력 구조체 */
typedef struct _dtvalid dtValid, *dtValidPtr;
struct _dtvalid {
   int clsyn;                            /* 마감 여부 */
   int hldy_yn;                          /* 금융휴무 처리여부 */
   char brcd[BR_C_LEN+1];                /* 사무소코드 */
   char sbjcd[SBJ_C_LEN+1];              /* 과목코드 */ 
   char mgrid[IDCD_LEN+1];               /* 책임자 ID */
   char optrid[IDCD_LEN+1];              /* 조작자 ID */
   char rckdt[DT_LEN+1];                 /* 기산일 */
} ;   
    
/* 일자정보 요청에 대한 출력 구조체 */
typedef struct _dtbasic dtBasic, *dtBasicPtr;
struct _dtbasic {
   int dowcd;                            /* 요일코드 */
   int leapyn;                           /* 윤년 여부 : 0/1 */
   int hldyyn;                           /* 휴일 여부 : 0/1/2 */
   int bfned_dds;                        /* 전 영업 소요일수 */
   int afned_dds;                        /* 익 영업 소요일수 */
   char basdt[DT_LEN+1];                 /* 기준일 */
   char bfdt[DT_LEN+1];                  /* 기준일의 전일 */
   char afdt[DT_LEN+1];                  /* 기준일의 익일 */ 
   char bf1bzdt[DT_LEN+1];               /* 전영업일 */
   char af1bzdt[DT_LEN+1];               /* 익영업일 */
} ; 
    
/* 농협 계좌 정보 구조체 */
typedef struct _acct nafacct, *nafacctPtr;
struct _acct {
   char brcd [BR_C_LEN +1];              /* 사무소코드 */
   char sbjcd[SBJ_C_LEN+1];              /* 과목코드 */
   char seqno[ACCT_SEQNO_LEN+1];         /* 일련번호 */
};  
    
/* 사무소 정보 구조체 */
typedef struct _brc brc, *brcPtr; 
struct _brc {
   char onl_c[BR_C_LEN+1];               /* 온라인 코드 */
   char giro_c[GIRO_C_LEN+1];            /* 지로코드 */
   char nafaco_c[NAFACO_DIS_LEN+1];      /* 중조구분코드 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char brnm_chg_dt[DT_LEN+1];           /* 사무소명 변경일자 */
   char brnm_chg_psno[PSNO_LEN+1];       /* 사무소명 변경 개인번호 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char org_form[ORG_FORM_LEN+1];        /* 조직형태 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
   char cus_tel[TEL_LEN+1];              /* 고객용 전화 */
   char emp_tel[TEL_LEN+1];              /* 직원용 전화 */
   char xuse_tel[XUSE_TEL_LEN+1];        /* 전용 전화 */
   char rep_fax[TEL_LEN+1];              /* 대표 FAX */
   char crdt_fax[TEL_LEN+1];             /* 신용 FAX */
   char rbno[RBNO_LEN+1];                /* 사업자 등록번호 */
   char genmgr_nm[GENMGR_NM_LEN+1];      /* 사무소장명 */
   char eng_brnm[BR_ENM_LEN+1];          /* 영문 사무소명 */
   char addr[BR_ADDR_LEN+1];             /* 주소 */
   char addr2[BLW_ADDR_LEN+1];           /* 읍면동 이하 주소 */
   char postno[POSTNO_LEN+1];            /* 우편번호 */
   char redc_bil_mo_br_c[BR_C_LEN+1];    /* 재할인어음 모점 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관 구분 */
   char rcv_br_c[BR_C_LEN+1];            /* 수관사무소코드 */
   char rcv_onl_c[BR_C_LEN+1];           /* 수관온라인코드 */
   char fx_c[FX_C_LEN+1];                /* 외환코드 */
   char fx_mo_br_c[BR_C_LEN+1];          /* 외환 모점코드 */
   char fx_type[FX_TP_C_LEN+1];          /* 외환 type */
   char mo_br_c[BR_C_LEN+1];             /* 모점사무소코드 */
   char mo_br_onl_c[BR_C_LEN+1];         /* 모점 온라인 */
   char nlf_onl_c[BR_C_LEN+1];           /* 구축협 온라인 코드 */
   char br_loc_inf[BR_LOCINF_LEN+1];     /* 사무소 위치정보 */
   char opn_dt[DT_LEN+1];                /* 신규일 */  
   char cls_dt[DT_LEN+1];                /* 폐쇄일 */
   char acc_cls_dt[DT_LEN+1];            /* 계정폐쇄일 */
   char lst_chg_dt[DT_LEN+1];            /* 사무소정보 최종변경일 */
   char clrhs_c[CLRHS_C_LEN+1];          /* 교환소 코드 */
   char clrhs_idx[CLRHS_IDX_LEN+1];      /* 교환 idx */
   char net1[CLRHS_C_LEN+1];             /* 관내교환소 코드 */
   char net2[CLRHS_C_LEN+1];             /* 상호교환소 코드 */
   char aud_mphon[TEL_LEN+1];            /* 감사 휴대폰 */
   char aud_mphon_chg_psno[PSNO_LEN+1];  /* 감사 휴대폰 변경 개인번호 */
   char chk_fee_yn[YNFLAG_LEN+1];        /* 수표발행 수수료 면제여부 */
   char coff_c[COFF_ONLC_LEN+1];         /* 시군지부 코드 */
   char loc_tp[LOC_TP_C_LEN+1];          /* 입지유형 */
   char dvlp_tp_c[DVLP_TP_LEN+1];        /* 발전형태 코드 */
   char rgn_form_c[RGN_FORM_LEN+1];      /* 지역형태 코드 */
   char aco_dis[ACO_DIS_C_LEN+1];        /* 조합구분 */
   char lntrt_avl_yn[YNFLAG_LEN+1];      /* 여신취급 가능여부 */
   char biz_stp_yn[YNFLAG_LEN+1];        /* 업무정지 여부 */       
};  
    
/* 사무소정보 기타 COUNT 정보 구조체 */
typedef struct _brcnt brcnt, *brcntPtr;
struct _brcnt {
   int  dist1_cnt;                       /* 직하위 사무소수 */
   int  dist2_cnt;                       /* 관할 사무소수 */
   int  rcvin_cnt;                       /* 수관 사무소수(폐쇄점) */
   int  mrg_cnt;                         /* 합병 사무소수 */
} ; 
    
/* 온라인코드를 이용한 사무소 조회 결과 구조체 */
typedef struct _onbr onbr, *onbrPtr;
struct _onbr {
   char hwan_c[BR_C_LEN+1];              /* 환코드 */
   char giro_c[BR_C_LEN+1];              /* 지로코드 */             
   char nafaco_dis_c[NAFACO_DIS_LEN+1];  /* 중조구분 */
   char org_frm_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관구분 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
};

/* 환코드를 이용한 사무소 조회 결과 구조체 */
typedef struct _hwbr hwbr, *hwbrPtr;
struct _hwbr {
   char onl_c[BR_C_LEN+1];               /* 온라인코드 */
   char giro_c[BR_C_LEN+1];              /* 지로코드 */             
   char nafaco_dis_c[NAFACO_DIS_LEN+1];  /* 중조구분 */
   char org_frm_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관구분 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
};

/* 지로코드를 이용한 사무소 조회 결과 구조체 */
typedef struct _girobr girobr, *girobrPtr;
struct _girobr {
   char onl_c[BR_C_LEN+1];               /* 온라인코드 */
   char hwan_c[BR_C_LEN+1];              /* 환코드 */             
   char nafaco_dis_c[NAFACO_DIS_LEN+1];  /* 중조구분 */
   char org_frm_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관구분 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
};

/* 사무소코드를 이용한 모점 조회 결과 구조체 */
typedef struct _mobr mobr, *mobrPtr;
struct _mobr {
   char br_c[BR_C_LEN+1];                /* 사무소코드 */
   char onl_c[BR_C_LEN+1];               /* 온라인코드 */
   char giro_c[BR_C_LEN+1];              /* 지로코드 */             
   char nafaco_dis_c[NAFACO_DIS_LEN+1];  /* 중조구분 */
   char org_frm_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관구분 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
};

/* 사무소명을 이용한 조회 결과 구조체 */
typedef struct _brnm brname, *brnmPtr;
struct _brnm {
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char nafaco_dis_c[NAFACO_DIS_LEN+1];  /* 중조구분 */
   char br_c[BR_C_LEN+1];                /* 사무소코드 */
   char onl_c[BR_C_LEN+1];               /* 온라인코드 */ 
   char giro_c[GIRO_C_LEN+1];            /* 지로코드 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
   char emp_tel[TEL_LEN+1];              /* 직원용 전화 */
};

/* 시군지부 관할 조합 사무소정보 */
typedef struct _coffhdr coffhdr, *coffhdrPtr;
struct _coffhdr {
   int  jurdbr_cnt;                      /* 관할사무소수 */
   int  jurdhoff_cnt;                    /* 관할 본부수 */
   int  jurdhdrbr_cnt;                   /* 관할 본소수 */
   int  jurdsubbr_cnt;                   /* 관할 지소수 */
   int  jurdclsbr_cnt;                   /* 관할 폐쇄점 수 */
   char coff_c[COFF_ONLC_LEN+1];         /* 시군지부코드 */
   char coff_nm[BRNM_LEN+1];             /* 시군지부 명 */
} ;
   
/* 조합 사무소 정보 */
typedef struct _jurdbr jurdbr, *jurdbrPtr;
struct _jurdbr {
   int  jurdbr_cnt;                      /* 관할 사무소수 */
   char br_c[BR_C_LEN+1];                /* 사무소코드 */
   char onl_c[BR_C_LEN+1];               /* 온라인코드 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
   char orgform_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관 구분 */
};  

/* 시도코드별 사무소 정보조회 헤더 */
typedef struct _provhdr provhdr, *provhdrPtr;
struct _provhdr {
   int  br_cnt;                          /* 사무소 수 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
   char prov_nm[PROV_NM_LEN+1];           /* 시도명 */
} ;

/* 시도코드별 사무소 정보조회 데이터 */
typedef struct _provc provbr, *provbrPtr;
struct _provc {
   char br_c[BR_C_LEN+1];                /* 사무소코드 */
   char onl_c[BR_C_LEN+1];               /* 온라인 코드 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char orgform_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관 구분 */
   char coff_c[COFF_ONLC_LEN+1];         /* 시군지부코드 */
} ;

/* 수관점 정보 */
typedef struct _rcvinf rcvinf;
struct _rcvinf {
   char br_c[BR_C_LEN+1];                /* 폐쇄사무소 코드 */
   char cls_dt[DT_LEN+1];                /* 폐쇄일자 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관 구분 */
} ;

/* 하위정보 */
typedef struct _distbr {
   char br_c[BR_C_LEN+1];                /* 관할 사무소코드 */
   char orgform_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관 구분 */
} distinf;

/* 합병 정보 */
typedef struct _mrginf {
   char ohbr_c[BR_C_LEN+1];              /* 구본소 사무소코드 */
   char mrg_dt[DT_LEN+1];                /* 합병 일자 */
   char orgform_c[ORG_FORM_LEN+1];       /* 구 조직형태 */
} mrginf ;
   
/* 업무정지 정보 */
typedef struct _stpinf {
   char ohbr_c[BR_C_LEN+1];              /* 구본소 사무소코드 */
   char stp_dt[DT_LEN+1];                /* 업무정지 일자 */
   char ctrmv_dt[DT_LEN+1];              /* 계약이전 일자 */
   char orgform_c[ORG_FORM_LEN+1];       /* 구 조직형태 */
} stpinf, *stpinfPtr ;
   
/* 우편번호, 주소 정보 */
typedef struct _pinf {
   char postno[POSTNO_LEN+1];            /* 우편번호 */
   int  seqno;
   char addr[ADDR_LEN+1];                /* 주소 */
} postaddr;

/* 우편번호 입력 정보 */
typedef struct _postin {
   int  addrmode;                        /* 한글,영문주소 선택 */ 
   char postno[POSTNO_LEN+1];            /* 우편번호 */
   int  seqno;
   char inaddr[INADDR_LEN+1];            /* 입력 주소 */
} postin, *postPtr;

/* 우편번호 입력시 주소 출력 정보 */
typedef struct _postout {
   int  seqno;
   char addr[ADDR_LEN+1];                /* 주소 */
} postnoaddr;

/* 통합계정수관점 사무소정보 */
typedef struct _itginf {
   char br_c[BR_C_LEN+1];                /* 사무소코드 */
   char onl_c[BR_C_LEN+1];               /* 온라인 코드 */
   char giro_c[GIRO_C_LEN+1];            /* 지로코드 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
   char orgform_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관 구분 */
   char rcvin_br_c[BR_C_LEN+1];          /* 수관사무소코드 */
} itginf;

/* 축협 사무소 정보 및 이수관점 정보 */
typedef struct _nlfinf nlfinf, *nlfinfPtr;
struct _nlfinf {
   char br_c[BR_C_LEN+1];                /* 축협사무소코드 */
   char giro_c[GIRO_C_LEN+1];            /* 축협 지로코드 */
   char brnm[BRNM_LEN+1];                /* 축협사무소명 */
   char prov_c[PROV_C_LEN+1];            /* 축협시도코드 */
   char orgform_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char opn_dt[DT_LEN+1];                /* 축협 개점일 */
   char cls_dt[DT_LEN+1];                /* 축협 폐점일 */
   char cls_dis_c[CLS_DIS_LEN+1];        /* 폐쇄구분 */
   char nlf_rcvin[BR_C_LEN+1];           /* 축협수관점 코드 */
   char naf_rcvin[BR_C_LEN+1];           /* 농협수관점 코드 */
   char itg_rcvin[BR_C_LEN+1];           /* 통합계정 수관점코드 */
   struct _itginf itginf;                /* 통합사무점 정보 */
} ;

/* ID 카드 정보 */
typedef struct _idlist {
   int id_knd;                           /* ID카드 취급자 구분 */
   char idno[IDCD_LEN+1];                /* ID 카드번호 */
   char reg_name[REGNM_LEN+1];           /* 등록자 명 */
} idcd_inf;

/* ID 카드 검증 입력정보 */
typedef struct _idcd {
   int  trm_knd;                         /* 단말기 종류 */ 
   char brcd[BR_C_LEN+1];                /* 사무소 코드 */ 
   char optr_idcd[IDCD_LEN+1];           /* 조작자 ID카드 */  
   char mgr_idcd[IDCD_LEN+1];            /* 책임자 ID카드 */ 
} idcdVrf, *idcdVrfPtr;

/* ID 카드 검증 출력정보 */
typedef struct _emp empinf, *empInfPtr;
struct _emp {
   char optr_idcd[IDCD_LEN+1];           /* 조작자 ID카드 */  
   char mgr_idcd[IDCD_LEN+1];            /* 책임자 ID카드 */ 
   char optr_nm[REGNM_LEN+1];            /* 조작자 성명 */
   char mgr_nm[REGNM_LEN+1];             /* 책임자 성명 */
   char optr_psno[PSNO_LEN+1];           /* 조작자 개인번호 */
   char mgr_psno[PSNO_LEN+1];            /* 책임자 개인번호 */
   char nslip_useyn[NSLIP_USE_YN_LEN+1]; /* 무전표 사용여부 */
} ;

/* 점정보 요청 정보 */
typedef struct _ininf {
   char trnbiz_dis[TRNDIS_LEN+1];        /* 거래업무구분 */
   char trnftrn_dis;                     /* 거래이체구분 */
   char hldy_dis;                        /* 거래휴일구분 */
   char trbr_c[BR_C_LEN+1];              /* 취급점 */
   char trm_no[TRMNO_LEN+1];             /* 취급단말기번 */
   char acctno[ACCTNO_LEN+1];            /* 계좌번호 */
   char acd_cnf_xcp;                     /* 하나로사고체크 제외 */
   char bizstp_cnf_xcp;                  /* 업무정지 체크 제외 */
   char aclstrn_imp;                     /* HTH 마감후 거래불가 */
   char acls_key;                        /* 마감후 키 */
   char svr_rollback;                    /* 서버 rollback */
   char xcftrn_cmpl;                     /* 환처리완료 Bit */
} ininf;

typedef struct _clsinf {
   char cls_br_c[BR_C_LEN+1];            /* 폐쇄점 코드 */
   char trre_dis_c[TRRE_DISC_LEN+1];     /* 이수관 코드 */
} clsinf;
   
/* 취급점/계좌점 정보 */
typedef struct _vbr {
   char br_c[BR_C_LEN+1];                /* 사무소코드 */
   char onl_c[BR_C_LEN+1];               /* 온라인코드 */
   char brnm[BRNM_LEN+1];                /* 사무소명 */
   char nafaco_dis_c[NAFACO_DIS_LEN+1];  /* 중조구분 */
   char biz_dis[BIZ_DIS_LEN+1];          /* 영업구분 */
   char orgform_c[ORG_FORM_LEN+1];       /* 조직형태 */
   char trre_dis[TRRE_DISC_LEN+1];       /* 이수관 구분 */
   char rcv_br_c[BR_C_LEN+1];            /* 수관점 */
   char tel_no[TEL_LEN+1];               /* 전화번호 */
   char prov_c[PROV_C_LEN+1];            /* 시도코드 */
   char aco_dis[ACO_DIS_C_LEN+1];        /* 조합구분 코드 */
   char lntrt_imp_yn[YNFLAG_LEN];        /* 여신취급불가 여부 */
   char giro_c[GIRO_C_LEN+1];            /* 지로코드 */
   char chk_fee_yn[YNFLAG_LEN];          /* 수표발행 수수료 bit */
   char nlf_onl_c[BR_C_LEN+1];           /* 구축협 온라인 코드 */
   char mo_br_c[BR_C_LEN+1];             /* 모점 코드 */
   char bizstp_yn[YNFLAG_LEN];           /* 업무정지 bit */
   char fx_c[FX_C_LEN+1];                /* 외환코드 */
   char fx_mo_br_c[BR_C_LEN+1];          /* 외환 모점코드 */
   char fx_type[FX_TP_C_LEN+1];          /* 외환 type */
   char clrhs_c[CLRHS_C_LEN+1];          /* 교환소 코드 */
   char clrhs_idx[CLRHS_IDX_LEN+1];      /* 교환 idx */
   char net1[CLRHS_C_LEN+1];             /* 관내교환소 코드 */
   char net2[CLRHS_C_LEN+1];             /* 상호교환소 코드 */
   int  mrg_cnt;                         /* 합병 건수 */
   char dtch_trm_knd[TRMKND_LEN+1];      /* 파출단말 종류코드 */
   char rnt_br_c[BR_C_LEN+1];            /* 타소등록점 */
   int  clsbr_cnt;                       /* 폐점 수 */
   clsinf clsInf[MAX_CLSBR_CNT];         /* 폐쇄점 정보 */
   char acccls_yn;                       /* 계리마감 여부 */
} vbr;

/* 점정보 결과 정보 */
typedef struct _vrfinf vrfinf, *vrfinfPtr;
struct _vrfinf {
   char trn_dis[TRNDIS_LEN+1];           /* 거래구분 */
   char capt_iz_dt[DT_LEN+1];            /* 자금화 일 */
   char opn_dt[DT_LEN+1];                /* 개국일 */
   vbr  tr_brinf;                        /* 취급점 정보 */
   vbr  acct_brinf;                      /* 계좌점 정보 */  
} ;

/* 구축/삼협 계좌의 이관계좌 정보 */
typedef struct _acctinf acctinf, *acctinfPtr;
struct _acctinf {
   char nlf_acct_no[ACCTNO_LEN+1];       /* 구축협 계좌번호 */
   char acct_no[ACCTNO_LEN+1];           /* 계좌번호 */
   char rrno_dis_c[TRNDIS_LEN+1];        /* 실명 구분 */
   char rrno[RRNO_LEN+1];                /* 실명번호 */
   char gus_nm[GUSNM_LEN+1];             /* 예금주명 */
   char opn_dt[DT_LEN+1];                /* 신규일 */
   char cls_yn[YNFLAG_LEN+1];            /* 해지여부 */
   char hanaro_yn[YNFLAG_LEN];           /* 하나로 여부 */
} ;

/* DB handle function prototype */
int UC_SmmdbConnect (int *aiStatCode, char *apStatMsg);
int UC_SmmdbDisconn (int *aiStatCode, char *apStatMsg);
int UC_SmmdbChkError (int *aiStatCode, char *apStatMsg);

/* 일자 함수 ProtoType */
int UC_SisHoliday (char *apSvcNm, char *apInDate, 
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetTrnDtInfo (char *apSvcNm, dtInfoPtr astIn, dtBasicPtr astOut,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetBzDtInfo (char *apSvcNm, dtInfoPtr astIn, dtBasicPtr astOut, 
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetDowDtInfo (char *apSvcNm, dtInfoPtr astIn, dtBasicPtr astOut,  
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetBzDtCntInfo (char *apSvcNm, cntInPtr astIn, cntOutPtr astOut,  
                                              int *aiStatCode, char *apStatMsg);
int UC_SvldRckDtInfo (char *apSvcNm, dtValidPtr astIn,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetBscDtInfo (char *apSvcNm, int iDisC, bscdtPtr astBizDt, 
                 bscdtPtr astTrnDt, bscdtPtr astHbizDt, bscdtEtcPtr astBscDtEtc,
                                              int *aiStatCode, char *apStatMsg);
int UC_RgetCaptIzInfo (char *apSvcNm, captIzPtr astCaptIz,
                                              int *aiStatCode, char *apStatMsg);
int UC_RgetExtensionInfo (char *apSvcNm, int aiMode, xtnPtr astXtn,
                                              int *aiStatCode, char *apStatMsg);

/* 사무소 정보 조회 Prototype */
int UC_SconvHwanCToOtherC (char *apFileNm, char *apHwanC, hwbrPtr astBrInf,
                                              int *aiStatCode, char *apStatMsg);
int UC_SconvOnlCToOtherC (char *apSvcNm, char *apOnlC, onbrPtr astBrInf, 
                                              int *aiStatCode, char *apStatMsg);
int UC_SconvGiroCToOtherC (char *apSvcNm, char *apGiroC, girobrPtr astBrInf, 
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetBrCToMoBrC (char *apSvcNm, char *apBrC, int aiLevel, int *aiSrchCnt,
                  mobr astBrInf[MAX_MOBRCNT], int *aiStatCode, char *apStatMsg);
int UC_SgetBrInfByBrNm (char *apSvcNm, char *apBrNm, int *aiSrchCnt, 
                  brname astBrInf[MAX_BRCNT], int *aiStatCode, char *apStatMsg);
int UC_SgetBrInfByBrC (char *apSvcNm, char *apBrC, brcPtr astBrInf,
                             brcntPtr astBrCnt, distinf astDistInf1[MAX_BRLIST], 
                  distinf astDistInf2[MAX_BRLIST], rcvinf astRcvInf[MAX_BRLIST], 
                              mrginf astMrgInf[MAX_BRLIST], stpinfPtr astStpInf,
                                              int *aiStatCode, char *apStatMsg); 
int UC_SgetBrInfByCoffC (char *apSvcNm, char *apCoffC, coffhdr *astHdrInf, 
                  jurdbr astBrInf[MAX_BRCNT], int *aiStatCode, char *apStatMsg);
int UC_SgetBrInfByProvC (char *apSvcNm, int aiSortMode, char *apProvC, 
                                 provhdr *astHdrInf, provbr astBrInf[MAX_BRCNT], 
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetNlfBrInf (char *apSvcNm, char *apBrC, nlfinf *astNlfBrInf,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetRcvinInfByBrC (char *apSvcNm, char *apBrC, int *aiSrchCnt, 
                 rcvinf astBrInf[MAX_BRLIST], int *aiStatCode, char *apStatMsg);
int UC_SgetMrgInfOfAco (char *apSvcNm, char *apBrC, int *aiSrchCnt, 
                 mrginf astBrInf[MAX_BRLIST], int *aiStatCode, char *apStatMsg);
int UC_SgetBizStpInfOfAco (char *apSvcNm, char *apBrC, stpinfPtr astBrInf, 
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetDistBrByBrC (char *apSvcNm, char *apBrC, int aiLevel, 
                                   int *aiSrchCnt, distinf astBrInf[MAX_BRLIST], 
                                              int *aiStatCode, char *apStatMsg);
int UC_SvrfBrInf (char *apSvcNm, ininf astInf,  vrfinf *astBrInf, 
                                              int *aiStatCode, char *apStatMsg);

/* 기타 정보 조회 Prototype */ 
int UC_SgetBizctgTp (char *apSvcNm, char *apBizC, char *apBizNm,
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetCusNm (char *apSvcNm, char *apCusC, char *apCusNm, 
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetAddrByPostNo (char *apSvcNm, postin astPost, int *aiSrchCnt, 
            postnoaddr astAddr[MAX_ADDRLIST], int *aiStatCode, char *apStatMsg);
int UC_SgetPostNoByAddr (char *apSvcNm, char *apAddr, 
                                 int *aiSrchCnt, postaddr astPost[MAX_ADDRLIST],
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetIdcdByPsnNo (char *apSvcNm, char *apBrC, char *apPsnNo, 
                                  int *aiSrchCnt, idcd_inf astIdInf[MAX_IDLIST],
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetEmpInfByIdcd (char *apSvcNm, idcdVrfPtr astIdcdInf, 
                         empInfPtr astEmpInf, int *aiStatCode, char *apStatMsg);
int UC_SvrfAcctNo (char *apSvcNm, char *apAcctNo, 
                                              int *aiStatCode, char *apStatMsg);
int UC_SgetAcctChkDigit (char *apSvcNm, char *apAcctNo, 
                                              int *aiStatCode, char *apStatMsg);

#ifdef  __cplusplus
}
#endif

#endif
