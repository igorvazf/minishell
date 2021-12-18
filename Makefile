NAME =		minishell
CC =		gcc
CFLAGS =	-Wall -Werror -Wextra
RM =		rm -rf

LIBFT_DIR =	./libft
LIBFT =		$(LIBFT_DIR)/libft.a

SRC_FILES =	main.c \
			crud_list.c \
			crud_env.c \
			free.c \
			init.c \
			miniexit.c \
			split_cmd.c \
			utilis.c \
			builtin.c \
			sanitizer.c \
			miniexport.c \
			minicd.c \
			miniecho.c \
			minienv.c \
			miniunset.c \
			minipwd.c \

			

SRC =		$(addprefix src/, $(SRC_FILES))

OBJECTS =	$(SRC:.c=.o)

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJECTS) include/minishell.h
			$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
			$(MAKE) -C $(LIBFT_DIR)

clean:
			$(MAKE) -C $(LIBFT_DIR) clean
			$(RM) $(OBJECTS)

fclean:		clean
			$(MAKE) -C $(LIBFT_DIR) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re libft
