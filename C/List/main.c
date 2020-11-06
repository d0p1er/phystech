#include "list.h"

int main() {
	struct List list = ListConstruct();
	
	AddValue(2, 10, &list);
	AddValue(3, 20, &list);
	AddValue(4, 30, &list);
	AddValue(3, 30, &list);

	PrintAll(&list);

	return 0;
}