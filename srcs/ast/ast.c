#include "ast.h"


// static t_token *get_last_token(t_token *root)
// {
//     t_token *last;

//     last = root;
//     while (last->left)
//     {
//         last = last->left;
//     }
//     return(last);
// }





int generate_ast(t_list *token_list, t_token **ast_r)
{

    t_token *token;
    // if(ast_root)
    //     printf("there s root in city %s\n", ast_root->value);
    if(!token_list)
    {
        printf("ast generate! great\n");
        //display_binary_tree(*ast_r);
        return 1;
    }
    else
    {
        token =  ((t_token *)token_list->content);
        if(*ast_r == NULL)
        {
            *ast_r = token;
            //printf("new root is  %s\n", (*ast_r)->value);
            generate_ast(token_list->next, ast_r);
        }
        else if(token->precedence >= (*ast_r)->precedence)
        {
            t_token *tmp = *ast_r;

            *ast_r = token;
            (*ast_r)->left = tmp;
            printf("there is new left node in city %s\n", (*ast_r)->left->value);
            generate_ast(token_list->next, ast_r);
        }
        else
        {
            if(!(*ast_r)->left)
            {
                (*ast_r)->left = token;
                generate_ast(token_list->next, ast_r);
            }
            else if(!(*ast_r)->right)
            {
                (*ast_r)->right = token;
                generate_ast(token_list->next, ast_r); 
            }
            else
                generate_ast(token_list, &(*ast_r)->right);
            
        }
        return 0;
    }
    
}