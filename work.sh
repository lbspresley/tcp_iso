# input : $ROME_HOME/trace/*.trc
realdata()
{
	awk 'BEGIN{
		enc=0
		linecnt=0
  }
	function prt_xml(str){
		gsub("admi", "\033[35madmi\033[0m", str)
		gsub("camt", "\033[35mcamt\033[0m", str)
		gsub("pacs", "\033[35mpacs\033[0m", str)

		gsub("MsgTpCd", "\033[33mMsgTpCd\033[0m", str)
		gsub("BizMsgIdr", "\033[33mBizMsgIdr\033[0m", str)
		gsub("SecurityHandshake", "\033[33mSecurityHandshake\033[0m", str)

		#gsub("AppHdr", "\033[33mMAppHdr\033[0m", str)
		#gsub("Document", "\033[33mMDocument\033[0m", str)
		gsub("<h:AppHdr", "\n<h:\033[33mMAppHdr\033[0m", str)
		gsub("<AppHdr", "\n<\033[33mMAppHdr\033[0m", str)
		gsub("<Document", "\n<\033[33mMDocument\033[0m", str)
  }
  {
		if (NF == 0 && linecnt>0 ){
			printf "\n"
			if (enc== 0 ){
				for (i=0;i<linecnt;i++){ print lines[i] }
				full=""
				for (i=3;i<linecnt-1;i++){ 
					str = substr(lines[i], 58)
					full = sprintf( "%s%s", full, str)
				}
				prt_xml(full)
			}
			linecnt=0
		} else {
			if( /000 :/ ) {
				if ($NF ~ /bwh:Bokwire/ || $NF ~ /h:AppHdr/ || $NF ~ /xmlns/) { enc=0 } else {enc=1}
			}
			lines[linecnt++]=$0
		}
  }' $@
}

xcut()
{
	awk '{
		if (substr($1, 1,3) !~ /</ || /data len: /){
			print
			next
		}
		gsub(">[ \t\r]*<", ">\n<")
		print
	} ' $@
}

xformat()
{
	awk '
	function dprint(n, str) {
		printf "%*s%s\n", n, "", str
	}

	BEGIN{
		depth=-1
		nextlevel=0
	}

	{
		if (substr($1, 1,3) !~ /</ || /data len: /){
			print
			next
		}
		tag=substr($0, 1, 2)
		if (tag == "</"){
			if(depth>0){depth--}
		} else {
			depth++
			if (nextlevel == 1){
				depth--
				nextlevel=0
			}
			if ($0 ~ "</") { nextlevel=1 }
		}
		dprint(depth, $0)
	} ' $@
}

fcut()
{
	INI_DIR=$CRUZMMS_JTRANS/resources/ini/tgrm
	DAT_DIR=$CRUZMMS_JTRANS/resources/data
	REP_DIR=$CRUZMMS_JTRANS/repository

	fcut_usage() {
		printf "Usage: fcut [-i tgrm-id] [-f fix-data-file]\n"
		printf "Registered TGRMs :\n"
		cnt=0
		for f in $(find $REP_DIR -type f -name "*I3.jar"); do
			let cnt=cnt+1
			printf "%2d : %s\n" $cnt $(basename $f _I3.jar)
		done
	}

	(( $# < 1 )) && fcut_usage && return

	tgrm=0
	tgrm_file=0

	set -- $(getopt f:i:h $*)
	while [ $1 != "--" ]; do
		case $1 in
			-i) tgrm=$2 && shift ;;
			-f) tgrm_file=$2 && shift ;;
			-h) fcut_usage && return ;;
		esac
		shift
	done

	if [ $tgrm = "0" ]; then
		fcut_usage
		return
	fi

	TGRM=${tgrm}_I3
	DAT_FILE=$DAT_DIR/$TGRM
	INI_FILE=$INI_DIR/${TGRM}.ini

	if [ $tgrm_file != "0" ]; then
		DAT_FILE=$tgrm_file
	fi

	if [ ! -r $DAT_FILE ]; then
		printf "File not found : %s\n" $DAT_FILE
		return
	fi

	if [ ! -r $INI_FILE ]; then
		printf "File not found : %s\n" $INI_FILE
		return
	fi

	fixcut $INI_FILE $DAT_FILE
}

