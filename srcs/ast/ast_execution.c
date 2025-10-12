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
    pid_t   pid;
    int     status;

    pid = fork();
    status = 0;
    if(pid == -1)
    {
        perror("Fork error");
        return(errno);
    }
    if(pid == 0)
    {
        //printf("voici path %s\n", path);
        execve(path, token->args, envp);
        perror("Execution error");
        exit(errno);
    }
    else
    {
        waitpid(pid, &status, 0);
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

int execute_ast_test(t_token *ast, char ***envp)
{
    int status;

    if(!ast)
        return(0);
        
    status = 0;
    if(ast->type == PIPE)
    {
        int tube[2];
        if(pipe(tube) == -1) {perror("fork"); return (-1);}
        pid_t f = fork();
        if(f == -1) { perror("fork"); return (-1);}
        if(f == 0)
        {
            close(tube[0]);
            dup2(tube[1], STDOUT_FILENO);
            close(tube[1]);
            int r = execute_ast_test(ast->left, envp);
            exit(r) ;
        }
        else
        {
            
            waitpid(f, &status, 0);
            int saved_stdin = dup(STDIN_FILENO);
            int saved_stdout = dup(STDOUT_FILENO);
            close(tube[1]);
            dup2(tube[0], STDIN_FILENO);
            close(tube[0]);
            execute_ast_test(ast->right, envp);
            dup2(saved_stdin, STDIN_FILENO);
            dup2(saved_stdout, STDOUT_FILENO);
            return (status);
        }
    }
    if(ast->type == BUILTIN)
    {
        execute_builtin(ast, envp);
        return(0);
    }
    else if(ast->type == CMD)
    {
        char *path = get_path(ast->value);
        if(!path)
            return(-1);
        execute_commande(ast, path, *envp);
        return(0) ;
    }
    return (0);
}