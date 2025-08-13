#ifndef	__CL_SQLC_H__
#define	__CL_SQLC_H__

#define		SQLCODE			sqlca.sqlcode
#define 	SQLMSG			sqlca.sqlerrm.sqlerrmc
#define 	SQLERRM			sqlca.sqlerrm.sqlerrmc
#define		SQLNUM			sqlca.sqlerrd[2]

#define 	SQL_OK				(	0)		/* query success			*/
#define 	SQL_NODATA			( 1403)		/* data not found			*/
#define 	SQL_DUP				(   -1)		/* duplicate key part		*/
#define		SQL_NOTEXIST		( -942)		/* TABLE/VIEW not exist		*/
#define		SQL_EOF				(-1002)		/* fetch out of sequence	*/
#define		SQL_NOTLOGON		(-1012)		/* DB not Log On			*/
#define 	SQL_NULL			(-1405)		/* include NULL data field	*/
#define		SQL_NOTCONNECT		(-3114)		/* DB not connected			*/

#endif

