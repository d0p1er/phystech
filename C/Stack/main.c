#include "Stack.h"


int main(){
	struct Stack stk = {};

	// Dump(&stk, NO_ERRORS, __FUNCTION__, __LINE__);

	// printf("0x%X\n", stk);
	StackConstruct(&stk);
	printf("construct\n");

	// printf("%lf\n", stk.data[stk.capacity + 2]);

	// printf("%d\n", &(stk.can_1));
	// printf("%d\n", &(stk.poison));
	// printf("%d\n", &(stk.size));
	// printf("%d\n", &(stk.capacity));
	// printf("%d\n", &(stk.can_2));

	// for (size_t i = 0; i < 3500; i++){
	// 	StackPush(&stk, 10*i);
	// }

	// for (size_t i = 0; i < 2500; i++){
	// 	StackPop(&stk);
	// }

	// stk.size = 10;
	// StackPush(&stk, 100);


	StackPush(&stk, 200);
	StackPush(&stk, 300);
	StackPush(&stk, 200);
	StackPush(&stk, 300);

	StackPop(&stk);
	StackPop(&stk);
	StackPop(&stk);
	StackPop(&stk);

	printf("push\n");

	// stk.size = 0;

	// stk.can_1 = 10;

	Dump(&stk, NO_ERRORS, __FUNCTION__, __LINE__);

	StackDestruct(&stk);

	Dump(&stk, NO_ERRORS, __FUNCTION__, __LINE__);

	return 0;

}