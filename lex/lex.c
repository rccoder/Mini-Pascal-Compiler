#include "lex.h"

// there must be less than N token in token array
#define N 100000

// the value in token and it shoud be the largest length
#define M 256

void lex(FILE *fp, Token token[], int * tokenCountPointer) {
    
    int tokenCount = * tokenCountPointer;
    // the data will be pushed in the one of the token in arrays
    char tokenData[M];
    
    char ch;
    int judgeQmark = 0;
    
    ch = fgetc(fp);
    while(ch != EOF) {
        
        // spance TAB LF
        if(!(ch == 32 || ch == 9|| ch == 10)) {
            // 去掉注释
            if(ch == '/') {
        
                if(ch == '/') {
                    // 消除歧义
                    tokenCount --;
                    ch = fgetc(fp); 
                    while(ch != '\n'){
                        ch = fgetc(fp);
                    }
                    
                }
                fseek(fp, -1L, SEEK_CUR);
            }
            // id and other important word
            if(isalpha(ch)) {

                tokenData[0] = ch;
                tokenData[1] = '\0';

                ch = fgetc(fp);
                
                int strLength = 0;
                while(isalnum(ch)) {
                    strLength++;
                    //printf("%c", ch);
                    pushToken(tokenData, ch);
                    ch = fgetc(fp);
                    if(strLength > 200) {
                        printf("Error");
                    }
                }
                       
                if(ch == '?') {
                    printf("Error");
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
                        ch = fgetc(fp);
                        // :==错误
                        if(ch == '=') {
                            printf("Error in: :==\n");
                            tokenCount --;
                        } else {
                            fseek(fp, -1L, SEEK_CUR);
                            pushToToken(ASSIGN, &token[tokenCount]._type, &token[tokenCount]._data.c);    
                        }
                        
                        
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
                    if(isalnum(ch)) {
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
                    } else {
                        fseek(fp, -1L, SEEK_CUR);
                    }
                    
                    
                    if(!judgeQmark) {
                        tokenCount --;
                    }
                    
                    //pushToToken(Q_MARK, &token[tokenCount]._type, &token[tokenCount]._data.c);

                    break;
                case '.':
                
                    //printf("1%c\n", ch);
                   //printf("3\n");
                    ch = fgetc(fp);
                    //printf("2%c\n", ch);
                    //ch = fgetc(fp);
                    //printf("4%c\n", ch);
                    if(ch == '.') {
                        pushToToken(RANGE, &token[tokenCount]._type, &token[tokenCount]._data.c);
                    } else {
                        
                        //fseek(fp, -1L, SEEK_CUR);
                        pushToToken(F_STOP, &token[tokenCount]._type, &token[tokenCount]._data.c);    
                    }
                    
                  //  pushToToken(F_STOP, &token[tokenCount]._type, &token[tokenCount]._data.c);
                    break;
                default:
                    break;
            }

            tokenCount ++;
        } else {

        }

        ch = fgetc(fp);
    }
    
    * tokenCountPointer = tokenCount;
}