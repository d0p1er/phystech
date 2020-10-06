#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

struct stack{
	double can_1;
	double* data;
	double poison;
	int size;
	int capacity;
	double can_2;
};

enum errors{
	NO_ERRORS = 0,
	INCORRECT_CAPASITY = 1,
	UNABLE_ALLOCATE_MEMORY = 2,
	NULL_POINTER = 3, 
	STACK_OVERFLOW = 4,
	STACK_EMPTY = 5,
	INDEX_OUT_OF_RANGE = 6,
	INVASION = 7
};


const char* path_logs = "Data/logs.txt";

void StackConstruct(struct stack* thou, int capacity);
void StackPush(struct stack* thou, double value);
double StackPop(struct stack* thou);
void StackDestruct(struct stack* thou);
void StackDelete(struct stack* thou);
int StackError(struct stack* thou);

void Dump(struct stack* thou, int error, int line);
void PrintErrorLogs(char* error, int line);
void PrintStackLogs(struct stack* thou);
char* TimeNow();

int main(){
	struct stack stk = {};

	// Dump(&stk, NO_ERRORS, __LINE__);

	// printf("0x%X\n", stk);
	StackConstruct(&stk, 2);
	printf("construct\n");

	printf("%lf\n", stk.data[-1]);

	// printf("%d\n", &(stk.can_1));
	// printf("%d\n", &(stk.poison));
	// printf("%d\n", &(stk.size));
	// printf("%d\n", &(stk.capacity));
	// printf("%d\n", &(stk.can_2));

	for (size_t i = 0; i < 35; i++){
		StackPush(&stk, 10*i);
	}

	for (size_t i = 0; i < 25; i++){
		StackPop(&stk);
	}

	// stk.size = 10;

	StackPush(&stk, 300);

	printf("push\n");

	// stk.can_1 = 10;

	Dump(&stk, NO_ERRORS, __LINE__);

	StackDestruct(&stk);

	Dump(&stk, NO_ERRORS, __LINE__);

	return 0;

}


void StackConstruct(struct stack* thou, int capacity){	
	if (capacity < 1)
		Dump(thou, INCORRECT_CAPASITY, __LINE__);

	thou->data = (double*) calloc(capacity + 2, sizeof(thou->data[0]));
	
	if (thou->data == NULL)
		Dump(thou, UNABLE_ALLOCATE_MEMORY, __LINE__);


	thou->poison = NAN;
	thou->size = 0;
	thou->capacity = capacity;


	thou->data[0] = thou->poison;
	thou->data[capacity + 1] = thou->poison;
	thou->data += 1;

	thou->can_1 = thou->poison;
	thou->can_2 = thou->poison;

	for (size_t i = 0; i < capacity; i++){
		thou->data[i] = thou->poison;
	}
}


void StackPush(struct stack* thou, double value){
	int error = StackError(thou);
	if (error)
		Dump(thou, error, __LINE__);

	Dump(thou, NO_ERRORS, __LINE__);

	if (thou->size == thou->capacity){
		thou->data -= 1;
		thou->capacity *= 2;
		thou->data = (double*) realloc(thou->data, (thou->capacity + 2)*sizeof(thou->data));

		if (thou->data == NULL)
			Dump(thou, UNABLE_ALLOCATE_MEMORY, __LINE__);

		thou->data[0] = thou->poison;
		thou->data[thou->capacity + 1] = thou->poison;
		thou->data += 1;

		for (size_t i = thou->size; i < thou->capacity; i++)
			thou->data[i] = thou->poison;
	}
	
	thou->data[thou->size] = value;
	thou->size++;
}


double StackPop(struct stack* thou){
	int error = StackError(thou);
	if (error)
		Dump(thou, error, __LINE__);

	if (thou->size == 0)
		Dump(thou, STACK_EMPTY, __LINE__);

	Dump(thou, NO_ERRORS, __LINE__);

	thou->size--;
	double value = thou->data[thou->size];
	thou->data[thou->size] = thou->poison;

	if (thou->size < thou->capacity/4){
		thou->data -= 1;
		thou->capacity /= 2;
		thou->data = (double*) realloc(thou->data, (thou->capacity + 2)*sizeof(thou->data));
		
		if (thou->data == NULL)
			Dump(thou, UNABLE_ALLOCATE_MEMORY, __LINE__);

		thou->data[0] = thou->poison;
		thou->data[thou->capacity + 1] = thou->poison;
		thou->data += 1;
	}

	return value;
}


