#include "main.h"
 #include <sys/stat.h>
#include <stdio.h>
#include <string.h>

static int process_user_input(char *str)
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

    printf("\n\n");
     ft_lstiter(*tokens_lst, display_content_lst);
    printf("\n\n");
    ft_lstiter(*tokens_lst, display_arg_of_cmd);
    ft_lstclear(tokens_lst, delete_list);
    return(0);
}


int run_minishell(char **envp)
{
    char *input;

    (void)envp;
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
            process_user_input(input);
            free(input);
            rl_on_new_line();
        }
    }
    return(0);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;

    //run_minishell(envp);

    char *cmd = "cat cat fefazzea fafa < out.txt dzadaz | grep grep | wc -l > out.txt";
    //char *cmd = "cat < infile.txt | grep error | sort -r > outfile.log";
    //char *cmd = "sort -u < unsorted.txt | grep error | tee result.log >> all.log";

    printf("Commande: %s\n", cmd);
    process_user_input(cmd);
    return(0);
}
