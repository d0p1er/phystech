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


void Preorder(struct NodeTree* node) {
	if (!node) return;

	printf("(");
	printf(OUTPUT_FORMAT_TREE, node->data);

	Preorder(node->left);
	Preorder(node->right);

	printf(")");

	return;
}


void WriteDataBase(FILE* file, struct NodeTree* node, size_t space_count) {
	if (!node) {
		space_count--;
		return;
	}

	PrintSpaces(file, space_count);
	fprintf(file, "[\n");
	space_count++;

	PrintSpaces(file, space_count);

	if (!node->left && !node->right)
		fprintf(file, "`"OUTPUT_FORMAT_TREE"`\n", node->data);
	else
		fprintf(file, "?"OUTPUT_FORMAT_TREE"?\n", node->data);

	WriteDataBase(file, node->left, space_count);
	WriteDataBase(file, node->right, space_count);

	space_count--;
	PrintSpaces(file, space_count);
	fprintf(file, "]\n");

	return;
}


void PrintSpaces(FILE* file, size_t space_count) {
	for (size_t i = 0; i < space_count; i++)
		fprintf(file, "    ");
}


void GraphDump(struct NodeTree* node) {
	FILE* graph_file = fopen("Data/graph.gv", "w");

	fprintf(graph_file, "digraph Tree {\n    ");
	GraphDumpTree(node, graph_file);
	fprintf(graph_file, "}\n");
	
	fclose(graph_file);

	system("dot -T png Data/graph.gv -o Data/tree.png");

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


struct Tree ReadTree(char* path) {
	size_t file_size = GetFileSize(path);
	char* text = GetTextFromFile(path, file_size);
	
	char* text_without_spaces = WithoutSpaces(text, file_size);
	char* start_tree = strchr(text_without_spaces, '[');
	
	struct Tree tree = {};
	struct NodeTree* root = (struct NodeTree*) calloc(1, sizeof(root[0]));
	
	tree.root = root;
	// root->parent = &tree;

	ReadNode(root, start_tree);

	return tree;
}

char* ReadNode(struct NodeTree* node, char* text) {
	if (*text == ']')
		return ++text;

	text++;

	if (*text == '?') {
		char* next_text = text + 1;
		next_text = strchr(next_text, '[');
		strtok(text, "?");

		node->data = ++text;

		struct NodeTree* node_left  = (struct NodeTree*) calloc(1, sizeof(node_left[0]));
		struct NodeTree* node_right = (struct NodeTree*) calloc(1, sizeof(node_right[0]));

		node_left->parent  = node;
		node_right->parent = node;

		node->left  = node_left;
		node->right = node_right;

		next_text = ReadNode(node_left, next_text);
		next_text = ReadNode(node_right, next_text);
		next_text++;

		return next_text;
	}
	else if (*text == '`') {
		char* data = (char*) calloc(100, sizeof(data[0]));
		text++;

		size_t counter = 0;
		while (*text != '`') {
			data[counter++] = *text++;
		}

		node->data = data;
		node->left  = 0;
		node->right = 0;

		text += 2;

		return text;
	}
}


char* WithoutSpaces(char* str, size_t lenght) {
	char* res = (char*) calloc(lenght, sizeof(res[0]));
	size_t counter = 0;
	int is_node = -1;

	while (*str) {
		if (*str == '`' || *str == '?')
			is_node *= -1;

		if (isspace(*str) && is_node == -1){
			str++;
			continue;
		}

		res[counter] = *str++;
		counter++;
	}
	res[counter] = '\0';

	return res;
}