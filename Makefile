NAME				=	minishell
CC					=	cc
AR					=	ar -rcs
RM					=	rm -f

CFLAGS				=	-Wall -Wextra -Werror -g
LINKER				=	-lreadline -lncurses

C_HAMOU_DIR			=	srcs/c_hamou
C_SPUVR_DIR			=	srcs/c_spuvr
LIBFT_DIR			=	srcs/c_spuvr/LIBFT
INCDIR				=	srcs/includes

INCLUDES			=	-I $(INCDIR) -I $(C_SPUVR_DIR) -I $(LIBFT_DIR)

MINISHELL_SRCS		=	$(C_HAMOU_DIR)/commands.c \
						$(C_HAMOU_DIR)/commands_utils.c \
						$(C_HAMOU_DIR)/commands_utils1.c \
						$(C_HAMOU_DIR)/free.c \
						$(C_HAMOU_DIR)/free_utils.c \
						$(C_HAMOU_DIR)/tokenization.c \
						$(C_HAMOU_DIR)/helper_fuc.c \
						$(C_HAMOU_DIR)/utils.c \
						$(C_HAMOU_DIR)/util99.c \
						$(C_HAMOU_DIR)/tokens_utils2.c \
						$(C_HAMOU_DIR)/tokens_utils1.c \
						$(C_HAMOU_DIR)/expand.c \
						$(C_HAMOU_DIR)/expand_utils.c \
						srcs/main.c \
						srcs/main_utils.c \
						srcs/main_utils2.c \
						srcs/main_utils3.c \
						srcs/signal_handler.c \
						$(C_SPUVR_DIR)/built-ins.c \
						$(C_SPUVR_DIR)/built-ins1.c \
						$(C_SPUVR_DIR)/env.c \
						$(C_SPUVR_DIR)/execute_heart.c \
						$(C_SPUVR_DIR)/execute_heart_help.c \
						$(C_SPUVR_DIR)/utils.c \
						$(C_SPUVR_DIR)/ft_chdir/ft_cd.c \
						$(C_SPUVR_DIR)/ft_chdir/ft_cd_1.c \
						$(C_SPUVR_DIR)/ft_chdir/ft_cd_utils.c \
						$(C_SPUVR_DIR)/utils1.c \
						$(C_SPUVR_DIR)/ft_export/ft_export.c \
						$(C_SPUVR_DIR)/ft_export/ft_export1.c \
						$(C_SPUVR_DIR)/ft_export/ft_export2.c \
						$(C_SPUVR_DIR)/ft_export/utils.c \
						$(C_SPUVR_DIR)/ft_export/utils2.c \
						$(C_SPUVR_DIR)/unset_exit/ft_exit.c \
						$(C_SPUVR_DIR)/ft_execut/exec_main.c \
						$(C_SPUVR_DIR)/unset_exit/ft_unset.c \
						$(C_SPUVR_DIR)/unset_exit/ft_exit_child.c \
						$(C_SPUVR_DIR)/ft_env/ft_env.c \
						$(C_SPUVR_DIR)/ft_execut/error.c \
						$(C_SPUVR_DIR)/ft_execut/util.c \
						$(C_SPUVR_DIR)/ft_execut/redirections.c \
						$(C_SPUVR_DIR)/ft_pipes/pipe_execution.c \
						$(C_SPUVR_DIR)/ft_pipes/pipe_help.c \
						$(C_SPUVR_DIR)/ft_execut/heredoc.c \
						$(C_SPUVR_DIR)/ft_execut/herdoc_utils.c \
						$(C_SPUVR_DIR)/ft_execut/herdoc_utils1.c \
						$(C_SPUVR_DIR)/ft_echo.c

LIBFT_SRCS_NAMES	=	ft_atoi.c ft_isdigit.c ft_memchr.c ft_putendl_fd.c ft_striteri.c \
						ft_strncmp.c ft_bzero.c ft_isprint.c ft_memcmp.c ft_putnbr_fd.c \
						ft_strjoin.c ft_strnstr.c ft_calloc.c ft_itoa.c ft_memcpy.c \
						ft_putstr_fd.c ft_strlcat.c ft_strrchr.c ft_isalnum.c ft_memmove.c \
						ft_split.c ft_strlcpy.c ft_strtrim.c ft_isalpha.c ft_memset.c \
						ft_strchr.c ft_strlen.c ft_arrlen.c ft_substr.c ft_isascii.c \
						ft_putchar_fd.c ft_strdup.c ft_strmapi.c ft_toupper.c ft_tolower.c \
						ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
						ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
						ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_strcmp.c \
						ft_swap.c ft_strndup.c ft_isspace.c ft_is_valid_ll.c ft_atoll.c

LIBFT_SRCS			=	$(addprefix $(LIBFT_DIR)/, $(LIBFT_SRCS_NAMES))

MINISHELL_OBJS		=	$(MINISHELL_SRCS:.c=.o)
LIBFT_OBJS			=	$(LIBFT_SRCS:.c=.o)

LIBFT_A				=	$(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(MINISHELL_OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) -o $(NAME) $(MINISHELL_OBJS) $(LIBFT_A) $(LINKER)

$(LIBFT_A): $(LIBFT_OBJS)
	$(AR) $(LIBFT_A) $(LIBFT_OBJS)

$(MINISHELL_OBJS): %.o: %.c $(INCDIR)/header.h $(C_SPUVR_DIR)/built_functions.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_OBJS): %.o: %.c $(LIBFT_DIR)/libft.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(MINISHELL_OBJS) $(LIBFT_OBJS)

fclean: clean
	$(RM) $(NAME) $(LIBFT_A)

re: fclean all
