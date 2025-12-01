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
		awk -v dcount=$data_count -v start_pattern=$spattern -v end_pattern=$epattern 
		' BEGIN{
			found=0
		}
		{
			if($0 ~ start_pattern){found=1}
			if(found==0){next}

			if(found==1 && end_pattern != 0 && $0 ~ end_pattern){found=0}
			if(dcount<0){next}
			if(/Comment : /){dcount--}
			print
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

	lfile_usage() {
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

	chktrs_usage() {
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
	chktrs_usage() {
		printf "Usage: chktrs [-v] [-i rule-name] [-R resource-directory]\n"
	}

	VIEW=0
	INI=$CRUZMMS_JTRANS/resources/ini
	param="0"

	set -- $(getopt vhi:R: $*)
	while [ $1 != "--" ]; do
		case $1 in
			-h) chktrs_usage && return ;;
			-v) VIEW=1 ;;
			-R) INI=$2 && shift ;;
			-i) param=$2 && shift ;;
		esac
		shift
	done

	if [ $VIEW == 1 ]; then
		DIR=$INI/rule
		printf "Rule Directory : %s\n\n" "$DIR"
		CNT=0
		for f in $DIR/*.ini; do
			CNT=$(( $CNT + 1 ))
			printf "%3d : %s\n" $CNT $(basename $f .ini)
		done
		return
	fi

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
			if(infile ~ /rule/){
				phase=rule
			} else if( FILENAME ~ /_I2.ini/ || FILENAME ~ /_I4.ini/){
					phase=tgt
			} else {
				phase=src
			}
			infile=FILENAME
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

		if ($1 >= 1 && $1 <= fcount[phase]){
			if (phase==src) {
				split($2, fconfig, ",")
				src_name[$1]=fconfig[1]
				src_len[$1]=fconfig[3]
				src_type[$1]=fconfig[4]
				next
			}

			if (phase==tgt ) {
				split($2, fconfig, ",")
				tgt_name[$1]=fconfig[1]
				tgt_len[$1]=fconfig[3]
				tgt_type[$1]=fconfig[4]
				next
			}
		}
	}
	function check_rule( r, t, s) {
		#printf "[%3d] [%2s] %-15s %3d <-- %3d\n", r, tgt_type[t], tgt_name[t], t, s
		if (tgt_type[t] != src_type[s]) {
			if ( !( (tgt_type[t] =="A" || tgt_type[t] =="AT") &&
				    (src_type[s] =="A" || src_type[s] =="AT") 
				  ) 
			) {
				printf "Invalid Type   : Rule(%3d) Target(%3d:%2s) <-- Source(%3d:%2s)\n", r, t, tgt_type[t], s, src_type[s] 
			}
		}
		if (tgt_len[t] != src_len[s]) {
			printf "Invalid Length : Rule(%3d) Target(%3d:%3d) <-- Source(%3d:%3d)\n", r, t, tgt_len[t], s, src_len[s] 
		}
		if (tgt_name[t] != src_name[s]) {
			if ( tgt_name[t] !~ "xmlns"  && src_name[s] !~ "xmlns" ) {
				printf "Invalid Name   : Rule(%3d) Target(%3d:%-15s) <-- Source(%3d:%-15s)\n", r, t, tgt_name[t], s, src_name[s] 
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

gack ()
{
	VERSION="v3.7.0"

	# 기본 변수 설정
	SHOW_FILENAME=1
	SHOW_LINENO=1
	IGNORE_CASE=0
	INVERT_MATCH=0
	FILES_ONLY=0
	COUNT_ONLY=0
	RECURSIVE=1
	COLOR=1
	CONTEXT_BEFORE=0
	CONTEXT_AFTER=0
	MAX_COUNT=-1
	PATTERN=""
	FILES=()
	SHOW_FILENAME_EXPLICIT=0

	# 색상 코드
	COLOR_RESET="\033[0m"
	COLOR_FILENAME="\033[1;32m"
	COLOR_LINENO="\033[1;33m"
	COLOR_MATCH="\033[30;43m"

	# 도움말 출력
	show_help() {
		printf "Usage: ack [options] PATTERN [FILE...]\n\n"
		printf "Options:\n"
		printf "\t%-30s %s\n" "-i, --ignore-case" "Ignore case distinctions"
		printf "\t%-30s %s\n" "-v, --invert-match" "Invert match"
		printf "\t%-30s %s\n" "-l, --files-with-matches" "Only print filenames"
		printf "\t%-30s %s\n" "-c, --count" "Print count of matching lines"
		printf "\t%-30s %s\n" "-n, --no-recurse" "No descending into subdirectories"
		printf "\t%-30s %s\n" "-H, --with-filename" "Print filename (default)"
		printf "\t%-30s %s\n" "-h, --no-filename" "Suppress filename prefix"
		printf "\t%-30s %s\n" "-A NUM, --after-context=NUM" "Print NUM lines of trailing context"
		printf "\t%-30s %s\n" "-B NUM, --before-context=NUM" "Print NUM lines of leading context"
		printf "\t%-30s %s\n" "-C NUM, --context=NUM" "Print NUM lines of context"
		printf "\t%-30s %s\n" "--color" "Force color output"
		printf "\t%-30s %s\n" "--nocolor" "Disable color output"
		printf "\t%-30s %s\n" "-m NUM, --max-count=NUM" "Stop after NUM matches per file"
		printf "\t%-30s %s\n" "--version" "Show version"
		printf "\t%-30s %s\n" "--help" "Show this help\n"
	}

	# 옵션 파싱
	parse_options() 
	{
		#set -- $(getopt ivlncHhA:B:C:m: $*)

		while [[ $# -gt 0 ]]; do
			case "$1" in
				-i|--ignore-case)
					IGNORE_CASE=1
					;;
				-v|--invert-match)
					INVERT_MATCH=1
					;;
				-l|--files-with-matches)
					FILES_ONLY=1
					;;
				-c|--count)
					COUNT_ONLY=1
					;;
				-n|--no-recurse)
					RECURSIVE=0
					;;
				-H|--with-filename)
					SHOW_FILENAME=1
					SHOW_FILENAME_EXPLICIT=1
					;;
				-h|--no-filename)
					SHOW_FILENAME=0
					SHOW_FILENAME_EXPLICIT=1
					;;
				-A|--after-context)
					CONTEXT_AFTER="$2"
					shift 
					;;
				--after-context=*)
					CONTEXT_AFTER="${1#*=}"
					;;
				-B|--before-context)
					CONTEXT_BEFORE="$2"
					shift 
					;;
				--before-context=*)
					CONTEXT_BEFORE="${1#*=}"
					;;
				-C|--context)
					CONTEXT_BEFORE="$2"
					CONTEXT_AFTER="$2"
					shift 
					;;
				--context=*)
					CONTEXT_VAL="${1#*=}"
					CONTEXT_BEFORE="$CONTEXT_VAL"
					CONTEXT_AFTER="$CONTEXT_VAL"
					;;
				-m|--max-count)
					MAX_COUNT="$2"
					shift 
					;;
				--max-count=*)
					MAX_COUNT="${1#*=}"
					;;
				--color|--colour)
					COLOR=1
					;;
				--nocolor|--nocolour)
					COLOR=0
					;;
				--version)
					echo "ack $VERSION"
					return 
					;;
				--help)
					show_help
					return
					;;
				--)
					break
					;;
				-*)
					echo "Unknown option: $1" >&2
					show_help
					return
					;;
				*)
					if [ -z "$PATTERN" ]; then
						PATTERN="$1"
					else
						FILES+=("$1")
					fi
					;;
			esac
			shift
		done
	}

	# 파일에서 패턴 검색 (awk 사용)
	search_in_file() 
	{
			local file="$1"
			local pattern="$2"
			
			awk -v file="$file" \
					-v pattern="$pattern" \
					-v ignore_case="$IGNORE_CASE" \
					-v invert="$INVERT_MATCH" \
					-v files_only="$FILES_ONLY" \
					-v count_only="$COUNT_ONLY" \
					-v show_filename="$SHOW_FILENAME" \
					-v color="$COLOR" \
					-v max_count="$MAX_COUNT" \
			'
			function ci_match(line, pat, pat_ci, igcase) {
				if (igcase != 1) {
					return match(line, pat)
				}

				return match(tolower(line), pat_ci)
			}

			function ci_highlight(line, pat, pat_ci, igcase, replacement) {
				if (igcase != 1) {
					gsub(pat, replacement, line)
					return line
				}
				lower_line = tolower(line)
				result=""
				pos=1
				while (match(substr(lower_line, pos), pat_ci)) {
					start = RSTART-1
					result = result substr(line, pos, start) "\033[30;43m" substr(line, pos+start, RLENGTH) "\033[0m"
					pos += start + RLENGTH
				}
				return result substr(line, pos)
			}

			BEGIN { 
				pattern_ci=tolower(pattern)
				match_count=0
				prt_file=0
				c_pattern=sprintf("\033[30;43m%s\033[0m", pattern)
			}
			{
				matched=0
				if (ci_match($0, pattern, pattern_ci, ignore_case)) { matched=1 }
					
				if (invert == 1) { matched=!matched }
					
				if (matched) {
					match_count++
							
					if (files_only == 1) {
						print file
						exit 0
					} 

					if (show_filename == 1  && prt_file != file) {
						printf "\n\033[1;32m%s\033[0m\n", file
						prt_file = file;
					}

					if (color == 1) {
						highlighted=ci_highlight($0, pattern, pattern_ci, ignore_case, c_pattern)
						printf "\033[1;33m%d\033[0m: %s\n", NR, highlighted
					} else {
						printf "%d: %s\n", NR, $0
					}
							
					if (max_count > 0 && match_count >= max_count) {
						exit 0
					}
				}
			}
			END {
				if (count_only != 1) {
					exit (match_count > 0 ? 1 : 0)
				}

				if (show_filename == 1) {
					if (color == 1) {
						printf "\033[1;32m%s\033[0m:%d\n", file, match_count
					} else {
						printf "%s:%d\n", file, match_count
					}
				} else {
					printf "%d\n", match_count
				}
			}
			' "$file" 2>/dev/null
			
			return $?
	}

	# 컨텍스트를 포함한 검색
	search_with_context() 
	{
		local file="$1"
		local pattern="$2"
			
		awk -v file="$file" \
			-v pattern="$pattern" \
			-v ignore_case="$IGNORE_CASE" \
			-v invert="$INVERT_MATCH" \
			-v show_filename="$SHOW_FILENAME" \
			-v color="$COLOR" \
			-v before="$CONTEXT_BEFORE" \
			-v after="$CONTEXT_AFTER" \
			-v max_count="$MAX_COUNT" \
		' 
		function ci_match(line, pat, pat_ci, igcase) {
			if (igcase != 1) {
				return match(line, pat)
			}

			return match(tolower(line), pat_ci)
		}

		function ci_highlight(line, pat, pat_ci, igcase, replacement) {
			if (igcase != 1) {
				gsub(pat, replacement, line)
				return line
			}
			lower_line = tolower(line)
			result=""
			pos=1
			while (match(substr(lower_line, pos), pat_ci)) {
				start = RSTART-1
				result = result substr(line, pos, start) "\033[30;43m" substr(line, pos+start, RLENGTH) "\033[0m"
				pos += start + RLENGTH
			}
			return result substr(line, pos)
		}

		BEGIN { 
			match_count=0
			after_pending=0
			last_printed=0
			prt_file="0"
			c_pattern=sprintf("\033[30;43m%s\033[0m", pattern)
			pattern_ci=tolower(pattern)
		}
		{
			matched=0
			if (ci_match($0, pattern, pattern_ci, ignore_case)) { matched=1 }
			if (invert == 1) { matched=!matched }
			if (matched) {
				match_count++
					
				# 구분선 출력
				if (before > 0 && last_printed > 0 && NR - last_printed > before + 1) { print "--" }

				if (show_filename == 1 && prt_file != file) {
					printf "\033[1;32m%s\033[0m\n", file
					prt_file = file
				}
							
				# before 컨텍스트 출력
				if (before > 0 && NR > 1) {
					start_line=NR - before
					if (last_printed>0 && NR-last_printed<=before) {
						start_line=last_printed+1
					}
					if (start_line < 1) start_line=1
					for (i=start_line; i<NR; i++) {
						if (color == 1) {
							printf "\033[1;33m%d\033[0m- %s\n", i, lines[i]
						} else {
							printf "%d- %s\n", i, lines[i]
						}
					}
				}
							
				# 매칭 라인 출력
				if (color == 1) {
					highlighted=ci_highlight($0, pattern, pattern_ci, ignore_case, c_pattern)
					printf "\033[1;33m%d\033[0m: %s\n", NR, highlighted
				} else {
					#printf "%d: %s\n", NR, $0
					printf "%s\n", $0
				}
							
				last_printed=NR
				after_pending=after
							
				if (max_count > 0 && match_count >= max_count) {
					exit 0
				}
			} else {
				# after 컨텍스트 출력
				if (after_pending > 0) {
					if (color == 1) {
						printf "\033[1;33m%d\033[0m- %s\n", NR, $0
					} else {
						printf "%d- %s\n", NR, $0
					}
					after_pending--
					last_printed=NR
				}
			}
					
			# 라인 버퍼에 저장 (before 컨텍스트용)
			if (before > 0) {
				lines[NR]=$0
				if (NR > before) {
					delete lines[NR - before]
				}
			}
		}
		END {
			exit (match_count > 0 ? 1 : 0)
		}
		' "$file" 2>/dev/null
			
		return $?
	}

	# 메인 함수
	main() 
	{
		# 옵션 파싱
		parse_options "$@"
			
		# 패턴이 없으면 도움말 출력
		if [ -z "$PATTERN" ]; then
			show_help
			return 1
		fi
			
		# 파일 목록이 없으면 현재 디렉토리 사용
		local reading_stdin=0
		if [ ${#FILES[@]} -eq 0 ]; then
			if [ ! -t 0 ]; then
				FILES=("/dev/stdin")
				reading_stdin=1
			else
				FILES=(".")
			fi
		fi

		if [ $reading_stdin -eq 1 ] && [ "$SHOW_FILENAME_EXPLICIT" -eq 0 ]; then
			SHOW_FILENAME=0
		fi
			
		local total_matches=0
		local files_searched=0
		local found_match=0
			
		# 각 파일/디렉토리 처리
		for target in "${FILES[@]}"; do
			if [ ! -e "$target" ]; then
				echo "$target: No such file or directory" >&2
				continue
			fi
					
			if [ -d "$target" ]; then
				# 디렉토리 처리
				local file_list=()
				if [ "$RECURSIVE" -eq 1 ]; then
					while IFS= read -r -d '' file; do
						if [ -f "$file" ] && [ -r "$file" ]; then
							file_list+=("$file")
						fi
					done < <(find "$target" -type f -print0 2>/dev/null)
				else
					for file in "$target"/*; do
						if [ -f "$file" ] && [ -r "$file" ]; then
							file_list+=("$file")
						fi
					done
				fi
							
				for file in "${file_list[@]}"; do
					files_searched=$((files_searched + 1))
					if [ "$CONTEXT_BEFORE" -gt 0 ] || [ "$CONTEXT_AFTER" -gt 0 ]; then
						search_with_context "$file" "$PATTERN" 
					else
						search_in_file "$file" "$PATTERN" 
					fi
					if (( $? == 1 )); then
						found_match=1
						#echo
					fi
				done
			else
				files_searched=$((files_searched + 1))
				if [ "$CONTEXT_BEFORE" -gt 0 ] || [ "$CONTEXT_AFTER" -gt 0 ]; then
					search_with_context "$target" "$PATTERN"
				else
					search_in_file "$target" "$PATTERN"
				fi
				if (( $? == 1 )); then
					found_match=1
					#echo
				fi
			fi
		done
			
		# 결과에 따라 종료 코드 반환
		if [ "$found_match" -eq 1 ]; then
			return 1
		else
			return 0
		fi
	}

	# 스크립트 실행
	main "$@"
}

