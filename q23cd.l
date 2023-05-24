%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int macroCount = 0;
int headerCount = 0;
%}

%%
^#define    { macroCount++; } /* Count macro definitions */
^#include   { headerCount++; } /* Count header file inclusions */
.|\n        /* Ignore other lines */
%%
int yywrap(){}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./count_macros_headers <input_file>\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Failed to open input file\n");
        return 1;
    }
    yyin = file;
    yylex();
    fclose(file);
    printf("Number of macros defined: %d\n", macroCount);
    printf("Number of header files included: %d\n", headerCount);
    return 0;
}
