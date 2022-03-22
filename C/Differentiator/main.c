#include "Tree/tree.h"
#include "Differ/differ.h"

int main() {
	struct Tree tree = {};
	TreeConstruct(&tree, NAN);

	tree.root = ReadMathExpression("Data/expr.txt");

	DBG GraphDump(tree.root, "Data/image1.png");

	FILE* file = fopen("Data/testlatex.tex", "w");

	PrintLatexStart(tree.root, &tree, file);
	struct NodeTree* old = tree.root;

	tree.root = Differentation(tree.root, &tree, file);

	PrintLatexEnd(old, tree.root, &tree, file);

	return 0;
}