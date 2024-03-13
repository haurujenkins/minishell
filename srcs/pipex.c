/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:09:45 by lle-pier          #+#    #+#             */
/*   Updated: 2024/02/27 11:08:26 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_cmd_1(t_data *da, char **envp)
{
	da->pid1 = fork();
	if (da->pid1 == -1)
	{
		close_all(da);
		free_data(da, envp);
		write(2, "Error Forking\n", 14);
		exit(EXIT_FAILURE);
	}
	if (da->pid1 == 0)
		pid_1(da, envp);
}

void	exec_cmd_2(t_data *da, char **envp)
{
	da->pid2 = fork();
	if (da->pid2 == -1)
	{
		close_all(da);
		free_data(da, envp);
		write(2, "Error Forking\n", 14);
		exit(EXIT_FAILURE);
	}
	if (da->pid2 == 0)
		pid_2(da, envp);
}

int	pipex(t_data *da, char **argv, char **envp)
{
	if (!(check_errors(da, argv)))
	{
		free_data(da, envp);
		exit(EXIT_FAILURE);
	}
	if (!(da->fd_input < 0) && !(da->cmd1 == NULL))
		exec_cmd_1(da, envp);
	if (!(da->fail_pipe == -1) && !(da->cmd2 == NULL))
		exec_cmd_2(da, envp);
	free_data(da, envp);
	waitpid(da->pid1, NULL, 0);
	waitpid(da->pid2, NULL, 0);
	return (0);
}

void	get_args(t_data *da, char **argv, char **envp)
{
	if (argv[2][0] == '\0')
		write(STDERR_FILENO, "permission denied:\n", 19);
	else
		da->cmd1 = ft_split(argv[2], ' ');
	if (da->cmd1 == NULL)
		exit(EXIT_FAILURE);
	if (argv[3][0] == '\0')
		write(STDERR_FILENO, "permission denied:\n", 19);
	else
		da->cmd2 = ft_split(argv[3], ' ');
	if (da->cmd2 == NULL)
		exit(EXIT_FAILURE);
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

int	main(int argc, char *argv[], char **envp)
{
	t_data	da;
	int		i;

	i = 0;
	if (argc != 5)
	{
		ft_printf("Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	set_all(&da);
	get_args(&da, argv, envp);
	pipex(&da, argv, envp);
	return (0);
}
