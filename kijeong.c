#include "SSUpreme.h"

#define STRBUF 1024

extern int programStat;
extern Wordbook* head;
extern int wordbookCNT;

//n번째 Wordbook 포인터 리턴
Wordbook* getNthWbPtr(int n)
{
    Wordbook* now = head;//Wordbook노드의 맨 첫번째 노드를 가져옴
	if(now == NULL)//만약 첫 노드가 NULL이면 NULL리턴하고 함수 종료
	{
		printf("HEAD가 존재하지 않습니다\n");
		return NULL;
	}
	if(wordbookCNT < n)//n.dic파일이 존재하지 않는다면(wordbookCNT보다 n이 크다면) NULL리턴
	{
		printf("%d.dic가 존재하지 않습니다\n", n);
		return NULL;
	}
    int i;
	//n-1번 next로 가며 단어장 탐색
    for(i = 0; i < n - 1; i++)
    {
		if(now ->next != NULL)
        	now = now->next;
    }
    //n.dic Wordbook 포인터 리턴
    return now;
}

//Wbn번째 Wordbook 포인터의 Wn번째 단어 리턴
Word* getNthWPtr(int Wbn, int Wn)
{
	Wordbook* tmpWb;
    Word* ptr;

	//Wbn번째 Wordbook포인터 가져오고 없다면 NULL 리턴
    tmpWb = getNthWbPtr(Wbn);
	if(tmpWb == NULL)
		return NULL;

	//Wordbook포인터의 Word의 head가져오고 NULL이면 NULL리턴
	ptr = tmpWb->wHead;
	if(ptr == NULL)
	{
		printf("%d.dic에 head가 존재하지 않습니다. \n", Wbn);
		return NULL;
	}

	//Wn - 1번 순회하며 Wn번째 Word포인터 찾아서 리턴
    int i;
    for(i = 0; i < Wn - 1; i++)
    {
		if(ptr != NULL)
	        ptr = ptr->next;
    }
    return ptr;
}

//선택 분기 함수
int menu(void)
{
    int 		choice = 0;
    int 		ins1;
    char 		buf[STRBUF];
    char 		breakC;
    Wordbook* 	tmpWb;
    Word* 		tmpW;
    int 		i;
    char*	 	ptr;
    
    while(1)
    {
        //출력 선택 부분
        system("clear");
        printf(">> 영어 단어 암기 프로그램 : 단어장 관리 <<\n");
        printf("1. 새 파일 추가하기\t\t2. 새 단어 추가하기\n");
        printf("3. 단어장 보기\t\t\t4. 단어 파일 목록보기\n");
        printf("5. 단어장 관리 종료\n\n");
        
        choice = userInputN("번호를 입력하세요 : ", 1);
        //선택 분기
        switch(choice)
        {
            case 1:
                makeDic(wordbookCNT+1);
                printf("계속하려면 q를 입력해주세요...\n");
                while( ( breakC = getch() ) != 'q' && breakC != 'Q' );
                break;
            case 2:
                ins1 = userInputN("파일명(일차) : ", 1);

				insert_Dic(ins1);
                printf("계속하려면 q를 입력해주세요...\n");
                while( ( breakC = getch() ) != 'q' && breakC != 'Q' );
                break;
            case 3:
                ins1 = userInputN("파일명(일차) : ", 1);
				print_Dic(ins1);
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
//dicNum번째 단어장에 단어 추가
int insert_Dic(int dicNum)
{
	Wordbook* 	tmpWb;
	Word* 		tmpW;
	char*		ptr;
	char		buf[STRBUF];
	int			i;

	//dicNum.dic이 존재하지 않으면 -1 리턴
    if(dicNum > wordbookCNT)
	{
		printf("%d.dic 파일이 존재하지 않습니다.\n", dicNum);
   		return -1; 
	}

	//Wordbook 포인터 가져오고 없으면 NULL리턴
    tmpWb = getNthWbPtr(dicNum); 
	if(tmpWb == NULL)
		return -1;

    while(1)
    {
   	  tmpW = (Word*)malloc(sizeof(Word));//새 Word객체 생성
   	  strcpy(buf, userInputS(0, "", 1, 1));//한 줄 입력받아서 buf에 저장

	  if(strcmp(buf, ".add") == 0)//입력한 문자열이 .add라면 .dic파일을 다시 쓰고 1리턴
	  {
    	writeWbFILE(tmpWb);
		return 1;	
	  }
		//첫 스페이스까지 잘라서 eng(영어)에 복사	  
	  ptr = strtok(buf, " ");
	  strcpy(tmpW->eng, ptr);

	  //스페이스까지 세번씩 잘라서 NULL이 아니면 값을 넣고 NULL이면 ""(빈문자열)을 복사
	  for(i = 0; i < 3; i++)
	  {
	 	ptr = strtok(NULL, " ");
		if(ptr != NULL)
			strcpy(tmpW->korDef[i], ptr);
		else
	  		strcpy(tmpW->korDef[i], "");
	  }
	  //Wordbook포인터에 tmpW객체를 새로 추가함
	  tmpW->next = NULL;
	  tmpWb->wHead = insertWList(tmpWb->wHead, tmpW);
	}
	return -1;
}
//dicNum번째 단어장의 모든 단어와 뜻 출력
int print_Dic(int dicNum)
{
	Wordbook* 	tmpWb;
	Word* 		tmpW;
	char		buf[STRBUF];

	//dicNum번째 단어장 포인터 가져옴
    tmpWb = getNthWbPtr(dicNum);
	if(tmpWb == NULL)
		return -1;

	//tmpWb단어장에 첫 단어가져와서 없으면 NULL리턴
   	tmpW = tmpWb->wHead;
    if(tmpW == NULL)
    {
    	printf("단어장에 단어가 존재하지 않습니다.\n");
		return -1;
    }

	//tmpW의 영어, 한글 뜻들 출력
    while(tmpW != NULL)
    {
        printf("%s %s %s %s\n", tmpW->eng, tmpW->korDef[0], tmpW->korDef[1], tmpW->korDef[2]);
        tmpW = tmpW->next;
    }
	return 1;
}

//dicNum.dic  단어장 파일 생성
int makeDic(int dicNum)
{
    char buf[5];
	//buf에 dicNum넣어서 문자열화함
    sprintf(buf, "%d", dicNum);
    
	//새 Wordbook* 노드를 생성
    Wordbook* Wbnew = (Wordbook*)malloc(sizeof(Wordbook));
	//WordBook* 노드 기본 설정
    strcpy(Wbnew->id, buf);
    Wbnew->next = NULL;
    Wbnew->wHead = NULL;
	//새 Wordbook* 노드를 리스트에 추가하고 파일을 새로 생성함
    addWbList(Wbnew);
    writeWbFILE(Wbnew);

	printf("%d.dic 파일이 추가되었습니다.\n", dicNum);
}

//woordbookCNT(현재 단어장 갯수)에 따라서 현재 단어장 파일명(.dic)모두 출력
void print_nDic(void)
{
    int i = 0;
    int dicNum = wordbookCNT;
    printf("-------단어 파일 목록-------\n");
	//현재 단어장의 갯수인 dicNum개의 n.dic파일 출력
    for(i = 1; i <= dicNum; i++)
    {
        printf("%d.dic\t", i);
        if(i % 5 == 0)    printf("\n");
    }
    printf("\n");
}



