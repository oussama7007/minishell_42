# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/16 23:42:48 by oadouz            #+#    #+#              #
#    Updated: 2025/05/20 17:46:54 by oadouz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = libft.a
CFLAGS = -Wall -Wextra -Werror

SRC = ft_atoi.c ft_isdigit.c ft_memchr.c ft_putendl_fd.c ft_striteri.c ft_strncmp.c \
	ft_bzero.c ft_isprint.c ft_memcmp.c ft_putnbr_fd.c ft_strjoin.c ft_strnstr.c \
	ft_calloc.c ft_itoa.c ft_memcpy.c ft_putstr_fd.c ft_strlcat.c ft_strrchr.c \
	ft_isalnum.c ft_memmove.c ft_split.c ft_strlcpy.c ft_strtrim.c \
	ft_isalpha.c ft_memset.c ft_strchr.c ft_strlen.c ft_arrlen.c ft_substr.c \
	ft_isascii.c ft_putchar_fd.c ft_strdup.c ft_strmapi.c ft_toupper.c ft_tolower.c\
	ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c \
	ft_lstnew_bonus.c ft_lstsize_bonus.c ft_strcmp.c ft_swap.c ft_strndup.c ft_isspace.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)


%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@
	ar -rcs $(NAME) $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
