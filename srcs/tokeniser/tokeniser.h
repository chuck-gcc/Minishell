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

#define CMD             1
#define WORD            2
#define BUILTIN         3
#define PIPE            4 //'|'
#define REDIR_LEFT      5 //'>'    
#define REDIR_RIGHT     6 //'<'
#define REDIR_APPEND    7 //'>>'
#define DELIM           8 //'<<'
#define VAR             9


typedef struct s_token
{
    int             num;
    int             type;
    int             precedence;
    int             asso;
    char            *value;
    char            **args;
    char            radir[2];
    struct s_token  *left;
    struct s_token  *right;

} t_token;


t_list  **get_token_list(char *str, t_list **lst);

int     ft_is_builtin(char *str);
int     ft_is_commande(char *str);
int     get_token_type(char *str);
char    *print_token_type(int token_type);
int     get_asso(int token_type);
int     get_precedence(int token_type);
void display_content_lst(void *liste);
# endif