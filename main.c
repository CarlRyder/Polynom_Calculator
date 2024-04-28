#include "poly.h"
#include "parser.tab.h"

#define DEFAULT_ERROR -1

int main()
{
    yyin = fopen("poly.txt", "r");
    if (yyin == NULL)
    {
        printf("[-] File with polynoms doesn't exist\n");
        return DEFAULT_ERROR;
    }
    yyparse();
    fclose(yyin);
}