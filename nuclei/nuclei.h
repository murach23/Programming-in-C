#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <ctype.h>

#define TOKEN_LENGTH 170
#define MAX_TOKENS 190
#define MAX_TOKEN_SIZE 90

#define ERROR(PHRASE) {fprintf(stderr, \
"Fatal Error %s occurredin %s , line %d\n ", PHRASE, \
__FILE__, __LINE__ ); \
exit (EXIT_FAILURE );}

char str[1000] = ""; // Initialize an empty string

int test_variable = 0;
int numVariables;
int car_var = 1;

struct variable {
  char * name;
  int value;
}
variables[100];

struct Program {
  char tokens[MAX_TOKENS][MAX_TOKEN_SIZE];
  int current_token;
};

void PRINTINTERP(struct Program *p);
void test1();
void print_program(struct Program *p);
void Prog(struct Program *p);
void INSTRCTS(struct Program *p);
void INSTRCT(struct Program *p);
void FUNC(struct Program *p);
void RETFUNC(struct Program *p);
void LISTFUNC(struct Program *p);
void INTFUNC(struct Program *p);
void BOOLFUNC(struct Program *p);
void IOFUNC(struct Program *p);
void SET(struct Program *p);
void PRINT(struct Program *p);
void IF(struct Program * p);
void LOOP(struct Program *p);
void LIST(struct Program *p);
void VAR(struct Program *p);
void STRING(struct Program *p);
void LITERAL(struct Program *p);
