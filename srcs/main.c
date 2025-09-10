#include "main.h"
 #include <sys/stat.h>
#include <stdio.h>
#include <string.h>


int run_minishell()
{
    char *line;

    while (1)
    {
        line = readline("minishell");
        if(line)
        {
            printf("voici la ligne %s\n", line);
        }
    }
    
}

int main(void)
{
    // t_list **tokens_lst;
    // char *str = "cat -A b c  < file.txt  | grep banana | wc -l > out.txt";
    // //char *str = "cat -A b c ";
    
    // tokens_lst = calloc(sizeof(t_list *) , 1);
    // if(!tokens_lst)
    //     return(1);
   
    
    // if(!get_token_list(str, tokens_lst))
    // {
    //     printf("Error token list\n");
    //     ft_lstclear(tokens_lst, delete_list);
    //     return(1);
    // }

    // printf("\n\n");
    // ft_lstiter(*tokens_lst, display_content_lst);
    // printf("\n\n");
    // ft_lstiter(*tokens_lst, display_arg_of_cmd);

    // t_token **ast = malloc(sizeof(t_token *));
    // if(!ast)
    // {
    //     ft_lstclear(tokens_lst, delete_list);
    //     return(1);
    // }
    //*ast = NULL;
    //generate_ast(*tokens_lst, ast);

    //display_binary_tree(NULL,*ast);
    //ft_lstclear(tokens_lst, delete_list);
    return(0);
}
