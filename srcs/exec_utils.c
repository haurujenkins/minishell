/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:10:19 by lle-pier          #+#    #+#             */
/*   Updated: 2024/03/21 13:36:33 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_all(t_data *da)
{
	da->cmd1 = NULL;
	da->cmd2 = NULL;
	da->cmd = NULL;
	da->fail_pipe = 0;
	da->fd_input = 0;
	da->fd_output = 0;
	da->i = 0;
	da->j = 0;
	da->my_path = NULL;
	da->pid1 = 0;
	da->pid2 = 0;
	da->point_path = NULL;
}

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

void	get_path(t_data *da, char **envp)
{
	if (!(envp[0] == NULL))
	{
		while (!(ft_strchr(envp[da->i], "PATH=")))
			da->i++;
		da->point_path = envp[da->i] + 5;
		da->my_path = ft_split(da->point_path, ':');
		if (da->my_path == NULL)
		{
			free_data(da, envp);
			exit(EXIT_FAILURE);
		}
	}
}
