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
typedef struct token
{
    int _type;
    union S _data;
} Token;
