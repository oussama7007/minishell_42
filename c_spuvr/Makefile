NAME = minishell

SRCS = main.c env.c utils.c built-ins1.c built-ins.c ft_export/utils2.c \
		ft_export/ft_export.c ft_export/ft_export1.c ft_export/utils.c

CFLAGS = -fsanitize=address -g -Wall -Werror -Wextra

CC = cc

LINKER = -lreadline

LIBFT_A = LIBFT/libft.a

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(LINKER) -o $(NAME)



%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re