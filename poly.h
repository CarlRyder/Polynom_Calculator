#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdint.h>

#define YYSTYPE uint64_t

extern FILE *yyin;

typedef struct polyElement {
    char variable;
    int coeff;
    int degree;
    struct polyElement* next;
} polyElement;

polyElement* create(char variable, int coeff, int degree);

polyElement* mult(polyElement* elem1, polyElement* elem2);
polyElement* polydegree(polyElement* elem, polyElement* degree);
polyElement* degree(polyElement* elem, int degree);
void summary(polyElement* elem1, polyElement* elem2);
void diff(polyElement* elem1, polyElement* elem2);
void mult_coeff(polyElement* elem, int coeff);
int calc_degree(int value, int deg);

void polysort(polyElement* poly);
void print(polyElement* poly);

void error_msg(char* errorMsg, int flag);