RED = \033[1;31m
BLUE = \033[1;35m
GREEN = \033[1;32m
DEFAULT = \033[0m
NAME		=	philo
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -pthread
RM			=	rm -rf
HEADER		=	philo.h
SOURCE		=	parcingtools.c philo.c checkphilo.c	
OBJS		=	$(SOURCE:.c=.o)
%.o: %.c
				@${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJS)
				@$(CC) $(OBJS) -o $(NAME)
				@echo "$(GREEN)$(NAME) Created √$(DEFAULT)"

all:			$(NAME)

clean:
				@$(RM) $(OBJS)
				@echo "$(BLUE)Files.o Deleted x$(DEFAULT)"

fclean:			clean
				@$(RM) $(NAME)
				@echo "$(RED)Files.o & Executable deleted X$(DEFAULT)"

re:				fclean all

.PHONY:		all clean fclean re
