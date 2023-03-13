#include <stdio.h>

//s



struct foo {
    char c;
    //int x;
    int i;
};

int main(void)
{
    char *s = malloc(1024);
    struct foo f = { .c='b', .i=12};

    struct foo *fp = (struct foo *)(s + 107);

    printf("fp 1: %c %d\n", fp->c, fp->i);


    //printf(%s)

    memcpy(s + 108, &f, sizeof(struct foo));
    memcpy(s + 108, &f, sizeof f);

    strcpy(s + 112, "Hi!");

    // strcpy(&s[112], "*");
    // strcpy(&(*(s[112])), "*");
    //strcpy(&s[112], '*');

    *(s + 112) = '*';
    s[112] = '!';

    printf("%s\n", s + 112);
    printf("fp 2: %c %d\n", fp->c, f.i, s+112, &f.i);


}



// myfree(s)
// {

//     check if my magic number is at s

//     if so:
//         print some error about double free
    
//     mark block free
//     write the magic number at s
// }