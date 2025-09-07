#include "ast.h"

void generate_ast(t_list *token_list, t_token **ast_root)
{

    t_token *token;
    //ft_lstiter(token_list, display_content_lst);
    (void)ast_root;
    
    
    if(!token_list)
    {
        printf("ast generate! great\n");
        return ;
    }
    
    token =  ((t_token *)token_list->content);

    if(*ast_root == NULL)
    {
        (*ast_root) = token;
        printf("root is  %s\n", (*ast_root)->value);
        generate_ast(token_list->next, ast_root);
    }

    if((*ast_root)->left)
    {
        t_token *next = (*ast_root)->left;
        generate_ast(token_list, &next);
    }
    else if (!(*ast_root)->left && token_list->next)
    {
        (*ast_root)->left = token;

        printf("new node %s\n", token->value);
        generate_ast(token_list->next, ast_root);
    }
    
}