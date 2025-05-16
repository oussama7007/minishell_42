NAME = MINISHELL


SRCS =  
LINKER = -lreadline
INCLUDES = -I includes 

CFLAGS = -Wall -Werror -Wextra
CC = cc 
OBJS = $(SRCS:.c=.o)
all :$(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKER) $(OBJS) -o $(NAME)

%.o: %.c includes/header.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm  -f $(NAME)

re : fclean all

.PHONY : clean