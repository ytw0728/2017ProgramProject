#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



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
