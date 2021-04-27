#include "list.h"

const TYPE_LIST poison = (TYPE_LIST) 0xDEADBEEF;

void ListConstruct(struct List* list) {
	list->capacity = 4;
	list->size = 0;
	list->free = 1;

	list->nodes = (struct NodeList*) calloc(list->capacity, sizeof(list->nodes[0]));

	list->nodes[0].value = 0;
	list->nodes[0].next  = 0;
	list->nodes[0].prev  = 0;

	for (size_t i = 1; i < list->capacity; i++) {
		list->nodes[i].value = poison;
		list->nodes[i].next  = i + 1;
		list->nodes[i].prev  = i - 1;
	}

	list->nodes[list->capacity - 1].next = 0;
	list->nodes[1].prev = 0;

	DBG DumpList(list, __FUNCTION__, __LINE__);
}


void ListDestruct(struct List* list) {
	DBG DumpList(list, __FUNCTION__, __LINE__);

	free(list->nodes);
	list->nodes = NULL;
	list->size = 0;
	
}


int AddValueBefore(TYPE_LIST value, struct List* list) {
	DBG DumpList(list, __FUNCTION__, __LINE__);

	int new_pos = 0;

	if (list->size == 0)
		new_pos = AddZeroSize(value, list);

	else {
		if (list->size == list->capacity - 2) {
			// PrintAll(list);
			ResizeUp(list);
		}

		new_pos = list->free;
		list->free = list->nodes[new_pos].next;

		list->nodes[new_pos].value = value;
		
		list->nodes[new_pos].next = list->head;
		list->nodes[new_pos].prev = 0;
		
		list->nodes[list->head].prev = new_pos;

		list->head = new_pos;
	}

	list->size++;

	DBG DumpList(list, __FUNCTION__, __LINE__);

	return new_pos;
}



int AddValueAfter(TYPE_LIST value, struct List* list) {
	DBG DumpList(list, __FUNCTION__, __LINE__);

	int new_pos = 0;

	if (list->size == 0)
		new_pos = AddZeroSize(value, list);

	else {
		if (list->size == list->capacity - 2) {
			// PrintAll(list);
			ResizeUp(list);
		}

		new_pos = list->free;
		list->free = list->nodes[new_pos].next;

		list->nodes[new_pos].value = value;
		
		list->nodes[list->tail].next = new_pos;
		list->nodes[new_pos].next = 0;
		
		list->nodes[new_pos].prev = list->tail;

		list->tail = new_pos;
	}

	list->size++;

	DBG DumpList(list, __FUNCTION__, __LINE__);

	return new_pos;
}


int AddZeroSize(TYPE_LIST value, struct List* list) {
	int pos = list->free;
	list->free = list->nodes[list->free].next;

	list->nodes[pos].value = value;
	list->nodes[pos].next = 0;
	list->nodes[pos].prev = 0;

	list->head = pos;
	list->tail = pos;

	return pos;
}

TYPE_LIST Delete(int pos, struct List* list) {
	DBG DumpList(list, __FUNCTION__, __LINE__);

	TYPE_LIST val = list->nodes[pos].value;
	list->nodes[pos].value = poison;
	list->size--;

	if (list->size == 1) {
		list->nodes[pos].next = list->free;
		list->nodes[pos].prev = 0;

		list->nodes[list->free].prev = pos;
		list->free = pos;

		return val;
	}

	if (pos == list->head) {
		list->head = list->nodes[pos].next;
		list->nodes[list->nodes[pos].next].prev = 0;

		UpdateFree(pos, list);

		return val;

	}

	if (pos == list->tail) {
		list->tail = list->nodes[pos].prev;
		list->nodes[list->nodes[pos].prev].next = 0;

		UpdateFree(pos, list);

		return val;
	}

	list->nodes[list->nodes[pos].prev].next = list->nodes[pos].next;
	list->nodes[list->nodes[pos].next].prev = list->nodes[pos].prev;

	UpdateFree(pos, list);

	DBG DumpList(list, __FUNCTION__, __LINE__);

	return val;
}


void UpdateFree(int pos, struct List* list) {
	list->nodes[pos].next = list->free;
	list->nodes[pos].prev = 0;
	list->nodes[list->free].prev = pos;
	list->free = pos;
}


void ResizeUp(struct List* list) {
	DBG DumpList(list, __FUNCTION__, __LINE__);

	list->nodes[list->free].next = list->capacity;
	list->capacity *= 2;

	list->nodes = (struct NodeList*) realloc(list->nodes, list->capacity * sizeof(list->nodes[0]));

	for (size_t i = list->size + 2; i < list->capacity; i++) {
		list->nodes[i].value = poison;
		list->nodes[i].next  = i + 1;
		list->nodes[i].prev  = i - 1;
	}


	list->nodes[list->capacity - 1].next = 0;

	DBG DumpList(list, __FUNCTION__, __LINE__);

	// PrintAll(list);
}


int FindElem(int pos, struct List* list) {
	DBG DumpList(list, __FUNCTION__, __LINE__);

	TYPE_LIST value = GetValue(pos, list);
	int new_pos = FindElemByValue(value, list);

	DBG DumpList(list, __FUNCTION__, __LINE__);

	return new_pos;
}


