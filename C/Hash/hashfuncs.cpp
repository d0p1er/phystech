#include "hashfuncs.h"

unsigned int Hash0(char* str) {
	return 1;
}

unsigned int Hash1(char* str) {
	return (unsigned int) str[0];
}

unsigned int Hash2(char* str) {
	unsigned int sum_ascii = 0;
	char* symbols_runner = str;

	for (; *symbols_runner; symbols_runner++)
		sum_ascii += (unsigned int) *symbols_runner;

	return sum_ascii;
}

unsigned int Hash3(char* str) {
	unsigned int sum_ascii = 0;
	char* symbols_runner = str;
	size_t counter = 0;

	for (; *symbols_runner; symbols_runner++) {
		sum_ascii += (unsigned int) *symbols_runner;
		counter++;
	}
	

	return (unsigned int) (sum_ascii / counter);
}

// unsigned int Hash4(char* data) {
// 	const unsigned int Polynomial = 0xEDB88320;
// 	unsigned int crc = 0;
// 	size_t length = 32;
// 	while (length--) {
// 		crc ^= *data++;

// 		for (unsigned int j = 0; j < 8; j++)
// 			crc = (crc >> 1) ^ (-int(crc & 1) & Polynomial);
// 	}

// 	return crc;
// } 


// unsigned int Hash4(char* str) {
// 	unsigned int hash = 0;
// 	// size_t iter = 32 / sizeof(unsigned int);
// 	for (size_t i = 0; i < 32; ++i) {
// 		hash = _mm_crc32_u32(hash, *str);
// 		str ++;
// 	}

// 	return hash;
// }

unsigned int Hash4(char* str) {
	u_int64_t hash = 0;
	u_int64_t* M = (u_int64_t*) str;
	for (u_int32_t i = 0; i < 4; ++i) {
		hash = _mm_crc32_u64(hash, M[i]);
	}
	return (u_int32_t)hash;
}


unsigned int Hash5(char* str) {
	unsigned int hash_sum = 0;
	char* symbols_runner = str;
	if (strlen(str) > 1) {
		char prev_symbol = *symbols_runner;
		symbols_runner++;

		for (; *symbols_runner; symbols_runner++) {
			hash_sum += ((unsigned int) prev_symbol) * (unsigned int) *(symbols_runner);
			prev_symbol = *symbols_runner;
		}
	}
	else {
		return (unsigned int) str[0];
	}
	
	return hash_sum;
}