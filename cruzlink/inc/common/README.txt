
# CruzLink 2.0 common header file


 개요


 - CruzLink 엔진 모듈에서 필요한 헤더 파일



 최종 수정 사항


 - 2009.07.01 김재엽

1. TB_CL_SVC_MASTER 테이블에 코어헤더 수신서비스명/화면번호 필드 추가로 인한 헤더 수정

수정 부분 : cl_str.h 229행 core_tr_cd, core_scm_no 추가 / rcv1 사이즈 조정

코어헤더 조립 시 필요한 필드들로 사이트에 따라 사양이 상이하기 때문에 결국 커스커마이징의 영역으로 봐야 함.


 - 2009.07.13 박준석

1. TB_CL_SVC_MASTER 테이블에 ostc_prc, var_idx 컬럼 추가로 인해 cl_str.h 구조체 필드 추가.  
