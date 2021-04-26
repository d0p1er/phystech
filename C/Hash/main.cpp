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

	char aa[32] = "aa";
	char bb[32] = "bb";
	char cc[32] = "cc";
	char dd[32] = "dd";

	for (int i = 0; i < 1000000; i++) {
		FindHash(&hash_table, aa, Hash4);

		FindHash(&hash_table, bb, Hash4);

		FindHash(&hash_table, cc, Hash4);

		FindHash(&hash_table, dd, Hash4);
	}
	
	printf("22\n");


	WriteData(&hash_table);
}