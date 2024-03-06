a.exe: main.c object/box.o include/box.h
	gcc main.c object/box.o
object/box.o: header/box.h header/error.h source/box.c
	gcc -c source/box.c -o object/box.o