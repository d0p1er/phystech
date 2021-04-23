//--------------------------------------------------
// HASHTABLE BASED ON MAP
//--------------------------------------------------

#include "hashtable.h"

const unsigned int poison_hash = (unsigned int) 0xDEADBEEF;
char* OUTPUT_DATA = "Data/output4";

void HashTableConstruct(struct HashTable* hash_table) {
	hash_table->capacity = 1;
	hash_table->size = 0;
}

void FillHashTable(struct HashTable* hash_table, unsigned int (*HashFunc)(char*), struct Text* data) {
	// printf("%ld\n", data->n_lines);
	for (size_t i = 0; i < data->n_lines; i++) {
		// printf("%ld\n", i);
		unsigned int tmp_hash = (*HashFunc)(data->pointers[i]);
		// printf("tmp hash : %d\n", tmp_hash);

		auto iter = hash_table->list.find(tmp_hash);
		// printf("check : %d\n", check);

		if (iter == hash_table->list.end()) {
			struct List list = {};
			ListConstruct(&list);
			AddValueAfter(data->pointers[i], &list);

			// tmp_cell.list[0] = data->pointers[i];

			hash_table->list.insert(make_pair(tmp_hash, list));

			hash_table->size++;
			// printf("%ld %ld\n", hash_table->cells[check].size, hash_table->cells[check].capacity);			
		}
		else {
			// if (hash_table->cells[tmp_hash].size >= hash_table->cells[tmp_hash].capacity)
			// 	ResizeList(hash_table, tmp_hash);

			AddValueAfter(data->pointers[i], &(hash_table->list[tmp_hash]));

			// hash_table->cells[tmp_hash].list[hash_table->cells[tmp_hash].size] = data->pointers[i];
			// printf("11111\n");
			// hash_table->cells[tmp_hash].size++;
		}
	}
}


void WriteData(struct HashTable* hash_table) {
	FILE* f = fopen(OUTPUT_DATA, "w");

	printf("%ld\n", hash_table->size);

	for (auto iter = hash_table->list.begin(); iter != hash_table->list.end(); iter++) {
		fprintf(f, "%d ", iter->first);
	}

	fprintf(f, "\n");

	for (auto iter = hash_table->list.begin(); iter != hash_table->list.end(); iter++) {
		fprintf(f, "%ld ", iter->second.size);
	}
}


// //--------------------------------------------------
// // HASHTABLE BASED ON ARR
// //--------------------------------------------------


// #include "hashtable.h"

// const unsigned int poison_hash = (unsigned int) 0xDEADBEEF;
// char* OUTPUT_DATA = "output4";
// const size_t SIZE_HASHTABLE = 148993;

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
