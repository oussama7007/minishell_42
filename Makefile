NAME        := minishell
CC          := cc
# CFLAGS      := -Wall -Wextra -Werror
LINKER      := -lreadline
INCLUDES    := -I srcs/includes

# === Directories ===
C_HAMOU_DIR := srcs/c_hamou
C_SPUVR_DIR := srcs/c_spuvr

INCDIR      := srcs/includes

# === Source files ===
HAMOU_SRC := \
	$(C_HAMOU_DIR)/commands.c $(C_HAMOU_DIR)/ex.c $(C_HAMOU_DIR)/free.c $(C_HAMOU_DIR)/tokenization.c \
	$(C_HAMOU_DIR)/utils.c $(C_HAMOU_DIR)/utils2.c srcs/main.c

SPUVR_SRC := \
	$(C_SPUVR_DIR)/built-ins.c $(C_SPUVR_DIR)/built-ins1.c $(C_SPUVR_DIR)/env.c $(C_SPUVR_DIR)/mainxxx.c $(C_SPUVR_DIR)/utils.c \
	$(C_SPUVR_DIR)/ft_chdir/ft_cd.c $(C_SPUVR_DIR)/ft_chdir/ft_cd_1.c $(C_SPUVR_DIR)/ft_chdir/ft_cd_utils.c \
	$(C_SPUVR_DIR)/ft_export/ft_export.c $(C_SPUVR_DIR)/ft_export/ft_export1.c $(C_SPUVR_DIR)/ft_export/ft_export2.c \
	$(C_SPUVR_DIR)/ft_export/utils.c $(C_SPUVR_DIR)/ft_export/utils2.c \
	$(C_SPUVR_DIR)/unset/ft_unset.c

SRCS := $(HAMOU_SRC) $(SPUVR_SRC)
OBJS := $(SRCS:.c=.o)

LIBFT_DIR = $(C_SPUVR_DIR)/LIBFT
# === Build ===
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKER) $(OBJS) $(LIBFT_DIR)/libft.a -o $(NAME)

%.o: %.c $(INCDIR)/header.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# === Clean ===
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
