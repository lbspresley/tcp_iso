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

