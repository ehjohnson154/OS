 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

 
 
 
int main(int argc, char *argv[]){ 

    (void) argc;
 
    int pfd[2];   // Pipe file descriptors, write and read
    //pfd[0] is read end, pfd[1] is write end
    pipe(pfd); 

    // if (argc > 1){
    //     char * path = argv[1];
    // }



    pid_t p = fork();

    if (p < 0){
        //fork failed
        return 1;

    }

    else if (p > 0 ){ //parent process

//     dup2() the write end of the pipe into stdout
//     close() the read end of the pipe
//execlp() the ls command

        dup2(pfd[1],1);
        close(pfd[0]);
        execlp("ls", "ls", "-la", argv[1], NULL); 

    }
    // The child will run wc:
//     dup2() the read end of the pipe into stdin
//     close() the write end of the pipe
//     execlp() the wc command

    else { //child process is p == 0

        dup2(pfd[0], 0); //something
        close(pfd[1]);
        //execlp("wc", "wc", "-l", argv[1], NULL);  //How to read from the input?
        execlp("wc", "wc", "-l", NULL);  
        //execlp(argv[1], "wc", "-l", NULL);

    }

}
