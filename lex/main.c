#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "./define.h"
#include "./util.h"
#include "./struct.h"

// there must be less than N token in token array
#define N 100000

// the value in token and it shoud be the largest length
#define M 256

// display the result on the screen
void display(Token token[], int tokenCount) {
    for(int j = 0; j < tokenCount; j++) {
            printf("(%s,", output[token[j]._type]);
            switch(token[j]._type) {
                case INT:
                    printf("%d", token[j]._data.i);
                    break;
                 case REAL:
                    printf("%f", token[j]._data.f);
                    break;
                default:
                    printf("%s", token[j]._data.c);
                    break;
            }
            printf(")\n");

        }
}


int main(int argc, char * argv[]) {



    char filename[100];

    //init the filename
    if(argc <= 1) {
        strcpy(filename, "test");
    } else {
        strcpy(filename, argv[1]);
    }

    // all of the token array

    Token token[N];

    // the number of the token in array
    int tokenCount = 0;

    FILE *fp;

    // open the file and catch the error
    if((fp = fopen(filename, "r")) == NULL) {
        printf("\nOpen File Error");
    }


    // the data will be pushed in the one of the token in arrays
    char tokenData[M];
    
    char ch;
    ch = fgetc(fp);


    int judgeQmark = 0;

    while(ch != EOF) {

        // spance TAB LF
        if(!(ch == 32 || ch == 9|| ch == 10)) {

            // id and other important word
            if(isalpha(ch)) {

                tokenData[0] = ch;
                tokenData[1] = '\0';

                ch = fgetc(fp);

                while(isalnum(ch)) {
                    //printf("%c", ch);
                    pushToken(tokenData, ch);
                    ch = fgetc(fp);
                }

                // fseek, back the cache
                fseek(fp, -1L, SEEK_CUR);
               
                checkIdentifier(tokenData, &token[tokenCount]._type, &token[tokenCount]._data.c);
                

            } else if(isdigit(ch)) {

                tokenData[0] = ch;
                tokenData[1] = '\0';

                ch = fgetc(fp);

                // real number
                if(ch == '.') {
                    
                    pushToken(tokenData, ch);
                    ch = fgetc(fp);
                    
                    while(isdigit(ch)) {
                        pushToken(tokenData, ch);
                        ch = fgetc(fp);
                    }
                    
                    fseek(fp, -1L, SEEK_CUR);
                    
                     token[tokenCount]._type = REAL;
                     token[tokenCount]._data.f =  atof(tokenData);
                     
                } else {
                    // int
                    while(isdigit(ch)) {

                        
                        pushToken(tokenData, ch);
                        ch = fgetc(fp);
                    }

                    fseek(fp, -1L, SEEK_CUR);
                    
                    token[tokenCount]._type = INT;
                    token[tokenCount]._data.i =  atoi(tokenData);
                }
                

            } else switch(ch) {
                case '*': 
                    ch = fgetc(fp);
                    if(ch == '*') {

                        pushToToken(EXP, &token[tokenCount]._type, &token[tokenCount]._data.c);
                        
                    } else {
                        fseek(fp, -1L, SEEK_CUR);

                        pushToToken(MULTI, &token[tokenCount]._type, &token[tokenCount]._data.c);
                        
                    }
                    break;
                case ':':
                    ch = fgetc(fp);
                    if(ch == '=') {
                        pushToToken(ASSIGN, &token[tokenCount]._type, &token[tokenCount]._data.c);
                        
                    } else {
                        fseek(fp, -1L, SEEK_CUR);
                        
                        pushToToken(COLON, &token[tokenCount]._type, &token[tokenCount]._data.c);
                    }
                    break;
                case '<':
                    ch = fgetc(fp);
                    if(ch == '=') {
                        
                        pushToToken(LE, &token[tokenCount]._type, &token[tokenCount]._data.c);
                        
                    } else if(ch == '>') {
                        
                        pushToToken(NE, &token[tokenCount]._type, &token[tokenCount]._data.c);
                        
                    } else {
                        fseek(fp, -1L, SEEK_CUR);
                        
                        pushToToken(LT, &token[tokenCount]._type, &token[tokenCount]._data.c);
                        
                    }
                    break;
                case '=':
                    
                    pushToToken(EQ, &token[tokenCount]._type, &token[tokenCount]._data.c);
                    
                    break;
                case '>':
                    ch = fgetc(fp);
                    if(ch == '=') {
                        
                        pushToToken(GE, &token[tokenCount]._type, &token[tokenCount]._data.c);
                        
                    } else {
                        fseek(fp, -1L, SEEK_CUR);
                        
                        pushToToken(GT, &token[tokenCount]._type, &token[tokenCount]._data.c);
                        
                    }
                    break;
                case '+':
                    
                    pushToToken(PLUS, &token[tokenCount]._type, &token[tokenCount]._data.c);
                   
                    break;
                case '-':
                    
                    pushToToken(MINUS, &token[tokenCount]._type, &token[tokenCount]._data.c);
                    
                    break;
                case '/':
                    
                    pushToToken(RDIV, &token[tokenCount]._type, &token[tokenCount]._data.c);
                    
                    break;
                case ',':
                    
                    pushToToken(COMMA, &token[tokenCount]._type, &token[tokenCount]._data.c);
                   
                    break;
                case ';':
                    
                    pushToToken(SEMIC, &token[tokenCount]._type, &token[tokenCount]._data.c);
                    
                    break;
                case '(':

                    pushToToken(LR_BRAC, &token[tokenCount]._type, &token[tokenCount]._data.c);
                    
                    break;
                case ')':
                    
                    pushToToken(RR_BRAC, &token[tokenCount]._type, &token[tokenCount]._data.c);
                    
                    break;
                case '[':
                    
                    pushToToken(LS_BRAC, &token[tokenCount]._type, &token[tokenCount]._data.c);
                    
                    break;
                case ']':
                    
                    pushToToken(RS_BRAC, &token[tokenCount]._type, &token[tokenCount]._data.c);
                    
                    break;
                case '`':
                    
                    pushToToken(P_MARK, &token[tokenCount]._type, &token[tokenCount]._data.c);

                    break;
                case '^':
                    
                    pushToToken(CAP, &token[tokenCount]._type, &token[tokenCount]._data.c);

                    break;
                case '\'':
                    
                    pushToToken(Q_MARK, &token[tokenCount]._type, &token[tokenCount]._data.c);
                    
                    ch = fgetc(fp);
                    tokenData[0] = '\0';
                    
                    judgeQmark = 0;
                    tokenCount ++;
                    
                    // string
                    while(isalnum(ch)) {
                        
                        judgeQmark = 1;    
                        
                        pushToken(tokenData, ch);
                        
                        ch = fgetc(fp);
                        
                        if(ch == '\'') {
                            token[tokenCount]._type = STRING;
                            token[tokenCount]._data.c = (char*)malloc(2);
                            strcpy(token[tokenCount]._data.c, tokenData); 
                            
                            fseek(fp, -1L, SEEK_CUR);
                        
                        }
                    }
                    
                    if(!judgeQmark) {
                        tokenCount --;
                    }
                    
                    //pushToToken(Q_MARK, &token[tokenCount]._type, &token[tokenCount]._data.c);

                    break;
                case '.':

                    pushToToken(F_STOP, &token[tokenCount]._type, &token[tokenCount]._data.c);

                default:
                    break;
            }

            tokenCount ++;
        } else {

        }

        ch = fgetc(fp);
    }
    
    fclose(fp);

    display(token, tokenCount);

    return 0;
}