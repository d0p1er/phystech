#ifndef CMD_NAME_H
#define CMD_NAME_H

enum Commands{
	#define DEF_CMD(name, num, m, arg, code) CMD_##name = num,
	
	#include "commands.h"

	#undef DEF_CMD
};

#endif