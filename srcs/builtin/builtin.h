# ifndef BUILTIN_H
#define BUILTIN_H

#include "../../libft/libft.h"
#include "../main.h"


int ft_env(char **envp, char **var);
int ft_cd(t_token *token);
int ft_pwd(void);
int ft_echo(t_token *token);



int ft_export(char ***envp, t_token *token);
char *export_var_expend(char **envp, char *var);
int is_on_env(char *var, char **env, int idx);
#endif