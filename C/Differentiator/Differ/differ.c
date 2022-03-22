#include "differ.h"

#define MAX_AMOUNT_VAR 100

struct Variable variables[MAX_AMOUNT_VAR] = {};
char* str_expr = NULL;

struct NodeTree* ReadMathExpression(char* path) {

	size_t file_size = GetFileSize(path);
	char* text = GetTextFromFile(path, file_size);
	char* text_without_spaces = WithoutSpaces(text, file_size);
	
	return GetG(text_without_spaces);
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


void PrintExpr(struct NodeTree* node) {
	if (!node || isnan(node->data)) return;

	printf("(");

	PrintExpr(node->left);

	if (node->type_data == NUMBER)
		printf(OUTPUT_FORMAT_TREE, node->data);
	else if (node->type_data == VARIABLE) {
		// printf("%c", (int) node->data);
		printf("%c", variables[(int) node->data].name);
	}
	else if (node->type_data == OPERATION)
		printf("%c", (int) node->data);
	else if (node->type_data == FUNCTION)
		PrintFunc((int) node->data);
	
	PrintExpr(node->right);

	printf(")");

	return;
}


void PrintFunc(int num_func) {
	#define DEF_FUNC(name, num, tex, code)	\
		if (num_func == num) {				\
			printf("%s", #name);			\
		}

	#include "../Data/functions.h"

	#undef DEF_FUNC
}


struct NodeTree* Simplify(struct NodeTree* node, int* simp) {
	if (!node || isnan(node->data)) return node;

	if (node->type_data == OPERATION) {
		if (node->data == MUL) {
			if ((int) (node->left)->data == 0 || (int) (node->right)->data == 0) {
				node->left = NULL;
				node->right = NULL;
				*simp++;
				return CreateNode(NUMBER, 0, NULL, NULL);
			}
			if ((int) (node->left)->data == 1) {
				node->left = NULL;

				*simp++;
				return node->right;
			}
			if ((int) (node->right)->data == 1) {
				node->right = NULL;

				*simp++;
				return node->left;
			}
		}

		if (node->data == ADD) {
			if ((int) (node->left)->data == 0) {
				node->left = NULL;

				*simp++;
				return node->right;
			}
			if ((int) (node->right)->data == 0) {
				node->right = NULL;

				*simp++;
				return node->left;
			}
		}

		if (node->data == SUB) {
			if ((int) (node->left)->data == 0) {
				node->left = NULL;

				*simp++;
				return node->right;
			}
			if ((int) (node->right)->data == 0) {
				node->right = NULL;

				*simp++;
				return node->left;
			}
		}

		if (node->data == POW) {
			if ((int) (node->right)->data == 1) {
				node->right = NULL;

				return node->left;
			}
		}

		if ((node->left)->type_data == NUMBER && (node->right)->type_data == NUMBER) 
			return CreateNode(NUMBER, Eval(node), NULL, NULL);
	}


	node->left = Simplify(node->left, simp);

	node->right = Simplify(node->right, simp);

	return node;
}


double Eval(struct NodeTree* node) {
	switch (node->type_data) {
		case NUMBER: return DATA;
		case VARIABLE: return variables[(int) DATA].value;
		case OPERATION:
			switch ((int) DATA) {
				case ADD: return DO_OPER(+);
				case SUB: return DO_OPER(-);
				case MUL: return DO_OPER(*);
				case DIV: return DO_OPER(/);
				case POW: return pow(Eval(L), Eval(R));
				default:  printf("UNKNOWN OPERATION\n"); return NAN;
			}
		default: printf("TYPE ERROR\n"); return NAN;
	}
}


struct NodeTree* Differentation(struct NodeTree* node, struct Tree* tree, FILE* file) {
	struct NodeTree* tmp = calloc(1, sizeof(tmp[0]));
	switch (node->type_data) {
		case NUMBER: 	DBG printf("NUM\n");	RETNODE(CREATE_NUM_NODE(0));  
		case VARIABLE: 	DBG printf("VAR\n");	RETNODE(CREATE_NUM_NODE(1));
		case OPERATION:
			switch ((int) DATA) {
				case ADD: DBG printf("ADD\n"); RETNODE(ADDITION(dL, dR));
				case SUB: DBG printf("SUB\n"); RETNODE(SUBTRACT(dL, dR));
				case MUL: DBG printf("MUL\n"); RETNODE(ADDITION(MULTIPLY(dL, cR), MULTIPLY(cL, dR)));
				case DIV: DBG printf("DIV\n"); RETNODE(DIVISION(SUBTRACT(MULTIPLY(dL, cR), MULTIPLY(cL, dR)), POWER(cR, CREATE_NUM_NODE(2))));
				case POW: {
					if (R->type_data == NUMBER) {
						RETNODE(MULTIPLY(dL, MULTIPLY(CREATE_NUM_NODE(R->data), POWER(cL, CREATE_NUM_NODE((int) R->data - 1)))));
					}
					else if (L->type_data == NUMBER) {
						RETNODE(MULTIPLY(CopyNode(node), MULTIPLY(dR, LOGN(cR))));
					}
				}
				default:  printf("UNKNOWN OPERATION\n"); RETNODE(node);
			}
		case FUNCTION:
			#define DEF_FUNC(name, num, tex, code)	\
				if ((int) DATA == num) {			\
					DBG printf("%s\n", #name); 		\
					RETNODE(code);					\
				}

			#include "../Data/functions.h"

			#undef DEF_FUNC

		default: printf("TYPE ERROR\n"); return node;
	}
}

int SizeTree(struct NodeTree* node, int size) {
	if (!node || isnan(node->data)) return size;

	size = SizeTree(node->left, size);

	size++;

	size = SizeTree(node->right, size);

	return size;

}

struct NodeTree* CreateNode(int type_data, TYPE_TREE data, struct NodeTree* node_left, struct NodeTree* node_right) {
	struct NodeTree* node = (struct NodeTree*) calloc(1, sizeof(node[0]));
	node->type_data = type_data;
	node->data = data;
	node->left = node_left;
	node->right = node_right;

	return node;
}

struct NodeTree* CopyNode(struct NodeTree* node) {
	struct NodeTree* new_node = (struct NodeTree*) calloc(1, sizeof(new_node[0]));
	new_node->type_data = node->type_data;
	new_node->data = node->data;
	new_node->left = node->left;
	new_node->right = node->right;

	return new_node;
}

struct NodeTree* PrintEqual(struct NodeTree* node_1, struct NodeTree* node_2, struct Tree* tree, FILE* file) {
	PrintRandomLatex(file);
	fprintf(file, "\\normalsize \\begin{center, tmargin=1cm, bmargin=1cm, lmargin=0cm, rmargin=1cm}\n$$\\n(");
	PrintNodeLatex(node_1, tree, file);
	fprintf(file, ")` = ");
	int s = SizeTree(node_2, 1);
	if (s > 10) 
		fprintf(file, "\\\\ \\normalsize \\begin{center,  tmargin=1cm, bmargin=1cm, lmargin=0cm, rmargin=1cm} $$ = ");

	PrintNodeLatex(node_2, tree, file);

	if (s > 10) 
		fprintf(file, "$$ \\end{center}");

	fprintf(file, "$$\n\\end{center}\n");

	return node_2;
}


void PrintRandomLatex(FILE* file) {
	struct Text text = FillText("Data/phrases.txt");
	int r = rand() % 10;

	fprintf(file, "%s\n", text.pointers[r]);
}


void PrintLatexStart(struct NodeTree* node, struct Tree* tree, FILE* file) {
	fprintf(file,	"\\documentclass{article}\n"
					"\\usepackage[utf8]{inputenc}\n"
					"\\usepackage[T2A]{fontenc}\n"
					"\\usepackage[russian]{babel}\n"
					"\\begin{document}\n"
					"\\begin{center}\n"
					"\\huge{Научная работа по теме: \nПроизводная сложных функций.\nДифференциал.}\n"
					"\\end{center}\n");

	fprintf(file, "\\normalsize{\n\nДавайте попробуем взять производную данной функции:}\n");

	fprintf(file, "\\large $$\n");
	PrintNodeLatex(node, tree, file);
	fprintf(file, "$$\n\\newpage");
}

void PrintLatexEnd(struct NodeTree* node_old, struct NodeTree* node, struct Tree* tree, FILE* file) {
	for (size_t i = 0; i < 20; i++) {
		Simplify(node, 0);
	}

	fprintf(file, "Немного упростим наш ответ и получим, что\n");
	PrintEqual(node_old, node, tree, file);

	fprintf(file, "\\end{document}\n");
	fclose(file);
}


void PrintNodeLatex(struct NodeTree* node, struct Tree* tree, FILE* file) {
	if (!node || isnan(node->data)) return;

	if (node->type_data == OPERATION && node != tree->root && (int) node->data != DIV && (int) node->data != POW)
		fprintf(file, "(");
	if (node->type_data != OPERATION || (int) node->data != DIV)
		PrintNodeLatex(node->left, tree, file);
	
	switch (node->type_data) {
		case NUMBER: fprintf(file, "%d", (int) node->data); break;
		case VARIABLE: fprintf(file, "%c", (int) node->data); break;
		case OPERATION:
			switch ((int) node->data) {
				case ADD: fprintf(file, "+"); break;
				case SUB: fprintf(file, "-"); break;
				case MUL: fprintf(file, "*"); break;
				case DIV: fprintf(file, "\\frac{"); PrintNodeLatex(node->left, tree, file); fprintf(file, "}"); break;
				case POW: fprintf(file, "^"); break;
				default:  printf("UNKNOWN OPERATION\n"); break;
			}
		case FUNCTION:

			#define DEF_FUNC(name, num, tex, code)				\
				if ((int) DATA == num) {						\
					fprintf(file, tex);							\
				}


			#include "../Data/functions.h"


			#undef DEF_FUNC
		default: printf("TYPE ERROR\n"); break;
	}
	if (node->type_data == OPERATION && (int) node->data == DIV)
		fprintf(file, "{");
	PrintNodeLatex(node->right, tree, file);
	if (node->type_data == OPERATION && (int) node->data == DIV)
		fprintf(file, "}");

	if (node->type_data == OPERATION && node != tree->root && (int) node->data != DIV && (int) node->data != POW)
		fprintf(file, ")");

	return;
}


//////////////////////////////////////////////////
// Read expression
//////////////////////////////////////////////////

struct NodeTree* GetG(char* str) {
	str_expr = str;
	struct NodeTree* node = GetE();

	Require('$');

	return node;
}


struct NodeTree* GetN() {
	double value = 0;
	int didnt_find_num = 1;
	while ('0' <= *str_expr && *str_expr <= '9') {
		value = value * 10 + *str_expr - '0';
		str_expr++;
		didnt_find_num = 0;
	}

	if (didnt_find_num) SyntaxError();

	struct NodeTree* node = CreateNode(NUMBER, (TYPE_TREE) value, NULL, NULL);

	return node;
}

struct NodeTree* GetE() {
	struct NodeTree* node = GetT();

	while (*str_expr == '+' || *str_expr == '-') {
		int operation = *str_expr;
		str_expr++;

		struct NodeTree* node_right  = GetT();

		if (operation == '+')	node = CreateNode(OPERATION, ADD, node, node_right);
		else					node = CreateNode(OPERATION, SUB, node, node_right);
	}

	return node;
}

struct NodeTree* GetT() {
	struct NodeTree* node = GetD();

	while (*str_expr == '*' || *str_expr == '/') {
		int operation = *str_expr;
		str_expr++;

		struct NodeTree* node_right = GetD();

		if (operation == '*')	node = CreateNode(OPERATION, MUL, node, node_right);
		else					node = CreateNode(OPERATION, DIV, node, node_right);
	}

	return node;
}

struct NodeTree* GetP() {
	if (*str_expr == '(') {
		str_expr++;
		struct NodeTree* node = GetE();

		Require(')');

		return node;
	}
	else if ('0' <= *str_expr && *str_expr <= '9')
		return GetN();
	else if ('A' <= *str_expr && *str_expr <= 'Z' && 'A' <= *(str_expr + 1) && *(str_expr + 1) <= 'Z')
		return GetF();
	else
		return GetV();
}

struct NodeTree* GetV() {
	printf("111\n");
	int value = *str_expr;
	str_expr++;

	variables[value].name = value;

	struct NodeTree* node = CreateNode(VARIABLE, (TYPE_TREE) value, NULL, NULL);

	return node;
}


struct NodeTree* GetD() {
	struct NodeTree* node = GetF();

	while (*str_expr == '^') {
		str_expr++;

		struct NodeTree* node_right = GetF();

		node = CreateNode(OPERATION, POW, node, node_right);
	}

	return node;
}

struct NodeTree* GetF() {
	struct NodeTree* node = (struct NodeTree*) calloc(1, sizeof(node[0]));

	if ('A' <= *str_expr && *str_expr <= 'Z' && 'A' <= *(str_expr + 1) && *(str_expr + 1) <= 'Z') {
		char data[10] = "";
		int i = 0;

		while ('A' <= *str_expr && *str_expr <= 'Z')
			data[i++] = *str_expr++;

		struct NodeTree* node_right = GetP();

		#define DEF_FUNC(name, num, tex, code)									\
			if (strcmp(data, #name) == 0) {										\
				node->type_data = FUNCTION;										\
				node->data = (TYPE_TREE) num;									\
				node = CreateNode(FUNCTION, (TYPE_TREE) num, NULL, node_right); \
			}

		#include "../Data/functions.h"

		#undef DEF_FUNC

		printf("%s\n", data);
	}
	else
		node = GetP();
	
	return node;
}

void Require(char symb) {
	if (*str_expr == symb) str_expr++;
	else SyntaxError();
}


void SyntaxError() {
	// print error number
	printf("ERROR : %s\n", str_expr);
}
