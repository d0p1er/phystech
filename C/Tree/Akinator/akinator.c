#include "akinator.h"

// const int MAX_SIZE_ANS = 10;
// const int MAX_SIZE_DATA = 100;

void StartGame(char* path) {
	struct Tree tree_akin = ReadTree(path);

	printf("Saluton mi amiko\nI'm AKINATOR3000. I can guess any thing in the world.\nWhat do you want to do?\nPlease choose game mode:\n");
	MainMenu(tree_akin.root, path);
}

void MainMenu(struct Node* node, char* path) {
	int keep_going = 1;
	int mode = 0;
	int update = 0;
	
	while (keep_going) {
		printf("1 - guessing the object\n2 - building object definition\n3 - comparison of two objects\n4 - database view\n5 - exit the game\n");
		scanf("%d", &mode);

		switch (mode) {
			case GUESSING: update = Guessing(node); if (update) UpdateDataBase(node, path); keep_going = ContinuePlaying(); break;
			case BUILDING_DEFINITION: BuildingDefinition(node); keep_going = ContinuePlaying(); break;
			case COMPARISON: Comparison(node); keep_going = ContinuePlaying(); break;
			case DATABASE_VIEW: GraphDump(node); keep_going = ContinuePlaying(); break;
			case EXIT: printf("Bye! Thanks for playing!\n"); return;
			default: printf("INCORRECT INPUT, TRY AGAIN...\n"); break;
		}
	}	
}

int ContinuePlaying() {
	printf("\nDo you want to continue playing?\n");

	char ans[MAX_SIZE_ANS] = "";
	scanf("%s", ans);

	if (!strcmp(ans, "yes") || !strcmp(ans, "y"))
		return 1;
	else if (!strcmp(ans, "no") || !strcmp(ans, "n"))
		return 0;
	else {
		printf("Wrong input, try again...\n");
		ContinuePlaying();
	}
}

int Guessing(struct Node* node) {
	printf("%s?\n", node->data);
	
	char ans[MAX_SIZE_ANS] = "";
	scanf("%s", ans);
	if (!strcmp(ans, "yes") || !strcmp(ans, "y")) {
		if (node->left)
			return Guessing(node->left);
		else {
			printf("It is %s\n", node->data);
			return 0;
		}
	}
	else if (!strcmp(ans, "no") || !strcmp(ans, "n")) {
		if (node->right)
			return Guessing(node->right);
		else {
			printf("I dont know who is it\n");
			printf("Please input who is it:\n");
			
			char object[MAX_SIZE_DATA] = "";
			scanf("%s", object);

			printf("How does %s differ from %s\n", object, node->data);
			char dif[MAX_SIZE_DATA] = "";
			scanf("%s", dif);

			AddObject(node, dif, node->data, object);

			return 1;
		}
	}
	else {
		printf("Wrong input, try again...\n");
		return Guessing(node);
	}
}

void AddObject(struct Node* node, DATA_TYPE dif, DATA_TYPE correct, DATA_TYPE wrong) {
	node->data = dif;

	struct Node* node_left  = (struct Node*) calloc(1, sizeof(node_left[0]));
	struct Node* node_right = (struct Node*) calloc(1, sizeof(node_right[0]));

	node_left->data  = correct;
	node_right->data = wrong;

	node_left->parent  = node;
	node_right->parent = node;

	node->left  = node_left;
	node->right = node_right;
}


void UpdateDataBase(struct Node* node, char* path) {
	printf("Update database?\n");

	char ans[MAX_SIZE_ANS] = "";
	scanf("%s", ans);

	if (!strcmp(ans, "yes") || !strcmp(ans, "y")) {
		FILE* file = fopen(path, "w");

		WriteDataBase(file, node, 0);

		return;
	}
	else if (!strcmp(ans, "no") || !strcmp(ans, "n")) {
		printf("OK. As you want\n");
		return;
	}
	else {
		printf("Wrong input, try again...\n");
		UpdateDataBase(node, path);
	}
}

