#ifndef STK
#define STK

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct StackNode {
    int member;
    struct StackNode * next;
};

typedef struct StackNode StackNode;

struct Stack {
    StackNode * top;
    StackNode * bottom;
    
};
typedef struct Stack Stack;

void stack_init(Stack *s);
bool stack_put(Stack *s, int data);
bool stack_empty(Stack *s);
int stack_pop(Stack *s);
int stack_peek(Stack *s);

#endif