#include <stdio.h>
#include <stdlib.h>

#include "libs/lexer.h"

char* get_input();

int main()
{
    char* program = get_input();

    lexer(program);

    return 0;
}

char* get_input() {
    char* program = (char*) malloc(20 * sizeof(char));
    
    printf("\n>> ");
    scanf("%20[^\n]", program);

    return program;
}