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

int main(int argc, char **argv, char **envp)
{
    t_token token_1;
    t_token token_2;
    t_token token_3;

    char *cmd[] = {"export", "Z=1","Z2=2","Z3=3", NULL};
    char *cmd_2[] = {"export", "Z=4","Z2=5","Z3=6", NULL};

    char **env;

    env = malloc(sizeof(char **) * 4);
    if(!env)
        return(1);
    env[0] = "A=1";
    env[1] = "B=2";
    env[2] =  "C=3";
    env[3] = NULL;



    token_1.type = BUILTIN;
    token_1.value = "export";
    token_1.args = cmd;
    
    token_2.type = BUILTIN;
    token_2.value = "export";
    token_2.args = NULL;

    token_3.type = BUILTIN;
    token_3.value = "export";
    token_3.args = cmd_2;

    ft_export(&env, &token_1);
    ft_export(&env, &token_2);
    ft_export(&env, &token_3);
    ft_export(&env, &token_2);
    (void)token_2;
    (void)token_1;

    // assert(is_on_env("Z=1", envp, ft_get_split_len(envp)) != -1);
    // assert(is_on_env("Z1=1", envp, ft_get_split_len(envp)) == -1);
    // assert(is_on_env("Z2=1", envp, ft_get_split_len(envp)) == -1);
    //run_minishell(envp);
    return(0);

}