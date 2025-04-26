CC = gcc
CFLAGS = -Wall -Werror -Wextra

AR = ar rcs

RM = @rm -f

NAME = libgnl_p.a
SRC = 	get_next_line_p.c \
		get_next_line_utils_p.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) 
	$(AR) $(NAME) $(OBJ) get_next_line_p.h

fclean: clean
	$(RM) $(NAME) 

clean:
	$(RM) *.o

re: fclean all

.PHONY : all bonus clean fclean re