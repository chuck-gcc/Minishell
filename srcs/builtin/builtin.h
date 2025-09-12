# ifndef BUILTIN_H
#define BUILTIN_H

#include "../../libft/libft.h"
#include "../main.h"


int ft_env(char **envp, char **var);
int ft_cd(t_token *token);
int ft_pwd(void);
int ft_echo(t_token *token);

#endif