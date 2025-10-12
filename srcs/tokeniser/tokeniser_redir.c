#include "tokeniser.h"

int is_redir(char *str)
{
    if(!str)
        return(-1);
    if(!ft_strncmp(str, "<", ft_strlen(str)))
        return(1);
    if(!ft_strncmp(str, ">", ft_strlen(str)))
        return(2);
    if(!ft_strncmp(str, ">>", ft_strlen(str)))
        return(3);
    if(!ft_strncmp(str, "<<", ft_strlen(str)))
        return(4);

    return(0);
}

static int redir_check(char *str)
{
    int redir_type;

    if(!str)
    {
        printf("bash: no redirection argument '\n");
        return(-1);
    }
    if(get_token_type(str) == PIPE)
    {
        printf("bash: syntax error near unexpected token `|'\n");
        return(-1);
    }
    redir_type = is_redir(str);
    if (redir_type)
    {
        printf("bash: syntax error near unexpected token `%s'\n", str);
        return(-1);
    }
    return(0);
}

int get_redir(t_list *node, char **input)
{
    int idx;
    char *redir;
    char *redir_arg;
    
    idx = 0;
    if(redir_check(input[idx + 1]) == -1)
    {
        printf("error redir check\n");
        return(-1);
    }
    redir = ft_strdup(input[idx]);
    if(!redir)
        return(-1);
    ((t_token *)node->content)->radir[0] = redir;
    if(get_token_type(input[idx]) == DELIM)
    {
        idx++;
        redir_arg = ft_strdup(input[idx++]);
        if(!redir_arg)
        {
            free(redir);
            redir = NULL;
            return(-1);
        }
        ((t_token *)node->content)->radir[1] = redir_arg;
        while (input[idx] && get_token_type(input[idx]) != PIPE)
            idx++;
    }
    else
    {
        idx++;
        while (input[idx] && get_token_type(input[idx]) != PIPE)
        {
            printf("were here %s and %s\n",print_token_type(get_token_type(input[idx])), input[idx] );
            idx++;
        }
        redir_arg = ft_strdup(input[idx - 1]);
        if(!redir_arg)
        {
            free(redir);
            redir = NULL;
            return(-1);
        }
        ((t_token *)node->content)->radir[1] = redir_arg;
    }
    //printf("we have proceced the redir %s for the commande :%s\n",((t_token *)node->content)->radir[0], ((t_token *)node->content)->value);
    
    return(idx);
}