void BuildingDefinition(struct Node* node) {
	printf("Please enter the name of the object:\n");
	char object[MAX_SIZE_DATA] = "";
	scanf("%s", object);

	struct List list = ListConstruct();
	int ans = ObjectDefinition(node, &list, object);

	if (ans)
		printf("There is no such object in the database\n");
	else {
		printf("\n\n%s is:\n", object);
		int pos = list.tail;
		size_t size = list.size;

		for (size_t i = 0; i < size; i++) {
			PrintDef(&list, pos);
			pos = list.nodes[pos].prev;
		}
	}
}

// stack а не list

int ObjectDefinition(struct Node* node, struct List* list, DATA_TYPE value) {
	if (!node) return 1;

	int proceed = 1;

	if (!strcmp(node->data, value)) {
		proceed = 0;

		return proceed;
	}

	AddValueBefore(node->data, list);
	proceed = ObjectDefinition(node->left, list, value);
	
	if (proceed) {
		Delete(list->head, list);
		AddValueBefore("NO", list);
		AddValueBefore(node->data, list);
	}
	else
		return proceed;
	
	proceed = ObjectDefinition(node->right, list, value);

	if (proceed) {
		Delete(list->head, list);
		Delete(list->head, list);
	}
	else
		return proceed;

	return proceed;
}


void Comparison(struct Node* node) {
	int ans_1 = 1;
	char object_1[MAX_SIZE_DATA] = "";
	struct List list_1 = {};
	printf("Please enter the name of the first object:\n");
	while (ans_1) {
		scanf("%s", object_1);

		list_1 = ListConstruct();
		ans_1 = ObjectDefinition(node, &list_1, object_1);

		if (ans_1)
			printf("There is no such object in the database. Try again...\n");
	}

	int ans_2 = 1;
	char object_2[MAX_SIZE_DATA] = "";
	struct List list_2 = {};
	printf("Please enter the name of the second object:\n");
	while (ans_2) {
		scanf("%s", object_2);

		list_2 = ListConstruct();
		ans_2 = ObjectDefinition(node, &list_2, object_2);
		
		if (ans_2)
			printf("There is no such object in the database. Try again...\n");
	}
	
	int pos_1 = list_1.tail;
	int pos_2 = list_2.tail;
	int equal = 0;

	if (!strcmp(list_1.nodes[pos_1].value, list_2.nodes[pos_2].value)) {
		equal = 1;
		printf("\n%s and %s are both\n", object_1, object_2);
	}
	else {
		printf("\n%s and %s have nothing equal\n", object_1, object_2);
		
		printf("\n%s is\n", object_1);
		for (size_t j_1 = 0; j_1 < list_1.size; j_1++) {
			PrintDef(&list_1, pos_1);
			pos_1 = list_1.nodes[pos_1].prev;
		}

		printf("\nAnd %s is\n", object_2);
		for (size_t j_2 = 0; j_2 < list_2.size; j_2++) {
			PrintDef(&list_2, pos_2);
			pos_2 = list_2.nodes[pos_2].prev;
		}

		return;
	}

	for (size_t i = 0; i < list_1.size; i++) {
		if (!strcmp("NO", list_1.nodes[pos_1].value))
			printf(DATA_TYPE_PRT " ", list_1.nodes[pos_1].value);
		else
			printf(DATA_TYPE_PRT "\n", list_1.nodes[pos_1].value);

		pos_1 = list_1.nodes[pos_1].prev;
		pos_2 = list_2.nodes[pos_2].prev;

		if (equal && strcmp(list_1.nodes[pos_1].value, list_2.nodes[pos_2].value)) {
			equal = 0;
			printf("\nBut %s is\n", object_1);
			for (size_t j_1 = i + 1; j_1 < list_1.size; j_1++) {
				PrintDef(&list_1, pos_1);
				pos_1 = list_1.nodes[pos_1].prev;
			}

			printf("\nAnd %s is\n", object_2);
			for (size_t j_2 = i + 1; j_2 < list_2.size; j_2++) {
				PrintDef(&list_2, pos_2);
				pos_2 = list_2.nodes[pos_2].prev;
			}

			return;
		}
	}
}

void PrintDef(struct List* list, int pos) {
	if (!strcmp("NO", list->nodes[pos].value))
		printf(DATA_TYPE_PRT " ", list->nodes[pos].value);
	else
		printf(DATA_TYPE_PRT "\n", list->nodes[pos].value);
}