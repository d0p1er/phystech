#include "calc.h"

char* str_expr = NULL;

double GetG(char* str) {
	str_expr = str;
	double value = GetE();

	Require('$');

	return value;
}


double GetN() {
	double value = 0;
	int didnt_find_num = 1;
	while ('0' <= *str_expr && *str_expr <= '9') {
		value = value * 10 + *str_expr - '0';
		str_expr++;
		didnt_find_num = 0;
	}

	if (didnt_find_num) SyntaxError();

	return value;
}


double GetE() {
	double value = GetT();

	while (*str_expr == '+' || *str_expr == '-') {
		int operation = *str_expr;
		str_expr++;

		double next_value = GetT();

		if (operation == '+')	value += next_value;
		else					value -= next_value;
	}

	return value;
}


double GetT() {
	double value = GetD();

	while (*str_expr == '*' || *str_expr == '/') {
		int operation = *str_expr;
		str_expr++;

		double next_value = GetD();

		if (operation == '*')	value *= next_value;
		else					value /= next_value;
	}

	return value;
}


double GetP() {
	if (*str_expr == '(') {
		str_expr++;
		double value = GetE();

		Require(')');

		return value;
	}
	else
		return GetN();
}


double GetD() {
	double value = GetP();

	while (*str_expr == '^') {
		str_expr++;

		double next_value = GetP();

		value = pow(value, next_value);
	}

	return value;
}

void Require(char symb) {
	if (*str_expr == symb) str_expr++;
	else SyntaxError();
}


void SyntaxError() {
	// print error number
	printf("ERROR : %s\n", str_expr);
}