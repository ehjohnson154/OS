
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>



//PART 2:
//open file, dub into file descriptor, exec command


//open file
//dup
//exec

//fork
//  exec
//wait
//close


//trick for variable number of commands on argv
//argv array is pointer to strings
//think of argv+0 for position 0, argv+1 for position 1, etc.
//run at argv+2 to start at position 2 and run rest of command, rather than argv[2]




int main(int argc, char *argv[]){
    (void) argc;

    //printf("hello");
    // Parse the command line
    //argc and argv is possible, with if/else statement based on arg count

    //execlp("ls", "ls", "-la", argv[1], NULL);
    //check if argc is >1
    //execlp() //run with commands, check for argv[1], nu

    // Make a pipe() in the parent


//     Parse the command line
// Make a pipe() in the parent
// fork().


    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644); //o644 is read/write permission with everyone else being read
    //O_trunc truncates it to 0 bytes long if it does exist, overwritting file contents
    int pfd[2];   // Pipe file descriptors, write and read
    //pfd[0] is read end, pfd[1] is write end
    pipe(pfd); 

    pid_t p = fork();

    if (p < 0){
        return 1;
    }

    else if (p > 0 ){ //parent process

        //file = fopen(argv[1]);
        wait(NULL);
        close(fd);

    }

    else { //child process is p == 0

        dup2(fd,1);
        //execlp("wc", "wc", "-l", argv[1], NULL);  //something
        execvp((argv[2]), (argv + 2)); //???

        //difference in lp and vp
        //lp: list a bunch of strings, terminate with null, great if you know compile time/how many args
        //v family: array of char pointers as arg/array of strings. better if you don't know how many args.

    }

}


 







