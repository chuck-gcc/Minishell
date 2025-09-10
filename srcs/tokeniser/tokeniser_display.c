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

void display_arg_of_cmd(void *liste)
{
    t_token *token;
    
    token = (t_token *)liste;
    if(token->type == CMD || token->type == BUILTIN)
    {
        printf("Commande: [%s]\n", token->value);
        int i = 0;
        printf("Args: ");
        while (token->args[i])
        {
            printf("[%s]", token->args[i]);
            i++;
        }
        printf("\n");
        printf("Redir: ");
        printf("[%s]", token->radir[0]);
        printf("[%s]", token->radir[1]);
        printf("\n");
    }
    printf("\n");
}
