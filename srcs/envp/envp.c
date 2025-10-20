#include "envp.h"

static void print_env(struct s_env_manager *self){return(ft_split_print(*(self->env)));}

static int destroy_env(struct s_env_manager *self)
{
    ft_split_clean(self->env);
    free(self);
    return(0);
}

static int dup_env(struct s_env_manager *self ,char **old)
{
    int i;
    int len_env;
    char **new_env;

    len_env = ft_get_split_len(old);
    if(!len_env)
        return(1);
    if(self->start)
        ft_split_clean(self->env);
    new_env = malloc(sizeof(char *) * (len_env + 1));
    if(!new_env)
        return(1);
    i = 0;
    while (old[i])
    {
        new_env[i] = ft_strdup(old[i]);
        i++;
    }
    new_env[i] = NULL;
    *self->env = new_env;
    if(!self->start)
        self->start = 1;
    return(0);
}

int swap_env(t_env *self, char **new_env)
{
    char ***tmp;

    if(!self || !(*self->env) || !new_env)
        return(1);
    tmp = self->env;
    *self->env = new_env;
    ft_split_clean(tmp);
    printf("environnement swapper avec succes\n");
    self->print_env(self);
    return(0); 
}

t_env *init_env(char **envp)
{
    t_env *self;

    self = malloc(sizeof(t_env));
    if(!self)
        return(NULL);
    ;
    if((self->env = malloc(sizeof(char **))) == NULL)
    {
        free(self);
        return(NULL);
    }
    self->start = 0;
    self->swap_env = swap_env;
    self->dup_env = dup_env;
    self->print_env = print_env;
    
    self->destroy_env = destroy_env;
    if(self->dup_env(self, envp) == 1)
    {
        free(self);
        return(NULL);
    }
    else
        printf("Environnement initialisé avec succes\n");
    return(self);
}

