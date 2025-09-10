#include "main.h"
 #include <sys/stat.h>
#include <stdio.h>
#include <string.h>


char *get_next_line(int fd);

void delete_list(void *content)
{
    t_token *token = (t_token *)content;

    if(token)
    {
        if(token->value)
        {
            free(token->value);
            token->value = NULL;
        }
        if(token->args)
        {
            char **tmp;

            tmp = token->args;
            while (*tmp)
            {
                free(*tmp);
                *tmp = NULL;
                tmp++;
            }
            free(token->args);
            token->args = NULL;
        }
        if(token->radir[0])
        {
            free(token->radir[0]);
            token->radir[0] = NULL;
        }
        if(token->radir[1])
        {
            free(token->radir[1]);
            token->radir[1] = NULL;
        }
        free(token);
        token = NULL;
    }
    
}



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



int main(void)
{
    t_list **tokens_lst;
    char *str = "cat -A b c  < file.txt  | grep banana | wc -l > out.txt";
    //char *str = "cat -A b c ";
    
    tokens_lst = calloc(sizeof(t_list *) , 1);
    if(!tokens_lst)
        return(1);
   
    
    if(!get_token_list(str, tokens_lst))
    {
        printf("Error token list\n");
        ft_lstclear(tokens_lst, delete_list);
        return(1);
    }

    printf("\n\n");
    ft_lstiter(*tokens_lst, display_content_lst);
    printf("\n\n");
    ft_lstiter(*tokens_lst, display_arg_of_cmd);

    // t_token **ast = malloc(sizeof(t_token *));
    // if(!ast)
    // {
    //     ft_lstclear(tokens_lst, delete_list);
    //     return(1);
    // }
    //*ast = NULL;
    //generate_ast(*tokens_lst, ast);

    //display_binary_tree(NULL,*ast);
    ft_lstclear(tokens_lst, delete_list);
    return(0);
}
