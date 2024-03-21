/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:49:04 by lle-pier          #+#    #+#             */
/*   Updated: 2024/03/21 14:41:28 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_cmd(t_data *da, char **envp)
{
	int	i;
	int	token;

	token = 0;
	get_path(da, envp);
	i = 0;
	if (!(ft_strchr(da->args[0][0], "/")) && !(envp[0] == NULL))
	{
		while (da->my_path[i])
		{
			da->cmd = ft_strjoin_slash(da->my_path[i], da->cmd1[0]);
			if (da->cmd == NULL)
			{
				free_data(da, envp);
				write(2, "Malloc Error", 12);
				exit(EXIT_FAILURE);
			}
			if (access(da->cmd, X_OK) == 0)
			{
				token = 1;
				if (da->fd_input != -1)
					dup2(da->fd_input, STDIN_FILENO);
				if (da->fd_output != -1)
					dup2(da->fd_output, STDOUT_FILENO);
				close(da->fd_input);
				close(da->fd_output);
				if (da->pid1 == -1)
				{
					free_data(da, envp);
					write(2, "Error Forking\n", 14);
					exit(EXIT_FAILURE);
				}
				else if (da->pid1 == 0)
				{
					execve(da->cmd, da->cmd1, envp);
				}
			}
			free(da->cmd);
			if (token == 1)
				break ;
			i++;
		}
	}
	return (0);
}

int	main_exec(t_data *da, char **envp)
{
	da->line = 0;
	while (da->line < da->pnum)
	{
		set_all(da);
		get_args(da, envp);
		check_files(da);
		if (da->pnum == 1)
		{
			da->pid1 = fork();
			if (da->pid1 == -1)
			{
				//close_all(da);
				free_data(da, envp);
				write(2, "Error Forking\n", 14);
				exit(EXIT_FAILURE);
			}
			if (da->pid1 == 0)
				exec_cmd(da, envp);
		}
		if (da->pnum > 1)
		{
			ft_printf("Pipexxxx\n");
		}
		waitpid(da->pid1, NULL, 0);
		da->line++;
	}
	// if (caseNum > 1)
	// 	main_pipex(da, envp);
	return (0);
}
