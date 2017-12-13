#include "SSUpreme.h"

#define FUNCNUM 5 // 프로그램 메인메뉴의 기능의 개수 
#define STRBUF 1024 // 사용자 입력 시 최대 입력 버퍼 크기
#define FILENAMEBUF 20 // 파일 이름 (id).dic 을 담는 버퍼 크기


// global variables
int programStat = 1; // init : 1, ready to end : -1, end : 0, keyboard input : 10, file input : 20, file output : 25 )

Wordbook* head = NULL; // Wordbook head 포인터 ( 단어장의 연결리스트 즉, 자기참조구조체의 헤드포인터)
int wordbookCNT = 0; // 단어장 연결리스트의 노드 갯수 : 총 단어장의 갯수 및 일차를 알 수 있다.


int main(){ 
		init();	// 파일의 내용을 읽고, 파일을 연결리스트화 한다.

		while( programStat ){ // programStat 이 0 이 아닐 때 까지 반복
				funcRoute(); // 매번 메인 메뉴를 실행한다. 
		}

		system("clear"); // 프로그램을 종료하기 전에 화면을 clear한다.
		return 0;
}

int init(){ 
		int err = 0;
		

		err = initWbList(); // 단어장 연결리스트를 초기화한다.

		return err;
}

void gotoxy( int x, int y){
		printf("\033[%d;%dH", y,x); // 커서를 콘솔창의 (x,y) 로 위치시킨다.
}


int funcRoute(){ 
		int err = 0;

		int n;
		system("clear"); // 매번 콘솔 화면을 clear 시킨다. 
		printf(" >> 영어 단어 암기 프로그램 << \n"); 
		printf("%-25s %-25s\n","1 : 영어 단어 맞추기", "2 : 플래시 카드" );
		printf("%-25s %-25s\n","3 : 행맨( hangman )", "4 : 단어장 관리" );
		printf("%-25s\n", "5 : 프로그램 종료");

		do{
				n = userInputN("번호를 선택하세요 : ", 1);
				if( n < 1 || FUNCNUM < n ) printf("[ 1 ~ %d 사이의 값을 입력해주세요 ]\n", FUNCNUM);
		}while( n < 1 || n > FUNCNUM );
		// n 이 1~FUNNCUM 일때까지 정수 값을 입력받는다.


		switch( n ){
				case 1 : machugi_menu(); break; // 입력값이 1 이면 영어 단어 맞추기
				case 2 : flashcard_menu(); break; // 입력값이 2면 플래시카드
				case 3 : hangman_menu(); break; // 입력값이 3이면 행맨
				case 4 : menu(); break; // 입력값이 4 면 단어장 관리
				case 5 : programStat = 0; break; // 입력값이 5이면 programStat에 0을 대입해 main 의 while 문을 종료시켜 전체 프로그램 종료
		}
		return err;
}

int getch(void){  // getch 구현
	int ch;  
	struct termios buf;
	struct termios save;  

	tcgetattr(0, &save);  
	buf = save;  
	buf.c_lflag &= ~(ICANON|ECHO);  
	buf.c_cc[VMIN] = 1;  
	buf.c_cc[VTIME] = 0;  
	tcsetattr(0, TCSAFLUSH, &buf);  // getchar 전에 콘솔창에 출력되지 않도록 상태 속성 지정 
	ch = getchar();  
	tcsetattr(0, TCSAFLUSH, &save); // getchar 후에 원래의 콘솔 인터페이스 속성으로 복귀
	return ch;  
}


int userInputN(char* message, int visible){ 
		
		int psTmp = programStat; 
		programStat = 10;

		int err = 0;


		int (*func)(void);
		if( visible ) func = getchar;	// visible이 1 이면 getchar 이용
		else func = getch; // visible이 0 이면 getch 이용

		char c;
		int spaceFlag = 0, re= 0, num = 0;

		printf("%s", message);
		while( ( c = func() ) ){
				if( c == '\n' || c == EOF) break; // c 가 개행문자이거나 EOF일떄 까지 반복

				if( '0' <= c && c <= '9' ){ 
						if( spaceFlag ){ // 공백이 한번이라도 입력된적이 있을 때,
								re = 1; // 다시 입력받도록 re = 1
								break;
						}
						c -= '0'; // 문자를 정수화 
						num *= 10; 
						num += c; 
						// 십진수로 정리
				}
				else if( !spaceFlag && c == ' ' ) spaceFlag = 1;
				else{
						re = 1; // '0' ~ '9' 가 입력되지 않았을 경우 다시 입력
						break;
				}
		}

		programStat = psTmp;
		if( err ) return -1;
		if( re ){
				printf("[하나의 정수만 입력해주세요]\n"); 
				while( c = func() ) if( c == '\n' || c == EOF) break; // 입력버퍼 비우기
				num = userInputN(message, visible);
				// 다시 입력받도록 재귀호출
		}

		if( !visible ) printf("\n"); // visible 이 0 일 경우 개행문자를 출력해줘 인터페이스 정리
		return num;
}

