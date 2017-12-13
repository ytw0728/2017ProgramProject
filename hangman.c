#include "SSUpreme.h"

extern int programStat;
extern Wordbook* head;
extern int wordbookCNT;


void hangman_menu(void) // 원하는 단어장을 불러오고 행맨 프로그램을 시작하는 함수 
{
	int type;
	FILE *day_fp;
	Wordbook *now = (Wordbook*)malloc(sizeof(Wordbook));
	
	int WbDay=userInputN("파일명(일차) : ",1);
	while(WbDay > wordbookCNT || WbDay <1)  //단어장 개수 안의 숫자를 선택할 떄까지 반복
	{
		printf("단어장 개수 범위 안의 숫자를 입력해주세요\n");
		WbDay=userInputN("파일명(일차) : ",1);
	}
	now = getNthWbPtr(WbDay);

	hangman(now,WbDay);
}






int hangman(Wordbook *now,int WbDay) //행맨프로그램을 실행하는 함수  원하는 단어장과 단어장 Head의 주소를 가져옴
{	
	char breakC;
	char* day =now->id;
	int failcount=-1;
	int len,flag,errorflag, i;
	errorflag=0;
	char* userinput;
	char wordprint[15]={0};

	int Nth=rand()%WListLen(day);
	if (Nth==0)
		Nth=Nth+WListLen(day);

	Word *word;

	word = getNthWPtr(WbDay,Nth); //단어를 불러옴



	int NthDef=rand()%3;	//힌트를 제공하는 정수 
	
	if (NthDef==2 && word->korDef[2]=="NULL")    // 3번째 또는 2번쨰 뜻이 없을때 뜻을 다시 호출
		NthDef=rand()%2;
	else if (NthDef==1 && word->korDef[1]=="NULL")
			NthDef=0;
	else
		NthDef=0;
	len=strlen(word->eng);  //단어의 길이 측정
	for (i = 0; i < len; i++)  //빈칸을 출력하기 위한 반복문
	{
		wordprint[i]=95;
	}

	system("clear");
	
	while(strcmp(wordprint,word->eng)!=0){  //단어를 맞출 떄까지 행맨을 실행하는 반복문
	
		system("clear");
	
		flag = 0;

		paint_hang(failcount); 
		paint_frame(wordprint, len);
		gotoxy(0,10);
		printf("힌트 : %s\n",word->korDef[NthDef] );
		gotoxy(0,20);
		userinput=userInputS(1,"입력 : ", 1, 0);
		
		while( !( 122 >= *userinput && 97 <= *userinput ) && !( 'A' <= *userinput && *userinput <= 'Z' ) ) //사용자가 입력한 것이 알파벳인지 확인하는 반복문
		{	
			printf("잘못 입력하셨습니다. 알파벳을 입력해주세요\n");
			userinput=userInputS(1,"입력 : ", 1, 0);
		}

		if( *userinput < 'a' ) *userinput += 'a' - 'A';
		
		for(i=0;i<len;i++) //사용자가 입력한 알파벳과 단어를 비교하는 반복문
		{
			if(*userinput==word->eng[i]) {
				wordprint[i]=word->eng[i];
				flag=1;
			}
			else if(*userinput!=word->eng[i]&&wordprint[i]==0)
				wordprint[i]=32;
		}
		
		if( flag == 0 ) failcount++;
		if(failcount == 5){     //그림이 완성되었을 때 프로그램을 종료하는 가정문
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
	paint_hang(failcount); //그림을 화면에 나타내줌
	paint_frame(wordprint, len);
	printf("\n\n\n축하합니다! 단어를 맞추셨습니다!!!!!!!!!!!!\n\n\n");

	printf("메뉴로 돌아가기 위해 q를 입력해주세요...\n");
	while( ( breakC = getch() ) != 'q' && breakC != 'Q' ) ;	 // q 를 누르면 함수 종료.	
	return 0;
}

int paint_hang(int failcount) //그림그리는 함수. failcount를 통해서 어디까지 그릴지 확인함.
{
	int i;
	char *a[6];

	gotoxy(10,2);
	printf("------------------+");

<<<<<<< HEAD
	for(i=0;i<6;i++) 
=======
	for(i=0;i<6;i++)
>>>>>>> 35a00b2cb1bc7dfb0553094afc54516cc9ef3a70
		a[i]=(char *)calloc(40,sizeof(char));
	
	a[0]="    O\n";
	a[1]="                          /";
	a[2]="|";
	a[3]="\\\n";
	a[4]="                          /";
	a[5]=" \\";
	
	gotoxy(24,3);

<<<<<<< HEAD
	for(i=0;i<failcount+1;i++) //인자로 받은 failcount의 값에 따라 그림을 그림
=======
	for(i=0;i<failcount+1;i++)
>>>>>>> 35a00b2cb1bc7dfb0553094afc54516cc9ef3a70
		printf("%s",a[i]);
	
	return 0;
}


void paint_frame(char wordprint[], int len)  //화면의 틀을 짜놓은 함수, 단어를 맞춘만큼 출력해줌
{
		int i;	

		gotoxy(0,8);
		printf("단어를 맞추어보세요!\n");
		printf("단어에 들어갈 알파벳을 유추해 입력해주세요!\n");
		gotoxy(0,17);
		
		for(i=0;i<len;i++) 
<<<<<<< HEAD
			printf("%c ",wordprint[i]); //화면에 단어출력
=======
			printf("%c ",wordprint[i]);
>>>>>>> 35a00b2cb1bc7dfb0553094afc54516cc9ef3a70

}

