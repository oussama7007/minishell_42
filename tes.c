#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
typedef struct s_command {
    char *cmd;             // Command name (e.g., "ls")
    char **args;           // Array of arguments (e.g., {"ls", "-l"})
    char **red_in;         // Array of input redirection files
    char **red_out;        // Array of output redirection files
    int *append;           // Array of flags (1 for >>, 0 for >)
    char *heredoc_delimiter;// Delimiter for << (e.g., "EOF")
    struct s_command *next;// Next command (for pipes)
} t_command;
typedef struct s_gc_list
{
    void *ptr;
    struct  s_gc_list *next;
}t_gc_list;

typedef struct s_head_list
{
    t_gc_list *head;
} t_head_list;
void    add_ptr_node(t_head_list *head, void *ptr)
{
    t_gc_list *node;

    node = malloc(sizeof(t_gc_list));
    if(!node)
        return;
    node->ptr = ptr;
    node->next = head->head;
    head->head = node;
}
void *gc_malloc(t_head_list *head,int size)
{
    void *ptr;

    ptr = malloc(size);
    if(!ptr)
        return NULL;
    add_ptr_node(head, ptr);
    return ptr;
}
void    free_gc(t_head_list *head)
{
    t_gc_list *tmp;
    t_gc_list *next;
    if(head)
    {
        tmp = head->head;
        while(tmp)
        {
            next = tmp->next;
            free(tmp->ptr);
            free(tmp);
            tmp = next;
        }
        head->head = NULL;
    }
}

void    f()
{
    system("leaks a.out");
}
int main()
{
    t_head_list head = {NULL};

    atexit(f);
    char *ptr = gc_malloc(&head ,10);
    t_command  *new = gc_malloc(&head ,sizeof(t_command));
    new->append = gc_malloc(&head,sizeof(int));
    new->args = gc_malloc(&head, sizeof(char *) * 7);
    free_gc(&head);
}