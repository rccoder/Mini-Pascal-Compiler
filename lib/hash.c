#pragma GCC diagnostic ignored "-Wwrite-strings"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


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
    
    // 开最大长度的空间
    HashNode * head = (HashNode*)calloc(size, sizeof(HashNode));
    
    hashtable->head = head;
    
    return hashtable;
}

// put a var in hashtable
HashTable * hashtable_put(HashTable *hashtable, char * key, char * value) {
    
    int index = hash(key, hashtable->size);
    
    HashNode *hashNode = hashtable->head + index;
    
    while(true) {
        // 曾经没有的情况 或者 有，并且第一个就是
        if(hashNode->key == NULL || *key == *(hashNode->key)) {
            
            if(hashNode->key == NULL) {
                hashtable->item_size = hashtable->item_size + 1;
            }
            
            hashNode->key = key;
            hashNode->value = value;
            return 0;
        }
        
        // 冲突
        // 下一个节点还不是空
        if(hashNode->key != NULL) {
            hashNode = hashNode->next;
            // 下个节点是空了，加数据
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
/*
int main() {
    HashTable * hashtable = hashtable_init(3);
    hashtable_put(hashtable, "a", "v");
    hashtable_put(hashtable, "b", "dxxx");
    hashtable_put(hashtable, "d", "dxxxxxxxxxxxxxxxxx");
    hashtable_put(hashtable, "d", "d");
    
    printf("%s", hashtable_get(hashtable, "d"));
    printf("%s", hashtable_get(hashtable, "c"));
    printf("%d", hashtable->item_size);
    return 0;
}
*/