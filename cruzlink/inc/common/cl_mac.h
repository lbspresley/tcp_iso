#ifndef	__CL_MAC_H__
#define	__CL_MAC_H__

#define		CHAR2VAR(dst, src, s_len) { \
			int	len; \
			if(*src == 0x00) \
			{ \
				dst.len = 0; \
			} \
			else \
			{ \
				len = ( s_len >= sizeof(dst.arr) ) ? sizeof(dst.arr)-1 : s_len; \
				memcpy(dst.arr, src, len); \
				dst.len = len; \
				dst.arr[dst.len] = 0x00; \
			} \
		}

#define		CHAR2VAR2(dst, src, s_len) { \
			int	len; \
			if(*src == 0x00) \
			{ \
				dst.len = 0; \
			} \
			else \
			{ \
				len = ( s_len >= sizeof(dst.arr) ) ? sizeof(dst.arr)-1 : s_len; \
				dst.len = sizeof(dst.arr)-1; \
				memset(dst.arr, 0x20, dst.len); \
				memcpy(dst.arr, src, len); \
				dst.arr[dst.len] = 0x00; \
			} \
		}

#define		VAR2CHAR(dst, src) { \
			int	len; \
			len = src.len; \
			if(len > 0) \
			{ \
				memcpy(dst, src.arr, len); \
			} \
			dst[len] = 0x00; \
		}

#define		VAR2CHAR_NULL(dst, src) { \
			int	len; \
			len = src.len; \
			memcpy(dst, src.arr, len); \
			dst[len] = 0x00; \
		}

#define		VAR2VAR(dst, src) { \
			int	len; \
			len = ( src.len >= sizeof(dst.arr) ) ? sizeof(dst.arr)-1 : src.len; \
			memcpy(dst.arr, src.arr, len); \
			dst.len = len; \
			dst.arr[dst.len] = 0x00; \
		}

#define		MEMSET_VAR(dst, src) { \
			int len; \
			len = sizeof(dst.arr) - 1; \
			memset(dst.arr, src, len); \
			dst.len = ( src == 0x00 ) ? 0 : len; \
			dst.arr[len] = 0x00; \
		}

#define		SQL_RETURN( rc ) { \
			if( rc != SQL_OK ) \
			{ \
				if( db_Rollback() != SQL_OK ) \
				{ \
					return ( -999 ); \
				} \
			} \
			else \
			{ \
				if( db_Commit() != SQL_OK ) \
				{ \
					return ( -99 ); \
				} \
			} \
			return(rc); \
		}

#endif

