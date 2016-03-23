// 定义联合体，存储 token 中的值
union S
{
    int i;
    float f;
    char * c;
};

// Token 结构体的定义
// _type
// _data
typedef struct token
{
    int _type;
    union S _data;
} Token;
