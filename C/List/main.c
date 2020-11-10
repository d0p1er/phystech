#include "list.h"

int main() {
	struct List list = ListConstruct();
	
	for (size_t i = 0; i < 10; i++)
		AddValue(i + 1, (i + 1)*10, &list);

	DrawGraph(&list);

	// AddValue(2, 10, &list);
	// AddValue(3, 20, &list);

	// DrawGraph(&list);
	// Delete(3, &list);
	// AddValue(4, 30, &list);
	// AddValue(3, 30, &list);
	// Delete(3, &list);

	printf("head %d\n", list.head);
	printf("tail %d\n", list.tail);

	int err = Verification(&list);
	printf("%d\n", err);

	PrintAll(&list);

	return 0;
}