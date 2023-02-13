#include <stdio.h>

int *foo(void)
{
    int x = 12;

    return &x; //burning the house down, but still a remnant

}

void bar(void)
{
    int y = 42, z = 100;
    printf("%d\n", y + z);
}

int main(void)
{
    int *val = *foo();
    printf("%d\n", val); //12
    bar();
    printf("%d\n", val); //42
}