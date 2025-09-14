#include "builtin.h"

void display_export(char **envp)
{
    int i;
    int j;

    if(!envp)
        return;
    j = 0;
    while (envp[j])
    {
        printf("declare -x ");
        i = 0;
        while (envp[j][i])
        {
            if(envp[j][i] == '=')
                printf("%c\"", envp[j][i]);
            else
                printf("%c", envp[j][i]);
            i++;
        }
        printf("\"\n");
        j++;
    }
}

/*
    A  word  consisting  only  of alphanumeric characters and under‐
    scores, and beginning with an alphabetic character or an  under‐
    score.  Also referred to as an identifier
*/







int ft_export(char ***envp, t_token *token)
{
    int i;
    char    **tmp;


    if(!envp || !*envp || !token)
        return(-1);
    i = 0;
    if(!token->args)
    {
        tmp = *envp;
        ft_split_quick_sort(tmp, ft_get_split_len(tmp), ft_strncmp);
        display_export(*envp);
    }
    while(token->args && token->args[i])
        i++;
    return(0);
}