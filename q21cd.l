%{
#include <stdio.h>
int charCount = 0;
int lineCount = 0;
int wordCount = 0;
%}

%%
[ \t]+         /* Ignore spaces and tabs */
\n              { lineCount++; }  /* Count new lines */
\/\/.*          /* Ignore single-line comments */
\/\*[^*]*\*\/   /* Ignore multi-line comments */
[a-zA-Z_][a-zA-Z0-9_]*  { wordCount++; } /* Count identifiers */
.               { charCount++; } /* Count other characters */
%%

int yywrap(){}

int main(int argc, char *argv[]) {
    yyin = fopen(argv[1], "r");
    yylex();
    printf("Number of characters: %d\n", charCount);
    printf("Number of lines: %d\n", lineCount);
    printf("Number of words: %d\n", wordCount);
    return 0;
}
