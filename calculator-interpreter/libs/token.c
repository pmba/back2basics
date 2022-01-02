#include <stdio.h>
#include <stdlib.h>

#include "token.h"

TokenList* new_token_list() {
    TokenList* token_list = (TokenList*) malloc(sizeof(TokenList));
    
    token_list->length = 0;
    token_list->head = NULL;
    token_list->tail = NULL;

    return token_list;
}

Token* new_token(TokenType type, char* value, unsigned int column) {
    Token* token = (Token*) malloc(sizeof(Token));

    token->type = type;
    token->value = value;
    token->column = column;
    token->next = NULL;

    return token;
}

void add_token(TokenList* list, Token* token) {
    
    if (list->head == NULL) {
        // If the head is null, then the list is empty
        list->head = token;
        list->tail = token;
    } else {
        // If the head is not null, then the list is not empty

        list->tail->next = token;
        list->tail = token;
    }

    token->next = NULL;
    ++list->length;
}

void create_add_tk(TokenList* list, TokenType type, char* value, unsigned int column) {
    Token* token = new_token(type, value, column);
    add_token(list, token);
}

void print_token_list(TokenList* list) {

    printf("\tLength: %u\n", list->length);

    Token* current_token = list->head;

    printf("\tData: \n");
    while (current_token != NULL) {
        printf("\t\t{ value: '%s', column: %d }\n", current_token->value, current_token->column);
        current_token = current_token->next;
    }
}