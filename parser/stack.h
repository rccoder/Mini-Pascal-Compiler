#ifndef STK
#define STK

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct StackNode {
    char member[30];
    struct StackNode * next;
};

typedef struct StackNode StackNode;

struct Stack {
    StackNode * top;
    StackNode * bottom;
    
};
typedef struct Stack Stack;

void stack_init(Stack *s);
bool stack_put(Stack *s, char * data);
bool stack_empty(Stack *s);
char * stack_pop(Stack *s);
char * stack_peek(Stack *s);
void stack_test(Stack *s);
#endif