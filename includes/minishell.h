#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# define ERROR -1
# define MULTIPLE_N 0
# define NOT_MULTIPLE 1
# define TRUE 1
# define FALSE 0

extern int	g_return;

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

typedef struct s_redirections
{
	int		in_redirection;
	int		out_redirection;
	char	*infile;
	char	*outfile;
	int		out_filename_len;
	int		fd_in;
	int		fd_out;
}	t_redirections;

typedef enum error
{
	NO_ERROR,
	MALLOC_ERROR,
	COMMAND_ERROR,
	MISSING_ARGS,
	FORK_ERROR,
	FILE_ERROR,
	PIPE_ERROR,
}	t_error;

typedef struct s_fork
{
	char			**cmd;
	pid_t			pid;
	int				pipe_fd[2];
	t_redirections	*redirections;
}	t_fork;

typedef struct s_pipes_data
{
	int				pipes_detected;
	int				pipes_count;
	int				cmds_count;
	int				tmp_infile;
	char			***pipes_cmds;
	t_fork			**fork;
}	t_pipes_data;

typedef struct s_pipes_init
{
	int		pipe_nb;
	int		pipe_arg;
	int		args_count;
}	t_pipes_init;

////////FUNCTIONS
//PROMPT
void	ft_free_all_arr(char **paths, char **cmd);
int		prompt_shell(char **envp_l,	t_pipes_data *pipes);

/****
PATHS
****/

char	*check_line_path(char **envp);
char	**get_path(char *envp_path);
char	**get_cmd(char *cmd, char **paths);

//PARSER
char	**raw_input_parser(char *input);
char	***pipes_parser(char **argv, char **envp_l, t_pipes_data *pipes);
char	**copy_envp(char **envp);
void	interpret_env_variables(char **argv, char **envp);
int		interpret_current_env_variable(char **argv, int start,
			int arg_index, char **envp);
char	*extract_env_variable_name(char *arg, int start);
int		variable_found_inside_env(char *env_variable_name, char **envp);
int		delete_var_inside_arg(char **argv, int start, int index);
int		backup_arg_before_var(char *backup, char *original, int end);
void	backup_arg_after_var(char *backup, char *original,
			int end, int current_char);
void	replace_var_by_status_code(char **argv, int start, int index);
int		env_variable_name_exists(char *arg, int start, char **envp);
void	remove_quotes(char **argv);
char	*isolate_pipe_symbols(char *input);

//REDIRECTIONS
char	**handle_infile_redirection(char **argv, t_redirections *redirections);
char	**handle_outfile_redirection(char **argv, t_redirections *redirections);
int		is_chevron_alone(char **argv, int arg_index, char chevron_type);
void	reset_redirections(t_redirections *redirections);
int		is_chevron(char c);

//DECORATION
void	print_decoration(void);

/***
FREE
***/

void	ft_free_all_arr(char **paths, char **cmd);
void	free_2d_arr(char **arr);
void	free_pipes_cmds_arr(char ***arr);
void	free_forks(t_pipes_data *pipes_data);

/****
ERROR
****/

void	ft_error_cmd(char *str);
void	ft_error(void);
int		ft_error_return(void);

/***
EXEC
***/

int		exec_cmd(char **argv, char **envp, t_pipes_data *pipes);

/******
BUILTIN
******/

void	builtin_echo(char **argv);
void	builtin_pwd(void);
int		builtin_cd(char **args, char **envp_l, int argc);
char	**builtin_export(char **envp_l, char **argv, int argc);
void	builtin_env( char **envp_l);
void	builtin_exit(char **argv, char **envp_l,
			t_pipes_data *pipes_data);

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
int		check_syntax(char *arg);
int		len_arg(char *argv);
void	sort_first_char(char **envp_l);
void	sort_after_first_char(char **envp_l);
int		sort_ascii(char **envp_l, int ret, int i);
void	dup_arr(char **src, char **dst);
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
int		count_splitted_arguments(char **argv);
char	**delete_argument(char **argv, int arg_index, int args_to_delete);
int		find_next_corresponding_quote(char *input, int end, char quote_type);

/*****
EXPORT
*****/

void	print_export(char **export_envp_l);
char	**builtin_unset(char **envp_l, char **argv);

/*****
SIGNAL
*****/

void	ft_signal(void);

/*****
PIPES
*****/

int		pipex(char ***pipes_cmds, t_pipes_data *pipes_data, char **envp);

////PATHS
char	**split_path(char *env_path);
char	**get_paths(char **envp);
void	get_files(char **argv, int argc, t_pipes_data *data);
void	find_cmd_path(t_pipes_data *data);
int		is_cmd_litteral_path(t_pipes_data *data, char **cmd_split, int i);
void	search_valid_path(t_pipes_data *data, char **cmd_split, int i);

////COMMANDS
t_error	get_cmds(char **argv, int argc, t_pipes_data *data);
t_error	ft_split_commands(t_pipes_data *data);
t_error	exec_cmds(t_pipes_data *data, char **envp);
void	alert_command_error(t_pipes_data *data);

////MEMORY MANAGEMENT
void	init_data(t_pipes_data *data, char ***pipes_cmds);
void	ft_free_all(t_pipes_data *data);
void	ft_free_arr(char **tmp_cmd_split);
void	ft_free_arr3d(char ***arr);

#endif
