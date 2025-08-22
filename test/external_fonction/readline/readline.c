#include "readline.h"

int ft_readline(void)
{

    char *line;

    while (1)
    {
        line = readline();
        if(line)
            printf("%s\n", line);
        else
            return (2);
    }
    return(0);
}