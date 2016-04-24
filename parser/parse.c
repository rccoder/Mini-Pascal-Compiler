#include "parse.h"

// 根据关键词得到在 table 里面的 col
int getTableIndex(char * key) {
    for(int col = 0; col < 200; col++) {
        if(strcmp(key_table[col], key) == 0) {
            return col;
        }
    }
    return -1;
}

// go 状态转移函数
bool go(lrTable ** table, Stack * statusStack, Stack * reduceStack) {
    
    
    int xGo = atoi(stack_peek(statusStack));
    int yGo= getTableIndex(stack_peek(reduceStack));
    
    char * goPurpose = (char *)malloc(42 * sizeof(char));
    printf("XGo: %d YGO: %d\n", xGo, yGo);
    if(table[xGo][yGo].status == GOTO) {
        
        //printf("go to %s\n", table[xGo][yGo].content[0]); 
        if(table[xGo][yGo].len != -1) {
            // 查到的值   
            strcpy(goPurpose, table[xGo][yGo].content[0]);
            // 压入栈
            stack_put(statusStack, goPurpose);
            printf("goto: statusStack put %s\n", goPurpose);
            return true;    
        } else {
            printf("Error: goto is none!\n");
        }
       
    }
     printf("%d bbbbbbbbbbbbbb\n", table[xGo][yGo].status);
    return false;
}

void shift(Stack * statusStack, Stack * reduceStack, char * statusInput, char * reduceInput) {
    
    printf("shift to %s\n", statusInput);
    
    // 状态栈压入 shift 到的状态
    stack_put(statusStack, statusInput);
    printf("statusStack put %s\n", statusInput);
    
    // 归约栈压入 新进入的字符串
    stack_put(reduceStack, reduceInput);
    printf("reduceStack put %s\n", reduceInput);
}

bool reduce(lrTable ** table, Stack * statusStack, Stack * reduceStack, char * reduceInput, int x, int y) {
    printf("reduce: ");
    int count;
    for(int i = 0, count = 0; i < table[x][y].len; i ++) {
        printf("%s", table[x][y].content[i]);
        count ++;
    }
    printf("\n");
    
   
    if(strcmp(table[x][y].content[2], "e") == 0) {
        stack_put(reduceStack, table[x][y].content[0]);
        printf("reduceStack put %s Empty\n", table[x][y].content[0]);
        return go(table, statusStack, reduceStack);
    } else {
        // 弹出次数 A -> B D  (4 - 2)
        for(int i = 0; i < table[x][y].len-2; i++) {
            // 弹出状态栈
            stack_pop(statusStack);
            printf("statusStack pop\n");
            
            // 状态栈归约，压入新的东西
            stack_pop(reduceStack);
            printf("reduceStack pop\n");    
        }
        // 归约出的东西
        stack_put(reduceStack, table[x][y].content[0]);
        printf("reduceStack put %s\n", table[x][y].content[0]);
        
        // go 表查询
        return go(table, statusStack, reduceStack);
    } 
    
    
    
}


// 语法分析主程序
void parse(Token token[], int tokenCount, Stack * statusStack, Stack * reduceStack, lrTable ** table) {
    
    // 给 状态栈压 #
    
    stack_put(statusStack, "0");
    printf("statusStack put 0\n");
    
    stack_put(reduceStack, "#");
    printf("reduceStack put #\n");
    
    for(int i = 0; i < tokenCount; i++) {
       R:
            printf("\n");
            // 即将进来的字符串
            char * commingString = (char *)malloc(20 * sizeof(char));
            // 发生移进的时候将要shift 到的状态，字符串形式 
            char * shiftPurpose= (char *)malloc(42 * sizeof(char));
            
            strcpy(commingString, parseOutput[token[i]._type]);
            printf("\nInput: %s\n", commingString);
            
            
            int tableIndex = getTableIndex(commingString);
            int  tableX= atoi(stack_peek(statusStack));
            //printf("%d-%d\n", tableIndex, tableY);
            
            int tableStatus = lrTable_getStatus(table, tableX, tableIndex);
            
            // 判断目前查表状态
            switch(tableStatus) {
                case ERROR:
                        printf("tableX: %d tableIndex %d\n", tableX, tableIndex);
                        printf("Syntax Error!\n");
                        exit(-1);
                        break;
                case ACCEPT:
                        printf("Accept too early\n");
                        
                        break;
                case REDUCE:
                
                        if(!reduce(table, statusStack, reduceStack, commingString, tableX, tableIndex)) {
                            printf("X: %d Y: %d\n", tableX, tableIndex);
                            printf("%d ", table[tableX][tableIndex].status);
                            printf("%d\n", table[tableX][tableIndex].len);
                            printf("content1:%s\n", table[tableX][tableIndex].content[0]);
                            printf("content2:%s\n", table[tableX][tableIndex].content[1]);
                            printf("content3:%s\n", table[tableX][tableIndex].content[2]);
                            printf("Reduce error!\n");
                        } else {
                            goto R;
                        }
                        break;
                case SHIFT:
                        
                        // example shift 56   will return "56"
                        strcpy(shiftPurpose, lrTable_getContentZero(table, tableX, tableIndex));
                        
                        shift(statusStack, reduceStack, shiftPurpose, commingString);
                        break;
            }
            
            
            //lrTable_getStatus(table, row, col);
    }
    
    //stack_test(statusStack);
}

/*
char * getTokenValue(Token tokenNow) {
    char * tep = (char*)malloc(30*sizeof(char));
    
    switch(tokenNow._type) {
        case INT:
            strcpy(tep, itoa(tokenNow._data.i));
            break;
        case REAL:
            strcpy(tep, itoa(tokenNow._data.i));
            break;
        default:
            break; 
    }
    return tep;
}
*/