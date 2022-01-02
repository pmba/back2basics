#ifndef LEXER_H
#define LEXER_H

void consume();
void lexer(char* raw_program);

void expr();
void term_tail();
void term();
void factor_tail();
void factor();
void number();

#endif