%{
#include <stdio.h>
#include "poly.h"
void yyerror(char* str) { error_msg(str); }
%}

%token DIGIT
%token VAR
%token VARNAME
%token PRINT

%%
input:  | input expr

expr:   PRINT poly ';' { 
        printf("Result: ");
        polysort((polyElement*)$2);
        print((polyElement*)$2);
        }
        |
        PRINT vars ';' {
        printf("Variable %c: ", (char)$2);
        print_var((char)$2);
        }
        |
        vars '=' poly ';' {
        polysort((polyElement*)$3);
        set_polynom((char)$1, (polyElement*)$3);
        };

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
        };

coeff:  coeff '^' deg {
        $$ = (uint64_t)degree((polyElement*)$1, (int)$3);
        }
        |
        coeff '^' coeff {
        polydegree((polyElement*)$1, (polyElement*)$3);
        $$ = $1;
        }
        |
        vars {
        polyElement* temp = (polyElement*)malloc(sizeof(polyElement));
        temp = copy_polynoms(temp, search_polynom((char)$1));
        $$ = (uint64_t)temp;
        }
        |
        deg {
        $$ = (uint64_t)create(0, (int)$1, 0);
        }
        |
        deg VAR {
        $$ = (uint64_t)create((char)$2, (int)$1, 1);
        }
        |
        deg VAR '^' deg {
        $$ = (uint64_t)create((char)$2, (int)$1, (int)$4);
        }
        |
        deg '*' VAR {
        $$ = (uint64_t)create((char)$3, (int)$1, 1);
        }
        |
        VAR {
        $$ = (uint64_t)create((char)$1, 1, 1);
        }
        |
        VAR '^' deg {
        $$ = (uint64_t)create((char)$1, 1, (int)$3);
        }
        |
        '(' poly ')' {
        $$ = $2;
        };

deg:    number {
        $$ = $1;
        }
        |
        number '^' deg {
        $$ = calc_degree((int)$1, (int)$3);
        };

vars:   VARNAME {
        $$ = $1;
        };

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
        };

%%