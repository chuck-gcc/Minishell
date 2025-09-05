#include "tokeniser.h"

char *print_token_type(int token_type)
{
    if(token_type == CMD)
        return("COMMANDE");
    if(token_type == WORD)
        return("WORD");
    if(token_type == BUILTIN)
        return("BUILTIN");
    if(token_type == PIPE)
        return("PIPE");
    if(token_type == REDIR_LEFT)
        return("REDIR LEFT");
    if(token_type == REDIR_RIGHT)
        return("REDIR RIGHT");
    if(token_type == REDIR_APPEND)
        return("REDIR APPEND");
    if(token_type == DELIM)
        return("DELIM");
    return(NULL);
}

int ft_is_builtin(char *str)
{
    if
    (   !ft_strncmp(str, "echo", ft_strlen_longest(str, "echo")) ||
        !ft_strncmp(str, "cd", ft_strlen_longest(str, "cd")) ||
        !ft_strncmp(str, "pwd", ft_strlen_longest(str, "pwd")) ||
        !ft_strncmp(str, "export", ft_strlen_longest(str, "export")) ||
        !ft_strncmp(str, "unset", ft_strlen_longest(str, "unset")) ||
        !ft_strncmp(str, "env", ft_strlen_longest(str, "env")) ||
        !ft_strncmp(str, "exit", ft_strlen_longest(str, "exit")) 
    )
        return(1);
    else
        return(0);
}


//using opendir and readdir for check if value is commande
// looping inside th repository
int ft_is_commande(char *str)
{
    DIR *dir;
    int is_cmd;
    struct dirent *files;
    dir = opendir("/usr/bin");
    is_cmd = 1;
    if(dir == NULL)
        return(-1);
    while((files = readdir(dir)))
        if(!ft_strncmp(str,files->d_name, ft_strlen_longest(str,files->d_name)))
            is_cmd = 0;
        
    closedir(dir);
    return(is_cmd);
}

int get_token_type(char *str)
{
    if(ft_is_builtin(str))
        return(BUILTIN);
    if(!ft_is_commande(str))
        return(CMD);
    if(!ft_strncmp(str, "|", ft_strlen_longest(str, "|")))
        return(PIPE);
    if(!ft_strncmp(str, ">", ft_strlen_longest(str, ">")))
        return(REDIR_RIGHT);
    if(!ft_strncmp(str, "<", ft_strlen_longest(str, "<")))
        return(REDIR_LEFT);
    if(!ft_strncmp(str, ">>", ft_strlen_longest(str, ">>")))
        return(REDIR_APPEND);
    if(!ft_strncmp(str, "<<", ft_strlen_longest(str, "<<")))
        return(DELIM);
    return(WORD);
}

int get_precedence(int token_type)
{
    if(token_type == PIPE)
        return(3);
    if(token_type == CMD)
        return(2);
    else
        return(1);
}

int get_asso(int token_type)
{
    if(token_type == PIPE)
        return(3);
    if(token_type == CMD)
        return(2);
    else
        return(1);
}

void display_content_lst(void *liste)
{
    t_token *token;
    char *value;
    
    token = (t_token *)liste;
    value = token->value;

    printf("%-10s | %-15s | precedence: %-3d | asso: %-3d\n",value,
    print_token_type(token->type),
    token->precedence,
    token->asso);
}