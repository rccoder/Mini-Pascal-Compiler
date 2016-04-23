
#ifndef PAR
#define PAR

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tokenUtil.h"
#include "stack.h"
#include "lrTable.h"


int getTableIndex(char * key);
bool go(lrTable ** table, Stack * statusStack, Stack * reduceStack);
void shift(Stack * statusStack, Stack * reduceStack, char * statusInput, char * reduceInput);
bool reduce(lrTable ** table, Stack * statusStack, Stack * reduceStack, char * reduceInput, int x, int y);
void parse(Token token[], int tokenCount, Stack * statusStack, Stack * reduceStack, lrTable ** table);
//char * getTokenValue(Token tokenNow);
#endif