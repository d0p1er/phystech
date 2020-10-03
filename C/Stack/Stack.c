#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

struct stack{
	double* data;
	size_t size;
	size_t capacity;
};

const char* path_logs = "Data/logs.txt";

void StackConstruct(struct stack* thou, size_t capacity);
void StackPush(struct stack* thou, double value);
double StackPop(struct stack* thou);
void StackDelete(struct stack* thou);
void PrintLogs(char* error);
char* TimeNow();

int main(){
	struct stack stk = {};

	StackConstruct(&stk, 2);

	StackPush(&stk, 100);
	StackPush(&stk, 200);
	StackPush(&stk, 300);
}

void StackConstruct(struct stack* thou, size_t capacity){
	assert(thou);

	thou->data = (double*) calloc(capacity, sizeof(thou->data[0]));
	if(thou->data == NULL){
		PrintLogs("[Error] Unable to allocate memory");
		exit(EXIT_FAILURE);
	}

	thou->size = 0;
	thou->capacity = capacity;

	for(size_t i = 0; i < capacity; i++){
		thou->data[i] = NAN;
	}
}

void StackPush(struct stack* thou, double value){
	assert(thou);

	if(thou->size >= thou->capacity){
		thou->data = (double*) realloc(thou->data, 2*(thou->capacity)*sizeof(double*));
		if(thou->data == NULL){
			PrintLogs("[Error] Unable to allocate memory");
			exit(EXIT_FAILURE);
		}
	}
	
	thou->data[thou->size] = value;
	thou->size++;
	
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

void PrintLogs(char* error){
	FILE* logs_file = fopen(path_logs, "a");

	char* timeNow = TimeNow();

	fprintf(logs_file, "[%s]\n%s\n", timeNow, error);

	fclose(logs_file);
}

char* TimeNow(){
	char* s = (char*) calloc(20, sizeof(s[0]));

	time_t t = time(NULL);
	struct tm* tt = localtime(&t);

	strftime(s, 20, "%d.%m.%Y %H:%M:%S ", tt);
	
	return s;
}