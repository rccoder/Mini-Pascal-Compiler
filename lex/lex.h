#ifndef LEX
#define LEX

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tokenUtil.h"

void lex(FILE *fp, Token token[], int * tokenCountPointer);

#endif