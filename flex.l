%{ 
#include "parser.tab.h"
#include "poly.h"
%}

%option yylineno
%option noyywrap

%%

[/][/].*       ;
[ \t\r]        ;
[\n]           { line_counter(); }
[0-9]+         { yylval = atoi(yytext); return DIGIT; }
[a-z]          { yylval = *yytext; return VAR; }
[A-Z]          { yylval = *yytext; return VARNAME; }
[=()*+\-^]     { return *yytext; }
[~]            { return PRINT; }
[;]            { return *yytext; }
.              { error_msg("incorrect symbol"); }

%%