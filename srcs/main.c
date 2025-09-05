#include "main.h"
 #include <sys/stat.h>
#include <stdio.h>
#include <string.h>


char *get_next_line(int fd);

void delete_list(void *content)
{
    t_token *token = (t_token *)content;
    if(token && token->value)
        free(token->value);
    if(token)
        free(token);
}


void display_content_lst(void *liste)
{
    t_token *token;
    char *value;
    
    token = (t_token *)liste;
    value = token->value;

    printf("%s", value);
    printf("\t\t\t%s\n", print_token_type(token->type));
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

int main(void)
{
    t_list **tokens_lst;
    char *str = "cat file.txt  | grep banana | wc -l";
    
    tokens_lst = calloc(sizeof(t_list *) , 1);
    if(!tokens_lst)
        return(1);
    
    if(!get_token_list(str, tokens_lst))
    {
        printf("Error token list\n");
        ft_lstclear(tokens_lst, delete_list);
        return(1);
    }

    ft_lstiter(*tokens_lst, display_content_lst);
    
    printf("\n\n\n");
    
    ft_lstclear(tokens_lst, delete_list);

    
    

    return(0);
}