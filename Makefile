NAME        := minishell
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g
LINKER      := -lreadline -lncurses
INCLUDES    := -I srcs/includes
 
# === Directories ===
C_HAMOU_DIR := srcs/c_hamou
C_SPUVR_DIR := srcs/c_spuvr
LIBFT_DIR = srcs/c_spuvr/LIBFT
LIBFT = $(LIBFT_DIR)/libft.a
INCDIR      := srcs/includes

# === Source files ===
HAMOU_SRC := \
	$(C_HAMOU_DIR)/commands.c $(C_HAMOU_DIR)/commands_utils.c $(C_HAMOU_DIR)/commands_utils1.c $(C_HAMOU_DIR)/free.c $(C_HAMOU_DIR)/free_utils.c  $(C_HAMOU_DIR)/tokenization.c $(C_HAMOU_DIR)/helper_fuc.c  \
	$(C_HAMOU_DIR)/utils.c $(C_HAMOU_DIR)/tokens_utils2.c $(C_HAMOU_DIR)/tokens_utils1.c $(C_HAMOU_DIR)/expand.c  $(C_HAMOU_DIR)/expand_utils.c srcs/main.c srcs/main_utils.c srcs/main_utils2.c srcs/main_utils3.c  srcs/signal_handler.c

SPUVR_SRC := \
	$(C_SPUVR_DIR)/built-ins.c $(C_SPUVR_DIR)/built-ins1.c $(C_SPUVR_DIR)/env.c $(C_SPUVR_DIR)/execute_heart.c $(C_SPUVR_DIR)/execute_heart_help.c $(C_SPUVR_DIR)/utils.c \
	$(C_SPUVR_DIR)/ft_chdir/ft_cd.c $(C_SPUVR_DIR)/ft_chdir/ft_cd_1.c $(C_SPUVR_DIR)/ft_chdir/ft_cd_utils.c $(C_SPUVR_DIR)/utils1.c \
	$(C_SPUVR_DIR)/ft_export/ft_export.c $(C_SPUVR_DIR)/ft_export/ft_export1.c $(C_SPUVR_DIR)/ft_export/ft_export2.c \
	$(C_SPUVR_DIR)/ft_export/utils.c $(C_SPUVR_DIR)/ft_export/utils2.c  $(C_SPUVR_DIR)/unset_exit/ft_exit.c $(C_SPUVR_DIR)/ft_execut/exec_main.c \
	$(C_SPUVR_DIR)/unset_exit/ft_unset.c $(C_SPUVR_DIR)/ft_env/ft_env.c $(C_SPUVR_DIR)/ft_execut/error.c $(C_SPUVR_DIR)/ft_execut/util.c \
	$(C_SPUVR_DIR)/ft_execut/redirections.c $(C_SPUVR_DIR)/ft_pipes/pipe_execution.c $(C_SPUVR_DIR)/ft_pipes/pipe_help.c $(C_SPUVR_DIR)/ft_execut/heredoc.c \
	$(C_SPUVR_DIR)/ft_execut/herdoc_utils.c $(C_SPUVR_DIR)/ft_execut/herdoc_utils1.c $(C_SPUVR_DIR)/ft_echo.c

SRCS := $(HAMOU_SRC) $(SPUVR_SRC)
OBJS := $(SRCS:.c=.o)

LIBFT_DIR = $(C_SPUVR_DIR)/LIBFT
# === Build ===
all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT_DIR)/libft.a $(LINKER) -o $(NAME)

%.o: %.c $(INCDIR)/header.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# === Clean ===
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