char* userInputS( int type , char* message, int visible, int whiteSpaceType ){
		
		if( type < 0 ) return NULL;
		int psTmp = programStat; 
		programStat = 10;
		
		int (*func)(void);
		if( visible ) func = getchar; // visible이 1 이면 getchar 
		else func = getch; // visible이 0 이면 getch

		int err = 0;
		char* str;
		char buffer[STRBUF]; // 문자열 생성 전 입력 버퍼로 이용
		int index = 0;

		while( index < STRBUF) buffer[index++] = 0; // 0으로 초기화

		char c;
		int length = 0, re = 0;

		index = 0;
		printf("%s", message);
		while( (c = func() )){
				if( c == '\n' || c == EOF ) break; // c 개행문자이거나 EOF일때 까지 반복 
				if( !whiteSpaceType &&  ( c == ' ' || c == '\t' ) ) continue; // whiteSpaceType이 0일때, 공백문자 무시 
				if( index < STRBUF && (type == 0 || index < type ) ) buffer[index++] = c;	// buffer에 문자값 넣기
				else{
						re = 1; // 위의 경우에 해당되지 않는 경우 에러로 간주하고 재입력
						break;
				}
		}

		programStat = psTmp;
		if( err ) return NULL;
		if( re ){
			printf("[ 다시 입력해주세요. (최대 %dByte ) ]\n", type == 0 ? STRBUF : type);
			while( c = func() ) if( c == '\n' || c == EOF ) break; // 입력 버퍼 비우기 
			str = userInputS( type, message, visible, whiteSpaceType);
			// 다시 입력받도록 재귀 호출
		}
		else{
			if( type > 0 ) str = (char*)calloc( type+1, sizeof(char));
			else str = (char*)calloc( strlen(buffer)+1, sizeof(char));
			strcpy( str, buffer);

			// str을 목적에 알맞게 메모리 동적할당 후 buffer배열의 값을 복사 
		}

		if( !visible ) printf("\n"); // visible이 0일 경우 개행문자를 출력해 인터페이스 정리
		return str;
}


int initWbList(){ 
	
	int err = 0;
	FILE* fp = fopen("dic.list","r"); // dic.list 파일 읽기모드로 열기
	int psTmp = programStat; 
	programStat = 20;

	if( fp == NULL ){
		err = -1;
		return err;
		// 파일 없으면 에러로 간주 -1 리턴
	}
	char fileNameBuf[FILENAMEBUF];
	
	while( fscanf(fp, "%s\n", fileNameBuf)  != EOF ){
		char* temp;
		temp = (char*)calloc(strlen(fileNameBuf) + 1, sizeof(char) );
		strcpy( temp, fileNameBuf);
		// dic.list 에 명시되어 있는 단어장 파일의 id [ (id).dic 중 id 부분  ex) "1", "2", ...] 과 ".dic"을 합쳐 파일명 문자열 동적크기로 생성

		openWbFILE(temp); // 만들어진 파일명 문자열로 단어장 파일에 접근
		free(temp); // calloc에 의해 할당된 메모리 공간 해제
	}

	fclose(fp); // 파일 닫기 
	programStat = psTmp;

	return err;
}
	
int addWbList( Wordbook* newNode ){ 
	
	int err = 0;
	if( head == NULL ) head = newNode; // head가 NULL 이면 전달된 노드의 주소를 head의 값으로
	else{
		Wordbook* now = head; // head의 값을 보존하기 위해 now 로 값 복사
		while( now->next != NULL ) now = now->next; // 단어장 연결리스트의 맨 뒤까지 while문 돌리기
		now->next = newNode; // 단어장 연결리스트의 맨 뒤에 노드 추가
	}

	if( !err ) wordbookCNT++; // 정상적으로 리스트에 추가되었으면 wordbookCNT를 증가시켜, 현재 단어장의 개수를 알린다.

	return err;
}

