#include "poly.h"
#include "parser.tab.h"

#define DEFAULT_ERROR -1

extern FILE *yyin;
int lineCount = 0;

int main()
{
    FILE* inputFile = fopen("poly.txt", "r");
    if (inputFile == NULL)
    {
        printf("[-] File with polynoms doesn't exist\n");
        return DEFAULT_ERROR;
    }

    yyin = inputFile;
    yyparse();
    fclose(yyin);
}

void line_counter()
{
    lineCount++;
}

void error_msg(const char* errorMsg, int flag)
{
    if (flag)
        printf("[-] Error in line %d: %s\n", lineCount + 1, errorMsg);
    else
        printf("[-] Error in line %d: %s\n", lineCount, errorMsg);
    system("pause");
    exit(DEFAULT_ERROR);
}