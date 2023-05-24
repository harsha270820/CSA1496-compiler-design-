%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cnt=0;
%}

%%
[0-9]+                  { cnt++; } /* Print integer constants */
[0-9]+\.[0-9]+          { cnt++; } /* Print floating-point constants */
%%
int yywrap(){}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./constants <input_file>\n");
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
    printf("No of constant:%d", cnt);
    return 0;
}
