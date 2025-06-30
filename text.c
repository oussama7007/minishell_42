#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>  // Required for malloc/free
#include <string.h>
 
typedef struct s_data
{
    int a;
} t_data;


// int function(t_data *data)
// {
//     data->a = 777;
// }

int main()
{
    //t_data *data = malloc(sizeof(t_data));
    // data->a = 15;
    char *arr;
    //function(data);
    //printf("%d\n", data->a);
    printf("=---%p-----\n",&arr);
    //printf("%p", &data);
}