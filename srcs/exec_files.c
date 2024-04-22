/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:03:01 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/19 15:12:57 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_files(t_data *da, int index)
{
	int	i;

	i = 0;
	da->fd_input = -1;
	da->fd_output = -1;
	if (da->in_tab[index][0] != NULL)
	{
		while (da->in_tab[index][i])
		{
			da->fd_input = open(da->in_tab[index][i], O_RDONLY);
			if (da->fd_input < 0)
				perror("Error opening input file");
			i++;
		}
	}
	if (da->fd_input != -1)
	{
		if (dup2(da->fd_input, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(da->fd_input);
	}
	if (da->out_tab[index][0] != NULL)
	{
		i = 0;
		while (da->out_tab[index][i])
		{
			if (da->append_tab[index][i] == NULL || \
			da->append_tab[index][i][0] == '0')
				da->fd_output = open(da->out_tab[index][i], O_WRONLY \
				| O_CREAT | O_TRUNC, 0644);
			else
				da->fd_output = open(da->out_tab[index][i], \
				O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (da->fd_output < 0)
			{
				close(da->fd_input);
				perror("Error opening output file");
			}
			i++;
		}
	}
	if (da->fd_output != -1)
	{
		if (dup2(da->fd_output, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(da->fd_output);
	}
	return (1);
}

void	close_fd(t_data *da, int index)
{
	da->i = 0;
	while (da->i < da->pnum - 1)
	{
		if (da->i != index - 1 && da->i != index)
		{
			close(da->pipefd[da->i][0]);
			close(da->pipefd[da->i][1]);
		}
		da->i++;
	}
}
