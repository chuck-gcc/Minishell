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
    int fd;

    fd = open("file.txt",  get_ssredir_option(REDIR_APPEND));
    if(fd == -1){perror("fd"); return(1);}
    char buffer[1024];
    int r;
    while ((r = read(STDIN_FILENO,buffer, 1023))  > 0)
    {
        buffer[r] = '\0';
        write(fd, buffer, ft_strlen(buffer));
    }
    
    close(fd);

    return (0);
}