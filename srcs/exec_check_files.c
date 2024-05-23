/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:53:36 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/23 15:46:51 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	infile_error(t_data *da, int index, int i)
{
	struct stat	filestat;

	while (da->in_tab[index][i])
	{
		da->fd_input = open(da->in_tab[index][i], O_RDONLY);
		if (da->fd_input < 0)
		{
			if (stat(da->in_tab[index][i], &filestat) == -1)
			{
				write(2, "bash: ", 6);
				write(2, da->in_tab[index][i], ft_strlen(da->in_tab[index][i]));
				write(2, ": No such file or directory\n", 28);
				exit(1);
			}
			if (S_ISDIR(filestat.st_mode))
			{
				write(2, "bash: ", 6);
				write(2, da->in_tab[index][i], ft_strlen(da->in_tab[index][i]));
				write(2, ": Is a directory\n", 17);
				exit(1);
			}
			if (!(filestat.st_mode & S_IXUSR))
			{
				write(2, "bash: ", 6);
				write(2, da->in_tab[index][i], ft_strlen(da->in_tab[index][i]));
				write(2, ": Permission denied\n", 21);
				exit(1);
			}
		}
		i++;
	}
}

int	outfile_extern_error(t_data *da, int index, int i)
{
	struct stat	filestat;

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
			if (stat(da->out_tab[index][i], &filestat) == -1)
			{
				write(2, "bash: ", 6);
				write(2, da->out_tab[index][i], ft_strlen(da->out_tab[index][i]));
				write(2, ": No such file or directory\n", 28);
				return (da->exit_status = 1, 1);
			}
			if (S_ISDIR(filestat.st_mode))
			{
				write(2, "bash: ", 6);
				write(2, da->out_tab[index][i], ft_strlen(da->out_tab[index][i]));
				write(2, ": Is a directory\n", 17);
				return (da->exit_status = 1, 1);
			}
			if (!(filestat.st_mode & S_IXUSR))
			{
				write(2, "bash: ", 6);
				write(2, da->out_tab[index][i], ft_strlen(da->out_tab[index][i]));
				write(2, ": Permission denied\n", 21);
				return (da->exit_status = 1, 1);
			}
		}
		i++;
	}
	return (0);
}

void	outfile_error(t_data *da, int index, int i)
{
	struct stat	filestat;

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
			if (stat(da->out_tab[index][i], &filestat) == -1)
			{
				write(2, "bash: ", 6);
				write(2, da->out_tab[index][i], ft_strlen(da->out_tab[index][i]));
				write(2, ": No such file or directory\n", 28);
				exit(1);
			}
			if (S_ISDIR(filestat.st_mode))
			{
				write(2, "bash: ", 6);
				write(2, da->out_tab[index][i], ft_strlen(da->out_tab[index][i]));
				write(2, ": Is a directory\n", 17);
				exit(1);
			}
			if (!(filestat.st_mode & S_IXUSR))
			{
				write(2, "bash: ", 6);
				write(2, da->out_tab[index][i], ft_strlen(da->out_tab[index][i]));
				write(2, ": Permission denied\n", 21);
				exit(1);
			}
		}
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
		i++;
	}
}
