#include "differ.h"


void ReadMathExpression(struct NodeTree* node, char* path) {
	size_t file_size = GetFileSize(path);
	char* text = GetTextFromFile(path, file_size);
	char* text_without_spaces = WithoutSpaces(text, file_size);

	ReadExpr(node, ++text_without_spaces);

	InorderWrite(node);
	printf("\n");
}

char* WithoutSpaces(char* str, size_t lenght) {
	char* res = (char*) calloc(lenght, sizeof(res[0]));
	size_t counter = 0;

	while (*str) {
		if (isspace(*str)){
			str++;
			continue;
		}

		res[counter++] = *str++;
	}
	res[counter] = '\0';

	return res;
}

#define MAX_DATA 100

char* ReadExpr(struct NodeTree* node, char* text) {
	if (*text == ')')
		return ++text;

	if (*text == '(') {
		text++;
		struct NodeTree* node_left  = (struct NodeTree*) calloc(1, sizeof(node_left[0]));
		node_left->parent = node;
		node->left = node_left;
		DBG printf("create left node %s\n", text);

		if (*text == '(') {
			text = ReadExpr(node_left, ++text);
			if (*text == ')') {
				printf("ret\n");
				return ++text;
			}
		}

		char data[MAX_DATA] = "";
		size_t counter = 0;
		while (*text != ')')
			data[counter++] = *text++;
		data[counter] = '\0';
		text++;

		sscanf(data, OUTPUT_FORMAT_TREE, &(node_left->data));
		node_left->type_data = NUMBER;
		DBG printf("write left node data %s\n", data);

		counter = 0;
		while (*text != '(')
			data[counter++] = *text++;
		data[counter] = '\0';
		text++;

		if (counter == 1)
			node->data = (TYPE_TREE) data[0];
		// sscanf(data, OUTPUT_FORMAT_TREE, &(node->data));
		node->type_data = OPERATION;
		DBG printf("write node data %s\n", data);


		struct NodeTree* node_right  = (struct NodeTree*) calloc(1, sizeof(node_right[0]));
		node_right->parent = node;
		node->right = node_right;
		DBG printf("create right node %s\n", text);

		if (*text == '(') {
			text = ReadExpr(node_right, text);
			if (*text == ')') {
				printf("ret\n");
				return ++text;
			}
		}

		counter = 0;
		while (*text != ')')
			data[counter++] = *text++;
		data[counter] = '\0';
		text++;

		sscanf(data, OUTPUT_FORMAT_TREE, &(node_right->data));
		node_right->type_data = NUMBER;
		DBG printf("write right node data %s\n", data);

		return ++text;
	}
}

double Eval(struct NodeTree* node) {
	#define DATA node->data
	#define L node->left
	#define R node->right
	#define DO_OPER(oper) Eval(L) oper Eval(R)

	#define RET

	switch (node->type_data) {
		case NUMBER: return DATA;
		// case VARIABLE: return var_table[DATA].value;
		case OPERATION:
			switch ((int) DATA) {
				case ADD: return DO_OPER(+);
				case SUB: return DO_OPER(-);
				case MUL: return DO_OPER(*);
				case DIV: return DO_OPER(/);
				default:  printf("UNKNOWN OPERATION\n"); return NAN;
			}
		default: printf("TYPE ERROR\n"); return NAN;
	}
}

// struct NodeTree* Differentation(struct NodeTree* node) {
// 	switch (node->type_data) {
// 		switch (node->type_data) {
// 		case NUMBER: return DATA;
// 		case VARIABLE: return var_table[DATA].value;
// 		case OPERATION:
// 			switch ((int) DATA) {
// 				case ADD: return DO_OPER(+);
// 				case SUB: return DO_OPER(-);
// 				case MUL: return DO_OPER(*);
// 				case DIV: return DO_OPER(/);
// 				default:  printf("UNKNOWN OPERATION\n"); return NAN;
// 			}
// 		default: printf("TYPE ERROR\n"); return NAN;
// 	}
// 	}
// }