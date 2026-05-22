#!/bin/bash

# check_encoding.sh - 파일 인코딩 확인 스크립트
# 사용법: check_encoding.sh <source_file>

if [ $# -eq 0 ]; then
    echo "사용법: $0 <source_file>"
    exit 1
fi

SOURCE_FILE="$1"

if [ ! -f "$SOURCE_FILE" ]; then
    echo "오류: 파일 '$SOURCE_FILE'을 찾을 수 없습니다."
    exit 1
fi

# 파일 인코딩 확인
ENCODING=$(file -bi "$SOURCE_FILE" | grep -o 'charset=[^;]*' | cut -d= -f2 | tr '[:upper:]' '[:lower:]')

echo "파일: $SOURCE_FILE"
echo "인코딩: $ENCODING"

# UTF-8이 아니면 EUC-KR로 간주
case "$ENCODING" in
    "utf-8"|"utf8"|"us-ascii"|"ascii")
        echo "UTF-8 호환 인코딩 - 기본 인코딩 사용"
        echo ""
        ;;
    *)
        echo "UTF-8이 아닌 인코딩 감지 - EUC-KR로 간주하여 finput-charset=EUC-KR 옵션 적용"
        echo "-finput-charset=EUC-KR"
        ;;
esac 