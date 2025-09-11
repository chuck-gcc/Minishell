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

    // printf("\n\n");
    //  ft_lstiter(*tokens_lst, display_content_lst);
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

    display_binary_tree(NULL,*ast,0);
    ft_lstiter(*tokens_lst, display_args_of_cmd);

    int r = execute_ast(*ast);

    ft_lstclear(tokens_lst, delete_list);
    free(ast);
    return(r);
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
            int status = process_user_input(input);
            printf("STATUS COMMANDE %d\n", status);
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

    run_minishell(envp);

    //char *cmd = "cat cat fefazzea fafa < out.txt dzadaz | grep grep | wc -l > out.txt";
    //char *cmd = "cat < infile.txt | grep error | sort -r > outfile.log";
    //char *cmd = "sort -u < unsorted.txt | grep error | tee result.log >> all.log";
    //char *cmd = "cat < file.txt | grep banana | wc -l >> file.log";
    //char *cmd = "echo hello world | echo hello";


    //printf("Commande: %s\n\n", cmd);

    //process_user_input(cmd);
    
    

    // pid_t pid;
    // int st;

    // pid = fork();
    // st = 11;
    // if(pid == -1)
    // {
    //     perror("Fork error");
    //     return(errno);
    // }
    // if(pid == 0)
    // {
    //     char *args[] = {"echo", "hello", "world", NULL};
    //     execve("/usr/bin/echo", args, NULL);
    //     perror("Execution error");
    //     exit(errno);
    // }
    // else
    // {

    //     wait(&st);
    //     printf("status %d\n", st);
    // }
    return(0);
}
