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

//	core.c
// default functions
void switchByErr(int errCode); // main error handling
void gotoxy( int x /* column */, int y /* row */);	// move screen cursor 
int init(); // funcCode = 101 // return ( error: -1 , no error: 0 )
int funcRoute(); // funcCode = 102 // start functions by user input


// user input functions
int getch(void); // for invisible input
int userInputN( char* message /* msg to print for input */, int visible); // funcCode = 103 // return user's Input, Number | return ( error : -1, no error : positive Int )
char* userInputS( int type /* length of string [ 0 / n ] */, char* message /* msg to print for input*/, int visible /* visibility of user input [ true / false ] */); // funcCode = 104 // return user's Input, String[Character array] ( type | nLetter( 1~n) : n, dynamic : 0 ) korean -> *2 | return ( error : null, no error : char pointer )


// linked list and file functions
int initWbList(); // funcCode = 199 // init word list
int addWbList( Wordbook* newNode /* struct node to add */ ); // funcCode = 120 // add new wordbook node ( end of list )
Word* insertWList( Word* head /* wHead of wordbook */, Word* newNode /* struct node to add */); // funcCode = 121 //  insert new wordbook node ( anywhere of list )

int WListLen(char* id); // funcCode = 130  // return the length of word list in (id).dic wordbook

int openWbFILE( char* id /* id string of wordbook ex) "1", "2", etc. */); // funcCode = 110 // open wordbook file with id | (id).dic
int writeWbFILE( Wordbook* node /* struct node to write on file */); //funcCode = 111 // clear and rewrite (id).dic wordbook file





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
void delay_time(int stop);
