/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:48:53 by lle-pier          #+#    #+#             */
/*   Updated: 2024/03/13 15:42:36 by lle-pier         ###   ########.fr       */
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
}				t_data;

void	free_data(t_data *da, char **envp);
void	pid_2(t_data *da, char **envp);
void	pid_1(t_data *da, char **envp);
void	close_all(t_data *da);
int		check_errors(t_data *da, char **argv);
void	pid_path_1(t_data *da, char **envp);
void	pid_path_2(t_data *da, char **envp);
void	set_all(t_data *da);
void	free_child(t_data *da);
int		main_pipex(char **argv, char **envp);

#endif