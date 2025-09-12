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


int ft_export(char ***envp, t_token *token)
{
    char **args;
    int i;

    if(!envp || !*envp)
        return(-1);
    i = 0;
    args = &token->args[1];
    while(args[i])
    {
        printf("%s\n", *args);
        i++;
    }    
    if(i == 0)
        display_export(*envp);

    return(0);
}