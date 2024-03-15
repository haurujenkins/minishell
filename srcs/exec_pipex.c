/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:01:33 by lle-pier          #+#    #+#             */
/*   Updated: 2024/03/15 14:24:47 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_files(t_data *da, char **args, int pnum)
{
	if (args[da->line][2] != NULL)
	{
		da->fd_input = open(args[da->line][2], O_RDONLY);
		if (da->fd_input < 0)
			perror("Error opening input file");
	}
	if (args[da->line][3] != NULL)
	{
		da->fd_output = \
		open(args[da->line][3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (da->fd_output < 0)
		{
			close(da->fd_input);
			perror("Error opening output file");
		}
	}
	if (pnum > 1)
	{
		if (pipe(da->pipefd) == -1)
		{
			close(da->fd_input);
			close(da->fd_output);
			da->fail_pipe = -1;
			perror("Error creating pipe");
		}
	}
	return (1);
}
