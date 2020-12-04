#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma once

// РБНФ
// G ::= E$
// E ::= T{[+-]T}*
// T ::= D{[*/]D}*
// P ::= (E) | N
// N ::= ['0'-'9']+
// D ::= P{[^]P}*

extern char* str_expr;

double GetG(char* str);
double GetN();
double GetE();
double GetT();
double GetP();
double GetD();
void Require(char symb);
void SyntaxError();
