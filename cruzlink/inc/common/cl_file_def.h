#ifndef __CL_FILE_DEF_H__
#define __CL_FILE_DEF_H__


#define ERR_LOG_FILE_DIR "%s/erlog/%.*s-%.*s"

#define DEFAULT_GET_SQ_NO "SQ_GET_SQNO_IN_FEP"


/*  Sys info monitor Directory  *---------------------------------------------*/
#define CL_SYS_INFO_LOG_DIR "%s/syslog"
#define CL_ERR_LOG_DIR		"%s/erlog"


/*	directory	*/

#if 0	/*	mail box dir modify	*/

#define CLM_FILE_RCV_DIR		"%s/%.*s/rcv"	/*	gc_filedir/chan_id/rcv		*/
#define CLM_FILE_SND_DIR		"%s/%.*s/snd"	/*	gc_filedir/chan_id/snd		*/

#else

/*	20101020 : mrpeng 디렉토리 추가변경	*/
/*	base dir가 변경 될 경우 적용안되는 문제 발생 - 솔로몬	*/
/*  
*   CL_FILE_HOME/CHAN_ID/rzt/FILENAME.rss(rsf)
*   CL_FILE_HOME/CHAN_ID/chk/FILENAME.chk
*   CL_FILE_HOME/CHAN_ID/data/FILENAME
*   CL_FILE_HOME/CHAN_ID/cmpl/FILENAME
*   CL_FILE_HOME/CHAN_ID/work/FILENAME
*/

#if 0
/*	20110314 : mrpeng busan bank	*/

#define CLM_CHECK_DIR		"%s/%.*s/chk"
#define CLM_DATA_DIR        "%s/%.*s/data"
#define CLM_RZT_DIR         "%s/%.*s/rzt"
#define CLM_COMPLETE_DIR    "%s/%.*s/cmpl"
#define CLM_WORK_DIR    	"%s/%.*s/work"

#define CLM_CHECK_FILE		"%s/%.*s/chk/%s"
#define CLM_DATA_FILE       "%s/%.*s/data/%s"
#define CLM_RZT_SUCESS      "%s/%.*s/rzt/%s.rss"
#define CLM_RZT_FAIL        "%s/%.*s/rzt/%s.rsf"
#define CLM_COMPLETE_FILE	"%s/%.*s/cmpl/%s"
#define CLM_WORK_FILE		"%s/%.*s/work/%s"

#else

#define CLM_CHECK_RCV_DIR		"%s/%.*s/rcv/chk"			/*	BASE/CHANID/rcv/chk						*/
#define CLM_DATA_RCV_DIR        "%s/%.*s/rcv/data"			/*	BASE/CHANID/rcv/data					*/
#define CLM_RZT_RCV_DIR         "%s/%.*s/rcv/rslt/%s"		/*	BASE/CHANID/rcv/rslt/YYYYMMDD			*/
#define CLM_COMPLETE_RCV_DIR    "%s/%.*s/rcv/cmpl/%s"		/*	BASE/CHANID/rcv/cmpl/YYYYMMDD			*/
#define CLM_WORK_RCV_DIR    	"%s/%.*s/rcv/work"			/*	BASE/CHANID/rcv/work					*/

#define CLM_CHECK_SND_DIR		"%s/%.*s/snd/chk"			/*  BASE/CHANID/snd/chk						*/
#define CLM_DATA_SND_DIR        "%s/%.*s/snd/data"			/*  BASE/CHANID/snd/data    				*/
#define CLM_RZT_SND_DIR         "%s/%.*s/snd/rslt/%s"		/*  BASE/CHANID/snd/rslt/YYYYMMDD			*/
#define CLM_COMPLETE_SND_DIR    "%s/%.*s/snd/cmpl/%s"		/*  BASE/CHANID/snd/cmpl/YYYYMMDD			*/
#define CLM_WORK_SND_DIR    	"%s/%.*s/snd/work"			/*  BASE/CHANID/snd/work					*/

#define CLM_CHECK_RCV_FILE		"%s/%.*s/rcv/chk/%s"		/*  BASE/CHANID/rcv/chk/filename			*/
#define CLM_DATA_RCV_FILE       "%s/%.*s/rcv/data/%s"		/*  BASE/CHANID/rcv/data/filename			*/
#define CLM_RZT_RCV_SUCESS      "%s/%.*s/rcv/rslt/%s/%s.rss"	/*  BASE/CHANID/rcv/rslt/YYYYMMDD/filename	*/
#define CLM_RZT_RCV_FAIL        "%s/%.*s/rcv/rslt/%s/%s.rsf"	/*  BASE/CHANID/rcv/cmpl/YYYYMMDD/filename	*/
#define CLM_COMPLETE_RCV_FILE	"%s/%.*s/rcv/cmpl/%s/%s"	/*  BASE/CHANID/rcv/work/YYYYMMDD/filename	*/
#define CLM_WORK_RCV_FILE		"%s/%.*s/rcv/work/%s"		/*	BASE/CHANID/rcv/work/filename			*/

#define CLM_CHECK_SND_FILE		"%s/%.*s/snd/chk/%s"		/*  BASE/CHANID/snd/chk/filename			*/
#define CLM_DATA_SND_FILE       "%s/%.*s/snd/data/%s.DAT"	/*	BASE/CHANID/snd/data/filename			*/
#define CLM_RZT_SND_SUCESS      "%s/%.*s/snd/rslt/%s/%s.rss"	/*	BASE/CHANID/snd/rslt/YYYYMMDD/filename	*/
#define CLM_RZT_SND_FAIL        "%s/%.*s/snd/rslt/%s/%s.rsf"	/*	BASE/CHANID/snd/rslt/YYYYMMDD/filename	*/
#define CLM_COMPLETE_SND_FILE	"%s/%.*s/snd/cmpl/%s/%s"	/*	BASE/CHANID/snd/cmpl/YYYYMMDD/filename	*/
#define CLM_WORK_SND_FILE		"%s/%.*s/snd/work/%s"		/*	BASE/CHANID/snd/work/filename			*/


#endif


#endif


#endif
