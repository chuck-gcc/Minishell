#include "../srcs/main.h"
#include <errno.h>
#include <assert.h>


int get_ssredir_option(int redir_type)
{
    if(redir_type == REDIR_RIGHT)
        return(O_WRONLY);
    if(redir_type == REDIR_APPEND)
    {
        printf("voici %d\n", O_APPEND);
        return(O_WRONLY | O_APPEND);
    }
    if((redir_type == REDIR_LEFT) | (redir_type == DELIM))
        return(O_RDONLY);
    return(-1);
}

int main(int argc, char **argv,char **envp)
{
    printf("voici la fonction test main\n");
    int tube[2];
    pid_t pid;
    int status;

    if(pipe(tube) == -1){perror("tube"); return (errno);}
    pid = fork();
    if(pid == -1){perror("test"); return(1);}
    if (pid == 0)
    {
        close(tube[0]);
        char *r;
        while ((r = readline("heredoc>")) != NULL)
        {
            if(ft_strncmp(r, "t", ft_strlen(r) - 1) == 0)
                exit(0);
            else
            {
                write(tube[1], r, ft_strlen(r));
                write(tube[1], "\n", ft_strlen("\n"));
            }
        }
        
    }
    else
    {   
        waitpid(pid, &status, 0);
        if(WIFEXITED(status))
        {
            int r;

            close(tube[1]);
            char buffer[1024];
            while ((r = read(tube[0],buffer, 1023)) > 0)
            {
                buffer[r] = '\0';
                printf("%s", buffer);
            }
            close(tube[0]);
        }


    }
    return (0);
}