//#include <iostream>
#include <stdio.h>
// using namespace std;
  
// int main(int argc, char** argv)
// {
//     cout << "You have entered " << argc
//          << " arguments:" << "\n";
  
//     for (int i = 0; i < argc; ++i)
//         cout << argv[i] << "\n";
  
//     return 0;
// }

int main(int argc,char* argv[])
{
    int arguments;
    printf("Name: %s",argv[0]);
    if(argc==1){
        printf("\no commands!");
    }
    if(argc>=2)
    {
        printf("\nNumber Of Arguments Passed: %d",argc);
        for(arguments=0;arguments<argc;arguments++)
            printf("\nargv[%d]: %s",arguments,argv[arguments]);
    }
    return 0;
}