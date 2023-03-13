#include <stdio.h>

int main(void){
    char *s = "Hello, world!";
    printf("%s\n", s+1); //ello, world!

    printf("%c\n", *(s+1)); //e
    printf("%c\n", s[1]); //e

    int a[5] = {0, 11, 22, 33, 44};

    printf("%p\n", a);
    printf("%p\n", a+1);

    printf("%d\n", *(a+1)); //11
    printf("%p\n", a[1]); //1
}