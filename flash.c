#include "SSUpreme.h"
#include <stdio_ext.h>
void flashcard(Wordbook *,int,int,int);
extern int funcStat;   
extern int programStat;
extern Wordbook* head; 
extern int wordbookCNT;
void delay_time(int stop){
	time_t start_time=0,end_time=0;
	start_time=clock();
	while(1){
		end_time=clock();
		if(((int)(end_time-start_time)/(CLOCKS_PER_SEC))==stop)
			break;
	}
}	
	

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
	
	for(i=1;i<=len;i++){
		question[i]=i;
		//printf("%d",question[i]);
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
	for(int i=1;i<=len;i++){
		Word *Wnow=getNthWPtr(WbDay,question[i]);
		if(question[i]==-1){
			printf("모든단어를 출력했습니다.\n");
			break;
		}
		printf("%d %s->",question[i],Wnow->eng);
		//delay_time(stop);
		fflush(stdout);
		sleep(stop);
		for(j=0;j<3;j++){
			if(Wnow->korDef[j]!=NULL){
				printf("%s",Wnow->korDef[j]);
				fflush(stdout);
				sleep(stop);
				//delay_time(stop);
			}
			sleep(stop*1000);
		}
		printf("\n");
	}

}





