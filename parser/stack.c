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

bool stack_put(Stack *s, char * data) {
    StackNode * newStackNode = (StackNode *)malloc(sizeof(StackNode));
    if(newStackNode == NULL) {
        return false;
    } else {
        strcpy(newStackNode->member, data);
        // newStackNode->member = data;
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

char * stack_pop(Stack *s) {
    char * tep = (char *)malloc(30*sizeof(char));
    StackNode * stackSwap = NULL;
    
    if(stack_empty(s)) {
        exit(-1);
    } else {
        strcpy(tep, s->top->member);
        //tep = s->top->member;
        stackSwap = s->top;
        s->top = s->top->next;
        free(stackSwap);
        return tep;     
    }
}

char * stack_peek(Stack *s) {
    char * tep = (char *)malloc(30*sizeof(char));
    
    if(stack_empty(s)) {
        exit(-1);
    } else {
        strcpy(tep, s->top->member);
        //tep = s->top->member;
        return tep;    
    }
}

void stack_test(Stack *s) {
    
    printf("Here is stack test function:\n");
    stack_put(s, "1");
    stack_put(s, "22");
    stack_put(s, "33");
    
    printf("%s", stack_pop(s));
    printf("%s", stack_peek(s));
}