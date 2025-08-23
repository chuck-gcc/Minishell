# ifndef TOKENISER_H
# define TOKENISER_H

#include<stdio.h>
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

#define cmd             0
#define word            1
#define builtin         2
#define pip            3
#define redirection_l   4    
#define redirection_r   5
#define redirection_ra  6
#define single_quote    7
#define double_quote    8
#define variable        9


typedef struct s_token
{
    int             type;
    char            *value;
    int             precedence;
    struct s_token *next;

} t_token;


t_list  **get_token_list(char *str);
void    delete_list(void *content);
void    display_content_lst(void *liste);

# endif