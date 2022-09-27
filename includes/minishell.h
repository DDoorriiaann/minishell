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
# define MULTIPLE_N 0
# define NOT_MULTIPLE 1

/****
PATHS
****/

char	*check_line_path(char **envp);
char	**get_path(char *envp_path);
char	**get_cmd(char *cmd, char **paths);
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
int		prompt_shell(char **envp_l);

/******
BUILTIN
******/

void	builtin_echo(char *buffer);
void	builtin_pwd(void);
int		builtin_cd(char *buffer, char **envp_l);

#endif
