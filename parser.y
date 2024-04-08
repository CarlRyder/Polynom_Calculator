%{
#include <stdio.h>
#include "poly.h"
void yyerror(char* str) { fprintf(stderr, "%s\n", str); }
%}

%token DIGIT

%union {
int num;
polyElement p;
}

%type<p> expr
%type<p> poly
%type<p> coeff
%type<num> deg
%type<num> number

%%
expr:   poly { 
        printf("\nExpression:\n");
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
        $$ = mult((polyElement*)$1, (polyElement*)$3);
        }
;

coeff:  coeff '^' deg {
        degree((polyElement*)$1, (int)$3);
        $$ = $1;
        }
        |
        coeff '^' coeff {
        polydegree((polyElement*)$1, (polyElement*)$3);
        $$ = $1;
        }
        |
        deg {
        $$ = create((int)$1, 0);
        }
        |
        deg 'x' {
        $$ = create(1, 1);
        mult_coeff((polyElement*)$$, (int)$1);
        }
        |
        deg '*' 'x' {
        $$ = create(1, 1);
        mult_coeff((polyElement*)$$, (int)$1);
        }
        |
        'x' {
        $$ = create(1, 1);
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
        '-' number {
        $$ = $1 * (-1);
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
        number DIGIT {
        $$ = $1 * 10 + $2;
        }
;

%%