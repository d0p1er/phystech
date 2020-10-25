#include "Stack.h"

const char* path_logs = "logs.txt";
const type poison = 0xDEADBEEF;

void StackConstruct(struct Stack* thou){
	thou->capacity = 1;
	thou->data = (type*) calloc(thou->capacity + 3, sizeof(thou->data[0]));
	
	if (thou->data == NULL)
		Dump(thou, NULL_DATA, __FUNCTION__, __LINE__);

	thou->size = 0;

	thou->data[0] = poison;
	thou->data[1] = 0;
	thou->data[3] = poison;
	thou->data += 1;

	thou->can_1 = poison;
	thou->can_2 = poison;

	thou->hash_sum = CountHash((char*) thou, sizeof(thou->can_1), sizeof(*thou) - sizeof(thou->can_2) - sizeof(thou->hash_sum));
	thou->data[thou->capacity] = CountHash((char*) thou->data, sizeof(thou->data[0]), sizeof(thou->data[0])*(thou->capacity));

	Dump(thou, NO_ERRORS, __FUNCTION__, __LINE__);

	int error = StackError(thou);
	if (error)
		Dump(thou, error, __FUNCTION__, __LINE__);
}


void StackPush(struct Stack* thou, type value){
	int error = StackError(thou);
	if (error)
		Dump(thou, error, __FUNCTION__, __LINE__);

	if (thou->size == thou->capacity)
		ResizeUp(thou);
	
	thou->data[thou->size] = value;
	thou->size++;

	thou->hash_sum = CountHash((char*) thou, sizeof(thou->can_1), sizeof(*thou) - sizeof(thou->can_2) - sizeof(thou->hash_sum));
	thou->data[thou->capacity] = CountHash((char*) thou->data, sizeof(thou->data[0]), sizeof(thou->data[0])*(thou->capacity));

	error = StackError(thou);
	if (error)
		Dump(thou, error, __FUNCTION__, __LINE__);
}


void ResizeUp(struct Stack* thou){
	thou->data -= 1;
	thou->capacity *= 2;
	thou->data = (type*) realloc(thou->data, (thou->capacity + 3)*sizeof(thou->data[0]));

	if (thou->data == NULL)
		Dump(thou, NULL_DATA, __FUNCTION__, __LINE__);

	thou->data[0] = poison;
	thou->data[thou->capacity + 2] = poison;
	thou->data += 1;

	for (size_t i = thou->size; i < thou->capacity; i++)
		thou->data[i] = 0;
}
	

type StackPop(struct Stack* thou){
	int error = StackError(thou);
	if (error)
		Dump(thou, error, __FUNCTION__, __LINE__);

	if (thou->size == 0)
		Dump(thou, Stack_EMPTY, __FUNCTION__, __LINE__);

	thou->size--;
	type value = thou->data[thou->size];
	thou->data[thou->size] = poison;

	if (thou->size < thou->capacity / 4)
		ResizeDown(thou);

	thou->hash_sum = CountHash((char*) thou, sizeof(thou->can_1), sizeof(*thou) - sizeof(thou->can_2) - sizeof(thou->hash_sum));
	thou->data[thou->capacity] = CountHash((char*) thou->data, sizeof(thou->data[0]), sizeof(thou->data[0])*(thou->capacity));

	error = StackError(thou);
	if (error)
		Dump(thou, error, __FUNCTION__, __LINE__);

	return value;
}

void ResizeDown(struct Stack* thou){
	thou->data -= 1;
	thou->capacity /= 2;
	thou->data = (type*) realloc(thou->data, (thou->capacity + 3)*sizeof(thou->data));
	
	if (thou->data == NULL)
		Dump(thou, NULL_DATA, __FUNCTION__, __LINE__);

	thou->data[0] = poison;
	thou->data[thou->capacity + 2] = poison;
	thou->data += 1;

	for (size_t i = thou->size; i < thou->capacity; i++)
		thou->data[i] = 0;
}


void StackDestruct(struct Stack* thou){
	int error = StackError(thou);
	if (error)
		Dump(thou, error, __FUNCTION__, __LINE__);


	thou->capacity = 0;
	thou->size = 0;
	thou->data -= 1;
	free(thou->data);

	StackConstruct(thou);
}