Word* insertWList( Word* head, Word* newNode ){ 
	
	int err = 0;
	if( head == NULL ) head = newNode; // head가 NULL이면 새로운 노드의 주소를 head의 값으로
	else{
		Word* now = head; // head의 값을 보존하기 위해 now 에 head값 복사
		Word* next = now->next; // now 의 다음 값을 미리 확인 하는 next 포인터
		Word* prev = now; // now 가 가리켰던 이전 값을 나타내는 prev 포인터
		while( now != NULL ){ // now 가 NULL 일때 까지 반복 
			if( strcmp( newNode->eng, now->eng ) < 0 ){ // 전달받은 노드와 now가 가리키는 노드의 단어를 비교했을때, 사전식 순서를 기준으로 새로운 노드의 단어가 우선일 때
				newNode->next = now; 
				if( prev == head ){
					newNode->next = prev;
					head = newNode;
				}
				else{
					newNode->next = prev->next;
					prev->next = newNode;
				} 
				break;

				// now 바로 전에 새로운 노드를 삽입하고 반복을 종료한다.
				// 만약 이전 노드가 head와 같다면 새로운 노드는 새로운 head가 된다.
			}
			else if( next == NULL || strcmp( newNode->eng, next->eng ) < 0 ){ // now가 맨 마지막 노드이거나, 사전식 순서를 기준으로 새로운 노드의 단어가 다음 노드의 단어보다 우선일 때
				newNode->next = next;
				now->next = newNode;
				break;
				// now가 가리키는 노드와 다음 노드 사이에 새로운 노드를 삽입하고 반복을 종료한다.
			}
			else if( next->next == NULL ){ // 현재 가리키는 노드의 다음 노드가 마지막 노드일 때 
				newNode->next = NULL;
				next->next = newNode;
				break;
				// 새로운 노드를 현재 단어 연결리스트의 맨 마지막에 추가한다.
			}

			prev = now; // prev는 now가 가장 최근 가리켰던 이전 값을 나타낸다.
			now = now->next; // now는 한 노드 전진시킨다.
			next = now->next; // next는 now의 다음 노트를 나타낸다.
		}
	}
	if( err ) return NULL;

	return head; // 현재 단어 연결리스트의 head 주소 값을 반환한다.
}



int WListLen(char* id){ 
	
	
	int len = 0;
	Wordbook* now; 
	now = head;
	// 단어장 연결리스트의 head값을 보존하기 위해 now에 head값을 복사한다.


	while( now != NULL && strcmp(now->id, id) ) now = now->next; // 단어장 연결리스트의 노드 중 전달받은 id 인자값과 같은 id 문자열을 가지고 있는 노드를 찾아 now로 가리킨다.

	Word* wNow; 
	wNow = now->wHead;
	// 단어장의 단어 연결리스트 wHead값을 보존하기 위해 wNow 에 wHead값을 복사한다.

	while( wNow != NULL ){
		len++;
		wNow = wNow->next;
	}
	// wNow가 마지막 노드를 가리킬때 까지 len 을 증가시킨다. 

	return len;
}

