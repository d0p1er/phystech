#define DO_PUSH(value) StackPush(&stk, value)
#define DO_POP StackPop(&stk)
#define DO_OPER(sign) DO_POP sign DO_POP
#define N_CMD(x) x
#define ARG(x) x 
#define MODE(x) x
#define COMPAR(comp) if (DO_POP comp DO_POP)
#define RIP rip = (int) cpu.tags[(int) value] - 1

// #define BOLD "\x1B[1m"
// #define KBCK  "\x1B[30m"
// #define KRED  "\x1B[31m"
// #define KGRN  "\x1B[32m"
// #define KYEL  "\x1B[33m"
// #define KBLU  "\x1B[34m"
// #define KMAG  "\x1B[35m"
// #define KCYN  "\x1B[36m"
// #define KWHT  "\x1B[37m"
 
// #define BCK(x) KBCK x RST
// #define RED(x) KRED x RST
// #define GRN(x) KGRN x RST
// #define YEL(x) KYEL x RST
// #define BLU(x) KBLU x RST
// #define MAG(x) KMAG x RST
// #define WHT(x) KWHT x RST
 
// #define BOLD(x) "\x1B[1m" x RST
 


DEF_CMD(PUSH, 	N_CMD(0), 		MODE(1), 	ARG(1),	{rip++;
													 switch((int) mode) {
													 	case 0: DO_PUSH(value); break;
													 	case 1: DO_PUSH(cpu.regs[(int) value]); break;
													 	case 2: DO_PUSH(cpu.RAM[(int) value]); break;
													 	case 3: DO_PUSH(cpu.RAM[(int) cpu.regs[(int) value]]); break;
													 	default: printf("Unknown mode\n");
													 }})

DEF_CMD(POP, 	N_CMD(1), 		MODE(1),	ARG(1),	{rip++;
													 switch((int) mode) {
													 	case 0: DO_POP; break;
													 	case 1: cpu.regs[(int) value] = DO_POP; break;
													 	case 2: cpu.RAM[(int) value] = DO_POP; break;
													 	case 3: cpu.RAM[(int) cpu.regs[(int) value]] = DO_POP; break;
													 	default: printf("Unknown mode\n");
													 }})

DEF_CMD(IN, 	N_CMD(2), 		MODE(0),	ARG(0),	{
													 double value = 0;
												 	 scanf("%lf", &value);
												 	 DO_PUSH(value);
													})

DEF_CMD(OUT, 	N_CMD(3), 		MODE(0),	ARG(0),	{
													 double ans = DO_POP;
													 printf("%lf\n", ans);
													})


DEF_CMD(ADD, 	N_CMD(10),		MODE(0),	ARG(0),	{DO_PUSH(DO_OPER(+));})

DEF_CMD(SUB, 	N_CMD(11), 		MODE(0),	ARG(0),	{DO_PUSH(DO_OPER(-));})

DEF_CMD(MUL, 	N_CMD(12), 		MODE(0),	ARG(0),	{DO_PUSH(DO_OPER(*));})

DEF_CMD(DIV, 	N_CMD(13), 		MODE(0),	ARG(0),	{DO_PUSH(DO_OPER(/));})

DEF_CMD(NEG, 	N_CMD(14), 		MODE(0),	ARG(0),	{DO_PUSH((-1) * DO_POP);})


DEF_CMD(SIN, 	N_CMD(20), 		MODE(0),	ARG(0),	{DO_PUSH(sin(DO_POP));})

DEF_CMD(COS, 	N_CMD(21), 		MODE(0),	ARG(0),	{DO_PUSH(cos(DO_POP));})

DEF_CMD(SQRT, 	N_CMD(22), 		MODE(0),	ARG(0),	{DO_PUSH(sqrt(DO_POP));})

DEF_CMD(LEN, 	N_CMD(23), 		MODE(0),	ARG(0),	{DO_PUSH(sqrt(pow(DO_POP - DO_POP, 2) + pow(DO_POP - DO_POP, 2)));})


DEF_CMD(DEC, 	N_CMD(30), 		MODE(0),	ARG(0),	{DO_PUSH(DO_POP - 1);})

DEF_CMD(INC, 	N_CMD(31), 		MODE(0),	ARG(0),	{DO_PUSH(DO_POP + 1);})


DEF_CMD(JA, 	N_CMD(50), 		MODE(0),	ARG(1),	{COMPAR(>) RIP;})

DEF_CMD(JAE, 	N_CMD(51), 		MODE(0),	ARG(1),	{COMPAR(>=) RIP;})

DEF_CMD(JB, 	N_CMD(52), 		MODE(0),	ARG(1),	{COMPAR(<) RIP;})

DEF_CMD(JBE, 	N_CMD(53), 		MODE(0),	ARG(1),	{COMPAR(<=) RIP;})

DEF_CMD(JE, 	N_CMD(54), 		MODE(0),	ARG(1),	{COMPAR(==) RIP;})

DEF_CMD(JNE, 	N_CMD(55), 		MODE(0),	ARG(1),	{COMPAR(!=) RIP;})

DEF_CMD(JDC, 	N_CMD(56), 		MODE(0),	ARG(1),	{if (AreNumbersEqual(DO_POP, DO_POP)) RIP;})


DEF_CMD(JMP, 	N_CMD(100), 	MODE(0),	ARG(1),	{RIP;})

DEF_CMD(CALL, 	N_CMD(101), 	MODE(0),	ARG(0),	{
													 StackPush(&cpu.service_stack, rip - 1);
													 Dump(&stk, 0, __FUNCTION__, __LINE__);
													})

DEF_CMD(RET, 	N_CMD(102), 	MODE(0),	ARG(0),	{rip = StackPop(&cpu.service_stack);})

DEF_CMD(DRAW, 	N_CMD(103), 	MODE(0),	ARG(0),	{
													 for (size_t i = 0; i < 100; i++) {
														for (size_t j = 0; j < 100; j++) {
															if ((int) cpu.RAM[i * 100 + j] == 46)
																printf("%s%c ", COLORS[1], (int) cpu.RAM[i * 100 + j]);
															else
																printf("%s%c ", COLORS[cpu.color], (int) cpu.RAM[i * 100 + j]);
														}
														printf("\n");
													}})

DEF_CMD(CLR, 	N_CMD(104), 	MODE(0),	ARG(1),	{cpu.color = (int) value;})

DEF_CMD(DUMP, 	N_CMD(111), 	MODE(0),	ARG(0),	{Dump(&stk, 0, __FUNCTION__, __LINE__);})

DEF_CMD(EXIT, 	N_CMD(666), 	MODE(0),	ARG(0),	{printf("exit\n"); return 1;})
