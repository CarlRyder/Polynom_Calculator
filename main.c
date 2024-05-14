#include "poly.h"
#include "parser.tab.h"

#define DEFAULT_ERROR -1
#define DEFAULT_MSG_LEN 64

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

void line_inc() { lineCount++; }
void line_dec() { lineCount--; }

void print_line(char* message)
{
    if (strlen(message) + 10 > DEFAULT_MSG_LEN)
        error_msg("print buffer overflow");
    char print[DEFAULT_MSG_LEN];
    if (lineCount < 10)
        sprintf(print, "   %d | %s", lineCount, message);
    else if (lineCount < 100)
        sprintf(print, "  %d | %s", lineCount, message);
    else
        sprintf(print, " %d | %s", lineCount, message);
    printf("%s", print);
}

void error_msg(const char* errorMsg)
{
    printf("[-] Error in line %d: %s\n", lineCount, errorMsg);
    exit(DEFAULT_ERROR);
}