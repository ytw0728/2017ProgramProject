#include "SSUpreme.h"

#define FUNCNUM 5
#define STRBUF 1024
#define FILENAMEBUF 20


// global variables
int funcStat = 100; // the number of running func ( prefix | core : 1 , managing word : 2, hangman : 3, quiz : 4, flash card : 5, error handling : 9 )
int programStat = 1; // init : 1, ready to end : -1, end : 0, keyboard input : 10, file input : 20, file output : 25 )

Wordbook* head = NULL; // Wordbook head pointer;
int wordbookCNT = 0; // the number of wordbook in list


// testcode //
 void printAllWord(){
	printf("%d\n", wordbookCNT );
 	//printf("\nletsprint\n");
 	Wordbook* now;
 	now = head;

	while( now != NULL ){
 		printf("%s.dic\n", now->id );
 		Word* wordNow = now->wHead;
 		while( wordNow != NULL ){
 			printf("%s %s %s %s\n", wordNow->eng, wordNow->korDef[0], wordNow->korDef[1], wordNow->korDef[2]);
 			wordNow = wordNow->next;
 		}
 		printf("\n");

		now = now->next;
 	}
}

int main(){

		init();

		// printAllWord();

		while( programStat ){
				funcRoute();
		}

		return 0;
}

int init(){ // funcCode = 101
		int err = 0;
		funcStat = 101;

		err = initWbList();

		return err;
}

void gotoxy( int x, int y){
		printf("\033[%d;%dH", y,x);
}

void switchByErr(int errCode){
		printf("error code : %d | from %d function\n", errCode, funcStat);
}

int funcRoute(){ // funcCode = 102
		funcStat = 102;

		int err = 0;

		int n;
		system("clear");
		printf(" >> 염어 단어 암기 프로그램 << \n");
		printf("1 : %-20s 2 : %-20s\n","영어 단어 맞추기", "플래시 카드" );
		printf("3 : %-20s 4 : %-20s\n","행맨( hangman )", "단어장 관리" );
		printf("5 : %-20s\n", "프로그램 종료");

		do{
				n = userInputN("번호를 선택하세요 : ", 1);
				if( n < 1 || FUNCNUM < n ) printf("[ 1 ~ %d 사이의 값을 입력해주세요 ]\n", FUNCNUM);
		}while( n < 1 || n > FUNCNUM );



		switch( n ){
				case 1 : machugi_menu(); break;
				case 2 : flashcard_menu(); break;
				case 3 : hangman_menu(); break;
				case 4 : menu(); break;
				case 5 : programStat = 0; break;
		}
		return err;
}

int getch(void){  
	int ch;  
	struct termios buf;  
	struct termios save;  

	tcgetattr(0, &save);  
	buf = save;  
	buf.c_lflag &= ~(ICANON|ECHO);  
	buf.c_cc[VMIN] = 1;  
	buf.c_cc[VTIME] = 0;  
	tcsetattr(0, TCSAFLUSH, &buf);  
	ch = getchar();  
	tcsetattr(0, TCSAFLUSH, &save);  
	return ch;  
}


int userInputN(char* message, int visible){ // funcCode = 103
		funcStat = 103;
		int err = 0;


		int (*func)(void);
		if( visible ) func = getchar;
		else func = getch;

		char c;
		int spaceFlag = 0, re= 0, num = 0;

		printf("%s", message);
		while( ( c = func() ) ){
				if( c == '\n' || c == EOF) break;

				if( '0' <= c && c <= '9' ){
						if( spaceFlag ){
								re = 1;
								break;
						}
						c -= '0';
						num *= 10;
						num += c;
				}
				else if( !spaceFlag && c == ' ' ) spaceFlag = 1;
				else{
						re = 1;
						break;
				}
		}

		if( err ) return -1;
		if( re ){
				printf("[하나의 정수만 입력해주세요]\n");
				while( c = func() ) if( c == '\n' || c == EOF) break;
				num = userInputN(message, visible);
		}

		if( !visible ) printf("\n");
		return num;
}

char* userInputS( int type , char* message, int visible, int whiteSpaceType ){// funcCode = 104
		funcStat = 104;
		if( type < 0 ) return NULL;
		
		int (*func)(void);
		if( visible ) func = getchar;
		else func = getch;

		int err = 0;
		char* str;
		char buffer[STRBUF];
		int index = 0;

		while( index < STRBUF) buffer[index++] = 0;

		char c;
		int length = 0, re = 0;

		index = 0;
		printf("%s", message);
		while( (c = func() )){
				if( c == '\n' || c == EOF ) break;
				if( !whiteSpaceType &&  ( c == ' ' || c == '\t' ) ) continue;
				if( index < STRBUF && (type == 0 || index < type ) ) buffer[index++] = c;	
				else{
						re = 1;
						break;
				}
		}


		if( err ) return NULL;
		if( re ){
			printf("[ 다시 입력해주세요. (최대 %dByte ) ]\n", type == 0 ? STRBUF : type);
			while( c = func() ) if( c == '\n' || c == EOF ) break;
			str = userInputS( type, message, visible, whiteSpaceType);
		}
		else{
			if( type > 0 ) str = (char*)calloc( type+1, sizeof(char));
			else str = (char*)calloc( strlen(buffer)+1, sizeof(char));
			strcpy( str, buffer);
		}

		if( !visible ) printf("\n");
		return str;
}


