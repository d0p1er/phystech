# HashTable Optimization
> sorry for my English

# Content
1. [Introduction](#intro)
2. [Beginning](#begin)

<a name="intro"></a>
## 1. Introduction

First of all, this project involves comparing 6 hash functions. And in the second part of the project I chose CRC32 and optimized this function, using SSE.

<a name="begin"></a>
## 2. Beginning

The first idea was to use common hash table looked something like this:

![struct1.png](Images/struct1.png)

```
struct CellHashTable {
	unsigned long long hash_value;
	struct List list;
};

struct HashTable {
	size_t size;
	size_t capacity;
	struct CellHashTable* cells;
};
```

But after I decided to use different structure based on map:
```
struct HashTable {
	size_t size;
	size_t capacity;
	map <unsigned long long, struct List> cells;
};
```

Because I thought it would be easier and more beautiful. And it really made the program run faster))).

![arr.png](Images/arr_long_long.jpg)
:arrow_down
![map.png](Images/map_long_long.jpg)

![fine.jpg](Images/fine.jpg)

