CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(PATH_SRC) -g3 -fsanitize=address
CFLAGS_B      =  -I$(PATH_SRC_B) -g3 -fsanitize=address
#-Wall -Wextra -Werror -g3 -fsanitize=address

RM          = @rm -f

PATH_LIBFT  = libft/
PATH_SRC    = src/
PATH_SRC_B	= src_bonus/
PATH_OBJ    = obj/
PATH_OBJ_B    = obj_bonus/

NAME            = pipex
NAME_B          = pipex_bonus
NAME_LIBFT      = libftprintf.a
NAME_INC		= pipex.h
NAME_INC_B		= pipex_bonus.h

LIBFT   = $(PATH_LIBFT)$(NAME_LIBFT)

INC	=	$(PATH_SRC)$(NAME_INC)
INCB=	$(PATH_SRC_B)$(NAME_INC_B)
SRC	=	$(PATH_SRC)main.c \
		$(PATH_SRC)inputs.c \
		$(PATH_SRC)pipes.c 
SRC_BONUS	=	$(PATH_SRC_B)main_bonus.c \
			$(PATH_SRC_B)inputs_bonus.c \
			$(PATH_SRC_B)pipes_bonus.c 
OBJ	=	$(patsubst $(PATH_SRC)%.c, $(PATH_OBJ)%.o, $(SRC))
OBJ_B	=	$(patsubst $(PATH_SRC_B)%.c, $(PATH_OBJ_B)%.o, $(SRC_BONUS))

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(PATH_LIBFT)

$(PATH_OBJ)%.o: $(PATH_SRC)%.c $(INC) | $(PATH_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(PATH_OBJ):
	@mkdir -p $(PATH_OBJ)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

bonus: $(NAME_B)

$(NAME_B): $(OBJ_B) $(LIBFT)
	$(CC) $(CFLAGS_B) $(OBJ_B) $(LIBFT) -o $(NAME_B)

$(PATH_OBJ_B)%.o: $(PATH_SRC_B)%.c $(INCB) | $(PATH_OBJ_B)
	$(CC) $(CFLAGS_B) -c $< -o $@

$(PATH_OBJ_B):
	@mkdir -p $(PATH_OBJ_B)

clean:
	$(RM) $(PATH_OBJ)*.o
	$(RM) $(PATH_OBJ_B)*.o
	$(MAKE) clean -C $(PATH_LIBFT)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_B)
	$(MAKE) fclean -C $(PATH_LIBFT)

re: fclean all

.PHONY: all clean fclean re
