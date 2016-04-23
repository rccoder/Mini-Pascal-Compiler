
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

char * lrTable_getContentZero(lrTable ** table, int row, int col);
int lrTable_getStatus(lrTable ** table, int row, int col);
void lrTable_test(lrTable ** table);
void insertToTable(lrTable ** table, char content[20][100], int * col, int * row, int line);
void readTableFile(lrTable ** table);
void lrTable_build(lrTable *** table);

#endif
