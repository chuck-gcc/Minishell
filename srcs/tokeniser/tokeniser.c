
#include "tokeniser.h"

t_token *new_node(char *str)
{
    t_token *new_node;

    new_node = malloc(sizeof(t_token));
    if(!new_node)
        return(NULL);
    new_node->value = ft_strdup(str);
    new_node->next = NULL;
    return(new_node);
}


t_list **get_token_list(char *str)
{
    char    **split;
    int i;
    t_list  *node;
    t_list  **node_lst;

    split = ft_split(str, 32);
    if(!split)
        return(NULL);
    node_lst = malloc(sizeof(t_list *));
    while (split[i])
    {
        node = malloc(sizeof(t_list));
        if(!node)
            return(NULL);
        node->content = new_node(split[i]);
        //printf("node content %s\n", ((t_token *)node->content)->value);
        if(node->content == NULL)
            return(NULL);
        free(split[i]);
        ft_lstadd_back(node_lst,node);
        i++;
    }
    free(split);
    //printf("token value : %s\n", ((t_token *) ((*node_lst)->content))->next->value);
    return(node_lst);
}

void delete_list(void *content)
{
    t_token *token = (t_token *)content;
    free(token->value);
    free(token);
}


void display_content_lst(void *liste)
{
    char *token = ((t_token *)liste)->value;
    (void)token;
    printf("Value du token %s\n", token);
}