#include "list.h"

const int poison = 0xDEADBEEF;

struct List ListConstruct() {
	struct List list = {};
	list.capacity = 32;
	list.size = 0;
	list.free = 1;

	list.values = (int*) calloc(list.capacity, sizeof(list.values[0]));
	list.next =   (int*) calloc(list.capacity, sizeof(list.values[0]));
	list.prev =   (int*) calloc(list.capacity, sizeof(list.values[0]));
	
	list.values[0] = 0;
	list.next[0]   = 0;
	list.prev[0]   = 0;

	for (size_t i = 1; i < list.capacity; i++) {
		list.values[i] = poison;
		list.next[i]   = i + 1;
		list.prev[i]   = i - 1;
	}

	list.next[list.capacity - 1] = 0;
	list.prev[1] = 0;

	return list;
}


void AddValue(int pos, int value, struct List* list) {
	if (list->values[pos] == poison) {
		
		list->values[pos] = value;

		if (pos != list->free) {
			list->next[list->prev[pos]] = list->next[pos];
			list->prev[list->next[pos]] = list->prev[pos];
		}
		else {
			list->prev[list->next[pos]] = 0;
			list->free = list->next[list->free];
		}

		list->next[list->tail] = pos;
		list->next[pos] = 0;
		list->prev[pos] = list->tail;

		list->next[0] = 0;
		list->prev[0] = 0;

		list->tail = pos;
		if (list->size == 0)
			list->head = pos;
		
		list->size++;
	}
	else {
		int new_pos = list->free;
		list->free = list->next[list->free];

		list->values[new_pos] = list->values[pos];
		list->values[pos] = value;

		list->next[new_pos] = list->next[pos];
		list->next[list->prev[pos]] = new_pos;
		list->next[list->tail] = pos;
		
		list->prev[new_pos] = list->prev[pos];
		list->prev[list->next[pos]] = new_pos;

		list->next[pos] = 0;
		list->prev[pos] = list->tail;
		
		list->next[0] = 0;
		list->prev[0] = 0;

		list->tail = pos;
		list->size++;
	}	
}

int Delete(int pos, struct List* list) {
	int val = list->values[pos];
	list->values[pos] = poison;
	list->size--;

	if (list->size == 1) {
		list->next[pos] = list->free;
		list->prev[pos] = 0;

		list->prev[list->free] = pos;
		list->free = pos;

		return val;
	}

	if (pos == list->head) {
		list->head = list->next[pos];
		list->prev[list->next[pos]] = 0;

		UpdateFree

		return val;

	}

	if (pos == list->tail) {
		list->tail = list->prev[pos];
		list->next[list->prev[pos]] = 0;

		UpdateFree

		return val;
	}

	list->next[list->prev[pos]] = list->next[pos];
	list->prev[list->next[pos]] = list->prev[pos];

	UpdateFree

	return val;
}

int Verification(struct List* list) {
	int pos = list->next[list->head];
	if (list->size > 2) {
		for (size_t i = 1; i < list->size - 1; i++) {
		printf("pos %d\n", pos);
		printf("prev next %d\n", list->prev[list->next[pos]]);
		printf("next prev %d\n", list->next[list->prev[pos]]);
		if (list->prev[list->next[pos]] != list->next[list->prev[pos]]) 
			return NEXT_PREV_ERROR;

		pos = list->next[pos];
		}
	}
	

	pos = list->next[list->head];
	for (size_t i = 0; i < list->size; i++)
		pos = list->next[pos];

	if (pos != 0)
		return NEXT_ERROR;

	pos = list->prev[list->tail];
	for (size_t i = 0; i < list->size; i++) 
		pos = list->prev[pos];

	if (pos != 0)
		return PREV_ERROR;

	return EVERYTHING_OKAY;
}


void DrawGraph(struct List* list) {
	FILE* graph_file = fopen("graph.gv", "w");

	fprintf(graph_file, "digraph List {");

	int pos = list->head;
	for (size_t i = 0; i < list->size; i++) {
		fprintf(graph_file, "	box%d [shape=\"record\", fillcolor = chartreuse, style = filled, label = \"{<value>%d|{<prev> %d|<pos> %d|<next> %d}}\"];\n", pos, list->values[pos], list->prev[pos], pos, list->next[pos]);
		fprintf(graph_file, "	box%d:prev -> box%d:pos;\n", pos, list->prev[pos]);
		fprintf(graph_file, "	box%d:next -> box%d:value;\n", pos, list->next[pos]);

		pos = list->next[pos];
	}

	pos = list->free;
	for (size_t i = 0; i < list->capacity - list->size - 1; i++) {
		fprintf(graph_file, "	box%d [shape=\"record\", fillcolor = red, style = filled, label = \"{<value>%d|{<prev> %d|<pos> %d|<next> %d}}\"];\n", pos, list->values[pos], list->prev[pos], pos, list->next[pos]);
		fprintf(graph_file, "	box%d:prev -> box%d:pos;\n", pos, list->prev[pos]);
		fprintf(graph_file, "	box%d:next -> box%d:value;\n", pos, list->next[pos]);

		pos = list->next[pos];
	}

	fprintf(graph_file, "}\n");
	
	fclose(graph_file);

	system("dot -Tpng graph.gv -o list.png");
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

	printf("\n");
}