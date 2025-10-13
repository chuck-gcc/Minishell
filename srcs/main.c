#include "main.h"
 #include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int execute_heredoc(t_token *ast, char *delim, char **envp)
{
    if(!ast)
        return(1);
    if(ast->radir[0] && ft_strncmp(ast->radir[0], "<<", ft_strlen(ast->radir[0]) ) == 0)
    {
        printf("here %s\n", ast->radir[0]);

        int tube[2];
        pid_t pid;
        int status;

        if(pipe(tube) == -1) {perror("pipe"); return(1);}
        pid = fork();
        if(pid == -1){perror("fork"); return(1);}
        else if (pid == 0)
        {
            char buffer[1024];
            int b_read;

            close(tube[0]);
            dup2(tube[1], STDIN_FILENO);
            do
            {
                b_read = write(tube[1], buffer, 1024);
                if(b_read == -1)
                {
                    perror("read");
                    return(1);
                }
                if(ft_index_of_c(buffer, 32) == -1)
                {
                    printf("one word %s et delim %s\n", buffer,delim);
                    if(ft_strncmp(buffer, delim, ft_strlen_longest(buffer, delim)) == 0)
                    {
                        ft_memset(buffer, 0, 1024);
                        exit(0);
                    }
                }
                ft_memset(buffer, 0, 1024);
            } while (b_read > 0);
            
            
            exit(errno);
        }
        else
        {
            char buf[1024];
            close(tube[1]);
            while (read(tube[0], buf, 1024) > 0)
            {
                if(ft_strlen(buf) > 0)
                    printf("voici %s\n", buf);
            }
            
            

            waitpid(pid, &status, 0);
            
            

            printf("voici status %d\n", status);
            if(WIFEXITED(status))
                printf("processur enfqnt terminer avec un code=%d\n", WEXITSTATUS(status));
            if(WIFSIGNALED(status))
                printf("processur enfqnt tuer par un signal\n");
            if(WIFSTOPPED(status))
                printf("processur enfqnt stoper par un signal\n");

        }
        

        return(1);
    }
    return(0);
}

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

    printf("\n");
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
    printf("\n");

    //int r = execute_ast(*ast, envp);
    int r = execute_heredoc(*ast, "n\n",*envp);
    // important know
    
    ft_lstclear(tokens_lst, delete_list);
    free(ast);
    return(r);
}


int run_minishell(char **envp)
{
    char *input;

    while (1)
    {
        input = readline("mini michel: ");
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
            //printf("voici le status %s\n", input);
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

    

    run_minishell(envp);
    
    return(0);
}