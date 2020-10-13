// #include "Stack.h"


// int main(){
// 	struct Stack stk = {};

// 	// Dump(&stk, NO_ERRORS, __FUNCTION__, __LINE__);

// 	// printf("0x%X\n", stk);
// 	StackConstruct(&stk);
// 	printf("construct\n");

// 	// printf("%lf\n", stk.data[stk.capacity + 2]);

// 	// printf("%d\n", &(stk.can_1));
// 	// printf("%d\n", &(stk.poison));
// 	// printf("%d\n", &(stk.size));
// 	// printf("%d\n", &(stk.capacity));
// 	// printf("%d\n", &(stk.can_2));

// 	for (size_t i = 0; i < 10; i++){
// 		StackPush(&stk, 10*i);
// 	}

// 	// for (size_t i = 0; i < 2500; i++){
// 	// 	StackPop(&stk);
// 	// }

// 	// stk.size = 10;
// 	// StackPush(&stk, 100);

// 	stk.data[0] = 10243104;
// 	printf("%lf\n", stk.data[0]);

// 	StackPush(&stk, 200);
// 	StackPush(&stk, 300);
// 	StackPush(&stk, 200);
// 	StackPush(&stk, 300);

// 	StackPop(&stk);
// 	StackPop(&stk);
// 	StackPop(&stk);
// 	StackPop(&stk);

// 	printf("push\n");

// 	// stk.size = 0;

// 	// stk.can_1 = 10;

// 	Dump(&stk, NO_ERRORS, __FUNCTION__, __LINE__);

// 	StackDestruct(&stk);

// 	Dump(&stk, NO_ERRORS, __FUNCTION__, __LINE__);

// 	return 0;

// }

#include "Stack.h"
// #define _CRT_SECURE_NO_WARNINGS

int main()
{
	struct Stack stk = {};
	StackConstruct(&stk);
	
	StackPush(&stk, 200);
	StackPush(&stk, 300);
	StackPush(&stk, 200);
	StackPush(&stk, 300);

	for (size_t i = 0; i < 1; i++)
	{
		stk.data[i] = NAN;
	}

	Dump(&stk, NO_ERRORS, __FUNCTION__, __LINE__);
	// printf("%lf", stk.data[2]);
}