#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "./define.h"
#include "./util.h"
#include "./struct.h"
// 能有多少个token
#define N 100000
// token 中的字符串的最大位数
#define M 256

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

                tokenData[0] = ch;
                tokenData[1] = '\0';

                ch = fgetc(fp);

                while(isalnum(ch)) {
                    //printf("%c", ch);
                    pushToken(tokenData, ch);
                    ch = fgetc(fp);
                }
                fseek(fp, -1L, SEEK_CUR);
               
                checkIdentifier(tokenData, &token[tokenCount]._type, &token[tokenCount]._data.c);
                

            } else if(isdigit(ch)) {

                tokenData[0] = ch;
                tokenData[1] = '\0';

                ch = fgetc(fp);

                while(isdigit(ch)) {

                    
                    pushToken(tokenData, ch);
                    ch = fgetc(fp);
                }

                fseek(fp, -1L, SEEK_CUR);
                
                token[tokenCount]._type = INT;
                token[tokenCount]._data.i =  atoi(tokenData);

            } else switch(ch) {
                case '*': 
                    ch = fgetc(fp);
                    if(ch == '*') {
                        token[tokenCount]._type = EXP;
                        token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                        strcpy(token[tokenCount]._data.c, " ");
                        
                    } else {
                        fseek(fp, -1L, SEEK_CUR);
                        token[tokenCount]._type = MULTI;
                        token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                        strcpy(token[tokenCount]._data.c, " ");

                    }
                    break;
                case ':':
                    ch = fgetc(fp);
                    if(ch == '=') {
                        token[tokenCount]._type = ASSIGN;
                        token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                        strcpy(token[tokenCount]._data.c, " ");
                        
                    } else {
                        fseek(fp, -1L, SEEK_CUR);
                        
                        token[tokenCount]._type = COLON;
                        token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                        strcpy(token[tokenCount]._data.c, " ");
                    }
                    break;
                case '<':
                    ch = fgetc(fp);
                    if(ch == '=') {
                        token[tokenCount]._type = LE;
                        token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                        strcpy(token[tokenCount]._data.c, " ");
                        
                    } else if(ch == '>') {
                        token[tokenCount]._type = NE;
                        token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                        strcpy(token[tokenCount]._data.c, " ");
                        
                    } else {
                        fseek(fp, -1L, SEEK_CUR);
                        token[tokenCount]._type = LT;
                        token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                        strcpy(token[tokenCount]._data.c, " ");
                        
                    }
                    break;
                case '=':
                    token[tokenCount]._type = EQ;
                    token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                    strcpy(token[tokenCount]._data.c, " ");
                    
                    break;
                case '>':
                    ch = fgetc(fp);
                    if(ch == '=') {
                        token[tokenCount]._type = GE;
                        token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                        strcpy(token[tokenCount]._data.c, " ");
                        
                    } else {
                        fseek(fp, -1L, SEEK_CUR);
                        token[tokenCount]._type = GT;
                        token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                        strcpy(token[tokenCount]._data.c, " ");
                        
                    }
                    break;
                case '+':
                    token[tokenCount]._type = PLUS;
                    token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                    strcpy(token[tokenCount]._data.c, " ");
                   
                    break;
                case '-':
                    token[tokenCount]._type = MINUS;
                    token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                    strcpy(token[tokenCount]._data.c, " ");
                    
                    break;
                case '/':
                    token[tokenCount]._type = RDIV;
                    token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                    strcpy(token[tokenCount]._data.c, " ");
                    
                    break;
                case ',':
                    token[tokenCount]._type = COMMA;
                    token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                    strcpy(token[tokenCount]._data.c, " ");
                   
                    break;
                case ';':
                    token[tokenCount]._type = SEMIC;
                    token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                    strcpy(token[tokenCount]._data.c, " ");
                    
                    break;
                case '(':
                    token[tokenCount]._type = LR_BRAC;
                    token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                    strcpy(token[tokenCount]._data.c, " ");
                    
                    break;
                case ')':
                    token[tokenCount]._type = RR_BRAC;
                    token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                    strcpy(token[tokenCount]._data.c, " ");
                    
                    break;
                case '[':
                    token[tokenCount]._type = LS_BRAC;
                    token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                    strcpy(token[tokenCount]._data.c, " ");
                    
                    break;
                case ']':
                    token[tokenCount]._type = RS_BRAC;
                    token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                    strcpy(token[tokenCount]._data.c, " ");
                    
                    break;
                case '.':
                    token[tokenCount]._type = F_STOP;
                    token[tokenCount]._data.c = (char*)malloc(sizeof(2));
                    strcpy(token[tokenCount]._data.c, " ");
                default:
                    break;
            }

            tokenCount ++;
        } else {

        }

        ch = fgetc(fp);
    }
    
    fclose(fp);

    for(int j = 0; j < tokenCount; j++) {
        printf("(%s,", output[token[j]._type]);
        switch(token[j]._type) {
            case INT:
                printf("%d", token[j]._data.i);
                break;
            default:
                printf("%s", token[j]._data.c);
                break;
        }
        printf(")\n");

    }
    return 0;
}