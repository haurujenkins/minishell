/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:49:04 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/14 11:09:40 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler_child()
{
	printf("\n");
}

void	sigquit_handler_child()
{
	printf("Quit (core dumped)\n");
}

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
	get_args(da, envp, index);
	check_files(da, index);
	exec_cmd(da, envp);
}

int	exec_recur(t_data *da, char **envp, int index)
{
	int	child_status;

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
			close(da->pipefd[index][1]);
		exec_recur(da, envp, index + 1);
	}
	waitpid(da->pid1, &child_status, 0);
	if (index == da->pnum - 1)
		da->exit_status = WEXITSTATUS(child_status);
	return (0);
}

void	check_cmd_stat(t_data *da)
{
	struct stat	filestat;

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

void	exec_cmd(t_data *da, char **envp)
{
	int			j;

	if (check_builtins(da) == 1)
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

	if (da->in_tab == NULL || da->in_tab[index][0] == NULL)
		return ;
	while (index < da->pnum)
	{
		i = 0;
		while (da->in_tab[index][i] != NULL)
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
	set_pipe(da);
	if (check_extern_builtins(da, envp, 0) == 0)
		exec_recur(da, envp, 0);
	return (0);
}
