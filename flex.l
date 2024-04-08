%{ 
#include "parser.tab.h" 
%}

%option yylineno
%option noyywrap

%%

[0-9]+         { yylval = atoi(yytext); return DIGIT; }
[ \t\r\n]      ;
[.]            { return EOF; }
[xX]           { return 'x'; }
.              { return *yytext; }

%%