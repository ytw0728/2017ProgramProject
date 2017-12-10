CC=gcc
ObjectDIR=../Object
OBJECTS= $(ObjectDIR)/core.o $(ObjectDIR)/kijeong.o $(ObjectDIR)/machugi.o $(ObjectDIR)/hangman.o $(ObjectDIR)/flash.o

Start:  Build Link

Build:  ../*.c
		@$(CC) -c ../*.c ../SSUpreme.h 2>log/build.log || true
		@cat log/build.log
		@mv *.o ../Object

BErrMsgProc:	log/build.log
				@cat log/build.log | grep "error" -3 ./log/error.log || true

BErrChk: log/error.log
		 @echo "[빌드 과정에서 에러가 발생했습니다. ]  => log/error.log file 참고"

Link :  $(OBJECTS) 	
		@$(CC) -o a.out $(OBJECTS)
		@echo
		@echo [빌드 완료]
		@echo 
		@echo

clean : 
		@echo remove *.o , a.out, *.gch in our project
		@rm ../Object/*.o
		@rm a.out
		@rm ../*.gch
		


##../Object/core.o ../Object/kijeong.o ../Object/machugi.o

## 후ㅜ.. 빌드에러 어떻게 grep 해서 넣는거ㅑㅇ아ㅓㅏㅏ아앙
