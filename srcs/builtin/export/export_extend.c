/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_extend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:23:35 by cw3l              #+#    #+#             */
/*   Updated: 2025/09/20 08:17:48 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

int ft_index_of_str(char **split, char *str)
{
    int i;
    int len;

    i = 0;
    while (split[i])
    {   
        len = ft_index_of_c(split[i], '=');
        if(ft_strncmp(split[i], str, len) == 0)
        {
            return(i);
        }
        i++;
    }
    return(-1);
}

char *var_not_on_env(char *var)
{
    char *new_var;

    new_var = malloc(sizeof(char) * (ft_strlen(var) + 1));
    if(!new_var)
    {
        perror("is_not_in_env");
        free(var);
        return(NULL);
    }
    else
        ft_strlcpy(new_var, var, ft_strlen(var) + 1);
    return(new_var);
}

char *var_on_env(char **envp, char *var, int idx_env)
{
    START;
    char *new_var;
    char *new_value;
    int i;
    int j;

    new_var = malloc(sizeof(char) * (ft_strlen(var) + 1));
    if(!new_var)
    {
        free(var);
        return(NULL);
    }
    new_value = &envp[idx_env][ft_index_of_c(envp[idx_env], '=') + 1];
    printf("voici new value %s\n", new_value);
    i = 0;
    while (var[i])
    {
        new_var[i] = var[i];
        if(var[i] == '=')
        {
            i++;
            break;
        }
        i++;
    }
    j = 0;
    while(new_value[j])
        new_var[i++] = new_value[j++]; 
    new_var[i] = '\0';

    return(new_var);
}



//heare


char *export_var_expend(char **envp, char *var)
{
    char *v;
    int idx_env;

    

    if(!envp | !*envp | !var )
        return(NULL);
    if(ft_index_of_c(var, '$') == -1)
        return(NULL);
    v = ft_substr(var, 0, ft_index_of_c(var, '=') + 1);
    if(!v)
        return(NULL);
    idx_env = ft_index_of_str(envp, &var[ft_index_of_c(var, '$') + 1]);
    if(idx_env == -1)
    {
        free(v);
        return(var);
    }
    else
    {
        START;
        char *va = var_on_env(envp, var, idx_env);
        printf("voici va %s\n", va);
        return(va);
    }
    return(NULL);
}