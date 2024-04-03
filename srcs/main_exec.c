/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:49:04 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/03 12:56:22 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_child(t_data *da, int index, char **envp)
{
	if (index != 0)
	{
		if (dup2(da->pipefd[index - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	if (index != da->pnum - 1)
	{
		if (dup2(da->pipefd[index][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	close_fd(da, index);
	exec_cmd(da, envp, index);
}

int	exec_recur(t_data *da, char **envp, int index)
{
	if (index == da->pnum)
	{
		close(da->pipefd[index - 1][0]);
		close(da->pipefd[index - 1][1]);
		return (0);
	}
	da->pid1 = fork();
	if (da->pid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (da->pid1 == 0)
	{
		exec_child(da, index, envp);
	}
	else
	{
		if (index != da->pnum - 1)
			close(da->pipefd[index][1]);
		exec_recur(da, envp, index + 1);
	}
	waitpid(da->pid1, NULL, 0);
	return (0);
}

void	exec_cmd(t_data *da, char **envp, int index)
{
	int	i;

	i = 0;
	get_args(da, envp, index);
	check_files(da, index);
	if (check_builtins(da) == 1)
		exit(EXIT_SUCCESS);
	while (da->my_path[i])
	{
		if (da->cmd1[0][0] != '/' && da->cmd1[0][0] != '.')
			da->cmd = ft_strjoin_slash(da->my_path[i], da->cmd1[0]);
		else
			da->cmd = ft_strdup(da->cmd1[0]);
		if (da->cmd == NULL)
		{
			free_data(da, envp);
			write(2, "Malloc Error", 12);
			exit(EXIT_FAILURE);
		}
		if (access(da->cmd, X_OK) == 0)
		{
			execve(da->cmd, da->cmd1, envp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		free(da->cmd);
		i++;
	}
}

int	main_exec(t_data *da, char **envp)
{
	set_pipe(da);
	if (check_extern_builtins(da, envp, 0) == 0)
		exec_recur(da, envp, 0);
	return (0);
}
