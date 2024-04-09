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
polyElement* polydegree(polyElement* elem, polyElement* degree);
polyElement* degree(polyElement* elem, int degree);
void summary(polyElement* elem1, polyElement* elem2);
void diff(polyElement* elem1, polyElement* elem2);
void mult_coeff(polyElement* elem, int coeff);
int calc_degree(int value, int deg);

void polysort(polyElement* poly);
void print(polyElement* poly);