#include "../Tree/tree.h"
// #include "../Stack/Stack.h"
#include "../List/list.h"


#define MAX_SIZE_ANS 10
#define MAX_SIZE_DATA 100

enum Modes {
	GUESSING = 1,
	BUILDING_DEFINITION = 2,
	COMPARISON = 3,
	DATABASE_VIEW = 4,
	EXIT = 5
};

void StartGame(char* path);
void MainMenu(struct NodeTree* node, char* path);
int ContinuePlaying();

int Guessing(struct NodeTree* node);
void AddObject(struct NodeTree* node, char* dif, char* correct, char* wrong);
void UpdateDataBase(struct NodeTree* node, char* path);

void BuildingDefinition(struct NodeTree* node);
int ObjectDefinition(struct NodeTree* node, struct List* list, TYPE_TREE value);
void Comparison(struct NodeTree* node);
void PrintDef(struct List* list, int pos);