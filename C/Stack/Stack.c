#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct stack{
	double* data;
	int size;
	int capacity;
};

void StackConstruct(struct stack* thou, int capacity);
void StackPush(struct stack* thou, double value);
double StackPop(struct stack* thou);
void StackDelete(struct stack* thou);

int main(){
	struct stack Stk = {};

	StackConstruct(&Stk, 10);

	StackPush(&Stk, 100);
	StackPush(&Stk, 200);
}

void StackConstruct(struct stack* thou, int capacity){
	assert(thou);

	thou->data = (double*) calloc(capacity, sizeof(double*));
}

void StackPush(struct stack* thou, double value){
	assert(thou);

	if(thou->size < thou->capacity){
		thou->data[thou->size] = value;
		thou->size++;
	}
	else{
		thou->data = (double*) realloc(thou->data, (thou->capacity)*2*sizeof(double*));
	}
	
}

double StackPop(struct stack* thou){
	assert(thou);

	return thou->data[--thou->size];
}

void StackDelete(struct stack* thou){
	free(thou->data);
	
	thou->size = 0;
	thou->capacity = 0;
}