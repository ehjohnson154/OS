

#include <stdio.h>
int main() {
   // printf() displays the string inside quotation

   int x = 12;
   float y = 3.14;
   char *s = "Hello, world!";

   printf("X is %d, y is %f,\n%s\n",x,y,s);

   int i;

   for (i = 0; i < 5; i++) {
   int result = (i * 5);
   printf("%d X 5 = %d\n", i, result);
   }

   return 0;
}