int openWbFILE( char* id ){ 
	
	int err = 0;

	char buffer[FILENAMEBUF]; // 파일명 문자열을 담을 버퍼
	int index = 0;
	while( index < FILENAMEBUF ) buffer[index++] = 0; // 버퍼를 0으로 초기화
	strcpy( buffer, id ); strcat(buffer, ".dic"); // 전달받은 id 문자열에 .dic을 이어붙여 (id).dic의 형태로 만들어 buffer에 저장한다. ex) "1.dic" 


	char* fn = (char*)calloc(strlen(buffer) + 1, sizeof(char) );
	strcpy( fn, buffer);
	// 파일명 문자열의 길이에 맞게 동적할당을 한 후 문자열 값을 복사한다.

	int psTmp = programStat;
	programStat = 20;

	FILE* fp = fopen( fn,"r"); // 만들어진 파일명 문자열에 의해 읽기 모드로 파일을 연다
	if( fp == NULL ){
		err = -1;
		return err;
	}
	// 파일이 없을 경우 에러로 간주하고 -1을 반환한다. 

	Wordbook* wbTemp = (Wordbook*)malloc(sizeof(Wordbook)); // 단어장 연결리스트의 노드가 될 단어장 구조체 포인터를 만들고 동적 메모리 할당 후 해당 위치를 저장한다.
	strcpy(wbTemp->id, id); // 해당 단어장 파일에서 .dic을 뺀 문자열을 멤버 변수 id배열에 지정해준다.
	wbTemp->next = NULL; 
	wbTemp->wHead = NULL;
	// 단어장 노드의 next( 다음 노드 )와 wHead( 단어 연결리스트의 head )를 null로 초기화 한다.

	char engTmp[16]; // 파일에서 영어를 입력받아 옮겨줄 임시 배열 
	char korTmp[3][61]; // 파일에서 한글뜻을 입력받아 옮겨줄 임시배열 
	char strBuffer[STRBUF]; // 파일에서의 입력을 1차적으로 받아줄 입력 버퍼
	index = 0;
	while( index < STRBUF ) strBuffer[index++] = 0; // buffer를 0 으로 초기화

	while(fscanf(fp, "%s", engTmp ) != EOF){ // 파일의 끝이 아닐 때까지 engTmp로 영어단어에 해당하는 문자열을 입력받아 저장.
		index = 0;
		fscanf( fp, "%[^\n]", strBuffer ); // engTmp에 해당하는 한글 뜻 부분을 모두 입력받음

		char* token = strtok (strBuffer," ");
	    while ( index < 3 && token != NULL){
	        strcpy( korTmp[index++], token);
	        token = strtok (NULL, " ");
	    }
	    // strtok를 통해 공백을 기준으로 문자열을 나눠 각각 한글 뜻 배열에 저장.

		Word* wTemp = (Word*)malloc( sizeof(Word) ); // 단어 연결리스트의 노드가 될 단어 구조체 포인터를 만들고 동적 메모리 할당 후 해당 위치를 지정.

		strcpy(wTemp->eng, engTmp); // 단어 노드의 영어 단어 멤버 변수에 engTmp 값 복사
		int i;
		for( i = 0 ; i < 3; i++ ){
			if( i < index ) strcpy(wTemp->korDef[i], korTmp[i]);
			else strcpy(wTemp->korDef[i] , "");
		}
		// 영어 단어에 해당하는 한글 뜻을 있는 만큼 (최대 3개) korDef에 복사하고, 3개 이하일 경우 나머지 한글 뜻 배열에 공문자열 저장
		wTemp->next = NULL; // 단어 노드의 다음 노드 포인터에 NULL 대입

		wbTemp->wHead = insertWList( wbTemp->wHead, wTemp ); // 단어 노드를 연결리스트에 사전식 순서에 맞춰 순서대로 삽입한 후 반환된 해당 연결 리스트의 head포인터를 단어장의 wHead에 저장
	}

	addWbList( wbTemp ); // 단어의 연결리스트화 작업이 끝난 단어장 노드를 단어장 연결리스트의 마지막 부분에 추가한다.
	fclose(fp); // 현재 열려있는 단어장 파일을 닫는다.
	programStat = psTmp;

	return err;
}

int writeWbFILE( Wordbook* node){ 
	
	int err = 0;

	char* id; // 파일명 문자열을 가리킬 id 포인터 변수
	id = (char*)calloc(strlen(node->id)+ 4 + 1, sizeof(char)); //  (id + ".dic" + NULL) 문자열 에 해당하는 길이만큼 동적할당해 그 위치를 id 에 저장.
	
	strcpy( id, node->id);
	strcat( id, ".dic");
	// id 위치에 파일명 문자열을 저장 [ (id).dic ]

	int psTmp = programStat;
	programStat = 25;

	FILE* fp = fopen(id, "w"); // 만들어진 파일명 문자열을 통해 쓰기 모드로 파일을 연다
	if( fp == NULL ){
		err = -1;
		return err;
	}
	// 파일이 없을 경우, 에러로 간주하고 -1 반환

	Word* now = node->wHead; // 파일로 저장하고자하는 단어장 노드인 node의 wHead 값을 보존하기 위해 단어 구조체 포인터 now 에 그 값을 복사한다.
	while( now != NULL ){
		fprintf(fp, "%s %s %s %s \n", now->eng, now->korDef[0], now->korDef[1], now->korDef[2] );
		now = now->next;
	}
	// node의 단어 연결리스트의 모든 노드의 내용을 "영어단어 뜻1 뜻2 뜻3 \n"의 양식에 맞춰 파일에 출력한다.

	fclose(fp); // 현재 다루고 있는 단어장 파일을 닫는다.

	fp = fopen("dic.list", "w"); // dic.list를 쓰기모드로 연다.
	if( fp == NULL ){
		err = -1;
		return err;
	}
	// 파일이 없을 경우 에러로 간주하고 -1을 반환한다.

	Wordbook* wbNow = head; // 단어장 연결리스트의 head 값을 보존하기 위해 단어장 구조체 포인터 변수 wbNow를 선언하고 wbNow에 head값을 복사한다.
	while( wbNow != NULL ){
		fprintf(fp,"%s\n", wbNow->id);
		wbNow = wbNow->next;
	}
	// 단어장 연결리스트의 모든 노드를 순회하며, 각 노드의 id를 dic.list 파일에 한 라인씩 출력한다.

	fclose(fp); // dic.list파일을 닫는다. 
	programStat = psTmp;

	return err;
}

