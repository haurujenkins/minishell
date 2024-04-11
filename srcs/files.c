/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:03:01 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/11 11:43:18 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_files(t_data *da, int index)
{
	//char	**temp_files;
	int		i;

	i = 0;
	da->fd_input = -1;
	da->fd_output = -1;
	//temp_files = NULL;
	if (da->in_tab[index][0] != NULL)
	{
		//temp_files = ft_split(da->in_tab[index][0], ' ');
		while (da->in_tab[index][i])
		{
			da->fd_input = open(da->in_tab[index][i], O_RDONLY);
			if (da->fd_input < 0)
				perror("Error opening input file");
			//free (temp_files[i]);
			i++;
		}
		//free (temp_files);
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
		//temp_files = ft_split(da->out_tab[index][0], ' ');
		while (da->out_tab[index][i])
		{
			da->fd_output = \
			open(da->out_tab[index][i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (da->fd_output < 0)
			{
				close(da->fd_input);
				perror("Error opening output file");
			}
			//free (temp_files[i]);
			i++;
		}
		//free (temp_files);
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
	// else if (index != (da->pnum - 1))
	// {
	// 	close(da->pipefd[0]);
	// 	dup2(da->pipefd[1], STDOUT_FILENO);
	// 	close(da->pipefd[1]);
	// }
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
