/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:24:11 by lle-pier          #+#    #+#             */
/*   Updated: 2024/06/03 17:09:47 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd(t_data *da)
{
	int	i;

	i = -1;
	while (da->cmd1[++i])
		free(da->cmd1[i]);
	free(da->cmd1);
	da->cmd1 = NULL;
}

void	check_cmd_stat(t_data *da, int index)
{
	struct stat	filestat;

	if ((da->cmd1[0][0] == '.' && da->cmd1[0][1] == '/') || \
	da->cmd1[0][0] == '/')
	{
		if (stat(da->cmd1[0], &filestat) < 0)
		{
			write(2, ": No such file or directory\n", 29);
			da->exit_status = 127;
			exit_child(da, index);
		}
		if (S_ISDIR(filestat.st_mode))
		{
			write(2, ": Is a directory\n", 17);
			da->exit_status = 126;
			exit_child(da, index);
		}
		if (!(filestat.st_mode & S_IXUSR))
		{
			write(2, ": Permission denied\n", 21);
			da->exit_status = 126;
			exit_child(da, index);
		}
	}
	da->cmd = ft_strdup(da->cmd1[0]);
}

void	check_cmd(t_data *da, int i, char **envp, int index)
{
	while (da->my_path[i])
	{
		if (da->cmd1[0][0] != '/' && da->cmd1[0][0] != '.')
			da->cmd = ft_strjoin_slash(da->my_path[i], da->cmd1[0]);
		else
			check_cmd_stat(da, index);
		if (da->cmd == NULL)
		{
			free_data(da, envp);
			write(2, "Malloc Error", 12);
			exit_child(da, index);
		}
		if (access(da->cmd, X_OK) == 0)
		{
			execve(da->cmd, da->cmd1, envp);
			perror("execve");
			free(da->cmd);
			free_cmd_notfound(da);
			exit(126);
		}
		free(da->cmd);
		i++;
	}
}

void	check_exec_exit(int index, t_data *da, int child_status)
{
	if (index == da->pnum - 1)
		da->exit_status = WEXITSTATUS(child_status);
	if (g_stop_execution == 2)
		da->exit_status = 131;
	if (g_stop_execution == 1)
		da->exit_status = 130;
	if (g_stop_execution == 1 || g_stop_execution == 2)
		g_stop_execution = 0;
}
