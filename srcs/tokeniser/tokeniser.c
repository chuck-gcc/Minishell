
#include "tokeniser.h"

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
    char *token = ((t_token *)liste)->value;
    (void)token;
    printf("Value du token %s\n", token);
}

int ft_is_builtin(char *str)
{
    if
    (   !ft_strncmp(str, "echo", ft_strlen_longest(str, "echo")) ||
        !ft_strncmp(str, "cd", ft_strlen_longest(str, "cd")) ||
        !ft_strncmp(str, "pwd", ft_strlen_longest(str, "pwd")) ||
        !ft_strncmp(str, "export", ft_strlen_longest(str, "export")) ||
        !ft_strncmp(str, "unset", ft_strlen_longest(str, "unset")) ||
        !ft_strncmp(str, "env", ft_strlen_longest(str, "env")) ||
        !ft_strncmp(str, "exit", ft_strlen_longest(str, "exit")) 
    )
        return(1);
    else
        return(0);
}

int ft_is_commande(char *str)
{
    DIR *dir;
    struct dirent *files;

    dir = opendir("/usr/bin");
    if(dir == NULL)
        return(-1);
    while((files = readdir(dir)))
        if(!ft_strncmp(str,files->d_name, ft_strlen_longest(str,files->d_name)))
            printf("%s\n", files->d_name);
    (void)str;

    return(0);
}

int get_token_type(char *str)
{
    if(ft_is_builtin(str))
        return(BUILTIN);
    if(ft_is_commande(str))
        return(CMD);
    if(!ft_strncmp(str, "|", ft_strlen_longest(str, "|")))
        return(PIPE);
    if(!ft_strncmp(str, ">", ft_strlen_longest(str, ">")))
        return(REDIR_RIGHT);
    if(!ft_strncmp(str, "<", ft_strlen_longest(str, "<")))
        return(REDIR_LEFT);
    if(!ft_strncmp(str, ">>", ft_strlen_longest(str, ">>")))
        return(REDIR_APPEND);
    if(!ft_strncmp(str, "<<", ft_strlen_longest(str, "<<")))
        return(DELIM);
    return(1);
}

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

        if(node->content == NULL)
            return(ft_split_clean(&split));
        ft_lstadd_back(lst, node);
        i++;
    }
    ft_split_clean(&split);
    return(lst);
}

