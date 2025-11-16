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
	view_flag=0

	set -- $(getopt vf:i:h $*)
	while [ $1 != "--" ]; do
		case $1 in
			-v) view_flag=1 ;;
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

	(( $view_flag == 1 )) && printf "INI : %s\n" $INI_FILE 
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
			for (f=idx+1;f<=fcount;) {
				if (parent[f] != idx){
					rtn_idx = f
					break
				}
				if (ftype[f] == "G" ){
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
			if (parent[i] != 0 ){
				i++
				continue
			}
			if (type[i] == "G" ){
				i=printGrid(0, i)
			} else {
				i=printField(0, i)
			}
		}
		printf "Data Len(%d), Parsing Len(%d)\n", length(data), POS-1
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
	editopt=0

	dfile_usage()
	{
		printf "Usage: dfile [-v] [-V] [-n CHID] [-l line] [-c data-count] [-s start] [-e end] [-h]\n"
	}

	set -- $(getopt vhc:s:e:n:l: $*)
	while [ $1 != "--" ]; do
		case $1 in
			-V) editopt=1 ;;
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

	(( $editopt == 1 )) && vi $FILE && return
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

chktrs_all()
{
	INI=$CRUZMMS_JTRANS/resources/ini
	TGRM=$INI/tgrm
	RULE=$INI/rule

	chktrs_usage()
	{
		printf "Usage: chktrs_all [-R resource-directory]\n"
	}

	set -- $(getopt R: $*)
	while [ $1 != "--" ]; do
		case $1 in
			-R) INI=$2 && shift ;;
		esac
		shift
	done

	if [ ! -d $INI ]; then
		printf "Directory not found : %s\n" $INI
		return
	fi

	find $INI/rule -type f -name "*_I[13].ini" | while read file; do
		chktrs -i $(basename $file .ini) -R $INI
	done
}

chktrs()
{
	chktrs_usage()
	{
		printf "Usage: chktrs [-i rule-name] [-R resource-directory]\n"
	}

	INI=$CRUZMMS_JTRANS/resources/ini
	param="0"

	set -- $(getopt hi:R: $*)
	while [ $1 != "--" ]; do
		case $1 in
			-h) chktrs_usage && return ;;
			-R) INI=$2 && shift ;;
			-i) param=$2 && shift ;;
		esac
		shift
	done

	if [ $param == "0" ]; then
		chktrs_usage
		return
	fi

	if [ ! -d $INI ]; then
		printf "Directory not found : %s\n" $INI
		return
	fi

	ifname=$(basename $param .ini)
	rule_file=$INI/rule/${ifname}.ini
	src_file=$INI/tgrm/${ifname}.ini
	tgt_file=$INI/tgrm/$(echo $ifname| awk '{gsub("_I1", "_I2"); gsub("_I3", "_I4"); print}').ini


	# check files
	[ ! -r $rule_file ] && printf "File not found : %s\n" $rule_file && chktrs_usage && return
	[ ! -r $src_file ] && printf "File not found : %s\n" $src_file && chktrs_usage && return
	[ ! -r $tgt_file ] && printf "File not found : %s\n" $tgt_file && chktrs_usage && return

	FILES="$rule_file $tgt_file $src_file"

	awk 'BEGIN{
		FS="="
		rule="rule"
		infile=""
		src="src"
		tgt="tgt"
		phase="init"
		parse=1
	}
	{
		if(infile != FILENAME){
			if(infile == ""){
				phase=rule
			} else {
				if( FILENAME ~ /_I2.ini/ || FILENAME ~ /_I4.ini/){
					phase=tgt
				} else {
					phase=src
				}
			}

			infile=FILENAME
			next
		}

		gsub(" ", "")
		if ($1 == "rulecount"){
			fcount[phase]=$2
			next
		}

		if ($0=="[desc]" || $0 == "[meta]"){
			parse=0
			next
		}

		if (phase==rule && $1 >= 1 && $1 <= fcount[phase]){
		 	split($2, fconfig, ",")
			t_field[$1]=fconfig[1]
			s_field[$1]=fconfig[2]
			next
		}

		if ($1 == "type") {
			parse=1
			types[phase]=$2
			next
		}
		if ($1 == "encoding") {
			encoding[phase]=$2
			next
		}
		if ($1 == "fieldcount") {
			fcount[phase]=$2
			next
		}

		if( parse==0 || phase =="init" || phase==rule) {next}

		if (phase==src && $1 >= 1 && $1 <= fcount[phase]){
		 	split($2, fconfig, ",")
			src_name[$1]=fconfig[1]
			src_len[$1]=fconfig[3]
			src_type[$1]=fconfig[4]
			next
		}

		if (phase==tgt && $1 >= 1 && $1 <= fcount[phase]){
		 	split($2, fconfig, ",")
			tgt_name[$1]=fconfig[1]
			tgt_len[$1]=fconfig[3]
			tgt_type[$1]=fconfig[4]
			next
		}
	}
	function check_rule( r, t, s) {
		#printf "[%3d] [%2s] %-15s %3d <-- %3d\n", r, tgt_type[t], tgt_name[t], t, s
		if (tgt_type[t] != src_type[s]) {
			if ( !( (tgt_type[t] =="A" || tgt_type[t] =="AT") &&
				    (src_type[s] =="A" || src_type[s] =="AT") 
				  ) 
			) {
				printf "Invalid Type   : Rule (%d) Target(%3d:%2s) <-- Source(%3d:%2s)\n", r, t, tgt_type[t], s, src_type[s] 
			}
		}
		if (tgt_len[t] != src_len[s]) {
			printf "Invalid Length : Rule (%d) Target(%3d:%3d) <-- Source(%3d:%3d)\n", r, t, tgt_len[t], s, src_len[s] 
		}
		if (tgt_name[t] != src_name[s]) {
			if ( tgt_name[t] !~ "xmlns"  && src_name[s] !~ "xmlns" ) {
				printf "Invalid Name   : Rule (%d) Target(%3d:%-15s) <-- Source(%3d:%-15s)\n", r, t, tgt_name[t], s, src_name[s] 
			}
		}
	}
	END{
		printf "Encoding : %s --> %s\n", encoding[src], encoding[tgt]

		for(i=1;i<=fcount[rule];i++) {
			check_rule( i, t_field[i], s_field[i])
		}
	}' $FILES

}