/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:01:33 by lle-pier          #+#    #+#             */
/*   Updated: 2024/03/26 11:10:25 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_args(t_data *da, char **envp, int index)
{
	char	*temp_cmd;

	temp_cmd = NULL;
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

int	check_files(t_data *da)
{
	char	**temp_files;
	int		i;

	i = 0;
	temp_files = NULL;
	if (da->args[da->line][2] != NULL)
	{
		temp_files = ft_split(da->args[da->line][2], ' ');
		while (temp_files[i] != NULL)
		{
			da->fd_input = open(temp_files[i], O_RDONLY);
			if (da->fd_input < 0)
				perror("Error opening input file");
			free (temp_files[i]);
			i++;
		}
		free (temp_files);
	}
	if (da->args[da->line][3] != NULL)
	{
		i = 0;
		temp_files = ft_split(da->args[da->line][3], ' ');
		while (temp_files[i] != NULL)
		{
			da->fd_output = \
			open(temp_files[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (da->fd_output < 0)
			{
				close(da->fd_input);
				perror("Error opening output file");
			}
			free (temp_files[i]);
			i++;
		}
		free (temp_files);
	}
	// else if (da->line != (da->pnum - 1))
	// {
	// 	close(da->pipefd[0]);
	// 	dup2(da->pipefd[1], STDOUT_FILENO);
	// 	close(da->pipefd[1]);
	// }
	return (1);
}
