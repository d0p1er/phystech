#include "cpu.h"

const double poison = NAN;

int CPU(char* path){
	struct Text text = FillText(path);

	for(size_t i = 0; i < text.n_lines - 1; i++){
		int cmd = 0;  // The poubivaju of the nahren
		double value = poison;
		sscanf(text.pointers[i], "%d %lf", &cmd, &value);

		struct Stack stk = {};
		StackConstruct(&stk);

		// printf("%d %d\n", cmd, value);

		switch(cmd){
			#define DEF_CMD(name, num, arg, code) case num: code; break;

			#include "../Data/commands.h"
			#undef DEF_CMD

			default: return 0;
		}	

		printf("%ld\n", i);
	}
}