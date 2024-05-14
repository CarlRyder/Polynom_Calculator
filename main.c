#include "poly.h"
#include "parser.tab.h"

#define DEFAULT_ERROR -1

extern FILE *yyin;
int lineCount = 1;

int main()
{
    FILE* inputFile = fopen("poly.txt", "r");
    if (inputFile == NULL)
    {
        printf("[-] File with polynoms doesn't exist\n");
        return DEFAULT_ERROR;
    }
    init_structs();
    yyin = inputFile;
    yyparse();
    fclose(yyin);
}

void line_counter()
{
    lineCount++;
}

int get_line()
{
    return lineCount;
}

void error_msg(const char* errorMsg)
{
    printf("[-] Error in line %d: %s\n", lineCount, errorMsg);
    exit(DEFAULT_ERROR);
}