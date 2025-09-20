#include "builtin.h"

int ft_unset(char ***envp, t_token *token)
{
    //char    **new_env;
    size_t valide_variable;

    if(!envp || !*envp || !token)
        return(-1);
    valide_variable = count_valide_variable(&token->args[1], UNSET);
    (void)valide_variable;
    return(0);
}