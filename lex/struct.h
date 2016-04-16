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


// hashnode 节点 —— 实际保存数据的单链表
typedef struct HashNode {
    char * key;
    char * value;
    HashNode * next;
} HashNode;


// hash 表 —— 保存 hash 表本身
typedef struct HashTable {
    // hashtable 最大长度
    int size;
    // hashtable 现有长度
    int item_size;
    HashNode * head;
} HashTable;