fixcut()
{
	awk 'BEGIN{
		found=0
		FS="="
		POS=1
		fcount=0
	}
	function dprint (depth, idx, data){
		if(depth<0){depth=0}
		fname = sprintf("%*s%.15s", depth, "", names[idx])
		if(data == "G") {
			printf "%-3d:%-20s [G:%d]\n", idx, fname, flen[idx]
		} else {
			printf "%-3d:%-20s [%3d]: \033[7;36m%s\033[0m\n", idx, fname, flen[idx], data
		} 
  }

	function printField (depth, idx) {
		field_data = substr (data, POS, flen[idx])
		POS += flen[idx]
		dprint (depth, idx, field_data)
		return idx+1
  }

	function printGrid (depth, idx) {
		grid_size = flen[idx]
		dprint(depth, idx, "G")

		rtn_idx = idx+1
		for (g=0;g<grid_size;g++) {
			for (f=idx+1;f<fcount;) {
				if (parent[f] != idx){
					rtn_idx = f
					break
				}
				if (type[f] == "G" ){
					f=printGrid(depth+1, f)
				} else {
					f=printField(depth+1, f)
			  }
			}
		}
		return rtn_idx
  }

	{
		if (length($0) > 100) {data=$0}
		if ($1 == "[field]") {found=1}
		if ($1 == "[desc]") {found=0}

		if (NF !=2 || found == 0) {next}
		if (found ==1 && $1 == "fieldcount") {fcount=$2}

		split($2, arr, ",")
		idx=$1
		name[idx]=arr[1]
		parent[idx]=arr[2]
		flen[idx]=arr[3]
		ftype[idx]=arr[4]
		fmin[idx]=arr[5]
	}

	END{
		for (i=1;i<=fcount;) {
			if (type[f] == "G" ){
				i=printGrid(0, i)
				break
			} 
			i=printField(0, i)
		}
	}' $@
}

dfile()
{
	DIR=$ROME_HOME/trace
	CH=oal2
	LINES=50
	spattern=0
	epattern=0
	data_count=5
	viewopt=0

	dfile_usage()
	{
		printf "Usage: dfile [-v] [-n CHID] [-l line] [-c data-count] [-s start] [-e end] [-h]\n"
	}

	set -- $(getopt vhc:s:e:n:l: $*)
	while [ $1 != "--" ]; do
		case $1 in
			-v) viewopt=1 ;;
			-h) dfile_usage && return ;;
			-n) CH=$2 && shift ;;
			-l) LINES=$2 && shift ;;
			-c) data_count=$2 && shift ;;
			-s) spattern=$2 && shift ;;
			-e) epattern=$2 && shift ;;
		esac
		shift
	done

	FILE=$(ls -alrt $DIR/${CH}*.trc | tail -1 | awk '{print $NF}')

	(( $viewopt == 1 )) && printf "File: %s\n" $FILE && return

	printf "%s\n" $FILE

	if [ $spattern != "0" ];then
		awk -v dcount=$data_count -v start_pattern=$spattern -v end_pattern=$epattern '
			BEGIN{
				found=0
			}
			{
				if($0 ~ start_pattern){found=1}
				if(found==0){next}

				if(found==1 && end_pattern != 0 && $0 ~ end_pattern){found=0}
				if(dcount<0){next}
				if(/Comment : /){dcount--}
				print
			}
		}' $FILE
	else
		tail -f $FILE
	fi | realdata
}

lfile()
{
	DIR=$ROME_HOME/log
	CH=oal2
	LINES=50
	viewopt=0

	lfile_usage()
	{
		printf "Usage: lfile [-v] [-n CHID] [-l line] [-h]\n"
	}

	set -- $(getopt vhn:l: $*)
	while [ $1 != "--" ]; do
		case $1 in
			-v) viewopt=1 ;;
			-h) lfile_usage && return ;;
			-n) CH=$2 && shift ;;
			-l) LINES=$2 && shift ;;
		esac
		shift
	done

	FILE=$(ls -alrt $DIR/${CH}*.log | tail -1 | awk '{print $NF}')

	(( $viewopt == 1 )) && printf "File: %s\n" $FILE && return

	printf "%s\n" $FILE

	tail -${LINES}f $FILE | colorview
}

colorview()
{
	awk '{
		if ($3 == "[W]"){
			printf "\033[35m%s\033[0m\n", $0
		} else if ($3 == "[E]"){
			printf "\033[31m%s\033[0m\n", $0
		} else {
			print
		} 
	}' $@
}

