#include "SSUpreme.h"

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
	
//플레시카드의 정보를 입력받는 함수 단어반복출력시간,파일명,타입을 입력하면 플레시카드가 실행된다.
void flashcard_menu(void){
	int type;
	int stop;
	char *day;
	int WbDay;
	Wordbook *now = (Wordbook*)malloc(sizeof(Wordbook));
	while(1){
	stop=userInputN("단어를 반복출력할 시간을 입력하세요:",1);
	if(stop==0) printf("다시입력하세요\n");
	else break;	
	}
	while(1){
	WbDay=userInputN("파일명(일차):",1);
	while(WbDay > wordbookCNT || WbDay <1)
	{
		printf("단어장 개수 범위 안의 숫자를 입력해주세요\n");
		WbDay=userInputN("파일명(일차) : ",1);
	}
	if(WbDay==0) printf("다시입력하세요\n");
	else break;
	}
		
		
	//WbDay=atoi(day);
	now=getNthWbPtr(WbDay);
	while(1){
	type=userInputN("출력방식(알파벳 순서대로:1, 무작위:2)",1);
		
	if(type==0) printf("다시입력하세요\n");
	else if (type!=1&&type!=2) printf("다시입력하세요\n");
	else break;
	}
	flashcard(now,type,WbDay,stop);
}
//입력한 반복시간마다 영어단어와 한글뜻이 출력된다.
void flashcard(Wordbook *now,int type,int WbDay,int stop){
	int i,j;
	int question[32];
	char *day=now->id;
	int len= WListLen(now->id);
	for(i=0;i<len;i++){
		question[i]=i;
	}	
	question[i]=-1;
	if(type==2){
		srand(time(NULL));
		int change;
		for(change=0;change<100;change++){
			int temp;
			int random1=rand()%(len);
			int random2;
			while( ( random2=rand()%(len) == random1  )) ; //ran1과 ran2가 다를때까지 실행x
			temp=question[random1];
			question[random1]=question[random2];
			question[random2]=temp;
		}
	}
	//for(int n=0;n<len;n++)
	//	printf("%d\n",question[n]+1);
	for(i=0;i<len;i++){
		Word *Wnow=getNthWPtr(WbDay,question[i]+1);
		if(question[i]==-1){
			printf("모든단어를 출력했습니다.\n");
			break;
		}
		printf("%s->",Wnow->eng);
		//delay_time(stop);
		fflush(stdout);
		sleep(stop);
		for(j=0;j<3;j++){
			if(Wnow->korDef[j][0]!='\0'){
				printf("%s",Wnow->korDef[j]);
				//fflush(stdout);
				//sleep(stop);
				//delay_time(stop);
			}
		}
		
		printf("\n");
		sleep(stop);
	}

}





