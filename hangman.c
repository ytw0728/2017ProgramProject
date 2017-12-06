#include "SSUpreme.h"

int hangman() 
{	
	char breakC;

	int blank[40]={0,};
	int failcount=-1;
	int len,flag,errorflag,i;
	errorflag=0;
	char* solar="";
	char* userinput;
	char* mmm;
	char word[]="mamamoo";
	len=strlen(word);
	char wordprint[15]={0};
	for(i=0;i<len;i++)
		wordprint[i]=95;


	system("clear");
	while(strcmp(wordprint,word)!=0){

		system("clear");
		flag = 0;

		paint_hang(failcount);
		paint_frame(wordprint, len);
		
		gotoxy(0,20);
		userinput=userInputS(1,"입력 : ");

		for(i=0;i<len;i++)
		{
			if(*userinput==word[i]) {
				wordprint[i]=word[i];
				flag=1;
			}
			else if(*userinput!=word[i]&&wordprint[i]==0)
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
			while( ( breakC = getch() ) != 'q' && breakC != 'Q' )
			return 0;
		}
	}
	system("clear");
	paint_hang(failcount);
	paint_frame(wordprint, len);
	printf("\n\n\n축하합니다! 단어를 맞추셨습니다!!!!!!!!!!!!\n\n\n");

	printf("메뉴로 돌아가기 위해 q를 입력해주세요...\n");
	while( ( breakC = getch() ) != 'q' && breakC != 'Q' )		
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


