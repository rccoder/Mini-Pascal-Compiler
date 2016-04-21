del *.o
del *.exe
gcc -c hashTable.c -o hashTable.o
gcc -c tokenUtil.c -o tokenUtil.o
gcc -c data.c -o data.o
gcc -c lex.c -o lex.o
gcc -c stack.c -o stack.o
gcc -c lrTable.c -o lrTable.o
gcc -c main.c -o main.o
gcc main.o hashTable.o tokenUtil.o data.o lex.o stack.o lrTable.o -o main.exe
main.exe
