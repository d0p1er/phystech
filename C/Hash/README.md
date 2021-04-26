# HashTable Optimization
> sorry for my English

# Content
1. [Introduction](#intro)
2. [Beginning](#begin)
3. [Optimization](#opt)

<a name="intro"></a>
## 1. Introduction

First of all, this project involves comparing 6 hash functions. And in the second part of the project I chose CRC32 and optimized this function, using SSE.

<a name="begin"></a>
## 2. Beginning

The first idea was to use common hash table looked something like this:

![struct1.png](Images/struct1.png)

```
struct CellHashTable {
	unsigned int hash_value;
	struct List list;
};

struct HashTable {
	size_t size;
	size_t capacity;
	struct CellHashTable* cells;
};
```

<a name="opt"></a>
## 3. Optimization

Function Hash4 took a lot of program's running time and I decided to rewrite it with SSE :

Before :

```
unsigned int Hash4(char* data) {
	const unsigned int Polynomial = 0xEDB88320;
	unsigned int crc = 0;
	size_t length = 32;
	while (length--) {
		crc ^= *data++;

		for (unsigned int j = 0; j < 8; j++)
			crc = (crc >> 1) ^ (-int(crc & 1) & Polynomial);
	}

	return crc;
} 
```

![new_time.jpg](Images/new_time.jpg)

![new.jpg](Images/new.jpg)

After:

![new_time.jpg](Images/new_intr_time.jpg)

![new.jpg](Images/new_intr.jpg)

```
unsigned int Hash4(char* str){
	unsigned int hash = 0;
	for (size_t i = 0; i < 32; ++i) {
		hash = _mm_crc32_u32(hash, *str);
		str++;
	}

	return hash;
}
```

It made the program 331% faster

![fine.jpg](Images/fine.jpg)