//--------------------------------------------------
// HASHTABLE BASED ON MAP
//--------------------------------------------------


#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <map>

#include "Text/Text.h"
#include "Struct/Struct.h"
#include "List/list.h"

extern const unsigned int poison_hash;

using namespace std;
// #define DEBUG

#ifndef DEBUG
	#define DBG if (0)
#else
	#define DBG
#endif

struct CellHashTable {
	unsigned int hash_value;
	struct List list;
};

struct HashTable {
	size_t size;
	size_t capacity;
	struct CellHashTable* cells;
};

void HashTableConstruct(struct HashTable* hash_table);
void FillHashTable(struct HashTable* hash_table, unsigned int (*HashFunc)(char*), struct Text* data);
// int CheckHash(struct HashTable* hash_table, unsigned int hash);
void ResizeList(struct HashTable* hash_table, unsigned int hash);
// void ResizeTable(struct HashTable* hash_table);
void WriteData(struct HashTable* hash_table);
// size_t FindFree(struct HashTable* hash_table, size_t iter);
TYPE_LIST FindHash(struct HashTable* hash_table, TYPE_LIST s, unsigned int (*HashFunc)(char*));

// //--------------------------------------------------
// // HASHTABLE BASED ON ARR
// //--------------------------------------------------


// #pragma once

// #include <stdio.h>
// #include <stdlib.h>
// #include <cstdlib>
// #include <map>

// #include "Text/Text.h"
// #include "Struct/Struct.h"
// #include "List/list.h"

// extern const unsigned int poison_hash;

// using namespace std;
// // #define DEBUG

// #ifndef DEBUG
// 	#define DBG if (0)
// #else
// 	#define DBG
// #endif

// struct CellHashTable {
// 	unsigned int hash_value;
// 	struct List list;
// };

// struct HashTable {
// 	size_t size;
// 	size_t capacity;
// 	struct CellHashTable* cells;
// };

// void HashTableConstruct(struct HashTable* hash_table);
// void FillHashTable(struct HashTable* hash_table, unsigned int (*HashFunc)(char*), struct Text* data);
// // int CheckHash(struct HashTable* hash_table, unsigned int hash);
// // void ResizeTable(struct HashTable* hash_table);
// size_t FindHash(struct HashTable* hash_table, unsigned int tmp_hash);
// void ResizeTable(struct HashTable* hash_table);
// void WriteData(struct HashTable* hash_table);

