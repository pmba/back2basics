#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"
#include "token.h"

#define DEBUG_MODE 0
#define DEBUG(s) if(DEBUG_MODE) { printf(s); } 

TokenList* token_list;

char* program;

int i = 0;

char* to_char_arr(char c) {
    char* carr = (char*) malloc(2 * sizeof(char));
    carr[0] = c;
    carr[1] = '\0';

    return carr;
}

char current_char() {
    return program[i];
}

void consume() {
    ++i;
}

void lexer(char* raw_program) {
    token_list = new_token_list();

    DEBUG("> New empty token list created.\n");

    // Allocate memory to the new program string withou empty spaces, tabs and newlines
    program = (char*) malloc(strlen(raw_program) * sizeof(char));

    int resi = 0;
    int pindex = 0;

    // Clean the empty spaces, newlines and tabs from raw_program
    while (raw_program[pindex] != '\0') {

        if (
            raw_program[pindex] != ' ' 
            && raw_program[pindex] != '\n' 
            && raw_program[pindex] != '\t'
        ) {
            program[resi] = raw_program[pindex];
            ++resi;
        }

        ++pindex;
    }

    // Add \0 to determine that is the end of the string
    program[resi] = '\0';

    expr();

    if (current_char() != '\0') {
        fprintf(stderr, "[!] Error: Unexpected char '%c' in position [%d]\n", current_char(), i);
        exit(1);
    }

    printf("\n");
    print_token_list(token_list);
}

void expr() {
    DEBUG("> Running Expr\n");

    term();
    term_tail();

    DEBUG("< Done Expr\n");
}

void term_tail() {
    DEBUG("> Running TermTail\n");

    if (current_char() == ADD_OP || current_char() == SUB_OP) {
        create_add_tk(token_list, BINOP, to_char_arr(current_char()), i);

        consume();

        factor();
        factor_tail();
    }

    DEBUG("< Done TermTail\n");
}

void term() {
    DEBUG("> Running Term\n");

    factor();
    factor_tail();

    DEBUG("< Done Term\n");
}

void factor_tail() {
    DEBUG("> Running FactorTail\n");

    if (current_char() == MULT_OP || current_char() == DIV_OP) {
        create_add_tk(token_list, BINOP, to_char_arr(current_char()), i);

        consume();

        factor();
        factor_tail();
    }

    DEBUG("< Done FactorTail\n");
}

void factor() {
    DEBUG("> Running Factor\n");

    if (current_char() == L_PARAM_VAL) {
        create_add_tk(token_list, LPARAM, to_char_arr(current_char()), i);

        consume();

        expr();

        if (current_char() == R_PARAM_VAL) {
            create_add_tk(token_list, RPARAM, to_char_arr(current_char()), i);
            
            consume();
        } else {
            fprintf(stderr, "[!] Error: Right parenthesis char expected in position [%d]\n", i);
            exit(1);
        }
    } else {
        number();
    }

    DEBUG("< Done Factor\n");
}

void number() {
    DEBUG("> Running Number\n");

    char* full_number = (char*) malloc(256 * sizeof(char));
    int number_index = 0;

    if (current_char() == UN_POS || current_char() == UN_NEG) {
        full_number[number_index++] = current_char();
        consume();
    }

    while(
        isdigit(current_char()) || 
        (current_char() == FLOAT_DEC && isdigit(program[i + 1]))
    ) {
        full_number[number_index++] = current_char();
        consume();
    }

    full_number[number_index] = '\0';
    
    create_add_tk(token_list, LPARAM, full_number, i);

    DEBUG("< Done Number\n");
}
