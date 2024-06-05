/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check_stat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:43:49 by lle-pier          #+#    #+#             */
/*   Updated: 2024/06/05 14:33:04 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	extern_outfile_stat(t_data *da, int index, int i)
{
	struct stat	filestat;

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
	return (0);
}

void	outfile_stat(t_data *da, int index, int i)
{
	struct stat	filestat;

	if (stat(da->out_tab[index][i], &filestat) == -1)
	{
		write(2, "bash: ", 6);
		write(2, da->out_tab[index][i], ft_strlen(da->out_tab[index][i]));
		write(2, ": No such file or directory\n", 28);
		exit_child(da, index);
	}
	if (S_ISDIR(filestat.st_mode))
	{
		write(2, "bash: ", 6);
		write(2, da->out_tab[index][i], ft_strlen(da->out_tab[index][i]));
		write(2, ": Is a directory\n", 17);
		exit_child(da, index);
	}
	if (!(filestat.st_mode & S_IXUSR))
	{
		write(2, "bash: ", 6);
		write(2, da->out_tab[index][i], ft_strlen(da->out_tab[index][i]));
		write(2, ": Permission denied\n", 21);
		exit_child(da, index);
	}
}

void	infile_stat(t_data *da, int index, int i)
{
	struct stat	filestat;

	if (stat(da->in_tab[index][i], &filestat) == -1)
	{
		write(2, "bash: ", 6);
		write(2, da->in_tab[index][i], ft_strlen(da->in_tab[index][i]));
		write(2, ": No such file or directory\n", 28);
		exit_child(da, index);
	}
	if (S_ISDIR(filestat.st_mode))
	{
		write(2, "bash: ", 6);
		write(2, da->in_tab[index][i], ft_strlen(da->in_tab[index][i]));
		write(2, ": Is a directory\n", 17);
		exit_child(da, index);
	}
	if (!(filestat.st_mode & S_IXUSR))
	{
		write(2, "bash: ", 6);
		write(2, da->in_tab[index][i], ft_strlen(da->in_tab[index][i]));
		write(2, ": Permission denied\n", 21);
		exit_child(da, index);
	}
}
