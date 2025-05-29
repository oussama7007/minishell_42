#include <stdio.h>

void swap_strings(char **x, char **y) {
    char *temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    char *fruits[] = {"Apple", "Banana", "Cherry"};
    char *p1 = fruits[0];
    char *p2 = fruits[2];
    
    swap_strings(&p1, &p2);
    
    printf("%s %s %s\n", fruits[0], fruits[1], fruits[2]);
    printf("%s %s\n", p1, p2);
    return 0;
}