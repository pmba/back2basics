#ifndef LLIST_H
#define LLIST_H


#define ADD_OP '+'
#define SUB_OP '-'
#define MULT_OP '*'
#define DIV_OP '/'
#define UN_NEG '-'
#define UN_POS '+'
#define L_PARAM_VAL '('
#define R_PARAM_VAL ')'
#define FLOAT_DEC '.'


typedef enum tokent {
    NUMBER, BINOP, UNARY, LPARAM, RPARAM
} TokenType;

typedef struct token {
    TokenType type;
    char* value;
    unsigned int column;
    struct token* next;
} Token;

typedef struct {
    unsigned int length;
    Token* head;
    Token* tail;
} TokenList;

TokenList* new_token_list();
Token* new_token(TokenType type, char* value, unsigned int column);
void add_token(TokenList* list, Token* token);
void create_add_tk(TokenList* list, TokenType type, char* value, unsigned int column);
void print_token_list(TokenList* list);

#endif