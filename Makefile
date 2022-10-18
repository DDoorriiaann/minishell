_YELLOW="\e[38;5;226m"
_RED="\e[38;5;9m"
_GREEN="\e[38;5;10m" 

NAME		= minishell 

SRC			=	main.c\
				decoration.c\
				paths.c\
				error.c\
				free.c\
				utils1.c\
				utils2.c\
				utils3.c\
				utils4.c\
				prompt.c\
				arg_parser/arg_parser.c\
				arg_parser/env_var_interpreter/interpret_env_variables.c\
				arg_parser/env_var_interpreter/utils_env_var_interpreter.c\
				arg_parser/env_var_interpreter/extract_env_var_name.c\
				arg_parser/env_var_interpreter/delete_var_inside_arg.c\
				arg_parser/env_var_interpreter/replace_var_by_status_code.c\
				arg_parser/env_var_interpreter/interpret_current_env_variable.c\
				arg_parser/quotes_remover/remove_quotes.c\
				arg_parser/redirections/handle_infile_redirection.c\
				builtin_export1.c\
				builtin_export2.c\
				builtin_env.c\
				builtin.c\

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
