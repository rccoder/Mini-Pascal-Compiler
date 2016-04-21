
#include "lrTable.h"

// 初始化lrTable
void lrTable_init() {
    
    table = NULL;
    table = (lrTable **)malloc(TABLE_ROW * sizeof(lrTable *));
    if(table == NULL) {
        printf("Can't malloc the mem in lrTable");
        exit(-1);
    } else {
        for(int i = 0; i < TABLE_ROW; i++) {
            table[i] = (lrTable *)malloc(TABLE_COL * sizeof(lrTable));
            if(table[i] == NULL) {
                printf("Cant't malloc the mem in lrTable[i]");
            } else {
                
                // 用大多数情况随机一下
                for(int j = 0; j < TABLE_COL; j++) {
                    table[i][j].status = ERROR;
                    if(j <= ACTION_OR_GO_DIVIDE) {
                        table[i][j].len = 0;
                    } else {
                        table[i][j].len = -1;
                    }
                    table[i][j].content = NULL;
                }
                
            }
        }
        readTableFile();
    }
}


void readTableFile() {
    
    FILE * fp;
    char ch;
    
    int col = 0, row = 0;
    
    int line = 0, index = 0; 
    
    // 表中的内容，一个字占一行，假定最大字符串长度为100, 最多20个字
    char content[20][100];
    
    
    if((fp = fopen("LRTable.txt", "r")) == NULL){
       printf("Can't Open LRTable"); 
    } else {
        ch = fgetc(fp);
       
        while(ch != EOF) {
           
            if(ch == ' ') {
                // 中间空格的情况 —— 赋值，换行，索引归一
                content[line][index] = 0;
                line ++;
                index = 0;
            } else if(ch == '\n') {
                // 换行的情况
              
                content[line][index] = 0;
                line ++;
                // line 表示的是第几个词， 可以标志 content 是由多少个词组成的
                insertToTable(content, &col, &row, line);
                
                
                // 新content
                line = index = 0;
            } else {
                // 一个词的一个字 
                content[line][index] = ch;
                index++;
            }
            ch = fgetc(fp);
        }
        
        fclose(fp);
        return;
    }
}

void insertToTable(char content[20][100], int * col, int * row, int line) {
    
    
    int xrow = * row;
    int ycol = * col;
    int l = line - 1;
    
    
    // reduce term -> factor
    if(strcmp("reduce", content[0]) == 0) {
        
        table[xrow][ycol].status = REDUCE;
        table[xrow][ycol].len = l;
        table[xrow][ycol].content = (char **)malloc(l * sizeof(char *));
        
        if(table[xrow][ycol].content == NULL) {
            printf("Error in get mem for table[xrow][ycol].content");
            exit(-1);
        }
        
        for(int i = 0; i < l; i ++) {
            
            table[xrow][ycol].content[i] = (char*)malloc(100 * sizeof(char));
            
            if(table[xrow][ycol].content[i] == NULL) {
                printf("Error: get the mem for table[xrow][ycol].content[i]");
                exit(-1);
            } else {
                // 字符串复制，一整行的内容
                strcpy(table[xrow][ycol].content[i], content[i+1]); 
                 
            }
        }
        (* col) ++;
        
    // shift
    } else if(strcmp("shift", content[0]) == 0) {
        
        table[xrow][ycol].status = SHIFT;
        table[xrow][ycol].len = l;
        table[xrow][ycol].content = (char **)malloc(l * sizeof(char *));
        
        if(table[xrow][ycol].content == NULL) {
            printf("Error in get ..... in shift");
            exit(-1);
        }
        
        table[xrow][ycol].content[0] = (char*)malloc(100 * sizeof(char));
        
        if(table[xrow][ycol].content[0] == NULL) {
            printf("Error: get the mem for table[xrow][ycol].content[0] in shift");
            exit(-1);
        } else {
            strcpy(table[xrow][ycol].content[0], content[1]);
            (*col)++;    
        }
            
    // accept    
    }else if(strcmp("accept", content[0]) == 0) {
        
        table[xrow][ycol].status = ACCEPT;
        (*col) ++;
        
    // -1 error
    } else if(strcmp("-1", content[0]) == 0) {
        
        table[xrow][ycol].status = ERROR;
        (*col)++;
    
    // 表示 LR1 表的一行已经结束  
    } else if(strcmp("Lee", content[0]) == 0) {
        
        // 表的新一行
        (*row) ++;
        *col = 0;
    
    // goto 表
    } else {
        
        table[xrow][ycol].status = GOTO;
        table[xrow][ycol].len = atoi(content[0]);
        (*col) ++;
        
    }
    return;
    
}
