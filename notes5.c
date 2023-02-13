#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <fcntl.h> //open

//gcc 0

int main(void)
{
    int fd = open("foo.out", O_CREAT|O_WRONLY, 0644);

    pid_t pid = fork();

    if (pid == -1){ //ERROR CHECKING
        perror("fork");
        return 1;
    }

    //char *s = pid == 0? "C": "P";
    char c = pid == ?"C": "P";

    for (int i = 0; i <2000, i++)
    {
        //write(fd, &c, 1);
        write(fd, s, 2);

    }
    close(fd);

}