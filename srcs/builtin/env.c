#include "builtin.h"

int check_variable(char **var)
{
    int i;

    i = 0;
    if(!var)
        return(0);
    while (var[i])
    {
        if(ft_index_of_c(var[i], '=') == -1)
        {
            printf("env: '%s': No such file or directory\n", var[i]);
            return(-1);
        }
        i++;
    }
    return(0);
}

int ft_env(t_env *env, char **var)
{
    char **ptr;

    if(!env || !env->env || check_variable(var) == -1)
        return(-1);
    printf("here\n");
    
    ptr = *env->env;
    while (*ptr)
    {
        printf("%s\n", *ptr);
        ptr++;
    }
    if(var)
    {
        while (*var)
        {
            printf("%s\n", *var);
            var++;
        }
    }
    return(0);
}