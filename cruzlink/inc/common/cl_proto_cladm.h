#ifndef __CL_PROTO_CLADM_H__
#define __CL_PROTO_CLADM_H__


/*-----------------------------------------------------------------------------
*   Func Name   : cf_MkRspTgrm
*   Decription  : 응답전문 처리
*   Input       :
*   Output      :
*   Return      :
*/
int cf_MkRspTgrm(S_CL_HEADER*       pFrame          /*  Input header    */
                , char*             pApDataBuf      /*  Input data      */
                , int               iApDataRealLen  /*  Input data len  */
                , S_CL_CFG_SVCMST*  pSvcMst         /*  Input Svc Master    */
                , S_CL_CFG_ADM_INF* pReqAdmInf      /*  Input Adm inf cfg   */
                , CFG_CLA_CFG_ADM*  pAdmCfg         /*  Adm inf cfg     */
                , char**            pRspBuf         /*  rsp msg         */
                , int*              piRspLen        /*  rsp msg len     */
                , S_CL_CFG_ADM_INF* pRspAdmInf      /*  rsp Adm inf cfg */
                , S_CL_ERR_FRAME*   pErrFrame );
/*------------------------------------------------------------------------------
*   Func Name   : cf_InsertAdmTr
*   Description : Insert ADM_TR
*   Input       :
*   Output      :
*   Return      :
*/
int cf_InsertAdmTr(S_CL_HEADER*     pFrame
                , char*             pApDataBuf      /*  Input data      */
                , int               iApDataRealLen  /*  Input data len  */
                , S_CL_CFG_SVCMST*  pSvcMst
                , S_CL_CFG_ADM_INF* pAdmInf
                , S_CL_ERR_FRAME*   pErrFrame );

/*-----------------------------------------------------------------------------
*   Func Name   : cf_MkRepTgrm
*   Decription  : 요청전문 처리
*   Input       :
*   Output      :
*   Return      :
*/

int cf_MkRepTgrm(S_CL_CFG_SVCMST*   pSvcMst         /*  Input Svc Master    */
                , S_CL_CFG_ADM_INF* pReqAdmInf      /*  Input Adm inf cfg   */
                , CFG_CLA_CFG_ADM*  pAdmCfg         /*  Adm inf cfg     */
                , char**             pReqBuf         /*  rsp msg         */
                , int*              piRspLen        /*  rsp msg len     */
                , S_CL_CFG_ADM_INF* pRspAdmInf      /*  rsp Adm inf cfg */
                , S_CL_ERR_FRAME*   pErrFrame );
/*-----------------------------------------------------------------------------
*   Func Name   : cf_UpdateNetSts
*   Decription  : 망관리 테이블 갱신 및 변경내역 Insert
*   Input       :
*   Output      :
*   Return      :
*/

int cf_UpdateNetSts(S_CL_HEADER*        pFrame          /*  Input header    */
                , char*             pApDataBuf      /*  Input data      */
                , int               iApDataRealLen  /*  Input data len  */
                , S_CL_CFG_SVCMST*  pSvcMst         /*  Input Svc Master    */
                , S_CL_CFG_ADM_INF* pReqAdmInf      /*  Input Adm inf cfg   */
                , char*             pRspBuf         /*  rsp msg         */
                , int*              piRspLen        /*  rsp msg len     */
                , S_CL_CFG_ADM_INF* pRspAdmInf      /*  rsp Adm inf cfg */
                , S_CL_ERR_FRAME*   pErrFrame );






#endif

