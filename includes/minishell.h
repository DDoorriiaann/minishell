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

int		prompt_shell(void);
void	ft_free_all_arr(char **paths, char **cmd);
char	*check_line_path(char **envp);
char	**get_path(char *envp_path);
void	ft_free_arr(char **arr);
char	**get_cmd(char *cmd, char **paths);

#endif
