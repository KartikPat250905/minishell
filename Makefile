NAME = minishell
CC = cc
INCLUDES = -Iincludes
CFLAGS = -Wall -Wextra -Werror
HEADER = minishell.h

LIBFT = srcs/libft

SOURCES = srcs/parsing/file.c \
		  srcs/parsing/actions.c \
		  srcs/parsing/enum_check.c \
		  srcs/parsing/fetch_safe.c \
		  srcs/parsing/parsing.c \
		  srcs/parsing/lexer/lexer.c \
		  srcs/main.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(LIBFT)/libft.a:
	make -C $(LIBFT)
	make bonus -C $(LIBFT)

$(NAME): $(OBJECTS) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT)/libft.a -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -f $(OBJECTS)
	make -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
