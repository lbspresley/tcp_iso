#!/bin/bash

# XML 파일을 분석하여 기본적인 XSD 생성 스크립트
# 사용법: ./generate_xsd.sh <xml_file>

if [ $# -eq 0 ]; then
    echo "사용법: $0 <xml_file>"
    echo "예시: $0 std.xml"
    exit 1
fi

XML_FILE="$1"
OUTPUT_XSD="${XML_FILE%.xml}.xsd"

if [ ! -f "$XML_FILE" ]; then
    echo "오류: 파일 '$XML_FILE'을 찾을 수 없습니다."
    exit 1
fi

echo "XML 파일 '$XML_FILE'을 분석하여 XSD 생성 중..."

# XML에서 namespace 추출
NAMESPACES=$(grep -o 'xmlns:[^=]*="[^"]*"' "$XML_FILE" | sed 's/xmlns:\([^=]*\)="\([^"]*\)"/\1=\2/')

# XSD 헤더 생성
cat > "$OUTPUT_XSD" << EOF
<?xml version="1.0" encoding="UTF-8"?>
<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema"
EOF

# namespace 추가
for ns in $NAMESPACES; do
    PREFIX=$(echo "$ns" | cut -d'=' -f1)
    URI=$(echo "$ns" | cut -d'=' -f2)
    echo "           xmlns:$PREFIX=\"$URI\"" >> "$OUTPUT_XSD"
done

cat >> "$OUTPUT_XSD" << EOF
           elementFormDefault="qualified"
           targetNamespace="urn:bok:std:iso:20022:xsd:001">

EOF

# XML 구조 분석 및 XSD 생성
echo "    <!-- XML 구조 분석 결과 -->" >> "$OUTPUT_XSD"

# 루트 엘리먼트 찾기
ROOT_ELEMENT=$(grep -o '<[^/][^:]*:' "$XML_FILE" | head -1 | sed 's/<\([^:]*\):/\1:/')
if [ -z "$ROOT_ELEMENT" ]; then
    ROOT_ELEMENT=$(grep -o '<[^/][^>]*>' "$XML_FILE" | head -1 | sed 's/<\([^>]*\)>/\1/')
fi

echo "    <xs:element name=\"$(echo $ROOT_ELEMENT | cut -d':' -f2)\" type=\"$(echo $ROOT_ELEMENT | cut -d':' -f2)Type\"/>" >> "$OUTPUT_XSD"

# 복잡한 타입 정의 생성
echo "" >> "$OUTPUT_XSD"
echo "    <xs:complexType name=\"$(echo $ROOT_ELEMENT | cut -d':' -f2)Type\">" >> "$OUTPUT_XSD"
echo "        <xs:sequence>" >> "$OUTPUT_XSD"

# 하위 엘리먼트들 찾기
grep -o '<[^/][^>]*>' "$XML_FILE" | sed 's/<\([^>]*\)>/\1/' | while read element; do
    if [[ $element != $ROOT_ELEMENT ]]; then
        ELEMENT_NAME=$(echo $element | cut -d':' -f2)
        if [ -n "$ELEMENT_NAME" ]; then
            echo "            <xs:element name=\"$ELEMENT_NAME\" type=\"xs:string\" minOccurs=\"0\"/>" >> "$OUTPUT_XSD"
        fi
    fi
done

echo "        </xs:sequence>" >> "$OUTPUT_XSD"
echo "    </xs:complexType>" >> "$OUTPUT_XSD"

echo "</xs:schema>" >> "$OUTPUT_XSD"

echo "✓ XSD 파일 생성 완료: $OUTPUT_XSD"
echo ""
echo "생성된 XSD 파일을 검토하고 필요에 따라 수정하세요."
