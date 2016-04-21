#include "stack.h"

void stack_init(Stack *s) {
    
    s->top = (StackNode *)malloc(sizeof(StackNode));
  
    if(s->top == NULL) {
        printf("Error init the Stack");
        exit(-1);
    } else {
        s->bottom = s->top;
        s->top->next == NULL;
    }
    return;
}

bool stack_put(Stack *s, int data) {
    StackNode * newStackNode = (StackNode *)malloc(sizeof(StackNode));
    if(newStackNode == NULL) {
        return false;
    } else {
        newStackNode->member = data;
        newStackNode->next = s->top;
        s->top = newStackNode;
        return true;
    }
}

bool stack_empty(Stack *s) {
    if(s->top == s->bottom) {
        return true;
    } else {
        return false;
    }
}

int stack_pop(Stack *s) {
    int tep;
    StackNode * stackSwap = NULL;
    
    if(stack_empty(s)) {
        exit(-1);
    } else {
        tep = s->top->member;
        stackSwap = s->top;
        s->top = s->top->next;
        free(stackSwap);
        return tep;     
    }
}

int stack_peek(Stack *s) {
    int tep;
    
    if(stack_empty(s)) {
        exit(-1);
    } else {
        tep = s->top->member;
        return tep;    
    }
}