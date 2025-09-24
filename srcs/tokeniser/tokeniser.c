
#include "tokeniser.h"

char *expend_var(char *str, char **envp)
{
    char *var;


    if(ft_index_of_c(str, '$') == -1)
        return(ft_strdup(str));
    var = &str[ft_index_of_c(str, '$') + 1];
    printf("voici %s\n", var);
    assert(1==2);
    return(var);
    
}

static t_token *new_token_node(char *str, int num, int precedent_token, char **envp)
{
    t_token *new_node;

    new_node = malloc(sizeof(t_token));
    if(!new_node)
        return(NULL);
    new_node->num = num;
    new_node->value = ft_strdup(str);
    new_node->type = get_token_type(str);
    if((new_node->type == CMD && precedent_token == CMD && num != 0 )
        || (new_node->type == BUILTIN && precedent_token == BUILTIN && num != 0))
        new_node->type = WORD;
    new_node->precedence = get_precedence(new_node->type);
    new_node->asso= get_asso(new_node->type);
    new_node->args = NULL;
    new_node->radir[0] = NULL;
    new_node->radir[1] = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return(new_node);
}

static t_list *new_list_node(char *str, int i, char *precedent, char **envp)
{
    t_list *node;

    node = malloc(sizeof(t_list));
    if(!node)
        return(NULL);
    node->content = new_token_node(str, i, get_token_type(precedent), envp);
    if(node->content == NULL)
            return(NULL);
    node->next = NULL;
    return(node);
}

 static int process_cmd_node(t_list *node, char **input, char **envp)
{
    int i;
    int r; 
    int rdir; 
    
    i = 0;
    r = get_args(node, input, envp);
    if(r == -1)
    {
        printf("error get arg\n");
        return(-1);
    }
    i += r ;
    if(is_redir(input[i]) > 0)
    {
        rdir = get_redir(node, &input[i]);
        if(rdir == -1)
        {
            printf("error get redir\n");
            return(-1);
        }
        else
            i += rdir;
    }
    return(i + 1);
}

static int process_node(t_list *node_lst, char **input, char **envp)
{
    int process;
    t_token *node;


    node = ((t_token *)(node_lst->content));
    process = 0;
    if(!input)
        return(1);
    if(node->type == CMD || node->type == BUILTIN)
    {
        process = process_cmd_node(node_lst, (input + 1), envp);
        if(process != -1)
            return(process);
        else
            return(-1);
    }
    
    return(1);
}

t_list **get_token_list(char *str, t_list **lst, char **envp)
{
    int i;
    int process;
    t_list  *node;
    char    **split;

    i = 0;
    split = ft_split(str, 32);
    if(!split)
        return(NULL);
    process = 0;
    while (split[i])
    {
        node = new_list_node(split[i], i, split[i - process], envp);
        if(!node)
            return(ft_split_clean(&split));
        process = process_node(node, &split[i], envp);
        if(process == -1)
            return(ft_split_clean(&split));
        i += process;
        ft_lstadd_back(lst, node);
    }

    ft_split_clean(&split);
    return(lst);
}

