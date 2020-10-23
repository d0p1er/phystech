#define DO_PUSH(value) StackPush(&stk, value)
#define DO_POP StackPop(&stk)
#define DO_OPER(sign) DO_POP sign DO_POP
#define ARG(x) x 

DEF_CMD(PUSH, 	0, 		ARG(1),	{DO_PUSH(value);})

DEF_CMD(POP, 	1, 		ARG(0),	{DO_POP;})

DEF_CMD(IN, 	2, 		ARG(0),	{int value = 0;
								 scanf("%d", &value);
								 DO_PUSH(value);
								})

DEF_CMD(OUT, 	3, 		ARG(0),	{printf("%lf\n", DO_POP);})

DEF_CMD(NEG, 	4, 		ARG(0),	{DO_PUSH((-1) * DO_POP);})


DEF_CMD(ADD, 	10,		ARG(0),	{DO_PUSH(DO_OPER(+));})

DEF_CMD(SUB, 	11, 	ARG(0),	{DO_PUSH(DO_OPER(-));})

DEF_CMD(MUL, 	12, 	ARG(0),	{DO_PUSH(DO_OPER(*));})

DEF_CMD(DIV, 	13, 	ARG(0),	{DO_PUSH(DO_OPER(/));})


DEF_CMD(SIN, 	20, 	ARG(0),	{DO_PUSH(sin(DO_POP));})

DEF_CMD(COS, 	21, 	ARG(0),	{DO_PUSH(cos(DO_POP));})

DEF_CMD(SQRT, 	22, 	ARG(0),	{DO_PUSH(sqrt(DO_POP));})


DEF_CMD(DUMP, 	111, 	ARG(0),	{Dump(&stk, 0, __FUNCTION__, __LINE__);})

DEF_CMD(EXIT, 	666, 	ARG(0),	{printf("exit\n"); return;})
