%{ 
#include "parser.tab.h"
#include "poly.h"
%}

%option yylineno
%option noyywrap

%%

[/][/].*       ;
[ \t\r]        ;
[\n]           { line_inc(); }
[0-9]+         { yylval = atoi(yytext); return DIGIT; }
[a-z]          { yylval = *yytext; return VAR; }
[A-Z]          { yylval = *yytext; return VARNAME; }
[+\-]          { yylval = *yytext; return SIGN; }
[=()*^;]       { return *yytext; }
[~]            { char nextChar = input();
                 if (nextChar != ' ') error_msg("output command was used incorrectly");
                 unput(nextChar);
                 return PRINT; }
.              { error_msg("incorrect symbol"); }

%%