#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_IDENTIFIER_LENGTH 50

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_CONSTANT,
    TOKEN_OPERATOR,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_IDENTIFIER_LENGTH+1];
} Token;

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

Token get_token(FILE *file) {
    Token token = {TOKEN_UNKNOWN, ""};
    int i = 0;
    char c = fgetc(file);

    // Skip whitespace and comments
    while (isspace(c) || c == '/') {
        if (c == '/') {
            c = fgetc(file);
            if (c == '/') {
                // Comment until end of line
                while (c != '\n' && c != EOF) {
                    c = fgetc(file);
                }
            } else {
                ungetc(c, file);
                c = '/';
                break;
            }
        } else {
            c = fgetc(file);
        }
    }

    // Check for identifiers and constants
    if (isalpha(c)) {
        token.type = TOKEN_IDENTIFIER;
        while (isalnum(c) && i < MAX_IDENTIFIER_LENGTH) {
            token.value[i++] = c;
            c = fgetc(file);
        }
        token.value[i] = '\0';
        ungetc(c, file);
    } else if (isdigit(c)) {
        token.type = TOKEN_CONSTANT;
        while (isdigit(c) && i < MAX_IDENTIFIER_LENGTH) {
            token.value[i++] = c;
            c = fgetc(file);
        }
        token.value[i] = '\0';
        ungetc(c, file);
    } else if (is_operator(c)) {
        token.type = TOKEN_OPERATOR;
        token.value[0] = c;
        token.value[1] = '\0';
    }

    return token;
}

int main(int argc, char **argv) {
    FILE *file;
    Token token;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    while ((token = get_token(file)).type != TOKEN_UNKNOWN) {
        switch (token.type) {
            case TOKEN_IDENTIFIER:
                printf("Identifier: %s\n", token.value);
                break;
            case TOKEN_CONSTANT:
                printf("Constant: %s\n", token.value);
                break;
            case TOKEN_OPERATOR:
                printf("Operator: %s\n", token.value);
                break;
            default:
                break;
        }
    }

    fclose(file);
    return 0;
}
