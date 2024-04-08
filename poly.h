#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdint.h>
#define YYSTYPE uint64_t

typedef struct polyElement {
    int coeff;
    int degree;
    struct polyElement* next;
} polyElement;

polyElement* create(int coeff, int degree);

polyElement* mult(polyElement* elem1, polyElement* elem2);
void summary(polyElement* elem1, polyElement* elem2);
void diff(polyElement* elem1, polyElement* elem2);
void mult_coeff(polyElement* elem, int coeff);
void degree(polyElement* elem, int degree);
void polydegree(polyElement* elem, polyElement* degree);
int calc_degree(int value, int deg);

void print(polyElement* poly);