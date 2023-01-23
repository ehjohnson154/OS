#include <stdio.h>
#include <string.h>

#define MAX_BYTE 2048

int main(int argc, const char *argv[])
{		
    char buffer[MAX_BYTE];


    // int arguments;
    printf("Name: %s",argv[0]);
    if(argc==1){
        printf("\no commands!");
    }
    if(argc>=2)
    {
        int i;
        printf("\nNumber Of Arguments Passed: %d\n",argc);
        for(i=0;i<argc;i++){
            FILE *fin = fopen(argv[i], "r");
            fread(buffer, MAX_BYTE, 1, fin);
            printf("%s\n", buffer);
            fclose(fin);
        }
           // printf("\nargv[%d]: %s",arguments,argv[arguments]);
    }

	


	

}