/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:48:53 by lle-pier          #+#    #+#             */
/*   Updated: 2024/03/21 11:46:50 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
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

void	get_args(t_data *da, char **envp);
int		main_exec(t_data *da, char **envp);
int		check_files(t_data *da);
int		exec_cmd(t_data *da, char **envp);
void	set_all(t_data *da);
void	free_data(t_data *da, char **envp);
void	get_path(t_data *da, char **envp);

#endif