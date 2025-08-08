#!/bin/bash

# XML namespace에 해당하는 XSD 다운로드 스크립트
# 사용법: ./download_xsd.sh <xml_file>

if [ $# -eq 0 ]; then
    echo "사용법: $0 <xml_file>"
    echo "예시: $0 std.xml"
    exit 1
fi

XML_FILE="$1"

if [ ! -f "$XML_FILE" ]; then
    echo "오류: 파일 '$XML_FILE'을 찾을 수 없습니다."
    exit 1
fi

echo "XML 파일 '$XML_FILE'에서 namespace를 추출 중..."

# namespace 추출
NAMESPACES=$(grep -o 'xmlns:[^=]*="[^"]*"' "$XML_FILE" | sed 's/xmlns:[^=]*="\([^"]*\)"/\1/')

echo "발견된 namespace:"
echo "$NAMESPACES"
echo ""

# ISO 20022 공식 사이트에서 XSD 다운로드
for ns in $NAMESPACES; do
    if [[ $ns == *"iso:20022"* ]]; then
        # namespace에서 메시지 타입 추출
        MSG_TYPE=$(echo "$ns" | sed 's/.*xsd:\([^:]*\)$/\1/')
        
        if [ -n "$MSG_TYPE" ]; then
            echo "다운로드 중: $MSG_TYPE.xsd"
            
            # ISO 20022 공식 사이트에서 다운로드 시도
            curl -s "https://www.iso20022.org/sites/default/files/documents/D7/ISO20022/Repository/$MSG_TYPE.xsd" -o "$MSG_TYPE.xsd"
            
            if [ -s "$MSG_TYPE.xsd" ]; then
                echo "✓ $MSG_TYPE.xsd 다운로드 완료"
            else
                echo "✗ $MSG_TYPE.xsd 다운로드 실패"
                rm -f "$MSG_TYPE.xsd"
            fi
        fi
    fi
done

echo ""
echo "다운로드 완료!"
