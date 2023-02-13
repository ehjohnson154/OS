#include <stdio.h>

int adder(int x, int y)
{
    int z = x + y;
    return z; //automatic variable, default in c. Automatically gets free once Z returns.
}


char *give_me_ram(int byte_count)
{
    char *ram = malloc(byte_count);

    return ram;

}

int main(void)
{
    printf("%d\n", adder(2,3));

    char *mem = give_me_ram(2048);
    int *ints = malloc(sizeof(int) * 100);
    int *ints = calloc(sizeof(int) * 100);
    
    strcpy(mem, "Hello, world!");

    puts(mem);
    free(mem);
    puts(mem);
}