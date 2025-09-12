#include "builtin.h"

int ft_cd(t_token *token)
{
    char *path;

    close(3);
    if(!token)
        return(1);
    if(ft_get_split_len(token->args) > 2)
    {
        printf("Minishell: cd: too many arguments\n");
        return(1);
    }
    path = token->args[1];
    if(chdir(path) != 0)
    {
        perror("Minishell: cd");
        return(errno);
    }
    return(0);
}