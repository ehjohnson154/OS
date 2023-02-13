#include <stdio.h>


int main(void)
{
    char s[2048];
    fgets(s, stdin, 2048); // "    ls    -l    -a   "
    char *tok;
    tok - strtok(s, " \t\r\n");

    while (tok = strtok(NULL, "\t\r\n") !=NULL )
    {

    }
}