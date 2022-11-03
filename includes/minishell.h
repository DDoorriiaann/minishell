#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# define ERROR -1
# define MULTIPLE_N 0
# define NOT_MULTIPLE 1
# define TRUE 1
# define FALSE 0

typedef struct s_env_var
{
	int		index;
	char	*name;
	int		name_len;
	char	*value;
	int		len;
}	t_env_var;

typedef struct s_arg_update
{
	char	*original_arg;
	char	*updated_arg;
}	t_arg_update;

////////FUNCTIONS
//PROMPT
void	ft_free_all_arr(char **paths, char **cmd);
int		prompt_shell(char **envp_l);

/****
PATHS
****/

char	*check_line_path(char **envp);
char	**get_path(char *envp_path);
char	**get_cmd(char *cmd, char **paths);

//PARSER
char	**arg_parser(char *input, char **envp, int s_code);
char	**copy_envp(char **envp);
void	interpret_env_variables(char **argv, char **envp, int s_code);
int		interpret_current_env_variable(char **argv, int start,
			int arg_index, char **envp);
char	*extract_env_variable_name(char *arg, int start);
int		variable_found_inside_env(char *env_variable_name, char **envp);
int		delete_var_inside_arg(char **argv, int start, int index);
int		backup_arg_before_var(char *backup, char *original, int end);
void	backup_arg_after_var(char *backup, char *original,
			int end, int current_char);
void	replace_var_by_status_code(char **argv, int start,
			int index, int s_code);
int		env_variable_name_exists(char *arg, int start, char **envp);
void	remove_quotes(char **argv);

//DECORATION
void	print_decoration(void);

/***
FREE
***/

void	ft_free_all_arr(char **paths, char **cmd);
void	free_2d_arr(char **arr);

/****
ERROR
****/

void	ft_error_cmd(char *str);
void	ft_error(void);
int		ft_error_return(void);

/***
EXEC
***/

int		exec_cmd(char **argv, char **envp);

/******
BUILTIN
******/

void	builtin_echo(char **argv);
void	builtin_pwd(void);
int		builtin_cd(char *argv, char **envp_l);
char	**builtin_export(char **envp_l, char **argv, int argc);
void	builtin_env( char **envp_l);
void	builtin_exit(char **argv);

/******
UTILS
******/

int		ft_isspace(char c);
int		ft_is_quote(char c);
int		skip_spaces(char *input, int index);
int		find_word_end(char *input, int index);
int		find_closing_quote(char *input, int end, char quote_type);
int		go_to_word_end(char *input, int index, int *argc);
int		go_to_quote_end(char *input, int index, int *argc);
int		check_syntax(char *argv);
int		len_arg(char *argv);
void	sort_first_char(char **envp_l);
void	sort_after_first_char(char **envp_l);
int		sort_ascii(char **envp_l, int ret, int i);
int		len_arg(char *argv);
void	dup_arr(char **src, char **dst);
int		check_syntax(char *argv);
int		size_env(char **envp_l);
int		size_arg(char *argv);
int		check_arg(char **envp_l, char *argv);
int		check_if_new_variables(char **argv, char **envp_l);
void	update_envp_l(char **argv, char **envp_l);
int		size_arg_before_equal(char *argv);
char	*extract_arg_with_equal(char *argv);
char	*extract_arg_after_equal(char *argv);
int		check_char_equal(char *argv);
int		check_plus(char *argv);
char	**check_dollars(char **argv);
void	print_error(char *argv);
void	print_error_unset(char *argv);
int		check_syntax_unset(char *argv);

/*****
EXPORT
*****/

void	print_export(char **export_envp_l);

char	**builtin_unset(char **envp_l, char **argv);

#endif
