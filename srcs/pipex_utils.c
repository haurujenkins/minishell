/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:01:59 by lle-pier          #+#    #+#             */
/*   Updated: 2024/03/11 16:09:21 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_data(t_data *da, char **envp)
{
	close(da->pipefd[0]);
	close(da->pipefd[1]);
	close(da->fd_input);
	close(da->fd_output);
	da->i = -1;
	if (!(da->cmd1 == NULL))
	{
		while (da->cmd1[++da->i])
			free(da->cmd1[da->i]);
		free (da->cmd1);
	}
	da->i = -1;
	if (!(da->cmd2 == NULL))
	{
		while (da->cmd2[++da->i])
			free(da->cmd2[da->i]);
		free (da->cmd2);
	}
	da->i = -1;
	if (!(envp[0] == NULL))
	{
		while (da->my_path[++da->i])
			free(da->my_path[da->i]);
		free(da->my_path);
	}
}

void	close_all(t_data *da)
{
	if (da->fd_input != -1)
		close(da->fd_input);
	if (da->fd_output != -1)
		close(da->fd_output);
	if (da->pipefd[0] != -1)
		close(da->pipefd[0]);
	if (da->pipefd[1] != -1)
		close(da->pipefd[1]);
}

void	pid_2(t_data *da, char **envp)
{
	close(da->pipefd[1]);
	dup2(da->pipefd[0], STDIN_FILENO);
	dup2(da->fd_output, STDOUT_FILENO);
	close(da->fd_input);
	close(da->fd_output);
	close(da->pipefd[0]);
	da->i = -1;
	if (!(ft_strchr(da->cmd2[0], "/")) && !(envp[0] == NULL))
	{
		while (da->my_path[++da->i])
		{
			da->cmd = ft_strjoin(da->my_path[da->i], da->cmd2[0]);
			if (da->cmd == NULL)
			{
				free_data(da, envp);
				write(2, "Malloc Error", 12);
				exit(EXIT_FAILURE);
			}
			execve(da->cmd, da->cmd2, envp);
			free(da->cmd);
		}
	}
	pid_path_2(da, envp);
}

void	pid_1(t_data *da, char **envp)
{
	close(da->pipefd[0]);
	dup2(da->fd_input, STDIN_FILENO);
	dup2(da->pipefd[1], STDOUT_FILENO);
	close(da->fd_input);
	close(da->fd_output);
	close(da->pipefd[1]);
	da->i = -1;
	if (!(ft_strchr(da->cmd1[0], "/")) && !(envp[0] == NULL))
	{
		while (da->my_path[++da->i])
		{
			da->cmd = ft_strjoin(da->my_path[da->i], da->cmd1[0]);
			if (da->cmd == NULL)
			{
				free_data(da, envp);
				write(2, "Malloc Error", 12);
			}
			execve(da->cmd, da->cmd1, envp);
			free(da->cmd);
		}
	}
	pid_path_1(da, envp);
}

int	check_errors(t_data *da, char **argv)
{
	da->fd_input = open(argv[1], O_RDONLY);
	if (da->fd_input < 0)
		perror("Error opening input file");
	da->fd_output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (da->fd_output < 0)
	{
		close(da->fd_input);
		perror("Error opening output file");
	}
	if (pipe(da->pipefd) == -1)
	{
		close(da->fd_input);
		close(da->fd_output);
		da->fail_pipe = -1;
		perror("Error creating pipe");
	}
	return (1);
}
