%{
#include <stdio.h>
#include "poly.h"
void yyerror(char* str) { error_msg(str); }
int yylex();
%}

%token DIGIT
%token SIGN
%token VAR
%token VARNAME
%token PRINT

%%
input:  | input expr

expr:   PRINT poly ';' { 
        print_line("Result: ");
        print((polyElement*)$2);
        }
        |
        PRINT vars ';' {
        char temp[16];
        sprintf(temp, "Variable %c: ", (char)$2);
        print_line(temp);
        print_var((char)$2);
        }
        |
        vars '=' poly ';' {
        set_polynom((char)$1, (polyElement*)$3);
        }
        |
        PRINT poly { 
        line_dec();
        error_msg("ending character ';' is missing");
        }
        |
        PRINT vars {
        line_dec();
        error_msg("ending character ';' is missing");
        }
        |
        vars '=' poly {
        line_dec();
        error_msg("ending character ';' is missing");
        };

poly:   coeff_x {
        $$ = $1;
        }
        |
        poly SIGN coeff_x { 
        $$ = (uint64_t)operation((char)$2, (polyElement*)$1, (polyElement*)$3);
        }
        |
        poly SIGN SIGN coeff_x {
        error_msg("two operation signs in a line");
        }
        |
        poly SIGN SIGN SIGN coeff_x {
        error_msg("three operation signs in a line");
        };

coeff_x:
        coeff {
        $$ = $1;
        }
        |
        coeff_x '^' coeff_x {
        $$ = (uint64_t)polydegree((polyElement*)$1, (polyElement*)$3);
        }
        |
        coeff_x '*' coeff_x { 
        $$ = (uint64_t)mult((polyElement*)$1, (polyElement*)$3);
        }
        |
        vars {
        polyElement* temp = (polyElement*)malloc(sizeof(polyElement));
        temp = copy_polynoms(temp, search_polynom((char)$1));
        $$ = (uint64_t)temp;
        }
        |
        '(' poly ')' {
        $$ = $2;
        };

coeff:  number {
        $$ = (uint64_t)create(0, (int)$1, 0);
        }
        |
        number VAR {
        $$ = (uint64_t)create((char)$2, (int)$1, 1);
        }
        |
        number VAR '^' deg {
        $$ = (uint64_t)create((char)$2, (int)$1, (int)$4);
        }
        |
        VAR {
        $$ = (uint64_t)create((char)$1, 1, 1);
        }
        |
        VAR '^' deg {
        $$ = (uint64_t)create((char)$1, 1, (int)$3);
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