#include "Tree/tree.h"
#include "Differ/differ.h"

int main() {
	struct Tree tree = {};
	TreeConstruct(&tree, NAN);

	struct Variable* variables = (struct Variable*) calloc(10, sizeof(variables[0]));

	ReadMathExpression(tree.root, "Data/expr.txt");

	// printf("%lf\n", Eval(tree.root, variables));


	return 0;
}