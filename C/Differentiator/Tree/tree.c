#include "tree.h"


struct NodeTree* TreeConstruct(struct Tree* tree, TYPE_TREE value_root) {
	struct NodeTree* new_node = (struct NodeTree*) calloc(1, sizeof(new_node[0]));
	
	new_node->data = value_root;
	new_node->left = 0;
	new_node->right = 0;

	tree->root = new_node;
	tree->size = 1;

	return new_node;
}


struct NodeTree* AddLeft(struct Tree* tree, TYPE_TREE value, struct NodeTree* node) {
	struct NodeTree* new_node = (struct NodeTree*) calloc(1, sizeof(new_node[0]));
	
	Emit(new_node, value, node);

	node->left = new_node;
	tree->size++;

	return new_node;
}


struct NodeTree* AddRight(struct Tree* tree, TYPE_TREE value, struct NodeTree* node) {
	struct NodeTree* new_node = (struct NodeTree*) calloc(1, sizeof(new_node[0]));
	
	Emit(new_node, value, node);

	node->right = new_node;
	tree->size++;

	return new_node;
}


void Emit(struct NodeTree* node, TYPE_TREE value, struct NodeTree* parent) {
	node->data = value;
	node->parent = parent;
	node->left = 0;
	node->right = 0;
}


void PreorderWrite(struct NodeTree* node) {
	if (!node) return;

	printf("(");
	printf(OUTPUT_FORMAT_TREE, node->data);

	PreorderWrite(node->left);
	PreorderWrite(node->right);

	printf(")");

	return;
}

void InorderWrite(struct NodeTree* node) {
	if (!node) return;

	printf("(");

	InorderWrite(node->left);

	printf(OUTPUT_FORMAT_TREE, node->data);

	InorderWrite(node->right);

	printf(")");

	return;
}


void GraphDump(struct NodeTree* node) {
	FILE* graph_file = fopen("Data/graph.gv", "w");

	fprintf(graph_file, "digraph Tree {\n    ");
	GraphDumpTree(node, graph_file);
	fprintf(graph_file, "}\n");
	
	fclose(graph_file);

	system("dot -T png Data/graph.gv -o Data/image.png");

	return;
}


void GraphDumpTree(struct NodeTree* node, FILE* graph_file) {
	if (!node)
		return;
	char* color = "chartreuse";
	if (!node->left && !node->right) {
		color = "lightskyblue";
	}

	fprintf(graph_file, "    box%p [shape=\"record\", fillcolor = %s, style = filled, label = \"{<data>"OUTPUT_FORMAT_TREE"|{<left> %p|<right> %p}}\"];\n", node, color, node->data, node->left, node->right);

	if (node->left && node->right) {
		fprintf(graph_file, "	box%p:left -> box%p [label = yes];\n", node, node->left);
		fprintf(graph_file, "	box%p:right -> box%p [label = no];\n", node, node->right);
	}
		

	GraphDumpTree(node->left, graph_file);
	GraphDumpTree(node->right, graph_file);

	return;
}
