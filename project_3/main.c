
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAX 2048

//execute command passed to it
void command (char ** args){

    //forking process
    pid_t pid = fork();

    //if valid, execute command
    if (pid == 0) {
        execvp(args[0], args);
        perror("ERROR: ");
        exit(1);
    }

    wait(NULL);
    printf("command executed!\n");

}
//main function that runs shell
int main() {
    
    //setting up variables for strtok
    char buf[MAX] = "",
    *delim = " \n";

    //continuous loop
    while(1) {
        //gets value, places into buffer array
        fgets(buf, MAX, stdin);
        char * array[MAX];
        int i = 0;
        //loop cycles through each tokenized item, places into array
        for (char *token = strtok (buf, delim); token; token = strtok (NULL, delim)){
            array[i] = token;
            printf ("%s\n", array[i]);
            i++;

        }
        //null terminator
        array[i] = '\0';

        //if statements to check for system call commands or exit
        if (strcmp(array[0],"cd")==0){
            //printf("in cd!\n"); 
            int ch = chdir(array[1]);
            
            if(ch<0){
                printf("chdir failure!!\n");
                perror("ERROR: ");
            }
            else{
                printf("cd executed!\n");
            }
            //printf("finished chdir!");
        }

        else if (strcmp(array[0],"exit")==0){
            printf("exiting!...");
            exit(0);

        }

        //if not syscall, execute command
        else {
        command(array);
        }
        //execvp(array[0],array);
    }
    return 0;
}


