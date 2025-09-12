#include "builtin.h"

int ft_echo(t_token *token)
{
    int start;
    int return_line;

    start = 1;
    return_line = ft_strncmp(token->args[1], "-n", ft_strlen(token->args[1]));
    if(return_line == 0)
        start = 2;
    while(token && token->args[start])
        printf("%s ",token->args[start++]);
    if(return_line != 0)
        printf("\n");
    return(0);
}
