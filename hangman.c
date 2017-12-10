#include "SSUpreme.h"

extern int funcStat;
extern int programStat;
extern Wordbook* head;
extern int wordbookCNT;


void hangman_menu(void){
	int type;
	char* day;
	FILE *day_fp;
	Wordbook *now = (Wordbook*)malloc(sizeof(Wordbook));


	day = userInputS(0, "파일명(일차) : ", 1);

	int WbDay=atoi(day);
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

	//printf("%s\n", now->id);
	Word *word;

	word = getNthWPtr(WbDay,Nth);
	len=strlen(word->eng);
	for (i = 0; i < len; i++)
	{
		wordprint[i]=95;
	}
	printf("%s\n", word->eng );

	printf("%c\n",67 );
	system("clear");
	printf("%c\n",68 );
	while(strcmp(wordprint,word->eng)!=0){
		printf("%c\n",70);
		system("clear");
		printf("%c\n",69 );
		flag = 0;

		paint_hang(failcount);
		paint_frame(wordprint, len);
		
		gotoxy(0,20);
		userinput=userInputS(1,"입력 : ", 1);

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
		printf("단어에 들어갈 알파벳을 유추해 입력해주세요!");
		gotoxy(0,17);
		
		for(i=0;i<len;i++) 
			printf("%c ",wordprint[i]);

}

