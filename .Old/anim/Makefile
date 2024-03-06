FLAGS = -Wall

a.exe: main.c object/load.o object/anim.o
	gcc $(FLAGS) main.c object/load.o object/anim.o ../wstr/object/wstr.o

# object/anim.c:
# 	gcc -c source/box.c -o object/box.o

# object/anim.c:
# 	gcc -c source/anim.c -o object/anim.o

object/load.o: source/load.c header/anim.h header/error.h header/dim.h ../wstr/include/wstr.h
	gcc -c $(FLAGS) source/load.c -o object/load.o

object/anim.o: source/anim.c header/anim.h header/error.h header/dim.h
	gcc -c $(FLAGS) source/anim.c -o object/anim.o



