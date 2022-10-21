_YELLOW="\e[38;5;226m"
_RED="\e[38;5;9m"
_GREEN="\e[38;5;10m" 

NAME		= minishell 

SRC			=	main.c\
				decoration.c\
				paths.c\
				error.c\
				builtin/builtin.c\
				builtin/export/extract_arg/extract_arg_after_equal.c\
				builtin/export/extract_arg/extract_arg_with_equal.c\
				builtin/export/update_envp_l/update_envp_l.c\
				builtin/export/print_export/print_export.c\
				builtin/export/check_arg/check_char_equal.c\
				builtin/export/check_arg/check_plus.c\
				builtin/export/check_arg/check_if_new_variables.c\
				builtin/export/check_arg/compare_arg_envp_l.c\
				builtin/export/size_env_or_arg/len_arg.c\
				builtin/export/size_env_or_arg/size_arg.c\
				builtin/export/size_env_or_arg/size_arg_before_equal.c\
				builtin/export/size_env_or_arg/size_env.c\
				builtin/export/sort_export/sort_after_first_char.c\
				builtin/export/sort_export/sort_ascii.c\
				builtin/export/sort_export/sort_first_char.c\
				builtin/export/export.c\
				builtin/env/builtin_env.c\
        builtin.c\
				free.c\
				utils1.c\
				utils2.c\
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
