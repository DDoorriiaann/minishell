_YELLOW="\e[38;5;226m"
_RED="\e[38;5;9m"
_GREEN="\e[38;5;10m" 

NAME		= minishell 

SRC			=	main.c\
				prompt.c\
				free.c\
				paths.c\
				parser.c\
				error.c\
				builtin.c\
				builtin_export1.c\
				builtin_export2.c\
				builtin_env.c\
				utils1.c\
				utils2.c\
				utils3.c\
				utils4.c\
				env_var_interpreter.c\
				env_var_interpreter2.c\
				decoration.c\

SRCDIR 		= ./src/

INCDIR 		= ./includes/

SRCS 		= $(addprefix $(SRCDIR), $(SRC))

OBJS		= $(SRCS:.c=.o)

CFLAGS 		= -Wall -Werror -Wextra -g -Llibft -lft -I$(INCDIR) -Ilibft -L/usr/local/lib -I/usr/local/include -lreadline 

CC			= gcc

.c.o:
			@$(CC) $(CFLAGS) -c $< -o $@

all :		$(NAME)

$(NAME):	$(OBJS)
			@make -sC libft
			@$(CC) $(OBJS) -o $(NAME) $(CFLAGS)
			@echo $(_GREEN)
			@echo "*************************"
			@echo "*                       *"
			@echo "*  COMPILATION SUCCESS  *"
			@echo "*                       *"
			@echo "*************************"

clean_1 : 
			@echo $(_YELLOW)
			@echo "*************************"
			@echo "*                       *"
			@echo "*    CLEAN  COMPLETE    *"
			@echo "*                       *"
			@echo "*************************"

clean : 	clean_1
			@rm -f $(OBJS)
			@make -sC libft clean
fclean_1 :
			@echo $(_RED)
			@echo "*************************"
			@echo "*                       *"
			@echo "*    FCLEAN COMPLETE    *"
			@echo "*                       *"
			@echo "*************************"

fclean : 	clean fclean_1
			@rm -f $(NAME)
			@make -sC libft fclean
	
re : 		fclean all 

.PHONY: all clean fclean re
