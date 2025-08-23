#include "main.h"


int main(void)
{
    t_list **tokens_lst;
    char *str = "cat file.txt | grep banana | wc -l";
    
    tokens_lst = calloc(sizeof(t_list *) , 1);
    if(!tokens_lst)
        return(1);
    
    if(!get_token_list(str, tokens_lst))
    {
        printf("Error token list\n");
        ft_lstclear(tokens_lst, delete_list);
        return(1);
    }

    ft_lstiter(*tokens_lst, display_content_lst);
    ft_lstclear(tokens_lst, delete_list);



    return(0);
}