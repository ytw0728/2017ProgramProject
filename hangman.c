#include "SSUpreme.h"

extern int funcStat;
extern int programStat;
extern Wordbook* head;
extern int wordbookCNT;


void hangman_menu(void){
	int type;
	FILE *day_fp;
	Wordbook *now = (Wordbook*)malloc(sizeof(Wordbook));
	
	int WbDay=userInputN("파일명(일차) : ",1);
	while(WbDay > wordbookCNT || WbDay <1)
	{
		printf("단어장 개수 범위 안의 숫자를 입력해주세요\n");
		WbDay=userInputN("파일명(일차) : ",1);
	}
	now = getNthWbPtr(WbDay);

	hangman(now,WbDay);
}






int hangman(Wordbook *now,int WbDay) 
{	
	char breakC;
	char* day =now->id;
	int failcount=-1;
	int len,flag,errorflag, i;
	errorflag=0;
	char* userinput;
	char wordprint[15]={0};
	int Nth=rand()%30;
	if (Nth==0)
		Nth=Nth+30;



	Word *word;

	word = getNthWPtr(WbDay,Nth);
	int NthDef=rand()%3;
	
	if (NthDef==2 && word->korDef[2]=="NULL")
		NthDef=rand()%2;
	else if (NthDef==1 && word->korDef[1]=="NULL")
			NthDef=0;
	else
		NthDef=0;
	len=strlen(word->eng);
	for (i = 0; i < len; i++)
	{
		wordprint[i]=95;
	}

	system("clear");
	
	while(strcmp(wordprint,word->eng)!=0){
	
		system("clear");
	
		flag = 0;

		paint_hang(failcount);
		paint_frame(wordprint, len);
		gotoxy(0,10);
		printf("힌트 : %s\n",word->korDef[NthDef] );
		gotoxy(0,20);
		userinput=userInputS(1,"입력 : ", 1);
		
		while(122<*userinput || 97>*userinput)
		{	
			printf("잘못 입력하셨습니다. 알파벳을 입력해주세요\n");
			userinput=userInputS(1,"입력 : ", 1);
		}
		for(i=0;i<len;i++)
		{
			if(*userinput==word->eng[i]) {
				wordprint[i]=word->eng[i];
				flag=1;
			}
			else if(*userinput!=word->eng[i]&&wordprint[i]==0)
				wordprint[i]=32;
		}
		
		if( flag == 0 ) failcount++;
		if(failcount == 5){
			system("clear");
			paint_hang(failcount);
			paint_frame(wordprint, len);
			
			printf("\n\n단어 맞추는데 실패하셨습니다ㅠㅠ\n");
			printf("다시 도전해주세요!\n\n");


			printf("메뉴로 돌아가기 위해 q를 입력해주세요...\n");
			gotoxy(0,10);
			printf("힌트 : %s\n",word->korDef[NthDef] );
			while( ( breakC = getch() ) != 'q' && breakC != 'Q' ) ;
			return 0;
		}
	}
	system("clear");
	paint_hang(failcount);
	paint_frame(wordprint, len);
	printf("\n\n\n축하합니다! 단어를 맞추셨습니다!!!!!!!!!!!!\n\n\n");

	printf("메뉴로 돌아가기 위해 q를 입력해주세요...\n");
	while( ( breakC = getch() ) != 'q' && breakC != 'Q' ) ;		
	return 0;
}

int paint_hang(int failcount) //그림그리는 함수.
{
	int i;
	char *a[6];

	gotoxy(10,2);
	printf("------------------+");

	for(i=0;i<6;i++)
		a[i]=(char *)calloc(40,sizeof(char));
	
	a[0]="    O\n";
	a[1]="                          /";
	a[2]="|";
	a[3]="\\\n";
	a[4]="                          /";
	a[5]=" \\";
	
	gotoxy(24,3);

	for(i=0;i<failcount+1;i++)
		printf("%s",a[i]);
	
	return 0;
}


void paint_frame(char wordprint[], int len){
		int i;	

		gotoxy(0,8);
		printf("단어를 맞추어보세요!\n");
		printf("단어에 들어갈 알파벳을 유추해 입력해주세요!\n");
		gotoxy(0,17);
		
		for(i=0;i<len;i++) 
			printf("%c ",wordprint[i]);

}

