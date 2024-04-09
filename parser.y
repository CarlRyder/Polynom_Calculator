%{
#include <stdio.h>
#include "poly.h"
void yyerror(char* str) { fprintf(stderr, "%s\n", str); }
%}

%token DIGIT

%%
expr:   poly { 
        printf("\nExpression:\n");
        polysort((polyElement*)$$);
        print((polyElement*)$$);
        }
;

poly:   coeff {
        $$ = $1;
        }
        |
        poly '+' coeff { 
        summary((polyElement*)$1, (polyElement*)$3);
        $$ = $1;
        } 
        |
        poly '-' coeff { 
        diff((polyElement*)$1, (polyElement*)$3);
        $$ = $1;
        }
        |
        poly '*' coeff { 
        $$ = (uint64_t)mult((polyElement*)$1, (polyElement*)$3);
        }
;

coeff:  coeff '^' deg {
        $$ = (uint64_t)degree((polyElement*)$1, (int)$3);
        }
        |
        coeff '^' coeff {
        polydegree((polyElement*)$1, (polyElement*)$3);
        $$ = $1;
        }
        |
        deg {
        $$ = (uint64_t)create((int)$1, 0);
        }
        |
        deg 'x' {
        $$ = (uint64_t)create((int)$1, 1);
        }
        |
        deg 'x' '^' deg {
        $$ = (uint64_t)create((int)$1, (int)$4);
        }
        |
        deg '*' 'x' {
        $$ = (uint64_t)create((int)$1, 1);
        }
        |
        'x' {
        $$ = (uint64_t)create(1, 1);
        }
        |
        'x' '^' deg {
        $$ = (uint64_t)create(1, (int)$3);
        }
        |
        '(' poly ')' {
        $$ = $2;
        }
;

deg:    number {
        $$ = $1;
        }
        |
        number '^' deg {
        $$ = calc_degree((int)$1, (int)$3);
        }
;

number: DIGIT {
        $$ = $1;
        }
        |
        '-' DIGIT {
        $$ = $2 * (-1);
        }
        |
        number DIGIT {
        $$ = $1 * 10 + $2;
        }
;

%%