// to do разделить на invasion
int StackError(struct Stack* thou){
	if (thou == NULL)
		return NULL_POINTER;

	if (thou->can_1 != poison || thou->can_2 != poison || thou->data[-1] != poison || thou->data[thou->capacity + 1] != poison)
		return INVASION;

	if (thou->can_2 != poison)


	if (thou->size < 0 || thou->capacity < 0)
		return INDEX_OUT_OF_RANGE;

	if (thou->size > thou->capacity)
		return Stack_OVERFLOW;

	if (thou->hash_sum != CountHash((char*) thou, sizeof(thou->can_1), sizeof(*thou) - sizeof(thou->can_2) - sizeof(thou->hash_sum)) || 
		thou->data[thou->capacity] != CountHash((char*) thou->data, sizeof(thou->data[0]), sizeof(thou->data[0])*(thou->capacity)))
		return BAD_HASH;

	return NO_ERRORS;
}


unsigned long long CountHash(char* str, const size_t i_start, const size_t i_end){
	int hash_sum = 0;
	
	for (size_t i = i_start; i < i_end; i++) {
		hash_sum += (unsigned long long) *(str + i);
		hash_sum = RollHash(hash_sum);
	}

	return hash_sum;
}


unsigned long long RollHash(unsigned long long hash_sum){
	return (hash_sum << 1);
}

// делать экзит из функции где вызывался дамп
void Dump(struct Stack* thou, int error, const char* func, const int line){
	if (!error)
		error = StackError(thou);

	switch (error){
		case NO_ERRORS:				PrintErrorLogs("(ok)", func, line, NO_ERRORS);							PrintStackLogs(thou);	break;
		case INCORRECT_CAPASITY:	PrintErrorLogs("(INCORRECT CAPASITY)", func, line, INCORRECT_CAPASITY);							exit(INCORRECT_CAPASITY);
		case NULL_DATA:				PrintErrorLogs("(NULL DATA)", func, line, NULL_DATA);											exit(NULL_DATA);
		case NULL_POINTER:			PrintErrorLogs("(NULL POINTER)", func, line, NULL_POINTER);										exit(NULL_POINTER);
		case Stack_OVERFLOW:		PrintErrorLogs("(Stack OVERFLOW)", func, line, Stack_OVERFLOW);			PrintStackLogs(thou);	exit(Stack_OVERFLOW);
		case INDEX_OUT_OF_RANGE:	PrintErrorLogs("(INDEX OUT OF RANGE)", func, line, INDEX_OUT_OF_RANGE);							exit(INDEX_OUT_OF_RANGE);
		case INVASION:				PrintErrorLogs("(INVASION)", func, line, INVASION);						PrintStackLogs(thou);	exit(INVASION);
		case BAD_HASH:				PrintErrorLogs("(BAD HASH)", func, line, BAD_HASH);						PrintStackLogs(thou);	exit(BAD_HASH);
		default:					PrintErrorLogs("(UNKNOWN ERROR)", func, line, error);											exit(error);
	}
}


void PrintErrorLogs(const char* error, const char* func, const int line, const int error_number){
	if(error != "(ok)")
		printf("ERROR[%d] %s CHECK LOGS\n", error_number, error);

	FILE* logs_file = fopen(path_logs, "a");

	char* timeNow = TimeNow();

	fprintf(logs_file, "\n##########################################################################################\n");
	fprintf(logs_file, "[%s]\nStack [%d] %s in %s on line %d\n", timeNow, error_number, error, func, line);

	fclose(logs_file);
}


void PrintStackLogs(struct Stack* thou){
	FILE* logs_file = fopen(path_logs, "a");

	fprintf(logs_file, "\n[0x%X] {\n", thou);
	fprintf(logs_file, "	can_1 = %lld\n", thou->can_1);
	fprintf(logs_file, "	can_2 = %lld\n", thou->can_2);
	fprintf(logs_file, "	hash_sum = %lld\n", thou->hash_sum);
	fprintf(logs_file, "	size = %ld\n", thou->size);
	fprintf(logs_file, "	capacity = %ld\n", thou->capacity);
	fprintf(logs_file, "	data [0x%X] = {\n", thou->data);

	if (thou->capacity > 0){
		for (size_t i = 0; i < thou->capacity; i++){
			if (thou->data[i] != poison)	// если poison != NAN
			// if (!isnan(thou->data[i]))				// только для double
				fprintf(logs_file, "		*[%ld] = "OUTPUT_FORMAT"\n", i, thou->data[i]);
			else
				fprintf(logs_file, "		 [%ld] = "OUTPUT_FORMAT"\n", i, thou->data[i]);
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