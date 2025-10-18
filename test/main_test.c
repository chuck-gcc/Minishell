#include "../srcs/main.h"
#include <errno.h>
#include <assert.h>

int err2(int r, const char *fonction, char *module)
{
    printf("[ fonction : %s ][ module : %s ] Err :%s\n", fonction, module, strerror(r));
    return (r);
}

int ft_fork()
{
    int i;
    int status;
    pid_t pid;

    i = 0;
    status = 0;
    while (i < 10)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("ft_fork");
            return (1);
        }
        if (pid == 0)
        {
            printf("voici le pid du process parent%d\n", getppid());
            printf("voici le pid du process enfant %d\n", getpid());
            if(i == 3)
                exit(20);
            exit(0);    
        }
        else
        {
            i++;
            waitpid(pid, &status, 0);
            printf("fin des process number: %d enfrant %d whith status %d\n",i, pid, WEXITSTATUS(status));
        }
        
    }

    return (0);
}

int main()
{

    ft_fork();
    return (0);
}