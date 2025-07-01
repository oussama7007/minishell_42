// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>
// #include <stdlib.h>

// char 	**function(char **arr)
// {
// 	char **aff;
// 	int len = 0;
// 	while(arr[len])
// 		len++;
// 	int i = 0;
// 	len++;
// 	aff = malloc(sizeof(char *) * len);
// 	while(arr[i])
// 	{
// 		aff[i] = strdup(arr[i]);
// 		i++;
// 	}
// 	int j = 0;
	
// 	aff[i] = strdup("morocco");
// 	aff[++i] = NULL;
// 	return aff;
// }

// int main()
// {
// 	char **arr = malloc(sizeof(char *) * 3);
// 	arr[0] = strdup("hello"); //  
// 	arr[1] = strdup("world");
// 	arr[3] = NULL;
// 	arr = function(arr);
// 	while(*arr)
// 	{
// 		printf("%s\n", *arr);
// 		arr++;
// 	}
// }