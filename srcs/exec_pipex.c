/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:01:33 by lle-pier          #+#    #+#             */
/*   Updated: 2024/03/26 15:18:32 by lle-pier         ###   ########.fr       */
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

void	get_args(t_data *da, char **envp, int index)
{
	char	*temp_cmd;

	temp_cmd = NULL;
	if (da->args[index][1] == NULL)
		temp_cmd = da->args[index][0];
	else
		temp_cmd = ft_strjoin(da->args[index][0], da->args[index][1]);
	if (temp_cmd[0] == '\0')
		write(STDERR_FILENO, "permission denied:\n", 19);
	else
	{
		da->cmd1 = ft_split(temp_cmd, ' ');
		if (da->args[index][1] != NULL)
			free(temp_cmd);
	}
	get_path(da, envp);
}
