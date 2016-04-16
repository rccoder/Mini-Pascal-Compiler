#include "stdafx.h"
#include "struct.h"
#include "../lib/hash.c"

const char output[64][10] = { "", 
                                "AND", "ARRAY", "BEGIN", "CASE",
                                "CONST", "DIV", "DO", "DOWNTO",
                                "ELSE", "END", "FILE", "FOR",
                                "FUNCTION", "GOTO", "IF", "IN",
                                "LABEL", "MOD", "NIL", "NOT",
                                "OF", "OR", "PACKED", "PROCEDURE",
                                "PROGRAM", "RECORD", "REPEAT", "SET",
                                "THEN", "TO", "TYPE", "UNTIL",
                                "VAR", "WHILE", "WITH", "ID",
                                "INT", "REAL", "STRING", "PLUS",
                                "MINUS", "MULTI", "RDIV", "EQ",
                                "LT", "GT", "LE", "GE",
                                "NE", "LR_BRAC", "RR_BRAC", "COMMA",
                                "P_MARK", "F_STOP", "RANGE", "COLON",
                                "ASSIGN", "SEMIC", "CAP", "EXP",
                                "LS_BRAC", "RS_BRAC", "Q_MARK" };

const char key_words[64][10] = { "", "and", "array", "begin", "case",
                                    "const", "div", "do", "downto",
                                    "else", "end", "file", "for",
                                    "function", "goto", "if", "in",
                                    "label", "mod", "nil", "not",
                                    "of", "or", "packed", "procedure",
                                    "program", "record", "repeat", "set",
                                    "then", "to", "type", "until",
                                    "var", "while", "with", "id",
                                    "int", "real", "string", "plus",
                                    "minus", "multi", "rdiv", "eq",
                                    "lt", "gt", "le", "ge", "ne",
                                    "lr_brac", "rr_brac", "comma",
                                    "p_mark", "f_stop", "range", "colon",
                                    "assign", "semic", "cap", "exp",
                                    "ls_brac", "rs_brac", "q_mark" };


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

