#include "main.h"

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

int main(void)
{
    t_list **tokens_lst;
    char *str = " echo hellow < file.txt | cat file.txt | grep banana | wc -l >> file2";
    
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
    ft_lstclear(tokens_lst, delete_list);



    return(0);
}