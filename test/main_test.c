#include "../srcs/main.h"
#include <errno.h>
#include <assert.h>

int err2(int r,const char *fonction, char *module)
{
    printf("[ fonction : %s ][ module : %s ] Err :%s\n",fonction,module,strerror(r));
    return(r);
}


int ft_fork()
{
    int fds[2];
    pid_t pid;
    int status;
    
    pipe(fds);
    printf("voici fd 0 : %d et fd 1 %d\n", fds[0], fds[1]);
    pid = fork();
    if(pid == 0)
    {
        printf("%d\n", isatty(fds[1]));
        close(fds[0]);
        dup2(STDOUT_FILENO, fds[1]);
        char *arg[] = {"/usr/bin/cat", "file.txt"};
        execve(arg[0], arg, NULL);
                
    }

    close(fds[1]);
    dup2(fds[0], STDOUT_FILENO);

    waitpid(pid, &status, 0);
    return(0);
}


int main()
{

    ft_fork();
    return(0);
}