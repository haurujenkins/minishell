/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:48:53 by lle-pier          #+#    #+#             */
/*   Updated: 2024/03/25 11:01:48 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct data_s
{
	int		i;
	int		j;
	int		line;
	int		out;
	char	**cmd1;
	char	**cmd2;
	char	**my_path;
	char	*cmd;
	char	*point_path;
	int		fd_input;
	int		fd_output;
	int		fail_pipe;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		pnum;
	char	***args;
}				t_data;


int		main_exec(char ***args, char **envp, int pnum);
//int		check_files(t_data *da, char **args, int pnum);
int		exec_cmd(t_data *da, char ***args, char **envp);
void	set_all(t_data *da);
void	free_data(t_data *da, char **envp);
void	get_path(t_data *da, char **envp);

#endif