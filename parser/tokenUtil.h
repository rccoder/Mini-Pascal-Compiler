#ifndef TU
#define TU

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "define.h"
#include "data.h"
// union, the data in Token
union S
{
    int i;
    float f;
    char * c;
};

// Token struct
// _type
// _data
struct token
{
    int _type;
    union S _data;
};
typedef struct token Token;
           
                                    
void pushToken(char * tokenData, char pushch);
void checkIdentifier(char * tokenData, int * type, char ** c);
void pushToToken(int defineNum, int * type, char ** c);

#endif