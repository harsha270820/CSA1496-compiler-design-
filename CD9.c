#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PROD 10
#define MAX_LEN 10

int main() {
    char S[MAX_LEN], L[MAX_LEN], prod[MAX_PROD][MAX_LEN];
    int n, i, j, k;

    printf("Enter the production rules for S:\n");
    scanf("%s", S);

    printf("Enter the production rules for L:\n");
    scanf("%s", L);

    printf("Enter the number of production rules for L:\n");
    scanf("%d", &n);

    // Eliminating left recursion from L
    char L1[MAX_LEN], L2[MAX_LEN];
    strcpy(L1, "");
    strcpy(L2, "");

    for (i = 0; i < n; i++) {
            if (L[i]== L[0]) {
            // If left recursion is found
            char temp[MAX_LEN];
            strcpy(temp, L[1]);
            strcat(temp, L2);
            sprintf(L2, "%s|%s", temp, &S[1]);
        }
        else {
            // If left recursion is not found
            char temp[MAX_LEN];
            strcpy(temp, L[i]);
            strcat(temp, L1);
            sprintf(L1, "%s|%s", temp, &S[1]);
        }
    }

    // Printing the new production rules for L
    printf("\nNew production rules for L:\n");
    printf("L -> %s%s\n", L1, "|");

    // Substituting the new production rule for L in the production rules for S
    printf("\nNew production rules for S:\n");
    printf("S -> (%s)%s\n", &L2[1], &S[1]);

    printf("S -> a%s\n", &S[1]);

    return 0;
}
