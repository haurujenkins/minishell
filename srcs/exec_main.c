/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:49:04 by lle-pier          #+#    #+#             */
/*   Updated: 2024/06/05 15:00:15 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_child(t_data *da, int index, char **envp)
{
	if (da->args[index][0] == NULL)
	{
		check_files(da, index);
		exit_child(da, index);
	}
	if (index != 0)
	{
		if (dup2(da->pipefd[index - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit_child(da, index);
		}
	}
	if (index != da->pnum - 1)
	{
		if (dup2(da->pipefd[index][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit_child(da, index);
		}
	}
	close_fd(da, index);
	get_args(da, envp, index);
	check_files(da, index);
	exec_cmd(da, envp, index);
}

int	exec_recur(t_data *da, char **envp, int index)
{
	int		child_status;

	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigquit_handler_child);
	if (index == da->pnum)
	{
		close(da->pipefd[index - 1][0]);
		return (close(da->pipefd[index - 1][1]), -1);
	}
	da->pid1 = fork();
	if (da->pid1 == -1)
		return (perror("fork"), -1);
	else if (da->pid1 == 0)
		exec_child(da, index, envp);
	else
	{
		if (index != da->pnum - 1)
			close(da->pipefd[index][1]);
		da->children[index] = da->pid1;
		exec_recur(da, envp, index + 1);
	}
	waitpid(da->pid1, &child_status, 0);
	check_exec_exit(index, da, child_status);
	return (0);
}

void	exec_cmd(t_data *da, char **envp, int index)
{
	int	j;

	free_pipe(da);
	if (check_builtins(da, index) == 1)
	{
		j = -1;
		while (da->my_env[++j] != NULL)
			free(da->my_env[j]);
		free(da->my_env);
		free_struct(da);
		exit(EXIT_SUCCESS);
	}
	else
		check_cmd(da, 0, envp, index);
	write(2, da->cmd1[0], ft_strlen(da->cmd1[0]));
	write(2, ": command not found\n", 20);
	free_cmd_notfound(da);
	exit(127);
}

void	del_tmpfiles(t_data *da, int index)
{
	int	i;

	while (index < da->pnum)
	{
		i = 0;
		while (da->in_tab[index][i] != NULL && da->delim_tab[index][i] != NULL)
		{
			if (da->delim_tab[index][i][0] == '1')
				unlink(da->in_tab[index][i]);
			i++;
		}
		index++;
	}
}

int	main_exec(t_data *da, char **envp)
{
	int	status;
	int	i;

	i = -1;
	status = 0;
	da->children = malloc(da->pnum * sizeof(pid_t));
	if (da->children == NULL)
		return (perror("malloc"), -1);
	if (set_pipe(da) == -1)
		return (-1);
	if (check_extern_builtins(da, envp, 0) == 0)
	{
		while (++i < da->pnum)
			da->children[i] = -1;
		if (exec_recur(da, envp, 0) == -1)
			return (-1);
		i = -1;
	}
	else
		i = 0;
	while (++i < da->pnum)
		if (da->children[i] != -1)
			waitpid(da->children[i], &status, 0);
	del_tmpfiles(da, 0);
	return (0);
}
