%{
#include <stdio.h>
#include "poly.h"
void yyerror(char* str) { fprintf(stderr, "%s\n", str); }
%}

%token DIGIT

%%
expr:   poly { 
        printf("\nExpression:\n");
        print((polyElement*)$$);
        }
;

poly:   coeff {
        //printf("Create polynom from coeff\n");
        $$ = $1;
        //print((polyElement*)$$);
        }
        |
        poly '+' coeff { 
        //printf("From poly + coeff to poly\n");
        summary((polyElement*)$1, (polyElement*)$3);
        $$ = $1;
        } 
        |
        poly '-' coeff { 
        //printf("From poly - coeff to poly\n");
        diff((polyElement*)$1, (polyElement*)$3);
        $$ = $1;
        }
        |
        poly '*' coeff { 
        //printf("From poly * poly to poly\n");
        $$ = mult((polyElement*)$1, (polyElement*)$3);
        }
;

coeff:  coeff '^' deg {
        //printf("From coeff ^ deg (%d) to coeff with x\n", (int)$3);
        degree((polyElement*)$1, (int)$3);
        $$ = $1;
        }
        |
        coeff '^' coeff {
        //printf("From coeff ^ coeff (%d) to coeff with x\n");
        polydegree((polyElement*)$1, (polyElement*)$3);
        $$ = $1;
        }
        |
        deg {
        //printf("From coeff without x\n");
        $$ = create((int)$1, 0);
        }
        |
        deg 'x' {
        //printf("From deg 'x' to coeff with x\n");
        $$ = create(1, 1);
        mult_coeff((polyElement*)$$, (int)$1);
        }
        |
        deg '*' 'x' {
        //printf("From deg * coeff to coeff with x\n");
        $$ = create(1, 1);
        mult_coeff((polyElement*)$$, (int)$1);
        }
        |
        'x' {
        //printf("Init with x\n");
        $$ = create(1, 1);
        }
        |
        '(' poly ')' {
        //printf("From ( poly ) to poly\n");
        $$ = $2;
        }
;

deg:    number { 
        //printf("From number (%d) to deg\n", (int)$1);
        $$ = $1;
        }
        |
        '-' number { 
        //printf("From - number (%d) to deg\n", (int)$1);
        $$ = $1 * (-1);
        }
        |
        number '^' deg {
        //printf("From number (%d) ^ deg (%d) to deg (%d)\n", (int)$1, (int)$3, (int)$$);
        $$ = calc_degree((int)$1, (int)$3);
        }
;

number: DIGIT {
        //printf("Initial number: %d\n", (int)$$); 
        $$ = $1;
        }
        |
        number DIGIT {
        //printf("Initial number: %d\n", (int)$$);
        $$ = $1 * 10 + $2;
        }
;

%%