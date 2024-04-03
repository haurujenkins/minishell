/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:10:19 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/03 15:18:04 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

void	set_all(t_data *da, char **envp)
{
	int	i;

	i = 0;
	da->cmd1 = NULL;
	da->cmd = NULL;
	da->fd_input = -1;
	da->fd_output = -1;
	da->i = 0;
	da->j = 0;
	da->my_path = NULL;
	da->pid1 = 0;
	da->point_path = NULL;
	da->my_env = malloc(sizeof(char *) * (ft_tablen(envp) + 1));
	while (envp[i] != NULL)
	{
		da->my_env[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		ft_strlcpy(da->my_env[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	da->my_env[i] = NULL;
}

void	free_data(t_data *da, char **envp)
{
	// close(da->pipefd[0]);
	// close(da->pipefd[1]);
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
	if (!(envp[0] == NULL))
	{
		while (da->my_path[++da->i])
			free(da->my_path[da->i]);
		free(da->my_path);
	}
}
