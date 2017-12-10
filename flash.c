#include "SSUpreme.h"
<<<<<<< HEAD
void flashcard(Wordbook *,int,int,int);
=======

>>>>>>> KiJeong
extern int funcStat;   
extern int programStat;
extern Wordbook* head; 
extern int wordbookCNT;



void flashcard_menu(void){
	int type;
	int stop;
	char *day;
	int WbDay;
	Wordbook *now = (Wordbook*)malloc(sizeof(Wordbook));
	stop=userInputN("단어를 반복출력할 시간을 입력하세요:",1);	
	day=userInputS(0,"파일명(일차):",1);
	WbDay=atoi(day);
	now=getNthWbPtr(WbDay);
	type=userInputN("출력방식(알파벳 순서대로:1, 무작위:2)",1);
	flashcard(now,type,WbDay,stop);
}

void flashcard(Wordbook *now,int type,int WbDay,int stop){
	int i,j;
	int question[31];
	char *day=now->id;
	int len= WListLen(now->id);
	
	printf("check\n");
	for(i=0;i<len;i++){
		question[i]=i;
		printf("%d",question[i]);
	}	
	question[i]=-1;
	if(type==2){
		srand(time(NULL));
		int change;
		for(change=0;change<100;change++){
			int temp;
			int random1=rand()%len;
			int random2;
			while( ( random2 = (rand()%len)) == random1 ) ; //ran1과 ran2가 다를때까지 실행x
			temp=question[random1];
			question[random1]=question[random2];
			question[random2]=temp;
		}
	}
	for(i=0;i<len;i++){
		Word *Wnow=getNthWPtr(WbDay,question[i]);
		printf("%s->",Wnow->eng);
		sleep(stop*1000);
		for(j=0;j<3;j++){
			if(Wnow->korDef[j]!=NULL){
				printf("%s",Wnow->korDef[j]);
<<<<<<< HEAD
				sleep(stop*1000);
			}
=======
			sleep(stop*1000);
>>>>>>> KiJeong
		}
	}
}





