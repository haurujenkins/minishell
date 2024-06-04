/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:53:36 by lle-pier          #+#    #+#             */
/*   Updated: 2024/06/04 16:27:34 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	infile_error(t_data *da, int index, int i)
{
	while (da->in_tab[index][i])
	{
		da->fd_input = open(da->in_tab[index][i], O_RDONLY);
		if (da->fd_input < 0)
		{
			infile_stat(da, index, i);
		}
		if (da->in_tab[index][i + 1])
			close(da->fd_input);
		i++;
	}
}

int	outfile_extern_error(t_data *da, int index, int i)
{
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
			if (extern_outfile_stat(da, index, i) == 1)
				return (1);
		if (da->out_tab[index][i + 1])
			close(da->fd_output);
		i++;
	}
	return (0);
}

void	outfile_error(t_data *da, int index, int i)
{
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
			outfile_stat(da, index, i);
		if (da->out_tab[index][i + 1])
			close(da->fd_output);
		i++;
	}
}

void	check_infile(t_data *da, int index)
{
	int			i;

	i = 0;
	while (da->in_tab[index][i])
	{
		da->fd_input = open(da->in_tab[index][i], O_RDONLY);
		if (da->fd_input < 0)
		{
			infile_error(da, index, i);
		}
		if (da->in_tab[index][i + 1])
			close(da->fd_input);
		i++;
	}
}

void	check_outfile(t_data *da, int index)
{
	int	i;

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
			outfile_error(da, index, i);
		}
		if (da->out_tab[index][i + 1])
			close(da->fd_output);
		i++;
	}
}
