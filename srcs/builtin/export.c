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
int is_valide_variable(char *var)
{
    char *ptr;
    int equal;

    ptr = var;
    equal = 0;
    if(!ft_isalpha(*ptr))
        return(-1);
    while(*ptr)
    {
        if(*ptr == '=')
        {
            equal = 1;
            ptr++;
        }
        if(!ft_isalnum(*ptr) && equal == 0)
            return(-1);
        ptr++;
    }
    return(0);
}


size_t count_valide_variable(char **vars)
{
    char **ptr;
    size_t i;

    ptr = vars;
    i = 0;
    while (*ptr)
    {
        if(is_valide_variable(*ptr) == 0)
            i++;
        else
            printf("minishell: export: `%s': not a valid identifier\n", *ptr);
        ptr++;
    }
    return(i);
}
size_t is_on_env(char *var, char **env, size_t idx)
{
    size_t i;

    i = 0;
    while (i <= idx)
    {
        int idx = ft_index_of_c(env[i],'=');
        if(ft_strncmp(var, env[i], idx ) == 0)
            return(i);
        i++;
    }
    return(-1);
}

char *export_expend_var(char *var)
{
    char *env_variable;
    char *new_var;

    env_variable = &var[ft_index_of_c(var,'=') + 2];
    printf("%s\n", env_variable);
    new_var = getenv(env_variable);
    if(!new_var)
        return(ft_strdup(" "));
    else
        return(ft_strdup(new_var));
}

char **get_new_env(char **envp, char **args)
{
    char **new_env;
    size_t len_env;
    size_t valide_var;
    size_t  i;
    size_t  j;

    len_env = ft_get_split_len(envp);
    valide_var = count_valide_variable(args);
    
    new_env = malloc(sizeof(char *) * len_env + valide_var + 1);
    if(!new_env)
    {
        perror("get new env");
        return(NULL);
    }
    i = 0;
    while (envp[i])
    {
        new_env[i] = ft_strdup(envp[i]);
        i++;
    }
    j = 0;
    while (args[j])
    {
        if(is_valide_variable(args[j]) != -1)
        {
            if(args[j][ft_index_of_c(args[j],'=') + 1] == '$')
            {
                free(args[j]);
                args[j] = export_expend_var(args[j]);
            }
            int on_env = is_on_env(args[j], new_env, i);
            if(on_env >= 0)
            {
                free(new_env[on_env]);
                new_env[on_env] = ft_strdup(args[j]);
            }
            else if(args[j][ft_index_of_c(args[j],'=') + 1] == '$')
                new_env[i++] = export_expend_var(args[j]);
            else
                new_env[i++] = ft_strdup(args[j]);
        }
        j++;
    }
    new_env[i] = NULL;
    return(new_env);
}


int ft_export(char ***envp, t_token *token)
{
    char    **new_env;


    if(!envp || !*envp || !token)
        return(-1);
    if(!token->args)
    {
        ft_split_quick_sort(*envp, ft_get_split_len(*envp), ft_strncmp);
        display_export(*envp);
        return(0);
    }
    new_env = get_new_env(*envp, &token->args[1]);
    if(!new_env)
        return(1);
    else
        *envp = new_env;
    return(0);
}