int initWbList(){ // funcCode = 199
	funcStat = 199;
	int err = 0;
	FILE* fp = fopen("dicList","r");
	if( fp == NULL ){
		err = -1;
		return err;
	}
	char fileNameBuf[FILENAMEBUF];
	
	while( fscanf(fp, "%s\n", fileNameBuf)  != EOF ){
		char* temp;
		temp = (char*)calloc(strlen(fileNameBuf) + 1, sizeof(char) );
		strcpy( temp, fileNameBuf);

		openWbFILE(temp);
		free(temp);
	}

	fclose(fp);

	return err;
}
	
int addWbList( Wordbook* newNode ){ // funcCode = 120 // insert new wordbook node
	funcStat = 120;
	int err = 0;
	if( head == NULL ) head = newNode;
	else{
		Wordbook* now = head;
		while( now->next != NULL ) now = now->next;
		now->next = newNode;
	}

	if( !err ) wordbookCNT++;

	return err;
}

Word* insertWList( Word* head, Word* newNode ){ // funcCode = 121 // insert new wordbook node
	funcStat = 121;
	int err = 0;
	if( head == NULL ) head = newNode;
	else{
		Word* now = head;
		Word* next = now->next;
		Word* prev = now;
		while( now != NULL ){
			if( strcmp( newNode->eng, now->eng ) < 0 ){
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
			}
			else if( next == NULL || strcmp( newNode->eng, next->eng ) < 0 ){
				newNode->next = next;
				now->next = newNode;
				break;
			}
			else if( next->next == NULL ){
				newNode->next = NULL;
				next->next = newNode;
				break;
			}

			prev = now;
			now = now->next;
			next = now->next;
		}
	}
	if( err ) return NULL;

	return head;
}



int WListLen(char* id){ // funcCode = 130 
	funcStat = 130;
	
	int len = 0;
	Wordbook* now;
	now = head;

	while( now != NULL && !strcmp(now->id, id) ) now = now->next;

	Word* wNow;
	wNow = now->wHead;

	while( wNow != NULL ){
		len++;
		wNow = wNow->next;
	}

	return len;
}

int openWbFILE( char* id ){ // funcCode = 110
	funcStat = 110;
	int err = 0;

	char buffer[100];
	int index = 0;
	while( index < 100 ) buffer[index++] = 0;
	strcpy( buffer, id ); strcat(buffer, ".dic");


	char* fn = (char*)calloc(strlen(buffer) + 1, sizeof(char) );
	strcpy( fn, buffer);

	FILE* fp = fopen( fn,"r");
	if( fp == NULL ){
		err = -1;
		return err;
	}

	Wordbook* wbTemp = (Wordbook*)malloc(sizeof(Wordbook));
	strcpy(wbTemp->id, id);
	wbTemp->next = NULL;
	wbTemp->wHead = NULL;

	char engTmp[16];
	char korTmp[3][61];
	index = 0;
	while( index < 100 ) buffer[index++] = 0;

	while(fscanf(fp, "%s", engTmp ) != EOF){
		index = 0;
		fscanf( fp, "%[^\n]", buffer );

		char* token = strtok (buffer," ");
	    while ( index < 3 && token != NULL){
	        strcpy( korTmp[index++], token);
	        token = strtok (NULL, " ");
	    }

		Word* wTemp = (Word*)malloc( sizeof(Word) );

		strcpy(wTemp->eng, engTmp);
		int i;
		for( i = 0 ; i < 3; i++ ){
			if( i < index ) strcpy(wTemp->korDef[i], korTmp[i]);
			else strcpy(wTemp->korDef[i] , "");
		}
		wTemp->next = NULL;

		wbTemp->wHead = insertWList( wbTemp->wHead, wTemp );
	}

	addWbList( wbTemp );
	fclose(fp);

	return err;
}

int writeWbFILE( Wordbook* node){ // funcCode = 111
	funcStat = 111;
	int err = 0;

	char* id;
	id = (char*)calloc(strlen(node->id)+ 4 + 1, sizeof(char)); // length of (id + ".dic" + NULL)
	
	strcpy( id, node->id);
	strcat( id, ".dic");
	FILE* fp = fopen(id, "w");
	if( fp == NULL ){
		err = -1;
		return err;
	}
	Word* now = node->wHead;
	while( now != NULL ){
		fprintf(fp, "%s %s %s %s \n", now->eng, now->korDef[0], now->korDef[1], now->korDef[2] );
		now = now->next;
	}

	fclose(fp);

	fp = fopen("dicList", "w");
	if( fp == NULL ){
		err = -1;
		return err;
	}
	Wordbook* wbNow = head;
	while( wbNow != NULL ){
		fprintf(fp,"%s\n", wbNow->id);
		wbNow = wbNow->next;
	}

	fclose(fp);
	return err;
}

