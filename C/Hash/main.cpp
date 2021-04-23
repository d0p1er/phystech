#include "hashtable.h"
#include "hashfuncs.h"

int main() {
	struct HashTable hash_table = {};
	// printf("-1\n");
	HashTableConstruct(&hash_table);
	// printf("0\n");
	struct Text data = FillText("dict");
	// printf("1\n");

	FillHashTable(&hash_table, Hash4, &data);

	WriteData(&hash_table);
}