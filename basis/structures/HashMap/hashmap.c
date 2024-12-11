#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

status_code create_hashMap(HashMap **new_hashMap, int *size_table) {
    *new_hashMap = (HashMap*)malloc(sizeof(HashMap));
    if (*new_hashMap == NULL) {
        return MemoryError;
    }

    (*new_hashMap)->size_table = *size_table;
    (*new_hashMap)->items = (HashItem**)calloc(*size_table, sizeof(HashItem*));
    if ((*new_hashMap)->items == NULL) {
        free(*new_hashMap);
        *new_hashMap = NULL;
        return MemoryError;
    }

    return OK;
}

status_code create_Item(HashItem **item, char *key, char *value) {
    *item = (HashItem*)malloc(sizeof(HashItem));
    if (*item == NULL) {
        return MemoryError;
    }

    (*item)->key = (char*)malloc((strlen(key) + 1) * sizeof(char));
    if ((*item)->key == NULL) {
        free(*item);
        *item = NULL;
        return MemoryError;
    }
    strcpy((*item)->key, key);

    (*item)->value = (char*)malloc((strlen(value) + 1) * sizeof(char));
    if ((*item)->value == NULL) {
        free((*item)->key);
        free(*item);
        *item = NULL;
        return MemoryError;
    }
    strcpy((*item)->value, value);
    
    (*item)->next = NULL;
    (*item)->hash = -1;

    return OK;
}

int hash_function(char* key, int size_table) {
    long int num = 0;
    int len = strlen(key);
    const long int BASE = 62;
    for (int i = 0; i < len; i++) {
        if (key[i] >= '0' && key[i] <= '9')
            num = (num * BASE + key[i] - '0') % size_table;
        else if (key[i] >= 'A' && key[i] <= 'Z')
            num = (num * BASE + key[i] - 'A' + 10) % size_table;
        else if (key[i] >= 'a' && key[i] <= 'z')
            num = (num * BASE + key[i] - 'a' + 36) % size_table;
    }
    return num;
}

status_code insert_Item(HashMap *hashMap, char *key, char *value) {
    int index = hash_function(key, hashMap->size_table);
    HashItem *item = NULL;
    status_code status = create_Item(&item, key, value);
    if (status != OK) {
        return status;
    }
    item->hash = index;

    if (hashMap->items[index] == NULL) {
        hashMap->items[index] = item;
    } else {
        HashItem *current = hashMap->items[index];
        while (current->next != NULL) {
            if (strcmp(current->key, item->key) == 0) {
                free(item->key);
                free(item->value);
                free(item);
                return ItemExist;
            }
            current = current->next;
        }
        if (strcmp(current->key, item->key) == 0) {
            free(item->key);
            free(item->value);
            free(item);
            return ItemExist;
        }
        current->next = item;
    }
    return OK;
}

char *get_Item(HashMap *hashMap, char *key) {
    int index = hash_function(key, hashMap->size_table);
    HashItem *item = hashMap->items[index];
    while (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            return item->value;
        }
        item = item->next;
    }
    return NULL;
}

status_code delete_Item(HashMap *hashMap, char *key) {
    int index = hash_function(key, hashMap->size_table);
    HashItem *current = hashMap->items[index];
    HashItem *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                hashMap->items[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            return OK;
        }
        prev = current;
        current = current->next;
    }
    return ItemDoesNotExist;
}

void destroy_Item(HashItem **item) {
    if (*item != NULL) {
        free((*item)->key);
        free((*item)->value);
        free(*item);
        *item = NULL;
    }
}

void destroy_hashMap(HashMap **hashMap) {
    for (int i = 0; i < (*hashMap)->size_table; ++i) {
        HashItem *item = (*hashMap)->items[i];
        while (item != NULL) {
            HashItem *next = item->next;
            destroy_Item(&item);
            item = next;
        }
    }
    free((*hashMap)->items);
    free(*hashMap);
    *hashMap = NULL;
}

void print_hashtable(HashMap *hashMap) {
    for (int i = 0; i < hashMap->size_table; ++i) {
        if (hashMap->items[i] != NULL) {
            printf("Bucket %d:\n", i);
            HashItem *current = hashMap->items[i];
            while (current != NULL) {
                printf("  Key: '%s', Value: '%s'\n", current->key, current->value);
                current = current->next;
            }
            printf("\n");
        }
    }
}

int check_collision(HashMap *hashMap) {
    int min_chain = INT_MAX;
    int max_chain = 0;

    for (int i = 0; i < hashMap->size_table; ++i) {
        HashItem *item = hashMap->items[i];
        int length_chain = 0;
        while (item != NULL) {
            length_chain++;
            item = item->next;
        }
        if (length_chain > 0) {
            if (length_chain < min_chain) {
                min_chain = length_chain;
            }
            if (length_chain > max_chain) {
                max_chain = length_chain;
            }
        }
    }
    return (min_chain > 0 && max_chain >= 2 * min_chain);
}

int is_prime(int num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

void rebuild_hashMap(HashMap *hashMap) {
    int old_size = hashMap->size_table;
    HashItem **old = hashMap->items;
    int new_size = old_size * 2;
    while (!is_prime(new_size)) {
        new_size++;
    }
    hashMap->size_table = new_size;
    hashMap->items = (HashItem**)calloc(new_size, sizeof(HashItem*));

    for (int i = 0; i < old_size; ++i) {
        HashItem *item = old[i];
        while (item != NULL) {
            int index = item->hash % new_size;
            if (hashMap->items[index] == NULL) {
                hashMap->items[index] = item;
                item->next = NULL;
            } else {
                HashItem *current = hashMap->items[index];
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = item;
                item->next = NULL;
            }
            item = item->next;
        }
    }
    free(old);
}
