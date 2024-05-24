/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:49:04 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/23 11:43:40 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler_child()
{
	printf("\n");
	stop_execution = 1;
}

void	sigquit_handler_child()
{
	printf("Quit (core dumped)\n");
	stop_execution = 2;
}

void	exec_child(t_data *da, int index, char **envp)
{
	if (da->args[index][0] == NULL)
	{
		check_files(da, index);
		exit(EXIT_SUCCESS);
	}
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
		return (close(da->pipefd[index - 1][1]), 0);
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
		{
			close(da->pipefd[index][1]);
		}
		da->children[index] = da->pid1;
		exec_recur(da, envp, index + 1);
	}
	waitpid(da->pid1, &child_status, 0);
	if (index == da->pnum - 1)
		da->exit_status = WEXITSTATUS(child_status);
	if (stop_execution == 2)
	{
		stop_execution = 0;
		da->exit_status = 131;
	}
	if (stop_execution == 1)
	{
		stop_execution = 0;
		da->exit_status = 130;
	}
	return (0);
}

void	check_cmd_stat(t_data *da)
{
	struct stat	filestat;

	if ((da->cmd1[0][0] == '.' && da->cmd1[0][1] == '/') || \
	da->cmd1[0][0] == '/')
	{
		if (stat(da->cmd1[0], &filestat) < 0)
		{
			write(2, da->cmd1[0], ft_strlen(da->cmd1[0]));
			write(2, ": No such file or directory\n", 29);
			exit(127);
		}
		if (S_ISDIR(filestat.st_mode))
		{
			write(2, da->cmd1[0], ft_strlen(da->cmd1[0]));
			write(2, ": Is a directory\n", 17);
			exit(126);
		}
		if (!(filestat.st_mode & S_IXUSR))
		{
			write(2, da->cmd1[0], ft_strlen(da->cmd1[0]));
			write(2, ": Permission denied\n", 21);
			exit(126);
		}
	}
	da->cmd = ft_strdup(da->cmd1[0]);
}

void	check_cmd(t_data *da, int i, char **envp)
{

	while (da->my_path[i])
	{
		if (da->cmd1[0][0] != '/' && da->cmd1[0][0] != '.')
			da->cmd = ft_strjoin_slash(da->my_path[i], da->cmd1[0]);
		else
			check_cmd_stat(da);
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

void	exec_cmd(t_data *da, char **envp, int index)
{
	int			j;

	if (check_builtins(da, index) == 1)
	{
		free_struct(da);
		j = -1;
		while (da->my_env[++j] != NULL)
			free(da->my_env[j]);
		free(da->my_env);
		exit(EXIT_SUCCESS);
	}
	if (ft_strchr(da->cmd1[0], "$?") == 1)
	{
		da->cmd = ft_strdup(ft_itoa(da->exit_status));
		if (ft_strlen(da->args[0][0]) > 2)
			da->cmd = ft_strjoin_ori(da->cmd, da->args[0][0] + 2);
		write(2, da->cmd, ft_strlen(da->cmd));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	else
		check_cmd(da, 0, envp);
	write(2, da->cmd1[0], ft_strlen(da->cmd1[0]));
	write(2, ": command not found\n", 20);
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

int main_exec(t_data *da, char **envp) 
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	da->children = malloc(da->pnum * sizeof(pid_t));
	if (da->children == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	set_pipe(da);
	if (check_extern_builtins(da, envp, 0) == 0)
	{
		while (i < da->pnum)
		{
			da->children[i] = -1;
			i++;
		}
		exec_recur(da, envp, 0);
		i = 0;
	}
	else
		i = 1;
	while (i < da->pnum)
	{
		if (da->children[i] != -1)
		{
			waitpid(da->children[i], &status, 0);
		}
		i++;
	}
	del_tmpfiles(da, 0);
	free(da->children);

	return (0);
}
