
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAX 2048

int main()
{
    
    char buf[MAX] = "",
    *delim = " \n";


    // char buf[MAX];
    while(1) {
        
        fgets(buf, MAX, stdin);

        // printf("string is: %s\n", buf);
        char * array[MAX];
        int i = 0;
        for (char *token = strtok (buf, delim); token; token = strtok (NULL, delim)){
            array[i] = token;
            printf ("%s\n", array[i]);
            i++;
            //place into array



        }
        i++;
        array[i] = '\0';
        
        execvp(array[0],array);
    }
    return 0;
}



// void command {


// }

    
    // char *token;                  //split command into separate strings
    // token = strtok(line," ");
    // int i=0;
    // while(token!=NULL){
    //     argv[i]=token;      
    //     token = strtok(NULL," ");
    //     i++;




//  while (1) {
//     fgets(line, MAX_LINE_SIZE, stdin); // read the line from input_file


//     // initialize next_field to point to the first field on the line
//     next_field = strtok(line, " \n");
    
//     // iterate through the fields on the line until we have exhausted them. strtok
//     // will return NULL when there are no more fields to be read
//     while (next_field != NULL) {
//       // write the current field to the output file
//     //   fprintf(output_file, "%d: %s\n", line_number, next_field);

//       // get the next word on the line--remember to pass NULL as the first argument
//       // because only the first call to strtok on each line should receive a pointer
//       // to line
//       next_field = strtok(NULL, " \n");
//     }
//   }