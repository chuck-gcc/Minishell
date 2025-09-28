
#include "builtin.h"

void ft_exit()
{
    pid_t pid;

    pid = getpid();

    printf("nous somme dans le pid %d\n", pid);
}