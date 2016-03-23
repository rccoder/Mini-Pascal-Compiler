#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "./define.h"
#include "./util.h"

// 能有多少个token
#define N 100000
// token 中的字符串的最大位数
#define M 256

// 定义联合体，存储 token 中的值
union S
{
    int i;
    float f;
    char * c;
};

// Token 结构体的定义
// _type
// _data
typedef struct token
{
    int _type;
    union S _data;
} Token;


int main() {

    // 所有的token数组
    Token token[N];
    int tokenCount = 0;

    FILE *fp;

    if((fp = fopen("./test", "r")) == NULL) {
        printf("\nOpen File Error");
    }


    char tokenData[M];
    // 开始扫描文件
    char ch;
    ch = fgetc(fp);


    while(ch != EOF) {

        // spance TAB LF(换行)，直接略过继续扫描
        if(!(ch == 32 || ch == 9|| ch == 10)) {

            // ID+标志符
            if(isalpha(ch)) {

                //printf("(ID,");
                //printf("%c", ch);
                tokenData[0] = ch;
                tokenData[1] = '\0';

                ch = fgetc(fp);

                while(isalnum(ch)) {
                    //printf("%c", ch);
                    pushToken(tokenData, ch);
                    ch = fgetc(fp);
                }
                fseek(fp, -1L, SEEK_CUR);
                //printf(")\n");
                token[tokenCount]._type = ID;
                token[tokenCount]._data.c = tokenData;

            } else if(isdigit(ch)) {

                tokenData[0] = ch;
                tokenData[1] = '\0';

                //printf("(INT,");

                ch = fgetc(fp);

                while(isdigit(ch)) {

                    //printf("%c", ch);
                    pushToken(tokenData, ch);
                    ch = fgetc(fp);
                }

                fseek(fp, -1L, SEEK_CUR);
                //printf(")\n");
                token[tokenCount]._type = INT;
                token[tokenCount]._data.i =  atoi(tokenData);

            } else switch(ch) {
                case '*': 
                    ch = fgetc(fp);
                    if(ch == '*') {
                        token[tokenCount]._type = EXP;
                        //printf("(EXP,%c%c)\n", tep, ch);
                    } else {
                        fseek(fp, -1L, SEEK_CUR);
                        token[tokenCount]._type = MULTI;

                        //printf("(MULTI,%c)\n", tep);
                    }
                    break;
                case ':':
                    ch = fgetc(fp);
                    if(ch == '=') {
                        token[tokenCount]._type = ASSIGN;
                        //printf("(ASSIGN,%c%c)\n", tep, ch);
                    } else {
                        fseek(fp, -1L, SEEK_CUR);
                        //printf("(COLON,%c\n", tep);
                        token[tokenCount]._type = COLON;
                    }
                    break;
                case '<':
                    ch = fgetc(fp);
                    if(ch == '=') {
                        token[tokenCount]._type = LE;
                        //printf("(LE,%c%c)\n", tep, ch);
                    } else if(ch == '>') {
                        token[tokenCount]._type = NE;
                        //printf("(NE,%c%c)\n", tep, ch);
                    } else {
                        fseek(fp, -1L, SEEK_CUR);
                        token[tokenCount]._type = LT;
                        //printf("(LT,%c)\n", tep);
                    }
                    break;
                case '=':
                    token[tokenCount]._type = EQ;
                    //printf("(EQ,%c)\n", ch);
                    break;
                case '>':
                    ch = fgetc(fp);
                    if(ch == '=') {
                        token[tokenCount]._type = GE;
                        //printf("(GE,%c%c)\n", tep, ch);
                    } else {
                        fseek(fp, -1L, SEEK_CUR);
                        token[tokenCount]._type = GT;
                        //printf("(GT,%c)\n", tep);
                    }
                    break;
                case '+':
                    token[tokenCount]._type = PLUS;
                    //printf("(PLUS,%c)\n", ch);
                    break;
                case '-':
                    token[tokenCount]._type = MINUS;
                    //printf("(MINUS,%c)\n", ch);
                    break;
                case '/':
                    token[tokenCount]._type = RDIV;
                    //printf("(RDIV,%c)\n", ch);
                    break;
                case ',':
                    token[tokenCount]._type = COMMA;
                    //printf("(COMMA,%c)\n", ch);
                    break;
                case ';':
                    token[tokenCount]._type = SEMIC;
                    //printf("(SEMIC,%c)\n", ch);
                    break;
                default:
                    break;
            }
            //printf("%c\n", ch);
            // token 数组下标 +1
            tokenCount ++;
        } else {

        }

        ch = fgetc(fp);
    }

    for(int i = 0; i < tokenCount; i++) {
        printf("%s===>%d===>", KEY_WORDS[token[i]._type], token[i]._type);
        switch(token[i]._type) {
            case INT:
                printf("%d", token[i]._data.i);
                break;
            default:
                printf("%s", token[i]._data.c);
                break;
        }
        printf("\n");

    }
    fclose(fp);
    return 0;
}