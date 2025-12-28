#include <stdlib.h>
#include <string.h>
#include "hashTable.h"

unsigned hash(char *ptr) {
	unsigned h = 0;
	while (*ptr) {
		h = (h<<4) + (unsigned)((*ptr++)-'A');
	}
	return (h % TABLE_SIZE);
}

bucket Bucket(char *key,void *value,bucket next) {
	bucket b = (bucket)malloc(sizeof(struct _bucket));
	b->key = strdup(key);
	b->value = value;
	b->next = next;
	return b;
}


Hash_table empty_table() {
	Hash_table t = (Hash_table)malloc(sizeof(struct _Hash_table));
	for (int i=0; i<TABLE_SIZE; i++) t->table[i] = NULL;
	return t;
}

void addEntry(Hash_table t,char *key,void *value) {
	unsigned index = hash(key);
	t->table[index] = Bucket(key,value,t->table[index]);
}

void *lookup(Hash_table t,char *key) {
	unsigned index = hash(key);
	bucket b;
	for (b=t->table[index]; b; b=b->next) if (strcmp(key,b->key) == 0) return b->value;
	return NULL;
}

