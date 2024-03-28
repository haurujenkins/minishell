/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:49:04 by lle-pier          #+#    #+#             */
/*   Updated: 2024/03/27 18:05:01 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_recur(t_data *da, char **envp, int index)
{
	//Condition d'arrêt de la récursion
	if (index == da->pnum)
	{
	// Exécution de la dernière commande
		//exec_cmd(da, envp, index);
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
	else if (da->pid1 == 0) //processus enfant
	{
		if (index != 0) //si ce n'est pas la premiere commande
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
		// fermeture des fd non utilises
		da->i = 0;
		while (da->i < da->pnum - 1)
		{
			if (da->i != index - 1 && da->i != index)
			{
				close(da->pipefd[da->i][0]);
				close(da->pipefd[da->i][1]);
			}
			da->i++;
		}
		// execution de la commande
		exec_cmd(da, envp, index);
		// perror("execve");
		// exit(EXIT_FAILURE);
	}
	else //processus parent
	{
		if (index != da->pnum - 1)
			close(da->pipefd[index][1]);
		//appel recursif
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
		da->cmd = ft_strjoin_slash(da->my_path[i], da->cmd1[0]);
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
	set_all(da, envp);
	//check_files(da);
	if (check_extern_builtins(da, envp, 0) == 0)
		exec_recur(da, envp, 0);
	// if (caseNum > 1)
	// 	main_pipex(da, envp);
	return (0);
}
