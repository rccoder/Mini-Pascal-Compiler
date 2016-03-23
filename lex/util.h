#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

const char KEY_WORDS[64][10] = { "", 
                                "AND", "ARRAY", "BEGIN", "CASE",
                                "CONST", "DIV", "DO", "DOWNTO",
                                "ELSE", "END", "_FILE", "FOR",
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


// 给字符串添加一个子串
// 直接改变传进来的字符串
void pushToken(char * tokenData, char pushch) {
    int length = strlen(tokenData);
    tokenData[length] = pushch;
    tokenData[length+1] = '\0';
}
