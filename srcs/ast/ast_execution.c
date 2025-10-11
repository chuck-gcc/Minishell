#include "ast.h"

char *get_os(void)
{
    int tube[2];
    char os[100];
    int status;
    int i;
    i = 0;
    if(pipe(tube) == -1) {perror("pipe"); return (NULL);}
    pid_t f;

    f = fork();
    if(f == -1) {perror("fork"); return(NULL);}
    if(f == 0)
    {
        close(tube[0]);
        dup2(tube[1], STDOUT_FILENO);
        close(tube[1]);
        char *argv[] = { "uname", NULL};
        if(execve("/usr/bin/uname", argv, NULL) == -1){perror("excve");exit(errno);}
    }
    else
    {
        close(tube[1]);
        waitpid(f,&status,0);
        if(( i = read(tube[0], os, 100)) == -1)
            printf("Error wirte\n");
        os[i - 1] = '\0';
        close(tube[0]);
    }
    return(ft_strdup(os));
}

char *get_base(char *str)
{
    char *os;

    os = get_os();
    if(os && !ft_strncmp(os,"Linux", ft_strlen(os)))
    {
        free(os);
        return(ft_strdup("/usr/bin/"));
    }
    else if( !ft_strncmp(os, "Darwin", ft_strlen(os)))
    {
        return(NULL);
    }
    return(os);
}

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
    //if mac os
    base = get_base(str);
    if(!base)
        return(NULL);
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
        printf("voici path %s\n", path);
        execve(path, token->args, envp);
        perror("Execution error");
        exit(errno);
    }
    else
    {
        wait(&status);
        //printf("status %d\n", status);
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

int execute_ast(t_token *ast, char ***envp)
{
    int status;

    printf("voici ast type %s\n", print_token_type(ast->type));
    status = 0;
    if(!ast)
        return(-1);

    if(ast->type == PIPE)
    {
        int tube[2];

        if(pipe(tube) == -1)
        {
            perror("pipe");
            return(errno);
        }
        pid_t pid =  fork();
        if(pid == -1)
        {
            perror("Fork error");
            return(errno);
        }
        else if(pid == 0)
        {
            close(tube[0]);
            if(dup2(tube[1], STDOUT_FILENO) == -1)
            {
                perror("dup");
                return(errno);
            }
            close(tube[1]);
            execute_ast(ast->left, envp);
            exit(0);
        }
        else
        {
            waitpid(pid, &status,0);
            close(tube[1]);
            execute_ast(ast->right, envp);
            return(status);
        }
    }
    printf("\ni am the fork [PID: %d], my father is [PID: %d] \n\n", getpid(), getppid());

    if(ast->type == CMD)
    {
        printf("we are in commande\n");
        char *path = get_path(ast->value);
        status = execute_commande(ast, path, *envp);
        free(path);
        exit(status);
    }
    else if(ast->type == BUILTIN)
    {
        printf("we are in buitltin\n");
        status = execute_builtin(ast, envp);
        return(status);

    }
    return(status);
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
            int saved_stdin = dup(STDIN_FILENO);
            int saved_stdout = dup(STDOUT_FILENO);
            waitpid(f, &status, 0);
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