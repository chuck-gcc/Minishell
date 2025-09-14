#include "tokeniser.h"

static int count_args(char **input)
{
    int i;

    if(!input)
        return(-1);
    i = 0;
    while (input[i] && get_token_type(input[i]) != PIPE)
        i++;
    return(i);
}

int ft_expend_var(t_token *token)
{
    int i;
    char *var;

    if(!token || !token->args)
        return(1);
    i = 0;
    while (token->args[i])
    {
        if(token->args[i][0] == '$')
        {
            var = getenv(&token->args[i][1]);
            free(token->args[i]);
            if(!var)
                token->args[i] = ft_strdup(" ");
            else
                token->args[i] = ft_strdup(var);
        }
        i++;
    }
    return(0);
}
int get_args(t_list *node, char **input)
{
    int i;
    int idx;
    int args_count;
    char **args;

    i = 0;
    idx = 0;
    args_count = 0;
    
    if(*input)
        args_count = count_args(input) + 1;
    if(args_count)
    {
        args = malloc(sizeof(char *) * (args_count) + 1);
        if(!args)
        {
            perror("Error malloc:");
            return(-1);
        }
        args[i++] = ft_strdup(((t_token *)node->content)->value);
        while (get_token_type(input[idx]) != PIPE && !is_redir(input[idx]))
            args[i++] = ft_strdup(input[idx++]);
        args[i] = NULL;
        ((t_token *)node->content)->args = args;
        ft_expend_var(((t_token *)node->content));
        return(idx);
    }
    else
        return(0);
}
