#include "tokeniser/tokeniser.h"
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/resource.h>
 #include <sys/types.h>
#include <sys/time.h>
/* 
    TOKEN:

        *command
        *arg
        *builtin
        *pipe
        *redirection left
        *redirection right
        *single quote
        *double cote
        *word
*/



int main(void)
{

    int fd;
    int dup_stdout = dup(STDOUT_FILENO);

    fd =  open("test.txt",O_CREAT | O_TRUNC |O_WRONLY,0755);
    if(fd == - 1)
        return(printf("Error open file"));

    printf("this whill be append in console\n");
    int dp = dup(fd);
    if(dp == -1)
        return(printf("Error Duplicate file\n"));
    
    write(dp,"this whilsl be append in file\n", strlen("this whilsl be append in file\n"));
    fflush(stdout);
    
    dup2(dup_stdout, STDOUT_FILENO);
    close(dp);
    write(dp,"this whilsl be append in file\n", strlen("this whilsl be append in file\n"));


    char *path;
    struct rusage ru;
    char *argv[] = {"/usr/bin/echo","hello world"};
    pid_t pid;

    pid = fork();
    if(pid == 0)
    {
        path = "/usr/bin/echo";
        int ex = execve(path,argv, NULL);
        if(ex == -1)
            printf(" [Execusion error] %d\n",ex);
        exit(1);
    }
    else
    {
        int status1;
        int status2;

        status1 = 0;
        status2 = 0;
        
        wait3(&status1,0, &ru);

        printf("ovici ru %p\n", ru.);
    }
    return(0);
}