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
		s=""
		for (i=0;i<n;i++) {s=sprintf("  %s", s) }
		printf "%s%s\n", s, str
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

fixcut()
{
	awk 'BEGIN{
		found=0
		FS="="
	}
	{
		if (length($0) > 100) {data=$0}
		if ($1 == "[field]") {found=1}
		if ($1 == "[desc]") {found=0}
		if (NF !=2 || found == 0) {next}
		if ($1 == "fieldcount") {fcount=$2}

		idx=$1
		split($2, arr, ",")
		name[idx]=arr[1]
		parent[idx]=arr[2]
		flen[idx]=arr[3]
		ftype[idx]=arr[4]
		fmin[idx]=arr[5]
	}

    # todo : fix this function
    # 1. check parentIdx
	# 2. check grid's min occur which is const value or variable value
	########################################################
	# ini sample
	#[field]
	# fieldcount=15
	# 1=Flex_grid_1_count     , 0, 10 , C  , 1
	# 2=Flex_grid_1           , 0, 4  , G  , %1 , 2
	# 3=Flex_grid_ele1        , 2, 10 , A  , 1
	########################################################
	function print_GridField(i, pos, parentIdx) {
		minOccur=fmin[i]
		printf "%3d:%-15s:G[%3d]\n", i, name[i], minOccur
		for (j=i+1;j<=fcount;j++) {
			if (parent[j] == parentIdx) {
				print_field(j, pos)
			}
		}
	}

	function print_field(i, pos) {
		if (ftype[i] != "G") {
			value=substr(data, pos, flen[i])
			if (ftype[i] == "C") { gridCount[i]=value }
			printf "%3d:%-15s:%c[%3d]:\033[5;35m%s\033[0m\n", i, name[i], ftype[i], flen[i], value)
			pos+=flen[i]
		} else {
			minOccur=fmin[i]
			if (substr(minOccur, 1, 1) == "%") {
				countRef=substr(minOccur, 2)
				minOccur=gridCount[countRef]
			}
			printf "%3d:%-15s:G[%3d]\n", i, name[i], minOccur
			#print_GridField(i, pos, parent[i], minOccur)
		}
	}

	END{
		pos=1
		for (i=1;i<=fcount;i++) {
			print_field(i, pos)
		}
	}' $@
}

dfile()
{
	spattern=0
	epattern=0

	if [ $spattern != "0" ];then
		awk -v start_pattern=$spattern -v end_pattern=$epattern '
			BEGIN{
				found=0
			}
			{
				if($0 ~ start_pattern){found=1}
				if(found==1 && end_pattern != 0 && $0 ~ end_pattern){found=0}
				if(found==0){next}
				print
			}
		}' $FILE
	else
		tail -f $FILE
	fi | realdata
}
