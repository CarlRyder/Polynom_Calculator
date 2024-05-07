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
[A-Z]=         { yylval = *yytext; printf("init variable %c\n", yylval); }
[()*+\-^]      { return *yytext; }
[.]            { return EOF; }
.              { error_msg("incorrect symbol", 1); }

%%