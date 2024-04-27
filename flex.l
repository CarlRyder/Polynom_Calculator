%{ 
#include "parser.tab.h" 
%}

%option yylineno
%option noyywrap

%%

[/][/].*       ;
[ \t\r\n]      ;
[0-9]+         { yylval = atoi(yytext); return DIGIT; }
[.]            { return EOF; }
[a-zA-Z]       { yylval = *yytext; return VAR; }
.              { return *yytext; }

%%