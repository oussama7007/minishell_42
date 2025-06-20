#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
void    not_yet(int *a)
{
  
}
void    modifie_a(int *a)
{
 
}
void   modifie_it(char **ptr)
{
   //(void)ptr;
   **ptr = 'p';
    printf("-----%p------\n", &ptr);
   //*ptr = strdup("hello world");
   printf("ptr :%s\n", *ptr);
}

void f()
{
    system("leaks a.out");
}
int main()
{
    //atexit(f);
    //char ptr[] = "abc" ;
    //printf("sizeof ptr is:%zu\n", sizeof(ptr));
   // char *p = &ptr;
    char   *p = NULL;
     
   printf("%s\n",p);
   //int *ptr = ;
   // modifie_it(&p);
   // printf("-----%p------\n", &p);
    //printf(" ptr :%d\n", p);
   // free(ptr);
}