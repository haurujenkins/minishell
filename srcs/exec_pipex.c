/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:01:33 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/19 15:34:11 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_path(t_data *da, char **envp)
{
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

char	*get_home(char **envp)
{
	char	*home;
	int		i;

	home = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
		{
			home = ft_strdup(envp[i] + 5);
			break ;
		}
		i++;
	}
	return (home);
}

void	get_args_builtins(t_data *da, int index)
{
	char	*temp_cmd;

	temp_cmd = NULL;
	if (da->args[index][1] == NULL)
		temp_cmd = ft_strdup(da->args[index][0]);
	else
		temp_cmd = ft_strjoin(da->args[index][0], da->args[index][1]);
	if (temp_cmd[0] == '\0')
		write(STDERR_FILENO, "permission denied:\n", 19);
	else
	{
		da->cmd1 = ft_split(temp_cmd, ' ');
		free(temp_cmd);
	}
}

void	get_args(t_data *da, char **envp, int index)
{
	char	*temp_cmd;

	temp_cmd = NULL;
	if (da->args[index][1] == NULL)
		temp_cmd = ft_strdup(da->args[index][0]);
	else
		temp_cmd = ft_strjoin(da->args[index][0], da->args[index][1]);
	if (temp_cmd[0] == '\0')
		write(STDERR_FILENO, "permission denied:\n", 19);
	else
	{
		da->cmd1 = ft_split(temp_cmd, ' ');
		free(temp_cmd);
	}
	get_path(da, envp);
}
