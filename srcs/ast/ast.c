#include "ast.h"

void display_binary_tree(t_token *parent, t_token *actual)
{
    (void)parent;

    if(actual == NULL)
        return;
    
    parent = actual;

    printf("%-10s | %-15s | precedence: %-3d | asso: %-3d\n",actual->value,
    print_token_type(actual->type),
    actual->precedence,
    actual->asso);
    display_binary_tree(actual,actual->left);


    if(!actual->right)
        printf("\033[0;31m" "go in right of :%-5s: Nothing\n\n" "\033[0m", parent->value);
    else
        printf("\033[0;32m""go in right of :%-10s\n\n""\033[0m", parent->value);

    display_binary_tree(actual, actual->right);
}

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


void    add_node(t_token *token, t_token *root, t_token *parent)
{
    if(!token)
    {
        return;
    }
    
    // printf("token: %s, ast : %s \n", token->value, root->value);
    // if(!root->left)
    // {
    //     root->left = token;
    //     token = NULL;
    // }
    // else if(!token->right)
    // {
    //     root->right = token;
    //     token = NULL;
    // }
    parent = root;
    add_node(token, root->left, parent);

    add_node(token, root->right, parent);

}


int generate_ast(t_list *token_list, t_token **ast_root)
{
    t_token *token;
    
    if(!token_list)
        return(1);
    token =  ((t_token *)token_list->content);

    if(!*ast_root)
    {
        *ast_root = token;
        //printf("new root\n");
        generate_ast(token_list->next, ast_root);
    }
    else
    {
        if(token->type == PIPE)
        {
            t_token *tmp = *ast_root;
            *ast_root = token;
            (*ast_root)->left = tmp;
            //printf("new root %s\n", token->value);
            generate_ast(token_list->next, ast_root);
        }
        else
        {
            if(!(*ast_root)->left)
                (*ast_root)->left = token;
            else
                (*ast_root)->right = token;
            generate_ast(token_list->next, ast_root);
        }
    }
    return 1;
}

// int generate_ast_1(t_list *token_list, t_token **ast_r)
// {

//     t_token *token;
//     // if(ast_root)
//     //     printf("there s root in city %s\n", ast_root->value);
//     if(!token_list)
//     {
//         printf("ast generate! great\n\n");
//         //display_binary_tree(*ast_r);
//         return 1;
//     }
//     else
//     {
//         token =  ((t_token *)token_list->content);
//         if(*ast_r == NULL)
//         {
//             *ast_r = token;
//             //printf("new root is  %s\n", (*ast_r)->value);
//             generate_ast(token_list->next, ast_r);
//         }
//         else if(token->precedence >= (*ast_r)->precedence)
//         {
//             t_token *new;

//             new = *ast_r;
//             *ast_r = token;
//             (*ast_r)->left  = new;
//             printf("childrend:  %s paretn : %s\n", token->value, new->value);
//             generate_ast(token_list->next, ast_r);
//         }
//         else
//         {
//             if(!(*ast_r)->left)
//             {
//                 (*ast_r)->left = token;
//                 generate_ast(token_list->next, ast_r);
//             }
//             else if(!(*ast_r)->right)
//             {
//                 (*ast_r)->right = token;
//                 generate_ast(token_list->next, ast_r); 
//             }
//             else
//                 generate_ast(token_list, &(*ast_r)->right);
            
//         }
//         return 0;
//     }
    
// }