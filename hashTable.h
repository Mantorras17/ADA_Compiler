#ifndef __hashTable_h__
#define __hashTable_h__

#define TABLE_SIZE 127 


struct _bucket { char *key; void *value; struct _bucket *next; };
typedef struct _bucket *bucket;

struct _Hash_table { bucket table[TABLE_SIZE]; };
typedef struct _Hash_table *Hash_table;

unsigned hash(char*);
bucket Bucket(char*,void*,bucket);

Hash_table empty_table(void);
void addEntry(Hash_table,char*,void*);
void *lookup(Hash_table,char*);

#endif
