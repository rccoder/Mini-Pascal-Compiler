
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

void parse(Token token[], int tokenCount, Stack * statusStack, Stack * reduceStack, lrTable ** table);
//char * getTokenValue(Token tokenNow);
#endif