#define DO_PUSH(value) StackPush(&stk, value)
#define DO_POP StackPop(&stk)
#define DO_OPER(sign) DO_POP sign DO_POP
#define ARG(x) x 
#define MODE(x) x
#define COMPAR(comp) if (DO_POP comp DO_POP)
#define RIP rip = (int) cpu.tags[(int) value] - 1

// PUSH rax и просто
// мб добавить mode ( для push и pop)
//		1) простой
//		2) регистры
//		3) RAM

DEF_CMD(PUSH, 		0, 		MODE(1), 	ARG(1),	{rip++;
												 switch((int) mode) {
												 	case 0: DO_PUSH(value); break;
												 	case 1: DO_PUSH(cpu.regs[(int) value]); break;
												 	case 2: DO_PUSH(cpu.RAM[(int) value]); break;
												 	case 3: DO_PUSH(cpu.RAM[(int) cpu.regs[(int) value]]); break;
												 	default: printf("Unknown mode\n");
												 }})

DEF_CMD(POP, 		2, 		MODE(1),	ARG(1),	{rip++;
												 switch((int) mode) {
												 	case 0: DO_POP; break;
												 	case 1: cpu.regs[(int) value] = DO_POP; break;
												 	case 2: cpu.RAM[(int) value] = DO_POP; break;
												 	case 3: cpu.RAM[(int) cpu.regs[(int) value]] = DO_POP; break;
												 	default: printf("Unknown mode\n");
												 }})

DEF_CMD(IN, 		4, 		MODE(0),	ARG(0),	{
												 double value = 0;
											 	 scanf("%lf", &value);
											 	 DO_PUSH(value);
												})

DEF_CMD(OUT, 		5, 		MODE(0),	ARG(0),	{
												 double ans = DO_POP;
												 printf("%lf\n", ans);
												})

DEF_CMD(NEG, 		6, 		MODE(0),	ARG(0),	{DO_PUSH((-1) * DO_POP);})


DEF_CMD(ADD, 		10,		MODE(0),	ARG(0),	{DO_PUSH(DO_OPER(+));})

DEF_CMD(SUB, 		11, 	MODE(0),	ARG(0),	{DO_PUSH(DO_OPER(-));})

DEF_CMD(MUL, 		12, 	MODE(0),	ARG(0),	{DO_PUSH(DO_OPER(*));})

DEF_CMD(DIV, 		13, 	MODE(0),	ARG(0),	{DO_PUSH(DO_OPER(/));})


DEF_CMD(SIN, 		20, 	MODE(0),	ARG(0),	{DO_PUSH(sin(DO_POP));})

DEF_CMD(COS, 		21, 	MODE(0),	ARG(0),	{DO_PUSH(cos(DO_POP));})

DEF_CMD(SQRT, 		22, 	MODE(0),	ARG(0),	{DO_PUSH(sqrt(DO_POP));})

DEF_CMD(LEN, 		23, 	MODE(0),	ARG(0),	{DO_PUSH(sqrt(pow(DO_POP - DO_POP, 2) + pow(DO_POP - DO_POP, 2)));})


DEF_CMD(DEC, 		30, 	MODE(0),	ARG(0),	{DO_PUSH(DO_POP - 1);})

DEF_CMD(INC, 		31, 	MODE(0),	ARG(0),	{DO_PUSH(DO_POP + 1);})


DEF_CMD(JA, 		50, 	MODE(0),	ARG(1),	{COMPAR(>) RIP;})

DEF_CMD(JAE, 		51, 	MODE(0),	ARG(1),	{COMPAR(>=) RIP;})

DEF_CMD(JB, 		52, 	MODE(0),	ARG(1),	{COMPAR(<) RIP;})

DEF_CMD(JBE, 		53, 	MODE(0),	ARG(1),	{COMPAR(<=) RIP;})

DEF_CMD(JE, 		54, 	MODE(0),	ARG(1),	{COMPAR(==) RIP;})

DEF_CMD(JNE, 		55, 	MODE(0),	ARG(1),	{COMPAR(!=) RIP;})

DEF_CMD(JDC, 		56, 	MODE(0),	ARG(1),	{if (AreNumbersEqual(DO_POP, DO_POP)) RIP;})


DEF_CMD(JMP, 		100, 	MODE(0),	ARG(1),	{RIP;})

DEF_CMD(CALL, 		101, 	MODE(0),	ARG(0),	{
												 StackPush(&cpu.service_stack, rip - 1);
												 Dump(&stk, 0, __FUNCTION__, __LINE__);
												})

DEF_CMD(RET, 		102, 	MODE(0),	ARG(0),	{rip = StackPop(&cpu.service_stack);})

DEF_CMD(DRAW, 		103, 	MODE(0),	ARG(0),	{
												 for (size_t i = 0; i < 50; i++) {
													for (size_t j = 0; j < 50; j++) {
														printf("%c ", (int) cpu.RAM[i * 50 + j]);
													}
													printf("\n");
												}})

DEF_CMD(DUMP, 		111, 	MODE(0),	ARG(0),	{Dump(&stk, 0, __FUNCTION__, __LINE__);})

DEF_CMD(EXIT, 		666, 	MODE(0),	ARG(0),	{printf("exit\n"); return;})