void StackDestruct(struct stack* thou){
	int error = StackError(thou);
	if (error)
		Dump(thou, error, __LINE__);

	thou->data -= 1;

	free(thou->data);

	StackConstruct(thou, 1);
}


void StackDelete(struct stack* thou){
	int error = StackError(thou);
	if (error)
		Dump(thou, error, __LINE__);

	free(thou);
}


int StackError(struct stack* thou){
	if (thou == NULL)
		return NULL_POINTER;

	if (!isnan(thou->can_1) || !isnan(thou->can_1) || !isnan(thou->data[-1]) || !isnan(thou->data[thou->capacity]))		// только для double
		return INVASION;

	if (thou->size < 0 || thou->capacity < 0)
		return INDEX_OUT_OF_RANGE;

	if (thou->size > thou->capacity)
		return STACK_OVERFLOW;


	return NO_ERRORS;
}


void Dump(struct stack* thou, int error, int line){
	if (!error)
		error = StackError(thou);

	switch (error){
		case NO_ERRORS:					PrintErrorLogs("Stack (ok)", line);						PrintStackLogs(thou);	break;
		case INCORRECT_CAPASITY:		PrintErrorLogs("Stack (INCORRECT CAPASITY)", line);								exit(INCORRECT_CAPASITY);
		case UNABLE_ALLOCATE_MEMORY:	PrintErrorLogs("Stack (UNABLE ALLOCATE MEMORY)", line);							exit(UNABLE_ALLOCATE_MEMORY);
		case NULL_POINTER:				PrintErrorLogs("Stack (NULL POINTER)", line);									exit(NULL_POINTER);
		case STACK_OVERFLOW:			PrintErrorLogs("Stack (STACK OVERFLOW)", line);			PrintStackLogs(thou);	exit(STACK_OVERFLOW);
		case INDEX_OUT_OF_RANGE:		PrintErrorLogs("Stack (INDEX OUT OF RANGE)", line);								exit(INDEX_OUT_OF_RANGE);
		case INVASION:					PrintErrorLogs("Stack (INVASION)", line);				PrintStackLogs(thou);	exit(INVASION);
	}
}


void PrintErrorLogs(char* error, int line){
	if(error != "Stack (ok)")
		printf("ERROR\n");

	FILE* logs_file = fopen(path_logs, "a");

	char* timeNow = TimeNow();

	fprintf(logs_file, "\n##########################################################################################\n");
	fprintf(logs_file, "[%s]\n%s on line %d\n", timeNow, error, line);

	fclose(logs_file);
}


void PrintStackLogs(struct stack* thou){
	FILE* logs_file = fopen(path_logs, "a");

	fprintf(logs_file, "\n[0x%X] {\n", thou);
	fprintf(logs_file, "	size = %d\n", thou->size);
	fprintf(logs_file, "	capacity = %d\n", thou->capacity);
	fprintf(logs_file, "	data [0x%X] = {\n", thou->data);

	if (thou->capacity > 0){
		for (size_t i = 0; i < thou->capacity; i++){
			// if (thou->data[i] != thou->poison)	// если poison != NAN
			if (!isnan(thou->data[i]))				// только для double
				fprintf(logs_file, "		*[%ld] = %lf\n", i, thou->data[i]);
			else
				fprintf(logs_file, "		 [%ld] = %lf\n", i, thou->data[i]);
		}
	}

	fprintf(logs_file, "	}\n}\n");

	fclose(logs_file);
}


char* TimeNow(){
	char* s = (char*) calloc(20, sizeof(s[0]));

	time_t t = time(NULL);
	struct tm* tt = localtime(&t);

	strftime(s, 20, "%d.%m.%Y %H:%M:%S ", tt);

	return s;
}