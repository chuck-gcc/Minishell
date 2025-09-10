#include "tokeniser.h"

void delete_list(void *content)
{
    t_token *token = (t_token *)content;

    if(token)
    {
        if(token->value)
        {
            free(token->value);
            token->value = NULL;
        }
        if(token->args)
        {
            char **tmp;

            tmp = token->args;
            while (*tmp)
            {
                free(*tmp);
                *tmp = NULL;
                tmp++;
            }
            free(token->args);
            token->args = NULL;
        }
        if(token->radir[0])
        {
            free(token->radir[0]);
            token->radir[0] = NULL;
        }
        if(token->radir[1])
        {
            free(token->radir[1]);
            token->radir[1] = NULL;
        }
        free(token);
        token = NULL;
    }
    
}