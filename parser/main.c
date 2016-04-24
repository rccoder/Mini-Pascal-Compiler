#include "stadfx.h"

// there must be less than N token in token array
#define N 100000

// the value in token and it shoud be the largest length
#define M 256



void readFile(FILE **fp);
void closeFile(FILE ** fp);
// void lex(FILE *fp, Token token[], int * tokenCountPointer);
void initHashTable(HashTable * hashtable);
void display(Token token[], int tokenCount);



int main(int argc, char * argv[]) {

    /* 词法分析开始 */
    
    // all of the token array
    Token token[N];
    
    // the number of the token in array
    int tokenCount = 0;
    
    FILE *fp;

    readFile(&fp);

    // init the hashtable
    // HashTable * hashtable = hashtable_init(N);
    
    // initHashTable(hashtable);
    

    lex(fp, token, &tokenCount);
    
    closeFile(&fp);

    display(token, tokenCount);
    
    /* 词法分析结束 */
    
    // 语法分析开始
    
    // 构建 状态栈，归约栈
    Stack statusStack, reduceStack;
    
    stack_init(&statusStack);
    stack_init(&reduceStack);
    
    // 构建 LR1 分析表
    lrTable ** table;
   
    lrTable_build(&table);
    
    parse(token, tokenCount, &statusStack, &reduceStack, table);
   
    
    /* 语法分析结束 */
    
    return 0;
}





void readFile(FILE ** fp) {

    //char filename[100];

    /*
    // init the filename
    if(argc <= 1) {
        strcpy(filename, "test");
    } else {
        strcpy(filename, *argv[1]);
    }
    */
    // open the file and catch the error
    if((*fp = fopen("test", "r")) == NULL) {
        printf("\nOpen File Error");
    }

}

void closeFile(FILE ** fp) {
    fclose(*fp);
}



void initHashTable(HashTable * hashtable) {
    hashtable_put(hashtable, "a", "v");
    hashtable_put(hashtable, "b", "dxxx");
    hashtable_put(hashtable, "d", "dxxxxxxxxxxxxxxxxx");
    hashtable_put(hashtable, "d", "d");
    
    printf("%s", hashtable_get(hashtable, "d"));
    printf("%s", hashtable_get(hashtable, "c"));
    printf("%d", hashtable->item_size);
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