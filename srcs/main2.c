#include <stdio.h>
#include <unistd.h>

int main ()
{
    void val;
    int *i = (int *)malloc(sizeof(int) * 2);
    int(val) = i;
    printf("%d", (int)val);
}
