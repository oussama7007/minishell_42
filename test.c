// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
void f()
{
    system("leaks a.out");
}
int main() 
{
    atexit(f);
   char ***arr = malloc(3 * sizeof(char **));
   arr[0] = malloc(sizeof(char *) * 3);
   arr[0][0] = strdup("hello world");
   arr[0][1] = strdup("welcome to morocco");
   arr[0][2] = NULL;

   arr[1] = malloc(sizeof(char *) * 3);
   arr[1][0] = strdup("hello world -- 1");
   arr[1][1] = strdup("welcome to morocco -- 1");
   arr[1][2] = NULL;

//    arr[2][0] = strdup("hello world -- 1");
//    arr[2][1] = strdup("welcome to morocco -- 1");
//    arr[2][2] = NULL;

   arr[2] = NULL;
   //int i = 0;
   char ***arr2 = arr;
   while(*arr2)
   {
        char **arr3 = *arr2;
        while(*arr3)
        {
            printf("%s\n", *arr3);
            arr3++;
        }
        arr2++;
   }
    char ***arr5 = arr;
   while(*arr5)
   {
        char **arr4 = *arr5;
        while(*arr4)
            free(*arr4++);
        free(*arr5);
        arr5++;
   }
   free(arr);

}