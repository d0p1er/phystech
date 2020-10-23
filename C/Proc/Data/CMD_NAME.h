enum Commands{
	#define DEF_CMD(name, num, arg, code) CMD_##name = num,
	
	#include "commands.h"

	#undef DEF_CMD
};