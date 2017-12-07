#include "SSUpreme.h"

#define STRBUF 1024

extern int funcStat;
extern int programStat;
extern Wordbook* head;
extern int wordbookCNT;

//return Nth Wordbook* from head
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

//return Wnth Word* from Wbnth WordBook.
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
    int ins1;
    char buf[STRBUF];
    char breakC;
    Wordbook* tmpWb;
    Word* tmpW;
    int i;
    char* ptr;
    
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
                break;
            case 2:
                ins1 = userInputN("파일명(일차) : ", 1);
                if(ins1 > wordbookCNT)
                {
                    printf("해당 단어장이 존재하지 않습니다.");
                    printf("계속하려면 q를 입력해주세요...\n");
                    while( ( breakC = getch() ) != 'q' && breakC != 'Q' );
                    break;
                }
                
                while(1)
                {
                    Word* tmpW = (Word*)malloc(sizeof(Word));
                    
                    gets(buf);
                    
                    if(strcmp(buf, ".add") == 0)
                    {
                        writeWbFILE(tmpWb);
                        break;
                    }
                    
                    ptr = strtok(buf, " ");
                    strcpy(tmpW->eng, ptr);
                    
                    for(i = 0; i < 3; i++)
                    {
                        ptr =  strtok(NULL, " ");
                        if(ptr != NULL)
                            strcpy(tmpW->korDef[i], ptr);
                        else
                            strcpy(tmpW->korDef[i] , "NULL");
                    }
                    tmpW->next = NULL;
                    insertWList(tmpWb->wHead, tmpW);
                }
                break;
            case 3:
                ins1 = userInputN("파일명(일차) : ", 1);
                tmpWb = getNthWbPtr(ins1);
                tmpW = tmpWb->wHead;
                
                if(tmpW == NULL)
                {
                    printf("단어장에 단어가 존재하지 않습니다.\n");
                    printf("계속하려면 q를 입력해주세요...\n");
                    while( ( breakC = getch() ) != 'q' && breakC != 'Q' );
                    break;
                }
                while(tmpW != NULL)
                {
                    printf("%s %s %s %s\n", tmpW->eng, tmpW->korDef[0], tmpW->korDef[1], tmpW->korDef[2]);
                    tmpW = tmpW->next;
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
    char buf[5];
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
        if(i % 5 == 0)    printf("\n");
    }
    printf("\n");
}


