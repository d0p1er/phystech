//--------------------------------------------------
// HASHTABLE BASED ON MAP
//--------------------------------------------------

#include "hashtable.h"

const unsigned int poison_hash = (unsigned int) 0xDEADBEEF;
char* OUTPUT_DATA = "Data/output4";
size_t SIZE_HASHTABLE = 371663;

void HashTableConstruct(struct HashTable* hash_table) {
	hash_table->capacity = SIZE_HASHTABLE;
	hash_table->size = 0;

	hash_table->cells = (struct CellHashTable*) calloc(SIZE_HASHTABLE, sizeof(hash_table->cells[0]));

	for (size_t i = 0; i < SIZE_HASHTABLE; i++) {
		ListConstruct(&(hash_table->cells[i].list));
	}
}

void FillHashTable(struct HashTable* hash_table, unsigned int (*HashFunc)(char*), struct Text* data) {
	// printf("%ld\n", data->n_lines);
	for (size_t i = 0; i < data->n_lines; i++) {
		// printf("%ld\n", i);
		unsigned int tmp_hash = (*HashFunc)(data->pointers[i]);
		// printf("tmp hash : %d\n", tmp_hash);

		size_t iter = (size_t) tmp_hash % SIZE_HASHTABLE;
		// printf("check : %d\n", check);
		if (hash_table->cells[iter].list.size == 0) {
			AddValueAfter((TYPE_LIST) data->pointers[i], &(hash_table->cells[iter].list));
			hash_table->size++;
		}
		else {
			// if (hash_table->cells[iter].hash_value == tmp_hash
			AddValueAfter((TYPE_LIST) data->pointers[i], &(hash_table->cells[iter].list));
			// else {
			// 	iter = FindFree(hash_table, iter);
			// 	hash_table->cells[iter].hash_value = tmp_hash;
			// 	AddValueAfter(data->pointers[i], &(hash_table->cells[iter].list));
			// 	hash_table->size++;
			// }
		}
	}
}

// size_t FindFree(struct HashTable* hash_table, size_t iter) {
// 	for (size_t i = iter + 1; i < SIZE_HASHTABLE; i++) {
// 		if (hash_table->cells[i].list.size == 0) {
// 			return i;
// 		}
// 	}
// 	for (size_t i = 0; i < iter; i++) {
// 		if (hash_table->cells[i].list.size == 0) {
// 			return i;
// 		}
// 	}
// 	return -1;
// }


TYPE_LIST FindHash(struct HashTable* hash_table, TYPE_LIST s, unsigned int (*HashFunc)(char*)) {
	unsigned int hash = (*HashFunc)((char*) s);
	size_t iter = (size_t) hash % SIZE_HASHTABLE;

	if (hash_table->cells[iter].list.size == 0) {
		return nullptr;
	}
	else {
		int i = FindElemByValue(s, &(hash_table->cells[iter].list));

		if (i >= 0)
			return hash_table->cells[iter].list.nodes[i].value;
		
		else 

			return nullptr;
	}
}


void WriteData(struct HashTable* hash_table) {
	FILE* f = fopen(OUTPUT_DATA, "w");

	printf("%ld\n", hash_table->size);

	for (size_t i = 0; i < hash_table->capacity; i++) {
		fprintf(f, "%d ", hash_table->cells[i].hash_value);
	}

	fprintf(f, "\n");

	for (size_t i = 0; i < hash_table->capacity; i++) {
		fprintf(f, "%ld ", hash_table->cells[i].list.size);
	}
}


// //--------------------------------------------------
// // HASHTABLE BASED ON ARR
// //--------------------------------------------------


// #include "hashtable.h"

// const unsigned int poison_hash = (unsigned int) 0xDEADBEEF;
// char* OUTPUT_DATA = "output4";
// const size_t SIZE_HASHTABLE = 148993;;

// void HashTableConstruct(struct HashTable* hash_table) {
// 	hash_table->capacity = SIZE_HASHTABLE;
// 	hash_table->size = 0;

// 	hash_table->cells = (struct CellHashTable*) calloc(hash_table->capacity, sizeof(hash_table->cells[0]));
// 	for (size_t i = 0; i < hash_table->capacity; i++) {
// 		hash_table->cells[i].hash_value = poison_hash;
// 		ListConstruct(&(hash_table->cells[i].list));
// 	}
// }

// void FillHashTable(struct HashTable* hash_table, unsigned int (*HashFunc)(char*), struct Text* data) {
// 	// printf("%ld\n", data->n_lines);
// 	for (size_t i = 0; i < data->n_lines; i++) {
// 		// printf("%ld\n", i);
// 		unsigned int tmp_hash = (*HashFunc)(data->pointers[i]);
// 		// printf("tmp hash : %lld\n", tmp_hash);

// 		size_t iter = FindHash(hash_table, tmp_hash);
// 		// printf("iter : %d\n", iter);

// 		if (iter == -1) {
// 			if (hash_table->size >= hash_table->capacity - 1) {
// 				ResizeTable(hash_table);
// 			}
// 			hash_table->cells[hash_table->size].hash_value = tmp_hash;
// 			AddValueAfter(data->pointers[i], &(hash_table->cells[hash_table->size].list));
// 			// printf("%ld %ld\n", hash_table->cells[iter].size, hash_table->cells[iter].capacity);
// 			hash_table->size++;
// 		}
// 		else {
// 			// if (hash_table->cells[tmp_hash].size >= hash_table->cells[tmp_hash].capacity)
// 			// 	ResizeList(hash_table, tmp_hash);
// 			AddValueAfter(data->pointers[i], &(hash_table->cells[iter].list));

// 			// hash_table->cells[tmp_hash].list[hash_table->cells[tmp_hash].size] = data->pointers[i];
// 			// printf("11111\n");
// 		}
// 	}
// }


// size_t FindHash(struct HashTable* hash_table, unsigned int tmp_hash) {
// 	for (size_t i = 0; i < hash_table->size; i++) {
// 		if (hash_table->cells[i].hash_value == tmp_hash) {
// 			return i;
// 		}
// 	}
// 	return -1;
// }

// void ResizeTable(struct HashTable* hash_table) {
// 	// printf("resize\n");
// 	size_t old_cap = hash_table->capacity;
// 	hash_table->capacity *= 2;
// 	hash_table->cells = (struct CellHashTable*) realloc(hash_table->cells, hash_table->capacity * sizeof(hash_table->cells[0]));

// 	for (size_t i = old_cap; i < hash_table->capacity; i++) {
// 		hash_table->cells[i].hash_value = poison_hash;
// 		ListConstruct(&(hash_table->cells[i].list));
// 	}
// }

// void WriteData(struct HashTable* hash_table) {
// 	FILE* f = fopen(OUTPUT_DATA, "w");

// 	printf("%ld\n", hash_table->size);

// 	for (size_t i = 0; i < hash_table->size; i++) {
// 		fprintf(f, "%d ", hash_table->cells[i].hash_value);
// 	}

// 	fprintf(f, "\n");

// 	for (size_t i = 0; i < hash_table->size; i++) {
// 		fprintf(f, "%ld ", hash_table->cells[i].list.size);
// 	}
// }
