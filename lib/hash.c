#pragma GCC diagnostic ignored "-Wwrite-strings"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// hashnode 节点 —— 实际保存数据的单链表
typedef struct HashNode {
    char * key;
    char * value;
    HashNode * next;
} HashNode;


// hash 表 —— 保存 hash 表本身
typedef struct HashTable {
    // hash 表的长度
    int size;
    int item_size;
    HashNode * head;
} HashTable;


// hash method
int hash(char * key, int size) {
    int rect = 0;
    while(*key != '\0') {
        rect += *key;  
        key ++;
    }
    return rect%size;
}

// init hashtable
HashTable * hashtable_init(int size) {
    
    HashTable * hashtable = (HashTable*)calloc(1, sizeof(HashTable));
    hashtable->size = size;
    hashtable->item_size = 0;
    
    HashNode * head = (HashNode*)calloc(size, sizeof(HashNode));
    
    hashtable->head = head;
    
    return hashtable;
}

// put a var in hashtable
HashTable * hashtable_put(HashTable *hashtable, char * key, char * value) {
    
    int index = hash(key, hashtable->size);
    
    HashNode *hashNode = hashtable->head + index;
    
    while(true) {
        // 曾经没有的情况 或者 已经存在
        if(hashNode->key == NULL || *key == *(hashNode->key)) {
            
            if(hashNode->key == NULL) {
                hashtable->item_size = hashtable->item_size + 1;
            }
            
            hashNode->key = key;
            hashNode->value = value;
            return 0;
        }
        
        // 冲突
        if(hashNode->key != NULL) {
            hashNode = hashNode->next;
        } else {
            HashNode * newNode = (HashNode*)calloc(1, sizeof(HashNode));
            newNode->key = key;
            newNode->value = value;
            hashNode->next = newNode;
            hashtable->item_size = hashtable->item_size + 1;
            return 0;
        }
    }
}

// get a var
char * hashtable_get(HashTable * hashtable, char * key) {
    int index = hash(key, hashtable->size);
    HashNode *hashNode = hashtable->head + index;
    
    while(hashNode != NULL) {
        if(hashNode->key != NULL && *key == *(hashNode->key)) {
            return hashNode->value;
        }
        hashNode = hashNode->next;
    }
    return NULL;
}

int main() {
    HashTable * hashtable = hashtable_init(10);
    hashtable_put(hashtable, "a", "v");
    hashtable_put(hashtable, "b", "dxxx");
    
    printf("%s", hashtable_get(hashtable, "b"));
    return 0;
}