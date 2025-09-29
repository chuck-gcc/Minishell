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
   
    if(!get_token_list(str, tokens_lst, *envp))
    {
        printf("Error token list\n");
        ft_lstclear(tokens_lst, delete_list);
        return(1);
    }

    ft_lstiter(*tokens_lst, display_args_of_cmd);

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
    //ft_lstiter(*tokens_lst, display_args_of_cmd);

    //int r = execute_ast(*ast, envp);

    ft_lstclear(tokens_lst, delete_list);
    free(ast);
    return(1);
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
            // if(!ft_strncmp(input,"exit", ft_strlen_longest(input,"exit")))
            // {
            //     free(input);
            //     clear_history();
            //     return(1);
            // }
            printf("voici le status %s\n", input);
            (void)process_user_input;
            int status = process_user_input(input, &envp);
            printf("STATUS COMMANDE %d\n\n", status);
            free(input);
            rl_on_new_line();
        }
    }
    return(0);
}

int main(int argc, char **argv, char **envp)
{
   
    //run_minishell(envp);

    int tube[2];
    int status;
    pid_t f;

    if(pipe(tube))
    {
        perror("Tube");
        return(1);
    }
    f = fork();
    if(f == -1)
    {
        perror("fork");
        return(1); 
    }
    else if(f == 0)
    {
        printf("we are in children\n");
        exit(11);
    }
    else
    {
        waitpid(f, &status, WUNTRACED | WCONTINUED);
        printf("im the parent children finish with status %d\n", status);
    }



    return(0);

}