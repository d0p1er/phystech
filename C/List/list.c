#include "list.h"

const int poison = 0xDEADBEEF;

struct List ListConstruct() {
	struct List list = {};
	list.capacity = 32;
	list.size = 0;
	list.free = 2;

	list.values = (int*) calloc(list.capacity, sizeof(list.values[0]));
	list.values[0] = 0;
	for (size_t i = 1; i < list.capacity; i++)
		list.values[i] = poison;

	list.next = (int*) calloc(list.capacity, sizeof(list.values[0]));
	list.prev = (int*) calloc(list.capacity, sizeof(list.values[0]));
	
	list.next[0] = 0;
	list.next[1] = 0;

	list.prev[0] = 0;
	list.prev[1] = 0;
	for (size_t i = 2; i < list.capacity; i++) {
		list.next[i] = i + 1;
		list.prev[i] = i - 1;
	}
	list.next[list.capacity - 1] = 0;
	list.prev[2] = 0;

	return list;
}


void AddValue(int pos, int value, struct List* list) {
	if (list->values[pos] == poison) {
		list->values[pos] = value;
		list->values[1] = value;

		if (pos != list->free) {
			list->next[list->prev[pos]] = list->next[pos];
			list->prev[list->next[pos]] = list->prev[pos];
		}
		else {
			list->prev[list->next[pos]] = list->prev[pos];
			list->free = list->next[list->free];
		}

		list->next[list->next[1]] = pos;
		list->next[pos] = 0;
		list->next[1] = pos;

		list->prev[pos] = list->prev[1];
		list->prev[1] = pos;

		list->next[0] = 0;
		list->prev[0] = 0;
		list->size++;
	}
	else {
		int new_pos = list->free;
		list->free = list->next[list->free];

		list->values[new_pos] = list->values[pos];
		list->values[pos] = value;
		list->values[1] = value;

		list->next[new_pos] = list->next[pos];
		list->next[list->prev[pos]] = new_pos;
		list->next[list->next[1]] = pos;
		
		list->prev[new_pos] = list->prev[pos];
		list->prev[list->next[pos]] = new_pos;

		list->next[pos] = 0;
		list->next[1] = pos;
		list->prev[pos] = list->prev[1];
		list->prev[1] = pos;
		
		list->next[0] = 0;
		list->prev[0] = 0;
		list->size++;
	}	
}

void PrintAll(struct List* list) {
	printf("values : ");
	for (size_t i = 0; i < list->capacity; i++)
		printf("%d ", list->values[i]);

	printf("\n");
	printf("next : ");
	for (size_t i = 0; i < list->capacity; i++)
		printf("%d ", list->next[i]);

	printf("\n");
	printf("prev : ");
	for (size_t i = 0; i < list->capacity; i++)
		printf("%d ", list->prev[i]);
}