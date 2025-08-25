
#include "tokeniser.h"


t_token *new_node(char *str)
{
    t_token *new_node;

    new_node = malloc(sizeof(t_token));
    if(!new_node)
        return(NULL);
    new_node->value = ft_strdup(str);
    new_node->type = get_token_type(str);
    new_node->next = NULL;
    return(new_node);
}


t_list **get_token_list(char *str, t_list **lst)
{
    int i;
    char    **split;
    t_list  *node;

    i = 0;
    split = ft_split(str, 32);
    if(!split)
        return(NULL);
    while (split[i])
    {
        node = malloc(sizeof(t_list));
        if(!node)
            return(ft_split_clean(&split));
        node->content = new_node(split[i]);
        //error simulation
        // if(i == 2)
        // {
        //     free(((t_token *)node->content)->value);
        //     ((t_token *)node->content)->value = NULL;
        //     free(node->content);
        //     node->content = NULL;
        // }
        node->next = NULL;
        if(node->content == NULL)
            return(ft_split_clean(&split));
        ft_lstadd_back(lst, node);
        i++;
    }
    ft_split_clean(&split);
    return(lst);
}

