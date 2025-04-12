CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(PATH_SRC) -g3 -fsanitize=address
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
		$(PATH_SRC)pipes.c 
#SRC_BONUS	=	$(PATH_SRC)main_bonus.c \
#		$(PATH_SRC)inputs_bonus.c \
#		$(PATH_SRC)pipes_bonus.c 
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
	$(RM) $(PATH_OBJ)*.o
	$(MAKE) clean -C $(PATH_LIBFT)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(PATH_LIBFT)

re: fclean all

.PHONY: all clean fclean re
