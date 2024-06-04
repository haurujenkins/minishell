/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:03:01 by lle-pier          #+#    #+#             */
/*   Updated: 2024/06/03 17:44:02 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_files(t_data *da, int index)
{
	da->fd_input = -1;
	da->fd_output = -1;
	if (da->in_tab[index][0] != NULL)
		check_infile(da, index);
	if (da->fd_input != -1)
	{
		if (dup2(da->fd_input, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(127);
		}
		close(da->fd_input);
	}
	if (da->out_tab[index][0] != NULL)
		check_outfile(da, index);
	if (da->fd_output != -1)
	{
		if (dup2(da->fd_output, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(127);
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
