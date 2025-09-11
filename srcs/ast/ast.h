#ifndef AST_H
#define AST_H

#include "../tokeniser/tokeniser.h"
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/time.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int     generate_ast(t_list *token_list, t_token **ast_root);
int     execute_ast(t_token *ast, char **envp);
void    display_binary_tree(t_token *parent, t_token *actual, int deriv);

#endif