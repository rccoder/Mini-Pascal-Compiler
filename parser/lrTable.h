
#ifndef LRT
#define LRT

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_ROW 2230
#define TABLE_COL 200

#define ERROR -1
#define ACCEPT 0
#define REDUCE 1
#define SHIFT 2
#define GOTO 3



#define ACTION_OR_GO_DIVIDE 65

struct lrTable {
    char ** content;
    int status;
    int len;  
};

typedef struct lrTable lrTable;

lrTable ** table;

void lrTable_test();
void insertToTable(char content[20][100], int * col, int * row, int line);
void readTableFile();
void lrTable_init();

#endif
