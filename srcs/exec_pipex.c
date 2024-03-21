/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:01:33 by lle-pier          #+#    #+#             */
/*   Updated: 2024/03/21 13:55:42 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_args(t_data *da, char **envp)
{
	char	*temp_cmd;
	int		i;

	i = 0;
	temp_cmd = NULL;
	temp_cmd = ft_strjoin(da->args[da->line][0], da->args[da->line][1]);
	if (temp_cmd[0] == '\0')
		write(STDERR_FILENO, "permission denied:\n", 19);
	else
	{
		da->cmd1 = ft_split(temp_cmd, ' ');
		while (da->cmd1[i])
		{
			printf("\nda->cmd1 = %s\n", da->cmd1[i]);
			i++;
		}
		free(temp_cmd);
	}
	get_path(da, envp);
}

int	check_files(t_data *da)
{
	if (da->args[da->line][2] != NULL)
	{
		da->fd_input = open(da->args[da->line][2], O_RDONLY);
		if (da->fd_input < 0)
			perror("Error opening input file");
	}
	if (da->args[da->line][3] != NULL)
	{
		da->fd_output = \
		open(da->args[da->line][3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (da->fd_output < 0)
		{
			close(da->fd_input);
			perror("Error opening output file");
		}
	}
	// if (da->pnum > 1)
	// {
	// 	if (pipe(da->pipefd) == -1)
	// 	{
	// 		close(da->fd_input);
	// 		close(da->fd_output);
	// 		da->fail_pipe = -1;
	// 		perror("Error creating pipe");
	// 	}
	// }
	return (1);
}
