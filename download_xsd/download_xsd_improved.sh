#!/bin/bash

# XML namespace에 해당하는 XSD 다운로드 스크립트 (개선된 버전)
# 사용법: ./download_xsd_improved.sh <xml_file>

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

# namespace 추출 (더 정확한 방법)
NAMESPACES=$(grep -o 'xmlns:[^=]*="[^"]*"' "$XML_FILE" | sed 's/xmlns:[^=]*="\([^"]*\)"/\1/')

echo "발견된 namespace:"
echo "$NAMESPACES"
echo ""

# XSD 다운로드 시도
for ns in $NAMESPACES; do
    if [[ $ns == *"iso:20022"* ]]; then
        # namespace에서 메시지 타입 추출
        MSG_TYPE=$(echo "$ns" | sed 's/.*xsd:\([^:]*\)$/\1/')
        
        if [ -n "$MSG_TYPE" ]; then
            echo "다운로드 시도 중: $MSG_TYPE.xsd"
            
            # 여러 소스에서 다운로드 시도
            SUCCESS=false
            
            # 1. ISO 20022 공식 사이트 (직접 링크)
            echo "  - ISO 20022 공식 사이트에서 시도..."
            curl -s -L "https://www.iso20022.org/sites/default/files/documents/D7/ISO20022/Repository/$MSG_TYPE.xsd" -o "$MSG_TYPE.xsd"
            
            if [ -s "$MSG_TYPE.xsd" ] && ! grep -q "<!DOCTYPE html>" "$MSG_TYPE.xsd"; then
                echo "  ✓ $MSG_TYPE.xsd 다운로드 완료 (ISO 20022)"
                SUCCESS=true
            else
                rm -f "$MSG_TYPE.xsd"
                echo "  ✗ ISO 20022 사이트에서 실패"
            fi
            
            # 2. GitHub에서 검색
            if [ "$SUCCESS" = false ]; then
                echo "  - GitHub에서 검색 시도..."
                curl -s "https://raw.githubusercontent.com/search?q=$MSG_TYPE.xsd+filename:$MSG_TYPE.xsd" -o /tmp/github_search.html
                if grep -q "raw.githubusercontent.com" /tmp/github_search.html; then
                    echo "  ✓ GitHub에서 찾음 (수동 다운로드 필요)"
                fi
                rm -f /tmp/github_search.html
            fi
            
            # 3. 로컬에서 검색
            if [ "$SUCCESS" = false ]; then
                echo "  - 로컬 파일 시스템에서 검색..."
                find . -name "*$MSG_TYPE*.xsd" 2>/dev/null | head -1 | while read file; do
                    if [ -n "$file" ]; then
                        cp "$file" "$MSG_TYPE.xsd"
                        echo "  ✓ 로컬에서 복사: $file"
                        SUCCESS=true
                    fi
                done
            fi
            
            if [ "$SUCCESS" = false ]; then
                echo "  ✗ $MSG_TYPE.xsd 다운로드 실패"
                echo "  수동으로 다운로드하거나 다른 소스를 확인하세요."
            fi
        fi
    fi
done

echo ""
echo "다운로드 완료!"
echo ""
echo "참고:"
echo "1. ISO 20022 공식 사이트: https://www.iso20022.org/"
echo "2. 한국은행 사이트: https://www.bok.or.kr/"
echo "3. SWIFT 사이트: https://www.swift.com/"
