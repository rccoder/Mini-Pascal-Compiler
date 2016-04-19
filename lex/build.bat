del *.o
del *.exe
gcc -c hashTable.c -o hashTable.o
gcc -c tokenUtil.c -o tokenUtil.o
gcc -c data.c -o data.o
gcc -c lex.c -o lex.o
gcc -c main.c -o main.o
gcc main.o hashTable.o tokenUtil.o data.o lex.o -o main.exe
main.exe
