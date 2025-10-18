#include "ast.h"

void destroy_token(t_token **tk)
{
    t_token *token; 

    token = *tk;
    if(token)
    {
        if(token->value)
        {
            free(token->value);
            token->value = NULL;
        }
        if(token->args)
        {
            char **tmp;

            tmp = token->args;
            while (*tmp)
            {
                free(*tmp);
                *tmp = NULL;
                tmp++;
            }
            free(token->args);
            token->args = NULL;
        }
        if(token->radir[0])
        {
            free(token->radir[0]);
            token->radir[0] = NULL;
        }
        if(token->radir[1])
        {
            free(token->radir[1]);
            token->radir[1] = NULL;
        }
        free(*tk);
        *tk = NULL;
    }
}
int execute_commande(t_token *token, char *path, char **envp)
{
    //int     tube[2];
    int status;

    status = 0;
    // if(open_redirection(token))
    // {
    //     pid_t g = execute_heredoc(token, tube, envp);
    //     waitpid(g,&status, 0);
    //     close(tube[1]);
    // }
    // else
    //     printf("no redirection\n");
    pid_t f1 = fork();
    if(f1 == -1) { perror("fork"); return (-1);}
    if(f1 == 0)
    {
        execve(path, token->args, envp);
        perror("Execution error");
        exit(errno); 
    }
    waitpid(f1,&status, 0);
    if(WIFEXITED(status))
        printf("process terminé avec succes\n");
    else
    {
        printf("Error %d\n", WIFEXITED(status));
        return(status);
    }
    return(status);
}


int execute_builtin(t_token *token, char ***envp)
{
    if(!token)
        return(1);
    if(ft_strncmp(token->value, "cd", ft_strlen(token->value)) == 0)
        return(ft_cd(token));
    if(ft_strncmp(token->value, "env", ft_strlen(token->value)) == 0)
        return(ft_env(*envp, *envp));
    if(ft_strncmp(token->value, "pwd", ft_strlen(token->value)) == 0)
        return(ft_pwd());
    if(ft_strncmp(token->value, "echo", ft_strlen(token->value)) == 0)
        return(ft_echo(token));
    if(ft_strncmp(token->value, "export", ft_strlen(token->value)) == 0)
        return(ft_export(envp,token));
    if(ft_strncmp(token->value, "unset", ft_strlen(token->value)) == 0)
        return(ft_unset(envp,token));
    if(ft_strncmp(token->value, "exit", ft_strlen(token->value)) == 0)
        ft_exit();
    return(1);
}

int      execute_ast(t_token *ast, char ***envp)
{
    int status;

    if(!ast)
        return(0);
        
    status = 0;
    if(ast->type == PIPE)
    {
        int tube[2];

        if(pipe(tube) == -1) {perror("fork"); return (-1);}
        pid_t f1 = fork();
        if(f1 == -1) { perror("fork"); return (-1);}
        if(f1 == 0)
        {
            close(tube[0]);
            dup2(tube[1],STDOUT_FILENO);
            close(tube[1]);
            exit(execute_ast(ast->left, envp));
        }

        pid_t f2 = fork();
        int status2 = 0;
        if(f2 == -1) { perror("fork"); return (-1);}
        if(f2 == 0)
        {
            close(tube[1]);
            dup2( tube[0], STDIN_FILENO);
            close(tube[0]);
            exit(execute_ast(ast->right, envp));
        }
        close(tube[0]);
        close(tube[1]);
        waitpid(f1,&status, 0);
        waitpid(f2,&status2, 0);
        printf("fork finished\n");
        return (status);
    }
    if(ast->type == BUILTIN)
    {
        int r = execute_builtin(ast, envp);
        return(r);
    }
    else if(ast->type == CMD)
    {
        printf("voici %s\n", ast->value);
        char *path = get_path(ast->value);
        if(!path)
            return(-1);
        
        int r = execute_commande(ast, path, *envp);
        return(r);
    }
    return (0);
}