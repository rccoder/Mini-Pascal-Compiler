#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


typedef struct stack {
   stackNode top;
   
} Stack;

Stack * initStack() {
    Stack * p = null;
    p = (Stack*) malloc (sizeof(Stack));
    if(p) {
        p->top = 0;
    }
    return p;
}

int pushStack(Stack * stack, int data) {
    stack->a[]
}

int main(int argc, char * argv[])
{
    int a = 0;
    a += 'c';
    printf("%d", a);
    return 0;
}