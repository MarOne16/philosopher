#COLORS FOR ...
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
#SETUP FOR ....
NAME		=	philo
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -pthread
RM			=	rm -rf
#FILES, DIRECTORIES AND PATHS
HEADER_F	=	philo.h
HEADER_DIR	=	headers/
HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_F))
SOURCE_F	=	parcingtools.c philo.c
SOURCE_DIR	=	
SOURCE		=	$(addprefix $(SOURCE_DIR), $(SOURCE_F))
#OBJECTS FILE
OBJS		=	$(SOURCE:.c=.o)
#COMMANDS
%.o: %.c
				@${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJS)
				@$(CC) $(OBJS) -lpthread -o $(NAME)
				@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

all:			$(NAME)

clean:
				@$(RM) $(OBJS)
				@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean:			clean
				@$(RM) $(NAME)
				@echo "$(RED)object files and executable deleted!$(DEFAULT)"

re:				fclean all

.PHONY:		all clean fclean re
