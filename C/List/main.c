#include "list.h"

// разобраться с дотом и расставлять ячейки в правильном порядке

int main() {
	struct List list = {};
	ListConstruct(&list);
	
	for (size_t i = 0; i < 30; i++) {
		// printf("%d", AddValueAfter((i + 1)*10, &list));
		AddValueAfter((i + 1)*10, &list);
	}
	// PrintAllList(&list);

	for (size_t i = 1; i < 10; i++) {
		// printf("%d", AddValueAfter((i + 1)*10, &list));
		Delete(i * 2, &list);
	}
	// PrintAllList(&list);

	for (size_t i = 0; i < 20; i++){
		// printf("%d", AddValueBefore((-1)*i*10, &list));
		AddValueBefore((-1)*i*10, &list);
	}

	// printf("%d\n", Verification(&list));

	// PrintAllList(&list);

	// Sort(&list);

	// PrintAllList(&list);

	DrawGraphList(&list);

	// AddValue(2, 10, &list);
	// AddValue(3, 20, &list);

	// DrawGraph(&list);
	// Delete(3, &list);
	// AddValue(4, 30, &list);
	// AddValue(3, 30, &list);
	// Delete(3, &list);

	// printf("head %d\n", list.head);
	// printf("tail %d\n", list.tail);

	// int err = Verification(&list);
	// printf("%d\n", err);

	

	


	return 0;
}