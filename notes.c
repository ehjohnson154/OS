
#include <stdio.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {

printf("before fork...\n");

pid_t pid = fork();


if(pid == 0) {
    char *new_argv[] = {
        "ls",
        "-la",
        "/usr/bin",
        NULL
    };


//int

execvp("ls", new_argv);
perror("exec");
exit(1);
}
printf("After exec\n:");
wait(NULL);
printf("all done!\n");
return 2
}


//fork();
// printf("after fork...\n");
//causes after fork message to print twice, as there is two processes

// charp *p = NULL;
// printf("%c\n:, *p");
// printf("Before exec\n");

// if (pid ==0) {
//     printf("child PID is %d]n",getpid());
//     printf("child parent PID is %d\n", getppid());
// }
// else {
//     printf("Parent PID is %d\n",getpid());
//     printf("Parent child PID is %d\n",pid);
//     wait(NULL);
// }