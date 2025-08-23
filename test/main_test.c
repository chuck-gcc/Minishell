#include "../srcs/main.h"



int ft_fork()
{
    pid_t f;
    int fds[2];
    int status;
    char buffer[10];
    


    status = 0;
    pipe(fds);
    f = fork();
    if(f == 0)
    {
        printf("We are in children %d\n", getpid());
        printf("Send message to the parent %d\n", getppid());
        close(fds[0]);
        write(fds[1], "hello\n", ft_strlen("hello\n"));
        close(fds[1]);
        exit(0);
    }
    int b;
    close(fds[1]);
    b = read(fds[0], buffer, 10);
    if(b == 0)
        printf("Nothing to read\n");
    else if (b == -1)
        perror("Err");
    close(fds[0]);
    printf("Bytes read : %d\n", b);
    printf("We are in parent %d the message of children:%d:  %s\n", getpid(),f, buffer);
    waitpid(f,&status,0);

    return(0);
}


int main()
{

    ft_fork();
    return(0);
}