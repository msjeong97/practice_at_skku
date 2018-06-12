# billboard.js에 기여하는 법
billboard.js는 모두에게 열려 있으며, 어떤 종류의 기여도 환영합니다.
우리의 프로젝트가 당신의 관심과 함께 다른 사람의 필요에 따라 성장할 수 있다고 믿습니다.

## 스타일 가이드
billboard.js에는 사용자가 따라야 하는 몇 가지 스타일 지침이 있습니다.
시작하기 전에 아래 지침을 주의 깊게 읽어 주십시오.

### Linting과 코드 규칙
코드의 스타일과 질을 유지하기 위해 우리는 [ESLint](http://eslint.org/)를 도입 했습니다. 
코드 스타일 [규칙](https://github.com/naver/eslint-config-naver/tree/master/rules)은 [Airbnb JavaScript Style Guide](https://github.com/airbnb/javascript)에 기반하여 몇 가지 수정 후 만들어졌습니다. 

### 커밋 로그 가이드라인
billboard.js는 다양한 목적에 형식화된 커밋 로그를 사용합니다(예:CHANGELOG작성, 용이한 기록 검색 등).
현재 형식을 깨지 않으려면 우리의 로그 커밋 지침을 따라야 합니다.
commit/push 명령을 내리기 전에 우리의 로그 커밋 지침을 따르십시오.

아웃라인은 다음과 같습니다:
```bash
<type>(<module>): <subject>
<BLANK LINE>
<body>
<BLANK LINE>
<footer>
```

- #### 종류
  - **feat**: 새로운 특징.
  - **fix**: 버그 수정.
  - **docs**: 문서만 변경.
  - **style**: 코드의 의미에 영향을 미치지 않는 변경 사항. 탭, 스페이스, 서식, 누락된 세미콜론 등.
  - **refactor**: 버그를 수정하거나 기능을 추가하지 않는 코드 변경.
  - **test**: 누락된 테스트를 변경하거나, 테스트를 추가할 때.
  - **chore**: 빌드 프로세스 또는 도구 및 라이브러리(예:문서 생성)에 대한 변경 사항.
  - **skip**: 첫번째 커밋 이후에 수행된 커밋. 일반적으로 코드 검토 변경 사항을 적용합니다.

- #### 코드 Body
커밋의 간단한 설명 메시지 부분입니다.
마지막으로,`Ref #ISSUE-NO`와 같이 관련된 github발급 번호를 포함하는 것이 좋습니다.

ex) Commit이 issue 번호 20과 관련이 있을 때,
```bash
Ref #20
```


버그를 수정하는 예시 commit:
```bash
Fix(Axis): Correct tick rendering

Update condition of tick to avoid unnecessary tick rendering

Ref #20
```

코드 리뷰를 적용한 예시 commit (첫번째 commit 이후):
> **Note:** Commit log starting with `skip:` type will be ignored by commit hook constraint.
```bash
skip: Applied the review
```

## pull request를 제출하는 방법
pull request를 제출하는 단계적 방법:

1. 당신의 저장소에 `billboard.js` 를 fork 합니다.
2. billboard.js master branch 로부터 새로운 branch를 생성합니다 (always up-to-date 로 하는 것을 잊지마세요).
3. 당신의 작업을 진행합니다.
4. 당신의 작업에 대한 test code를 생성합니다 (가능할 때).
5. `npm run lint` 명령어로 linting을 하고 code style을 체크합니다  (오류 또는 경고가 없을 때 까지 업데이트).
6. `npm test` 명령어 또는 `npm test:chrome` 명령어로 크롬 브라우저를 위해 테스트 합니다.
   모든 테스트가 적어도 최신 버전의 Chrome에서 통과했는지 확인하십시오 (모바일/데스크탑).
7. 규칙에 따라 commit 로그를 작성하고 저장소 branch로 push 합니다.
8. 당신의 billboard.js branch로부터 새로운 PR을 생성하시오
9. 리뷰를 기다립니다
   당신의 기여가 받아들여지기에 충분하다면, 우리의 branch에 merge 될 것입니다.
10. 다 끝!


## License
billboard.js에 기여하는 것은 당신의 기여가 [MIT](https://opensource.org/licenses/MIT) 라이선스에 의한 허가를 받는 것에 동의하는 것입니다.
