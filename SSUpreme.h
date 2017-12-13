#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termio.h>
#include <time.h>


///////////////////////////////////////    struct  //////////////////////////////////////////////////
typedef struct word{ // struct of word ( will be the node of word linked list )
	char eng[16]; // 영어 단어 ( 15글자 )
	char korDef[3][61]; // 한글 뜻 최대 3개 ( 30 글자 )

	struct word* next; // 자기참조 포인터
}Word;

typedef struct wordbook{ // struct of wordbook ( will be the node of wordbook linked list )
	char id[5]; // (id).dic file
		
	struct wordbook* next; // 자기참조 포인터 : 단어장 
	struct word* wHead; // 자기참조 포인터 : 단어  ( 해당 일차의 단어 연결리스트를 가지고 있음. )
}Wordbook;	
/////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////	function declaration	////////////////////////////////////////

//	core.c
// default functions
void gotoxy( int x /* column */, int y /* row */);	// move screen cursor 
int init();  // return ( error: -1 , no error: 0 ) 최초 프로그램 실행 시에 단어장 리스트를 만들어 낸다.
int funcRoute();  // 초기 메뉴 함수, 유저의 입력에 따라 함수를 실행한다.


// user input functions
int getch(void); // getch 구현
int userInputN( char* message /* 입력 안내 메시지 */, int visible /* 입력이 시각적으로 보일지 안보일지 [ true / false ] */);  // return user's Input, Number | return ( error : -1, no error : positive Int )
char* userInputS( int type /* 문자열의 바이트 크기 [ 0 최대 1024 동적길이 / n ] */, char* message /* 입력 안내 메시지 */, int visible /* 입력이 시각적으로 보일지 안보일지 [ true / false ] */, int whiteSpaceType /* [ 0 공백문자 무시 | 1 공백문자 허용 ]   */ );  // return user's Input, 문자열 ( type | n 바이트 ( 1~n) : n, dynamic : 0 ) 영어에 한한 설명임. |  return ( error : null, no error : char pointer )


// linked list and file functions
int initWbList();  // init word list
int addWbList( Wordbook* newNode /* 추가할 단어장 노드 포인터 */ );  // add new wordbook node ( end of list )
Word* insertWList( Word* head /* 단어를 추가할 단어 연결리스트의 헤드 포인터 */, Word* newNode /* 추가할 단어 노드 포인터 */);  //  insert new wordbook node ( anywhere of list )

int WListLen(char* id);   // (id).dic 파일 내의 포함된 단어의 개수를 알려준다.

int openWbFILE( char* id /* 단어장의 일차 ( "1", "2" 등 ) */);  // (id).dic 파일을 열고 읽는다.
int writeWbFILE( Wordbook* node /* 파일에 적고자 하는 단어장 노드 */);  // (id).dic에 리스트의 내용을 쓴다.





//	kijeong.c
Wordbook* getNthWbPtr(int n);
Word* getNthWPtr(int Wbn, int Wn);
int menu(void);
int insert_Dic(int dicNum);
int print_Dic(int dicNum);
int makeDic(int dicNum);
void print_nDic(void);


//	machugi.c
void machugi_menu(void);
void machugi(int type,Wordbook *now,int WbDay);


//	hangman.c
void hangman_menu(void);
int hangman(Wordbook *now,int WbDay);
int paint_hang(int );
void paint_frame( char wordprint[], int len);

//	flash.c
void flashcard_menu(void);
void flashcard(Wordbook *now,int type,int WbDay,int stop);
