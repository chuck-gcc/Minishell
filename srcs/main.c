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

int argument_fusion(t_list **tokens_lst)
{
    t_list *tokens = *tokens_lst;
    char *line = NULL;
    if(!tokens_lst || !*tokens_lst )
        return(-1);
    while (tokens)
    {
        if(tokens && ((t_token *)(tokens->content))->type == CMD)
        {
            tokens = tokens->next;
            while (tokens && ((t_token *)(tokens->content))->type == WORD)
            {
                t_token *token_v = (t_token *)(tokens->content);
                line = ft_strjoin(line, token_v->value, ' ');
                printf("content %s, token type %d\n", line, ((t_token *)(tokens->content))->type);
                tokens = tokens ->next;
            }
        }
        else
            tokens = tokens->next;
    }
    return(0);
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

void test_ast(t_list **list)
{
    t_token *root;
    t_token *token1 = (*list)->content;
    t_token *token2 = (*list)->next->content;
    t_token *token3 = (*list)->next->next->content;
    t_token *token4 = (*list)->next->next->next->content;
    t_token *token5 = (*list)->next->next->next->next->content;
    t_token *token6 = (*list)->next->next->next->next->next->content;
    t_token *token7 = (*list)->next->next->next->next->next->next->content;
    t_token *token8 = (*list)->next->next->next->next->next->next->next->content;

    // printf("Token 1 %s\n", token1->value);
    // printf("Token 2 %s\n", token2->value);
    // printf("Token 3 %s\n", token3->value);
    // printf("Token 4 %s\n", token4->value);
    // printf("Token 5 %s\n", token5->value);
    // printf("Token 6 %s\n", token6->value);
    // printf("Token 7 %s\n", token7->value);
    // printf("Token 8 %s\n", token8->value);

    root = token6;
    root->left = token3;
    root->right = token7;
    root->right->left = token8;
    root->left->left = token1;
    root->left->left->left = token2;
    root->left->right = token4;
    root->left->right->left = token5;
    printf("\n");
    display_binary_tree(NULL,root);
}

int main(void)
{
    t_list **tokens_lst;
    //char *str = "cat -A  < file.txt  | grep banana | wc -l > out.txt";
    char *str = " wc -l > out.txt baba";
    
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

    ft_lstclear(tokens_lst, delete_list);
    return(0);
}