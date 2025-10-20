#include "../srcs/main.h"
#include <errno.h>
#include <assert.h>


typedef struct s_env_manager
{
    char **env;
    int   start;

    int  (*dup_env)(struct s_env_manager *self ,char **new);
    int  (*destoy)(struct s_env_manager *self);
    void  (*print_env)(struct s_env_manager *self);

} t_env;

void print_env(struct s_env_manager *self){return(ft_split_print(self->env));}

int destroy(struct s_env_manager *self)
{
    ft_split_clean(&self->env);
    free(self);
    return(0);
}

int dup_env(struct s_env_manager *self ,char **old)
{
    int len_env;
    int i;
    len_env = ft_get_split_len(old);
    if(!len_env)
        return(1);
    if(self->start)
    {
        ft_split_clean(&self->env);
    }
    self->env = malloc(sizeof(char *) * (len_env + 1));
    if(!self->env)
        return(1);
    i = 0;
    while (old[i])
    {
        self->env[i] = ft_strdup(old[i]);
        i++;
    }
    self->env[i] = NULL;
    if(!self->start)
        self->start = 1;
    return(0);
}


int main(int argc, char **argv,char **envp)
{
    (void)argc;
    (void)argv;

    t_env *self;

    self = malloc(sizeof(t_env));
    if(!self)
        return(1);
    self->env = NULL;
    self->start = 0;
    self->dup_env = dup_env;
    self->print_env = print_env;
    self->destoy = destroy;

    int r = self->dup_env(self, envp);
    assert(r == 0);
    
    char *h[] = {"hekdza","fezfz","gzrgz", NULL};
    r = self->dup_env(self, h);
    
    
    r = self->dup_env(self, envp);
    r = self->dup_env(self, h);
    r = self->dup_env(self, envp);
    r = self->dup_env(self, h);

    r = self->destoy(self);

    return (0);
}