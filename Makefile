


all: 
	gcc main.c -o file_manager.exe -lncurses 
			

clean:
		rm *.exe
		rm *~
