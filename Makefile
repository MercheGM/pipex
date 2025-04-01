CC          = cc
CFLAGS      = -g3 -fsanitize=address -I$(PATH_SRC)
#-Wall -Wextra -Werror -g3 -fsanitize=address

RM          = @rm -f

PATH_LIBFT  = libft/
PATH_SRC    = src/
PATH_OBJ    = obj/

NAME            = pipex
NAME_LIBFT      = libftprintf.a
NAME_INC		= pipex.h

LIBFT   = $(PATH_LIBFT)$(NAME_LIBFT)

INC	=	$(PATH_SRC)$(NAME_INC)
SRC	=	$(PATH_SRC)main.c \
		$(PATH_SRC)inputs.c \
		$(PATH_SRC)utils.c 
OBJ	=	$(patsubst $(PATH_SRC)%.c, $(PATH_OBJ)%.o, $(SRC))

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(PATH_LIBFT)

$(PATH_OBJ)%.o: $(PATH_SRC)%.c $(INC) | $(PATH_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(PATH_OBJ):
	@mkdir -p $(PATH_OBJ)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	$(RM) *.o
	$(MAKE) clean -C $(PATH_LIBFT)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(PATH_LIBFT)

re: fclean all

.PHONY: all clean fclean re
