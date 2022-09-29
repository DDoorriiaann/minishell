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
char	**parser(char *input);
char	**copy_envp(char **envp);

/***
FREE
***/

void	ft_free_all_arr(char **paths, char **cmd);
void	ft_free_arr(char **arr);

/****
ERROR
****/

void	ft_error_cmd(char *str);

/***
EXEC
***/

void	exec_cmd(char *argv, char **envp);

/******
BUILTIN
******/

void	builtin_echo(char *buffer);
void	builtin_pwd(void);
int		builtin_cd(char *buffer, char **envp_l);

/******
UTILS
******/

int		ft_isspace(char c);
int		ft_is_quote(char c);
int		skip_spaces(char *input, int index);
int		find_word_end(char *input, int index);
void	free_2d_arr(char **arr);
int		find_closing_quote(char *input, int end, char quote_type);
int		go_to_word_end(char *input, int index, int *argc);
int		go_to_quote_end(char *input, int index, int *argc);

#endif
