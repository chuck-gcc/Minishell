#ifndef AST_H
#define AST_H

#include "../tokeniser/tokeniser.h"

int generate_ast(t_list *token_list, t_token **ast_root);

#endif