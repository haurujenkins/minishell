/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:49:04 by lle-pier          #+#    #+#             */
/*   Updated: 2024/03/14 16:27:53 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_cmd(t_data *da, char **args, char **envp)
{
	int	i;
	int	token;

	token = 0;
	if (args == NULL)
		return (0);
	get_path(da, envp);
	i = 0;
	if (args[0][0] == '\0')
		write(STDERR_FILENO, "permission denied:\n", 19);
	else
		da->cmd1 = ft_split(args[0], ' ');
	if (!(ft_strchr(args[0], "/")) && !(envp[0] == NULL))
	{
		while (da->my_path[i])
		{
			da->cmd = ft_strjoin(da->my_path[i], da->cmd1[0]);
			if (da->cmd == NULL)
			{
				free_data(da, envp);
				write(2, "Malloc Error", 12);
				exit(EXIT_FAILURE);
			}
			if (access(da->cmd, X_OK) == 0)
			{
				token = 1;
				da->pid1 = fork();
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
				else
				{
					wait(NULL);
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

int	main_exec(char **args, char **envp)
{
	t_data	da;
	int		pNum;

	pNum = 0;
	while (args[pNum])
		pNum++;
	set_all(&da);
	if (pNum == 1)
		exec_cmd(&da, args, envp);
	if (pNum > 2)
		ft_printf("Pipexxxx\n");
	// if (caseNum > 1)
	// 	main_pipex(&da, args, envp);
	return (0);
}
