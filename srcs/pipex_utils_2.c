/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:16:52 by lle-pier          #+#    #+#             */
/*   Updated: 2024/03/13 15:34:33 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pid_path_1(t_data *da, char **envp)
{
	if (envp[0] == NULL)
	{
		if (1)
			execve(da->cmd1[0], da->cmd1, envp);
		write(STDERR_FILENO, "env: '", 6);
		write(STDERR_FILENO, da->cmd1[0], ft_strlen(da->cmd1[0]));
		write(STDERR_FILENO, "' No such file or directory\n", 28);
		exit(EXIT_FAILURE);
	}
	else
		execve(da->cmd1[0], da->cmd1, envp);
	write(STDERR_FILENO, "command not found : ", 20);
	write(STDERR_FILENO, da->cmd1[0], ft_strlen(da->cmd1[0]));
	write(STDERR_FILENO, "\n", 1);
	free_child(da);
	exit(EXIT_FAILURE);
}

void	pid_path_2(t_data *da, char **envp)
{
	if (envp[0] == NULL)
	{
		if (1)
			execve(da->cmd2[0], da->cmd2, envp);
		write(STDERR_FILENO, "env: '", 6);
		write(STDERR_FILENO, da->cmd2[0], ft_strlen(da->cmd2[0]));
		write(STDERR_FILENO, "' No such file or directory\n", 28);
		exit(EXIT_FAILURE);
	}
	else
		execve(da->cmd2[0], da->cmd2, envp);
	write(STDERR_FILENO, "command not found : ", 20);
	write(STDERR_FILENO, da->cmd2[0], ft_strlen(da->cmd2[0]));
	write(STDERR_FILENO, "\n", 1);
	free_child(da);
	exit(EXIT_FAILURE);
}

void	set_all(t_data *da)
{
	da->cmd1 = NULL;
	da->cmd1 = NULL;
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

void	free_child(t_data *da)
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
	free(da->my_path);
}
