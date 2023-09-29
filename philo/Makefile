NAME	=	philo
CC	=	cc
FLAGS	=	-Wall -Wextra -Werror -g #-fsanitize=address
FLAGS2	=	-pthread

SRC	=	philo.c \
		utils.c \
		utils2.c \
		time_handler.c \
		activities.c \


#H_FILE	= include/philo.h
RM	= rm -f


OBJ =		$(SRC:.c=.o)

all: $(NAME) 

$(NAME): $(OBJ) 
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(FLAGS2)
	@ echo "Philosophers are redy to live"

clean:
	@$(RM) $(OBJ)
	@ echo "object files deleted"

fclean: clean
	@ /bin/rm -f $(NAME)
	@ echo "all files deleted"

re: clean all

.PHONY: all clean fclean re 

