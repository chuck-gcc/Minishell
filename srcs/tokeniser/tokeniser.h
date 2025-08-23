# ifndef TOKENISER_H
# define TOKENISER_H

#include<stdio.h>
#include <dirent.h>
#include "../../libft/libft.h"

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

#define CMD             0
#define word            1
#define BUILTIN         2
#define PIPE            3 //'|'
#define REDIR_LEFT      4 //'>'    
#define REDIR_RIGHT     5 //'<'
#define REDIR_APPEND    6 //'>>'
#define DELIM           7 //'<<'
#define variable        8


typedef struct s_token
{
    int             type;
    char            *value;
    int             precedence;
    struct s_token *next;

} t_token;


t_list **get_token_list(char *str, t_list **lst);
void    delete_list(void *content);
void    display_content_lst(void *liste);
int ft_is_builtin(char *str);
int ft_is_commande(char *str);
int get_token_type(char *str);

# endif