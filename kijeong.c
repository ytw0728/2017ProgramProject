#include "SSUpreme.h"

#define STRBUF 1024

extern int funcStat;
extern int programStat;
extern Wordbook* head;
extern int wordbookCNT;




Wordbook* getNthWbPtr(int n)
{
	Wordbook* now = head;
	int i;
	for(i = 0; i < n - 1; i++)
	{
		now = now->next;
	}

	return now;
}

Word* getNthWPtr(int Wbn, int Wn)
{
	Word* ptr = getNthWbPtr(Wbn)->wHead;
	int i;
	for(i = 0; i < Wn - 1; i++)
	{
		ptr = ptr->next;
	}
	return ptr;
}

int menu(void)
{
	int choice = 0;
	while(1)
	{
		//출력 선택 부분
		system("clear");
		printf(">> 영어 단어 암기 프로그램 : 단어장 관리 <<\n");
		printf("1. 새 파일 추가하기\t\t2. 새 단어 추가하기\n");
		printf("3. 단어장 보기\t\t\t4. 단어 파일 목록보기\n");
		printf("5. 단어장 관리 종료\n\n");

		choice = userInputN("번호를 입력하세요 : ", 1);
		int ins1;
		char buf[STRBUF];
		char breakC;
		//선택 분기
		switch(choice)
		{
			case 1:
				makeDic(wordbookCNT+1);
				break;
			case 2:
				break;
			case 3:
				ins1 = userInputN("파일명(일차) : ", 1);
				Wordbook* tmpWb = getNthWbPtr(ins1);
				Word* tmp = tmpWb->wHead;
				while(tmp->next != NULL)
				{
					printf("%s %s %s %s\n", tmp->eng, tmp->korDef[0], tmp->korDef[1], tmp->korDef[2]);
					tmp = tmp->next;
				}
				printf("계속하려면 q를 입력해주세요...\n");
				while( ( breakC = getch() ) != 'q' && breakC != 'Q' );
				break;
			case 4:
				print_nDic();
				printf("계속하려면 q를 입력해주세요...\n");
				while( ( breakC = getch() ) != 'q' && breakC != 'Q' );
				break;
			case 5:
				return 1;
				break;
			default:
				printf("잘못된 입력입니다\n\n\n");
				break;
		}
	}
}

int makeDic(int dicNum)
{
	char buf[STRBUF];
	sprintf(buf, "%d", dicNum);

	Wordbook* Wbnew = (Wordbook*)malloc(sizeof(Wordbook));
	strcpy(Wbnew->id, buf);
	Wbnew->next = NULL;
	Wbnew->wHead = NULL;

	addWbList(Wbnew);
	writeWbFILE(Wbnew);
}

//print all .dic file
void print_nDic(void)
{
	int i = 0;
	int dicNum = wordbookCNT;
	printf("-------단어 파일 목록-------\n");
	for(i = 1; i <= dicNum; i++)
	{
		printf("%d.dic\t", i);
		if(i % 5 == 0)	printf("\n");
	}
	printf("\n");
}