int FindElemByValue(TYPE_LIST value, struct List* list) {
	int pos = list->head;
	// if (!strcmp(list->nodes[pos].value, value))
	// 	return pos;

	// while (list->nodes[pos].next != 0) {
	// 	pos = list->nodes[pos].next;
	// 	if (!strcmp(list->nodes[pos].value, value))
	// 		return pos;
	// }

	// return -1;

	if (_mm256_movemask_epi8 (_mm256_cmpeq_epi32 (*(list->nodes[pos].value), *value)) == -1)
		return pos;

	while (list->nodes[pos].next != 0) {
		pos = list->nodes[pos].next;
		if (_mm256_movemask_epi8 (_mm256_cmpeq_epi32 (*(list->nodes[pos].value), *value)) == -1)
			return pos;
	}
	return -1;
}


TYPE_LIST GetValue(int pos, struct List* list) {
	int curr_pos = list->head;

	for (size_t i = 0; i < pos; i++)
		curr_pos = list->nodes[curr_pos].next;

	return list->nodes[curr_pos].value;
}


// void Sort(struct List* list) {
// 	DBG DumpList(list, __FUNCTION__, __LINE__);

// 	int pos = list->head;
// 	struct NodeList tmp_node = {};
// 	int tmp_pos = 0;

// 	for (size_t i = 1; i < list->size + 1; i++) {
// 		tmp_node = list->nodes[i];
// 		tmp_pos = list->nodes[pos].next;

// 		list->nodes[i] = list->nodes[pos];
		
// 		Swap(i, list);



// 		list->nodes[pos] = tmp_node;

// 		// printf("%d\n", list->nodes[i].next);
// 		// printf("%d\n", list->nodes[pos].next);

// 		Swap(pos, list);

		

// 		if (list->nodes[i].prev == 0)
// 			list->head = i;
// 		if (list->nodes[i].next == 0)
// 			list->tail = i;

// 		list->nodes[i].prev = i - 1;
// 		list->nodes[i].next = i + 1;

// 		pos = tmp_pos;
// 	}

// 	DBG DumpList(list, __FUNCTION__, __LINE__);
// }


// void Swap(int pos, struct List* list) {
// 	if (list->nodes[pos].prev != 0 && list->nodes[pos].next != 0) {
// 		list->nodes[list->nodes[pos].prev].next = pos;
// 		list->nodes[list->nodes[pos].next].prev = pos;
// 	}
// 	else if (list->nodes[pos].prev == 0 && list->nodes[pos].next != 0) {
// 		list->nodes[list->nodes[pos].next].prev = pos;
// 	}
// 	else if (list->nodes[pos].prev != 0 && list->nodes[pos].next == 0) {
// 		list->nodes[list->nodes[pos].prev].next = pos;
// 	}
// }

int Verification(struct List* list) {
	int pos = list->nodes[list->head].next;

	if (list->size > 2) {
		for (size_t i = 1; i < list->size - 1; i++) {
		if (list->nodes[list->nodes[pos].next].prev != list->nodes[list->nodes[pos].prev].next) 
			return NEXT_PREV_ERROR;

		pos = list->nodes[pos].next;
		}
	}


	pos = list->head;
	for (size_t i = 0; i < list->size; i++) {
		if (pos == 0)
			return NEXT_ERROR;

		pos = list->nodes[pos].next;
	}

	if (pos != 0)
		return NEXT_ERROR;


	pos = list->tail;
	for (size_t i = 0; i < list->size; i++) {
		if (pos == 0)
			return PREV_ERROR;

		pos = list->nodes[pos].prev;
	} 

	if (pos != 0)
		return PREV_ERROR;


	size_t counter = 0;
	for (size_t i = 1; i < list->capacity; i++) {
		if (list->nodes[i].value != poison)
			counter++;
	}
	if (counter != list->size)
		return WRONG_SIZE;

	return EVERYTHING_OKAY;
}


void DumpList(struct List* list, const char* func, const int line) {
	int error = Verification(list);

	switch (error) {
		case EVERYTHING_OKAY: 	PrintErrorLogs("ok", func, line, EVERYTHING_OKAY); 					break;
		case NEXT_PREV_ERROR: 	PrintErrorLogs("NEXT PREV ERROR", func, line, NEXT_PREV_ERROR); 	break;
		case NEXT_ERROR: 		PrintErrorLogs("NEXT ERROR", func, line, NEXT_ERROR);				break;
		case PREV_ERROR:		PrintErrorLogs("PREV ERROR", func, line, PREV_ERROR);				break;
		case WRONG_SIZE:		PrintErrorLogs("WRONG SIZE", func, line, WRONG_SIZE);				break;
		default:				PrintErrorLogs("UNKNOWN ERROR", func, line, error);					break; 
	}
}


void PrintErrorLogs(const char* error, const char* func, const int line, const int error_number) {
	if(error != "ok")
		printf("ERROR[%d] %s CHECK LOGS\n", error_number, error);

	FILE* logs_file = fopen("logs.txt", "a");

	char* timeNow = TimeNow();

	fprintf(logs_file, "\n##########################################################################################\n");
	fprintf(logs_file, "[%s]\nList [%d] %s in %s on line %d\n", timeNow, error_number, error, func, line);

	fclose(logs_file);
}


char* TimeNow() {
	char* s = (char*) calloc(20, sizeof(s[0]));

	time_t t = time(NULL);
	struct tm* tt = localtime(&t);

	strftime(s, 20, "%d.%m.%Y %H:%M:%S ", tt);

	return s;
}
