#ifndef AST_H
#define AST_H

#include "../tokeniser/tokeniser.h"

int     generate_ast(t_list *token_list, t_token **ast_root);
void    display_binary_tree(t_token *parent, t_token *actual);

#endif