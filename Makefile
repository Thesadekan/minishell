NAME        = minishell

SRC         = minishell.c cd.c echo.c env.c builtin.c exit.c bin.c export.c \
              fd.c free.c parsing.c global.c pwd.c \
              redir.c sort_env.c tokens.c unset.c

OBJ         = $(SRC:.c=.o)
CC          = cc
CFLAGS      = -g -Wall -Wextra -Werror -I. -I$(LIBFT_DIR)/includes

LIBFT_DIR   = libft
LIBFT_A     = $(LIBFT_DIR)/libft.a
READLINE    = -lreadline -lncurses

# === RULES ===

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_A) $(READLINE)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null 2>&1

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null 2>&1
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@rm -f $(NAME)

re: fclean all

debug: $(NAME)
	gdbgui $(NAME)

.PHONY: all clean fclean re
