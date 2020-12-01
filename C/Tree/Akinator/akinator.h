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
void MainMenu(struct Node* node, char* path);
int ContinuePlaying();

int Guessing(struct Node* node);
void AddObject(struct Node* node, char* dif, char* correct, char* wrong);
void UpdateDataBase(struct Node* node, char* path);

void BuildingDefinition(struct Node* node);
int ObjectDefinition(struct Node* node, struct List* list, DATA_TYPE value);
void Comparison(struct Node* node);
void PrintDef(struct List* list, int pos);