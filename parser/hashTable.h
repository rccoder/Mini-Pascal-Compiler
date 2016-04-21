#ifndef HT
#define HT

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


// hashnode 节点 —— 实际保存数据的单链表
struct HashNode {
    char * key;
    char * value;
    struct HashNode * next;
};
typedef struct HashNode HashNode;


// hash 表 —— 保存 hash 表本身
struct HashTable {
    // hashtable 最大长度
    int size;
    // hashtable 现有长度
    int item_size;
    HashNode * head;
};
typedef struct HashTable HashTable;

// hash 函数
int hash(char * key, int size);
// 初始化 hashTable
HashTable * hashtable_init(int size);
// put
HashTable * hashtable_put(HashTable *hashtable, char * key, char * value);
// get
char * hashtable_get(HashTable * hashtable, char * key);

#endif