#include "readline.h"

int main(void)
{

    char *line;

    while (1)
    {
        line = readline("voici le prompt\n");
        if(line)
            printf("%s\n", line);
        else
            return (2);
    }
    return(0);
}