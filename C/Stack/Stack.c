#include "Stack.h"

const char* path_logs = "Data/logs.txt";

void StackConstruct(struct stack* thou, int capacity){	
	if (capacity < 1)
		Dump(thou, INCORRECT_CAPASITY, __FUNCTION__, __LINE__);

	thou->data = (double*) calloc(capacity + 3, sizeof(thou->data[0]));
	
	if (thou->data == NULL)
		Dump(thou, NULL_DATA, __FUNCTION__, __LINE__);


	thou->poison = NAN;
	thou->size = 0;
	thou->capacity = capacity;


	thou->data[0] = thou->poison;
	thou->data[capacity + 2] = thou->poison;
	thou->data += 1;

	thou->can_1 = thou->poison;
	thou->can_2 = thou->poison;

	for (size_t i = 0; i < capacity; i++){
		thou->data[i] = thou->poison;
	}

	thou->hash = CountHashStack(thou);
	thou->data[thou->capacity] = CountHashData(thou);
}


void StackPush(struct stack* thou, double value){
	int error = StackError(thou);
	if (error)
		Dump(thou, error, __FUNCTION__, __LINE__);

	printf("1\n");

	Dump(thou, NO_ERRORS, __FUNCTION__, __LINE__);

	if (thou->size == thou->capacity){
		thou->data -= 1;
		thou->capacity *= 2;
		thou->data = (double*) realloc(thou->data, (thou->capacity + 3)*sizeof(thou->data));

		if (thou->data == NULL)
			Dump(thou, NULL_DATA, __FUNCTION__, __LINE__);

		thou->data[0] = thou->poison;
		thou->data[thou->capacity + 2] = thou->poison;
		thou->data += 1;

		for (size_t i = thou->size; i < thou->capacity; i++)
			thou->data[i] = thou->poison;
	}
	
	thou->data[thou->size] = value;
	thou->size++;

	thou->hash = CountHashStack(thou);
	thou->data[thou->capacity] = CountHashData(thou);
}


double StackPop(struct stack* thou){
	int error = StackError(thou);
	if (error)
		Dump(thou, error, __FUNCTION__, __LINE__);

	if (thou->size == 0)
		Dump(thou, STACK_EMPTY, __FUNCTION__, __LINE__);

	Dump(thou, NO_ERRORS, __FUNCTION__, __LINE__);

	thou->size--;
	double value = thou->data[thou->size];
	thou->data[thou->size] = thou->poison;

	if (thou->size < thou->capacity/4){
		thou->data -= 1;
		thou->capacity /= 2;
		thou->data = (double*) realloc(thou->data, (thou->capacity + 3)*sizeof(thou->data));
		
		if (thou->data == NULL)
			Dump(thou, NULL_DATA, __FUNCTION__, __LINE__);

		thou->data[0] = thou->poison;
		thou->data[thou->capacity + 2] = thou->poison;
		thou->data += 1;
	}

	thou->hash = CountHashStack(thou);
	thou->data[thou->capacity] = CountHashData(thou);

	return value;
}


void StackDestruct(struct stack* thou){
	int error = StackError(thou);
	if (error)
		Dump(thou, error, __FUNCTION__, __LINE__);

	// free(thou->data);

	thou->size = 0;
	thou->capacity = 1;
	thou->hash = CountHashStack(thou);

	StackConstruct(thou, 1);
}


void StackDelete(struct stack* thou){
	int error = StackError(thou);
	if (error)
		Dump(thou, error, __FUNCTION__, __LINE__);

	free(thou);
}


int StackError(struct stack* thou){
	if (thou == NULL)
		return NULL_POINTER;

	if (thou->data == NULL)
		return NULL_DATA;

	// if(thou->can_1 != thou->poison || thou->can_1 != thou->poison || thou->data[-1] != thou->poison || thou->data[thou->capacity] != thou->poison)	// при poison != NAN
	if (!isnan(thou->can_1) || !isnan(thou->can_1) || !isnan(thou->data[thou->capacity + 1]) || !isnan(thou->data[-1]))						// только для double
		return INVASION;

	if (thou->size < 0 || thou->capacity < 0)
		return INDEX_OUT_OF_RANGE;

	if (thou->size > thou->capacity)
		return STACK_OVERFLOW;

	if (thou->hash != CountHashStack(thou) || thou->data[thou->capacity] != CountHashData(thou))
		return BAD_HASH;


	return NO_ERRORS;
}


size_t CountHashStack(struct stack* thou){
	int hash = 0;
	size_t i_end = sizeof(*thou) - sizeof(thou->can_2) - sizeof(thou->hash);

	char* str = (char*) thou;
	
	for (size_t i = sizeof(thou->can_1); i < i_end; i++){
		hash += (int) *(str + i);
		hash = RollHash(hash);
	}

	return hash;
}

size_t CountHashData(struct stack* thou){
	int hash = 0;
	size_t i_end = sizeof(thou->data[0])*(thou->capacity);

	char* str = (char*) thou;
	
	for (size_t i = 0; i < i_end; i++){
		hash += (int) *(str + i);
		hash = RollHash(hash);
	}

	return hash;
}


size_t RollHash(int hash){
	return (hash << 1) | ((hash >> 31) & 1);
}


void Dump(struct stack* thou, int error, const char* func, int line){
	if (!error)
		error = StackError(thou);

	switch (error){
		case NO_ERRORS:				PrintErrorLogs("(ok)", func, line, NO_ERRORS);							PrintStackLogs(thou);	break;
		case INCORRECT_CAPASITY:	PrintErrorLogs("(INCORRECT CAPASITY)", func, line, INCORRECT_CAPASITY);							exit(INCORRECT_CAPASITY);
		case NULL_DATA:				PrintErrorLogs("(UNABLE ALLOCATE MEMORY)", func, line, NULL_DATA);								exit(NULL_DATA);
		case NULL_POINTER:			PrintErrorLogs("(NULL POINTER)", func, line, NULL_POINTER);										exit(NULL_POINTER);
		case STACK_OVERFLOW:		PrintErrorLogs("(STACK OVERFLOW)", func, line, STACK_OVERFLOW);			PrintStackLogs(thou);	exit(STACK_OVERFLOW);
		case INDEX_OUT_OF_RANGE:	PrintErrorLogs("(INDEX OUT OF RANGE)", func, line, INDEX_OUT_OF_RANGE);							exit(INDEX_OUT_OF_RANGE);
		case INVASION:				PrintErrorLogs("(INVASION)", func, line, INVASION);						PrintStackLogs(thou);	exit(INVASION);
		case BAD_HASH:				PrintErrorLogs("(BAD HASH)", func, line, BAD_HASH);						PrintStackLogs(thou);	exit(BAD_HASH);
	}
}


void PrintErrorLogs(char* error, const char* func, int line, int error_number){
	if(error != "Stack (ok)")
		printf("ERROR[%d] %s CHECK LOGS\n", error_number, error);

	FILE* logs_file = fopen(path_logs, "a");

	char* timeNow = TimeNow();

	fprintf(logs_file, "\n##########################################################################################\n");
	fprintf(logs_file, "[%s]\nStack [%d] %s in %s on line %d\n", timeNow, error_number, error, func, line);

	fclose(logs_file);
}


void PrintStackLogs(struct stack* thou){
	FILE* logs_file = fopen(path_logs, "a");

	fprintf(logs_file, "\n[0x%X] {\n", thou);
	fprintf(logs_file, "	can_1 = %lf\n", thou->can_1);
	fprintf(logs_file, "	can_2 = %lf\n", thou->can_2);
	fprintf(logs_file, "	hash = %ld\n", thou->hash);
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