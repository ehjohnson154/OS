#include <stdio.h>

int *foo(void)
{
    if (x == 0) return;

    printf("%d\n", x);

    foo(x-1);

}

int main(void)
{
    foo(5);
}