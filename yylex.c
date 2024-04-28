#include "poly.h"
#include "parser.tab.h"

extern int lineCount = 0;
extern int currChar = 0;

int yylex()
{
    while ((currChar = fgetc(yyin)) == ' ' || currChar == '\t');
    while (currChar == '/')
    {
        currChar = fgetc(yyin);
        if (currChar == '/')
        {
            while ((currChar = fgetc(yyin)) != '\n');
            lineCount++;
            return currChar;
        }
        else
        {
            lineCount++;
            error_msg("[-] Incorrect comment", 1);
        }
    }
    if (currChar == '$')
    {
        // TODO: variables
    }
    else if (isdigit(currChar))
    {
        yylval.digit = 0;
        ungetc(currChar, yyin);
        // TODO: digit
        return DIGIT;
    }
    else if (isalpha(currChar))
    {
        yylval.var = currChar;
        return VAR;
    }
    else if (currChar == '~')
    {
        currChar = fgetc(yyin);
        // TODO: print
    }
    else
    {
        if (currChar == '(' || currChar == ')' ||
            currChar == '+' || currChar == '-' ||
            currChar == '^' || currChar == '*' ||
            currChar == '=')
            return currChar;
        else if (currChar == '\n')
        {
            lineCount++;
            return currChar;
        }
        else if (currChar == EOF)
            return 0;
        else
            error_msg("[-] Incorrect symbol", 0);
    }
    return currChar;
}