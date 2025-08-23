#include "main.h"


int main(void)
{
    t_list **tokens;
    char *str = " cat file.txt | grep banana | wc -l";
    
    tokens = get_token_list(str);
    if(!tokens)
    {
        printf("Error token list\n");
        return(1);
    }

    ft_lstiter(*tokens, display_content_lst);

    ft_lstclear(tokens, delete_list);
    return(0);
}