#!/bin/bash
export LIBPATH=/usr/lib:/opt/freeware/lib:/usr/local/lib:/usr/ccs/lib:/home/oracle/product/11.2.0/db_1/lib:/home/oracle/product/11.2.0/db_1/network/lib:/usr/lib:/home/knbfep/pgm/rome/lib:/home/knbfep/trans/tool/lib:/home/tmax/tmax/lib64
ICONV=/usr/bin/iconv

KR="IBM-1363"
[ $(uname -s) == "Linux" ] && KR="EUC-KR"

mktempname()
{
        if [ $(uname -s) == "Linux" ] ; then
                echo $(mktemp -u /tmp/iconv.XXXXXX.out)
        else
                echo /tmp/iconv.$(date +"%H%M%S")$(awk 'BEGIN { srand(); printf "%d", rand() * 1e9) }').out
        fi
}

conv()
{
        OUTFILE=$(mktempname)

        FROM=$KR
        TO="UTF-8"
        if (( $1 == 1 )); then
                FROM="UTF-8"
                TO=$KR
        fi
        #echo $ICONV -f $FROM -t $TO $2 
        $ICONV -f $FROM -t $TO $2 > $OUTFILE 2>/dev/null
        if (( $? != 0 )); then
                echo FAIL
                exit 3
        fi

        printf "%s" "$OUTFILE"
        #rm -f $OUTFILE
        exit 0
}

iconv_usage()
{
        echo FAIL
        #printf "Usage: iconv type infile\n"
        exit 1
}

(( $# < 2 )) && iconv_usage
[ ! -r $2 ] && iconv_usage 

conv $@


