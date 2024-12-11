#ifndef HASHMAP_H_INCLUDED
#define HASHMAP_H_INCLUDED

#include "standard_libs.h"
#include "status_code.h"

typedef struct HashItem {
    struct HashItem *next;
    char *key;
    char *value;
    int hash; 
} HashItem;

typedef struct {
    HashItem **items;
    int size_table;
} HashMap;

status_code create_hashMap(HashMap **new_hashMap, int *size_table);
status_code create_Item(HashItem **item, char *key, char *value);
int hash_function(char* key, int size_table);
status_code insert_Item(HashMap *hashMap, char *key, char *value);
char *get_Item(HashMap *hashMap, char *key);
status_code delete_Item(HashMap *hashMap, char *key);
void destroy_Item(HashItem **item);
void destroy_hashMap(HashMap **hashMap);
void print_hashtable(HashMap *hashMap);
int check_collision(HashMap *hashMap);
int is_prime(int num);
void rebuild_hashMap(HashMap *hashMap);

#endif