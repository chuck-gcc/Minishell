#include "ast.h"

void generate_ast(t_list *token_list, t_token *ast_root)
{

    if(!token_list)
        return ;

    if(ast_root == NULL)
    {
        
        ast_root = token_list->content;
        printf("root is note null %s\n", ast_root->value);
        generate_ast(token_list->next, ast_root);
    }
    return;
}