#include "differ.h"


void ReadMathExpression(struct NodeTree* node, char* path) {
	size_t file_size = GetFileSize(path);
	char* text = GetTextFromFile(path, file_size);
	char* text_without_spaces = WithoutSpaces(text, file_size);

	ReadExpr(node, ++text_without_spaces);

	PrintExpr(node);
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
		struct NodeTree* node_left  = (struct NodeTree*) calloc(1, sizeof(node_left[0]));
		node_left->parent = node;
		node->left = node_left;

		if (*(++text) == '(') {
			text = ReadExpr(node_left, text);

			if (*text == ')')
				return ++text;
		}
		else 
			text = WriteNodeTreeData(node_left, text, ')');

		text = WriteNodeTreeData(node, text, '(');

		struct NodeTree* node_right  = (struct NodeTree*) calloc(1, sizeof(node_right[0]));
		node_right->parent = node;
		node->right = node_right;

		if (*text == '(') {
			text = ReadExpr(node_right, text);
			if (*text == ')') {
				printf("ret\n");
				return ++text;
			}
		}

		text = WriteNodeTreeData(node_right, text, ')');

		return ++text;
	}
}

char* WriteNodeTreeData(struct NodeTree* node, char* text, char end) {
	char data[MAX_DATA] = "";
	size_t counter = 0;

	while (*text != end)
		data[counter++] = *text++;
	data[counter] = '\0';
	text++;

	if (IsOper(data[0])) {
		node->type_data = OPERATION;
		node->data = (TYPE_TREE) data[0];
	}
	else {
		node->type_data = NUMBER;
		sscanf(data, OUTPUT_FORMAT_TREE, &(node->data));
	}

	return text;
}

int IsOper(char c) {
	if (c == ADD || c == SUB || c == MUL || c == DIV || c == POW)
		return 1;
	else
		return 0;
}

double Eval(struct NodeTree* node) {
	#define DATA node->data
	#define L node->left
	#define R node->right
	#define DO_OPER(oper) Eval(L) oper Eval(R)

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

void PrintExpr(struct NodeTree* node) {
	if (!node) return;

	printf("(");

	PrintExpr(node->left);

	if (node->type_data == OPERATION)
		printf("%c", (int) node->data);
	else
		printf(OUTPUT_FORMAT_TREE, node->data);

	PrintExpr(node->right);

	printf(")");

	return;
}

// struct NodeTree* Differentation(struct NodeTree* node) {
// 	switch (node->type_data) {
// 		switch (node->type_data) {
// 		case NUMBER: return DATA;
// 		// case VARIABLE: return var_table[DATA].value;
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

// struct NodeTree* CreateNodeDiff()