# XML Namespace에서 XSD 확인 및 다운로드 방법

## 1. XML에서 Namespace 확인

### 방법 1: 수동 확인
XML 파일에서 `xmlns:` 속성을 찾아 namespace를 확인합니다.

```xml
<bwh:BokwireEnvelope xmlns:bwh="urn:bok:std:iso:20022:xsd:001">
    <h:AppHdr xmlns:h="urn:iso:std:iso:20022:tech:xsd:head.001.001.03">
```

### 방법 2: 스크립트 사용
```bash
./download_xsd.sh std.xml
```

## 2. XSD 다운로드 방법

### 방법 1: ISO 20022 공식 사이트
- URL: https://www.iso20022.org/
- Repository: https://www.iso20022.org/sites/default/files/documents/D7/ISO20022/Repository/
- 예시: `head.001.001.03.xsd`

### 방법 2: 한국은행(BOK) 사이트
- URL: https://www.bok.or.kr/
- 한국은행 전용 ISO 20022 스키마 제공

### 방법 3: SWIFT 사이트
- URL: https://www.swift.com/
- SWIFT ISO 20022 메시지 스키마

### 방법 4: GitHub 검색
```bash
# GitHub에서 XSD 파일 검색
curl -s "https://raw.githubusercontent.com/search?q=head.001.001.03.xsd"
```

## 3. 자동화 스크립트

### 기본 다운로드 스크립트
```bash
./download_xsd.sh <xml_file>
```

### 개선된 다운로드 스크립트
```bash
./download_xsd_improved.sh <xml_file>
```

### XSD 생성 스크립트
```bash
./generate_xsd.sh <xml_file>
```

## 4. XML 유효성 검증

### xmllint 사용
```bash
xmllint --schema <xsd_file> <xml_file> --noout
```

### 예시
```bash
xmllint --schema std_corrected.xsd std.xml --noout
```

## 5. 현재 프로젝트의 Namespace

### 발견된 Namespace
1. `urn:bok:std:iso:20022:xsd:001` (BokwireEnvelope)
2. `urn:iso:std:iso:20022:tech:xsd:head.001.001.03` (AppHdr)

### 필요한 XSD 파일
1. `head.001.001.03.xsd` - ISO 20022 표준 헤더
2. `001.xsd` - 한국은행 전용 스키마 (필요시)

## 6. 문제 해결

### XSD 다운로드 실패 시
1. 공식 사이트에서 수동 다운로드
2. 다른 버전의 XSD 시도
3. 로컬에서 유사한 XSD 파일 검색
4. XML 구조를 기반으로 XSD 수동 생성

### 유효성 검증 오류 시
1. XSD 파일의 import 문 확인
2. Namespace 선언 확인
3. XML 구조와 XSD 구조 일치 확인

## 7. 참고 자료

- [ISO 20022 공식 사이트](https://www.iso20022.org/)
- [한국은행 사이트](https://www.bok.or.kr/)
- [SWIFT 사이트](https://www.swift.com/)
- [XML Schema Tutorial](https://www.w3schools.com/xml/schema_intro.asp)
