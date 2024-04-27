#include "poly.h"
#include "parser.tab.h"

FILE *streamIn;

#define yyin streamIn
#define DEFAULT_ERROR -1

int main()
{
    streamIn = fopen("poly.txt", "r");
    if (streamIn == NULL)
    {
        printf("[-] File with polynoms doesn't exist\n");
        return DEFAULT_ERROR;
    }
    yyparse();
    fclose(streamIn);
}