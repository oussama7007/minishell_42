#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}
char *skip_space(char *str)
{
	while(*str && is_space(*str))
		str++;
	return str;
}
int main()
{
    char *str = strdup("      hello world");
    str = skip_space(str);
    printf("%s", str);
}