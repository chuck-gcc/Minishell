#include "ast.h"

char *get_path(char *str)
{
    char *path;
    char *base;
    int len_1;
    int len_2;
    int i;
    int j;

    if(!str)
        return(NULL);
    base = "/usr/bin/";
    len_1 = ft_strlen(base);
    len_2 = ft_strlen(str);
    i = 0;
    j = 0;
    path = malloc(sizeof(char *) * (len_1 + len_2 ) + 1);
    if(!path)
        return(NULL);
    while (base[i])
        path[j++] = base[i++];
    i = 0;
    while (str[i])
        path[j++] = str[i++];
    path[j] = '\0';
    return(path);
}


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
        (void)path;
        execve(path, token->args, envp);
        perror("Execution error");
        exit(errno);
    }
    else
    {
        wait(&status);
        printf("status %d\n", status);
    }
    return(status);
}


int execute_builtin(t_token *token, char **envp)
{
    if(!token)
        return(1);
    if(ft_strncmp(token->value, "cd", ft_strlen(token->value)) == 0)
        return(ft_cd(token));
    if(ft_strncmp(token->value, "env", ft_strlen(token->value)) == 0)
        return(ft_env(envp, envp));
    return(1);
}

int execute_ast(t_token *ast, char **envp)
{
    int status;
    int r;

    status = 0;
    if(!ast)
    {
        return(-1);
    }

    if(ast->type == PIPE)
    {
        pid_t pid =  fork();
        if(pid == -1)
        {
            perror("Fork error");
            return(errno);
        }
        else if(pid == 0)
        {
            
            printf("\ni am the children [PID: %d], my father is [PID: %d] \n\n", getpid(), getppid());
            execute_ast(ast->left, envp);

        }
        else
        {
            wait(&status);
            printf("\ni am  [PID: %d], the father of [PID: %d] i'm wating the status %d \n",getpid(),pid, status);
            exit(status);
        }
    }
    else if(ast->type == CMD)
    {
        char *path = get_path(ast->value);

        int r = execute_commande(ast, path, envp);
        printf("%s\n", path);
        free(path);
        return(r);
    }
    else if(ast->type == BUILTIN)
    {
        r = execute_builtin(ast, envp);
        return(r);
    }
    
    execute_ast(ast->right, envp);
    return(status);
}