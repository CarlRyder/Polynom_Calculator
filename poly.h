#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define YYSTYPE uint64_t
#define VARCOUNTS 26

typedef struct polyElement {
    char variable;
    int coeff;
    int degree;
    struct polyElement* next;
} polyElement;

typedef struct polyVariable {
    char varnames[VARCOUNTS];
    polyElement polynoms[VARCOUNTS];
} polyVariable;

void init_structs();

void set_polynom(char varname, polyElement* polynom);
polyElement* search_polynom(char varname);

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
void print_var(char varname);

void error_msg(const char* errorMsg);
void line_counter();
