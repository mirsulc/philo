NAME	=	philo
CC	=	cc
FLAGS	=	-Wall -Wextra -Werror -g #-fsanitize=address
FLAGS2	=	-pthread

SRC	=	src/philo.c \
		src/utils.c \
		src/utils2.c \



#H_FILE	= include/philo.h
RM	= rm -f


OBJ =		$(SRC:.c=.o)

all: $(NAME) 

$(NAME): $(OBJ) 
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(FLAGS2)
	@ echo "Philosophers are redy to eat"

clean:
	@$(RM) $(OBJ)
	@make clean -C --no-print-directory --silent
	@ echo "object files deleted"

fclean: clean
	@ make fclean -C --no-print-directory --silent
	@ /bin/rm -f $(NAME)
	@ echo "all files deleted"

re: clean all

.PHONY: all clean fclean re 

