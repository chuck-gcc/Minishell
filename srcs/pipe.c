// #include "main.h"
//  #include <sys/stat.h>
// #include <stdio.h>
// #include <string.h>

// int tube[2];
// int status;

// pipe(tube);
// pid_t f = fork();
// if(f == -1) { perror("fork"); return(errno);}
// else if(f == 0)
// {
//     char *commande[] = {"/bin/echo", "hello world", 0};
//     char *c = commande[0];
//     close(tube[0]);
//     if(dup2(tube[1], STDOUT_FILENO) == -1) { perror("dup2"); return(errno);}
//     printf("launch commande\n");
//     close(tube[1]);
//     if(execve(c, commande, envp) == -1) 
//     {
//         perror("exvce"); 
//         printf("Erreur %d\n", errno);
//         return(errno);
//     }
// }   
// else
// {
//     close(tube[1]);
//     waitpid(f, &status, 0);
//     printf("we are in parent status is %d\n", status);
//     if(status == 0)
//     {
//         if (dup2(tube[0], STDIN_FILENO) == -1)
//         {
//             perror("dup2 parent");
//             return errno;
//         }
//         char *commande[] = {"/usr/bin/grep", "w", "--colour=always", NULL};
//         char *c = commande[0];
//         if(execve(c, commande, envp) == -1) 
//         {
//             perror("exvce"); 
//             printf("Erreur %d\n", errno);
//             return(errno);
//         }
//     }
// }