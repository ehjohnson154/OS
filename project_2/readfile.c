#include <stdio.h>
#include <string.h>

#define MAX_BYTE 2048

int main(int argc, const char *argv[])
{		
    char buffer[MAX_BYTE];

	FILE *fin = fopen(argv[1], "r");
    fread(buffer, MAX_BYTE, 1, fin);
    printf("%s\n", buffer);

	fclose(fin);

}
