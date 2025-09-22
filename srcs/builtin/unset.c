#include "builtin.h"

int add_in_env(char *var, char **args)
{
    int i;
    char *str;

    i = 0;
    while (args[i])
    {   
        str = ft_substr(args[i], 0, ft_index_of_c(args[i], '='));
        if(ft_strncmp(str, var, ft_strlen_longest(str, var)) == 0)
            return(0);
        i++;
    }
    return(1);
}

char **upload_env(char **envp, char **args, int env_len)
{
    int i;
    int k;
    char **new_env;

    new_env = malloc(sizeof(char *) * env_len);
    if(!new_env)
    {
        perror("unset");
        return(NULL);
    }
    i = 0;
    k = 0;
    while (envp[i] != NULL)
    {
        char *c2 = ft_substr(envp[i], 0, ft_index_of_c(envp[i], '='));
       if(add_in_env(c2, args))
       {
            new_env[k] = envp[i];
            k++;
       }
        else
            printf("we dont add %s\n", envp[i]);
       i++;
    }
    new_env[k] = NULL;
    return(new_env);
}

int unset_valide_variable(char **envp, char **args, int *err)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (args[i])
    {
        if(!ft_isalpha(args[i][0]) && args[i][0] != 32)
        {
            printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
            *err = 1;
        }
        else
        {
            if(is_on_env(args[i], envp, ft_get_split_len(envp)) > -1)
                count++;
        }
        i++;
    }
    return(count);
}

int ft_unset(char ***envp, t_token *token)
{
    int err;
    int new_env_len;
    int valide_variable;
    char    **new_env;

    err = 0;
    if(!envp || !*envp || !token)
        return(-1);
    
    valide_variable = unset_valide_variable(*envp, &token->args[1], &err);
    printf("voici le nombre in env : %d et la valeur de retour %d\n", valide_variable,err);
    
    new_env_len = (ft_get_split_len(*envp) - valide_variable) + 1;
    new_env =  upload_env(*envp, &token->args[1], new_env_len);
    if(!new_env)
    {
        printf("Error new env\n");
        return(1);
    }
    *envp = new_env;
    return(err);
}