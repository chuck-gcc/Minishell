#include "main.h"
 #include <sys/stat.h>
#include <stdio.h>
#include <string.h>

// static int process_user_input(char *str)
// {

    
//     t_list **tokens_lst;

//     tokens_lst = calloc(sizeof(t_list *) , 1);
//     if(!tokens_lst)
//         return(1);
   
    
//     if(!get_token_list(str, tokens_lst))
//     {
//         printf("Error token list\n");
//         ft_lstclear(tokens_lst, delete_list);
//         return(1);
//     }

//     printf("\n\n");
//      ft_lstiter(*tokens_lst, display_content_lst);
//     printf("\n\n");
//     ft_lstiter(*tokens_lst, display_arg_of_cmd);
//     ft_lstclear(tokens_lst, delete_list);
//     return(0);
// }


int run_minishell(char **envp)
{
    //char *input;
    char *env[3] = {"Z=1", "Zfz", NULL};
    ft_env(envp, env);

    while (1 == 2)
    {
        
        // input = readline("minishell: ");
        // if(input)
        // {
        //     if(*input)
        //         add_history(input);
        //     if(!ft_strncmp(input,"exit", ft_strlen_longest(input,"exit")))
        //     {
        //         free(input);
        //         clear_history();
        //         return(1);
        //     }
        //     //process_user_input(input);
        //     free(input);
        //     rl_on_new_line();
        //}
    }
    return(0);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    run_minishell(envp);
    return(0);
}
