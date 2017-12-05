#include "SSUpreme.h"


extern int funcStat;
extern int programStat;
extern Wordbook* head;
extern int wordbookCNT;


void machugi_menu(void){
	int type;
	char* day;
	FILE *day_fp;
	Wordbook *now = (Wordbook*)malloc(sizeof(Wordbook));

	//printf("파일명(일차):");
	//scanf("%s",day);

	day = userInputS(0, "파일명(일차) : ", 1);

	int WbDay=atoi(day);
	now = getNthWbPtr(WbDay);
	//openWbFILE(now->id);

	//day = (char*)realloc( day, strlen(day) + 50 * sizeof(char) + 1);


	//strcat(day,".dic");
	/*
	 * if((day_fp=fopen(day,"r"))==NULL){
	 printf("오류: 파일을 열수없습니다.\n");
	 exit(-1);
	 }
	 */

	//scanf("%d",&type);
	type=userInputN("출력방식(알파벳  순서대로:1, 무작위:2)", 1);
	machugi(type,now,WbDay);

}
void machugi(int type,Wordbook *now,int WbDay){  
	int i;
	int question[31];
	char *day = now->id;


	//printf("%s\n", now->id);

	int len= WListLen(now->id);

	for(i=0;i<len;i++)
		question[i]=i;
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

	int cnt_q=0,cnt_c=0,cnt_ic=0;//전체,맞은,틀린문제수
	int num=0;
	char *ans;
	int c;// 엔터일때  메뉴로 나감
	int q_num=0;//퀴즈번호
	while(1){
		Word * Wnow=getNthWPtr(WbDay,question[q_num]);
		printf("%s->",Wnow->eng);

		ans=userInputS(0,"", 1);
		if((strcmp(ans,".quit"))==0){
			printf("당신의 점수는 %.2f 점입니다.\n",((float)cnt_c/cnt_q)*100);
			printf("계속하려면 엔터를 입력해주세요...");
			while( getch() != '\n' ) ;
			break;
		}
		if((strcmp(ans,Wnow->korDef[0])==0)||(strcmp(ans,Wnow->korDef[1])==0)||(strcmp(ans,Wnow->korDef[2])==0)){
			printf("correct!\n");
			cnt_q++;cnt_c++;
			q_num++;
		}
		else{
			printf("incorrect!\n");
			cnt_q++;cnt_ic++;
			q_num++;
		}
	}
}

