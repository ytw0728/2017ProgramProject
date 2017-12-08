#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termio.h>
#include <time.h>


///////////////////////////////////////    struct  //////////////////////////////////////////////////
typedef struct word{ // struct of word ( will be the node of word linked list )
	char eng[16];
	char korDef[3][61];

	struct word* next;
}Word;

typedef struct wordbook{ // struct of wordbook ( will be the node of wordbook linked list )
	char id[5]; // (id).dic file
		
	struct wordbook* next;
	struct word* wHead;
}Wordbook;	
/////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////	function declaration	////////////////////////////////////////

//	kijeong.c
Wordbook* getNthWbPtr(int n);
Word* getNthWPtr(int Wbn, int Wn);
int menu(void);
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



