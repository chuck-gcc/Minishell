#include "main.h"
 #include <sys/stat.h>
#include <stdio.h>
#include <string.h>

static int process_user_input(char *str, char ***envp)
{

    
    t_list **tokens_lst;
    
    tokens_lst = calloc(sizeof(t_list *) , 1);
    if(!tokens_lst)
        return(1);
   
    if(!get_token_list(str, tokens_lst))
    {
        printf("Error token list\n");
        ft_lstclear(tokens_lst, delete_list);
        return(1);
    }

    // printf("\n\n");
    //ft_lstiter(*tokens_lst, display_args_of_cmd);
    // printf("\n\n");

    t_token **ast = malloc(sizeof(t_token *));
    if(!ast)
    {
        ft_lstclear(tokens_lst, delete_list);
        return(1);
    }
    *ast = NULL;
    generate_ast(*tokens_lst, ast);
    if(!*ast)
    {
        ft_lstclear(tokens_lst, delete_list);
        return(1);
    }

    //display_binary_tree(NULL,*ast,0);
    //ft_lstiter(*tokens_lst, display_args_of_cmd);

    int r = execute_ast(*ast, envp);

    ft_lstclear(tokens_lst, delete_list);
    free(ast);
    return(r);
}


int run_minishell(char **envp)
{
    char *input;

    while (1)
    {
        input = readline("minishell: ");
        if(input)
        {
            if(*input)
                add_history(input);
            if(!ft_strncmp(input,"exit", ft_strlen_longest(input,"exit")))
            {
                free(input);
                clear_history();
                return(1);
            }
            int status = process_user_input(input, &envp);
            (void)status;
            //printf("STATUS COMMANDE %d\n\n", status);
            free(input);
            rl_on_new_line();
        }
    }
    return(0);
}

int ft_index_of_str(char **split, char *str)
{
    int i;

    i = 0;
    while (split[i])
    {   
        if(ft_strncmp(split[i], str, ft_index_of_c(split[i], '=') - 1) == 0)
            return(i);
        i++;
    }
    return(-1);
}

char *export_var_expend(char **envp, char *var)
{
    int idx_str_in_env;
    int equal_idx_var;
    int i;
    int j;
    char *first_part;
    char *seconde_part;
    char *new_var;

    equal_idx_var = ft_index_of_c(var,'=');
    if(equal_idx_var == -1 || var[equal_idx_var + 1] != '$')
    {
        return(var);
    }
    else
    {
        printf("error %d\n", equal_idx_var);
        idx_str_in_env = ft_index_of_str(envp, &var[equal_idx_var + 2]);
        if(idx_str_in_env == -1)
        {
            printf("not in env %s\n", &var[equal_idx_var + 1]);
            return(strdup(""));
        }
        first_part = ft_substr(var, 0, ft_index_of_c(var, '='));
        seconde_part = &envp[idx_str_in_env][ft_index_of_c(envp[idx_str_in_env], '=') + 1];
        printf("var %s and %s \n", first_part, seconde_part);
        int new_var_len = ft_strlen(first_part) + ft_strlen(seconde_part) + 2;
        new_var = malloc(sizeof(char) * new_var_len);
        if(!new_var)
            return(NULL);
        i = 0;
        j = 0;
        while (first_part[i])
        {
            new_var[j++] = first_part[i++];
        }
        new_var[j++] = '=';
        i = 0;
        while (seconde_part[i])
        {
            new_var[j++] = seconde_part[i++];
        }
        new_var[j] = '\0';
    }
    return(new_var);
}
int main(int argc, char **argv, char **envp)
{
    

    //run_minishell(envp);

    char *var = "Z1=$Z";

    char *new_var = export_var_expend(envp, var);
    printf("voici %s\n", new_var);
    return(0);
}
