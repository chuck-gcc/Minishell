
#include "tokeniser.h"


t_token *new_node(char *str, int num)
{
    t_token *new_node;

    new_node = malloc(sizeof(t_token));
    if(!new_node)
        return(NULL);
    new_node->num = num;
    new_node->value = ft_strdup(str);
    new_node->type = get_token_type(str);
    new_node->precedence = get_precedence(new_node->type);
    new_node->asso= get_asso(new_node->type);
    new_node->args = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return(new_node);
}

static int count_args(char **input)
{
    int i;

    if(!input || !*input)
        return(-1);
    i = 0;
    while (get_token_type(input[i]) == WORD)
    {
        i++;
    }
    return(i);
}

static int is_redir(char *str)
{
    if(!str)
        return(-1);
    if(!ft_strncmp(str, "<", ft_strlen(str)))
        return(1);
    if(!ft_strncmp(str, ">", ft_strlen(str)))
        return(2);
    if(!ft_strncmp(str, ">>", ft_strlen(str)))
        return(3);

    return(0);
}

// static int redir_check_validity(char **intput)
// {
//     int i;

//     i = 0;
//     while (get_token_type(intput[i]) == WORD)
//     {
//         i++;
//     }
//     if(i < 1)
//     {
//         printf("syntax error near unexpected token \n");
//         return(0);
//     }
//     else
//         return(1);
// }

int get_args(t_list *node, char **input)
{
    int i,idx, args_count;
    char **args;

    i = 0;
    idx = 0;
    args_count = count_args(input);
    if(args_count)
    {
        args = malloc(sizeof(char *) * (args_count + 1));
        if(!args)
        {
            perror("Error malloc:");
            return(-1);
        }
        while (get_token_type(input[idx]) != PIPE && !is_redir(input[idx]))
        {
            args[i] = ft_strdup(input[idx]);
            i++;
            idx++;
        }
        args[i] = NULL;
        ((t_token *)node->content)->args = args;
        //printf("we have proceced the args for the commande :%s\n",((t_token *)node->content)->value);
        return(idx);
    }
    else
    {
        return(0);
    }
}



static int get_redir(t_list *node, char **input)
{
    int idx;
    int redir_type;
    char *redir;
    char *redir_arg;
    
    idx = 0;
    if(get_token_type(input[idx + 1]) == PIPE)
    {
        printf("bash: syntax error near unexpected token `|'\n");
        return(-1);
    }
    redir_type = is_redir(input[idx + 1]);
    if (redir_type)
    {
        printf("bash: syntax error near unexpected token `%s'\n", input[idx]);
        return(-1);
    }
    redir = ft_strdup(input[idx]);
    if(!redir)
        return(-1);
    ((t_token *)node->content)->radir[0] = redir;
    idx += 1;
    while (get_token_type(input[idx]) == WORD)
    {
        idx++;
    }
    redir_arg = ft_strdup(input[idx - 1]);
    if(!redir_arg)
    {
        free(redir);
        redir = NULL;
        return(-1);
    }
    ((t_token *)node->content)->radir[1] = redir_arg;
    //printf("we have proceced the redir %s for the commande :%s\n",((t_token *)node->content)->radir[0], ((t_token *)node->content)->value);
    return(idx);
}

t_list **get_token_list(char *str, t_list **lst)
{
    int i;
    char    **split;
    t_list  *node;

    i = 0;
    split = ft_split(str, 32);
    if(!split)
        return(NULL);
    while (split[i])
    {
        if(get_token_type(split[i]) == CMD)
        {
            node = malloc(sizeof(t_list));
            if(!node)
                return(ft_split_clean(&split));
            node->content = new_node(split[i], i);
            i++;

            int r = get_args(node, &split[i]);
            if(r == -1)
                return(ft_split_clean(&split));
            //assert(r == 1);
            i += r;

            if(is_redir(split[i]))
                i += get_redir(node, &split[i]);
            if(r == -1)
                return(ft_split_clean(&split));
            //assert(i == 5);
            (void)get_redir;
        }
        else
        {
            node = malloc(sizeof(t_list));
            if(!node)
                return(ft_split_clean(&split));
            node->content = new_node(split[i], i);
            i++;
        }
        
        //error simulation
        // if(i == 2)
        // {
        //     free(((t_token *)node->content)->value);
        //     ((t_token *)node->content)->value = NULL;
        //     free(node->content);
        //     node->content = NULL;
        // }
        node->next = NULL;
        if(node->content == NULL)
            return(ft_split_clean(&split));
        ft_lstadd_back(lst, node);
    }
    ft_split_clean(&split);
    return(lst);
}

