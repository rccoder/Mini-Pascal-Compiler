#include "tokenUtil.h"
/* 
 * push the char pusch to the string called tokenData
 */
void pushToken(char * tokenData, char pushch) {
    int length = strlen(tokenData);
    tokenData[length] = pushch;
    tokenData[length+1] = '\0';
}


/*
 * check the ID and others, and the return the token which was chenged
 * 这里应该优化
 */
void checkIdentifier(char * tokenData, int * type, char ** c)
{
    int flag = 1;
    // 在符号表里找到
    for(int i = 1; i < 36; i++) {
        if(strcmp(tokenData, key_words[i]) == 0) {
            flag = 0;
            *type = i; 
            *c = (char*)malloc(2);
            strcpy(*c, " "); 
        }
    }
    // 没有找到
    if (flag) {
        *type = ID;
        *c = (char*)malloc(sizeof(tokenData));
        strcpy(*c, tokenData);
    }
}

void pushToToken(int defineNum, int * type, char ** c) {
    *type = defineNum;
    *c = (char*)malloc(sizeof(2));
    strcpy(*c, " ");
}



