CC = cc
CFLAGS = -Wall -Werror -Wextra -Ilibft

AR = ar rcs

RM = @rm -f

NAME = libftprintf.a
NAME_LIB = libft.a

PATH_LIB = libft

SRC = 	ft_printf.c \
		ft_printf_hex.c \
		ft_printf_utils.c
OBJ = $(SRC:.c=.o)

all : $(PATH_LIB)/$(NAME_LIB) $(NAME) 

$(NAME) : $(OBJ) $(PATH_LIB)/$(NAME_LIB)
	cp $(PATH_LIB)/$(NAME_LIB) $(NAME)
	$(AR) $(NAME) $(OBJ) $(PATH_LIB)/$(NAME_LIB)

$(PATH_LIB)/$(NAME_LIB) :
	@$(MAKE) -C $(PATH_LIB)

fclean: clean
	$(RM) $(NAME) 
	$(RM) $(PATH_LIB)/$(NAME_LIB) 

clean:
	$(RM) *.o
	$(RM) $(PATH_LIB)/*.o

re: fclean all

.PHONY : all bonus clean fclean re