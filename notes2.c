#include <stdio.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
int fd = open("foo.out", 0_WRONGLY|0_CREAT, 0644); //0 means octal(base 8) number
//0644 = 110 110 100 (?)

if(fd == -1) {
    perror("open");
    return 1;
}

dup2(fd, 1);

write(1, "Hello!\n", 7);

close(fd);

}