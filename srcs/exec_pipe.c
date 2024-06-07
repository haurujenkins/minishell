/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:52:20 by lle-pier          #+#    #+#             */
/*   Updated: 2024/06/07 12:55:44 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_pipe(t_data *da)
{
	da->pipefd = (int **)malloc((da->pnum + 1) * sizeof(int *));
	if (da->pipefd == NULL)
	{
		perror ("malloc");
		return (-1);
	}
	da->i = 0;
	while (da->i < da->pnum)
	{
		da->pipefd[da->i] = (int *)malloc(2 * sizeof(int));
		if (da->pipefd[da->i] == NULL)
		{
			perror("malloc");
			return (-1);
		}
		if (pipe(da->pipefd[da->i]) == -1)
		{
			perror("pipe");
			return (-1);
		}
		da->i++;
	}
	da->pipefd[da->i] = NULL;
	return (0);
}

int	is_fd_open(int fd)
{
	int	result;

	result = isatty(fd);
	if (result != 0)
		return (1);
	else
	{
		if (errno != EBADF)
			return (1);
		else
			return (0);
	}
}

void	free_pipe(t_data *da)
{
	da->i = 0;
	if (da->pipefd == NULL || da->pnum == 0 || da->pipefd[0] == NULL)
		return ;
	while (da->pipefd[da->i] != NULL)
	{
		if (is_fd_open(da->pipefd[da->i][0]))
			close(da->pipefd[da->i][0]);
		if (is_fd_open(da->pipefd[da->i][1]))
			close(da->pipefd[da->i][1]);
		free(da->pipefd[da->i]);
		da->i++;
	}
	free(da->pipefd);
	da->pipefd = NULL;
}

void	close_fds(t_data *da)
{
	if (is_fd_open(da->fd_input))
		close(da->fd_input);
	if (is_fd_open(da->fd_output))
		close(da->fd_output);
}
