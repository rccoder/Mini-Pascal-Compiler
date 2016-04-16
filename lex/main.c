#include "stdafx.h"
#include "./define.h"
// #include "./util.h"
#include "./struct.h"
// #include "../lib/hash.c"

// there must be less than N token in token array
#define N 100000

// the value in token and it shoud be the largest length
#define M 256

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


// hash method
int hash(char * key, int size) {
    int rect = 0;
    while(*key != '\0') {
        rect += *key;  
        key ++;
    }
    return rect%size;
}

// init hashtable
HashTable * hashtable_init(int size) {
    
    HashTable * hashtable = (HashTable*)calloc(1, sizeof(HashTable));
    hashtable->size = size;
    hashtable->item_size = 0;
    
    // 开最大长度的空间
    HashNode * head = (HashNode*)calloc(size, sizeof(HashNode));
    
    hashtable->head = head;
    
    return hashtable;
}

// put a var in hashtable
HashTable * hashtable_put(HashTable *hashtable, char * key, char * value) {
    
    int index = hash(key, hashtable->size);
    
    HashNode *hashNode = hashtable->head + index;
    
    while(true) {
        // 曾经没有的情况 或者 有，并且第一个就是
        if(hashNode->key == NULL || *key == *(hashNode->key)) {
            
            if(hashNode->key == NULL) {
                hashtable->item_size = hashtable->item_size + 1;
            }
            
            hashNode->key = key;
            hashNode->value = value;
            return 0;
        }
        
        // 冲突
        // 下一个节点还不是空
        if(hashNode->key != NULL) {
            hashNode = hashNode->next;
            // 下个节点是空了，加数据
        } else {
            HashNode * newNode = (HashNode*)calloc(1, sizeof(HashNode));
            newNode->key = key;
            newNode->value = value;
            hashNode->next = newNode;
            hashtable->item_size = hashtable->item_size + 1;
            return 0;
        }
    }
}

// get a var
char * hashtable_get(HashTable * hashtable, char * key) {
    int index = hash(key, hashtable->size);
    HashNode *hashNode = hashtable->head + index;
    
    while(hashNode != NULL) {
        if(hashNode->key != NULL && *key == *(hashNode->key)) {
            return hashNode->value;
        }
        hashNode = hashNode->next;
    }
    return NULL;
}


void initHashTable(HashTable * hashtable) {
/*    
    hashtable_put(hashtable, "a", "v");
    hashtable_put(hashtable, "b", "dxxx");
    hashtable_put(hashtable, "d", "dxxxxxxxxxxxxxxxxx");
    hashtable_put(hashtable, "d", "d");
    
    printf("%s", hashtable_get(hashtable, "d"));
    printf("%s", hashtable_get(hashtable, "c"));
    printf("%d", hashtable->item_size);
*/
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
    
    // init the hashtable
    HashTable * hashtable = hashtable_init(N);
    
    initHashTable(hashtable);
    
    ch = fgetc(fp);


    int judgeQmark = 0;

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
    
    fclose(fp);

    display(token, tokenCount);

    return 0;
}