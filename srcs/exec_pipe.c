/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:52:20 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/24 18:35:41 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_pipe(t_data *da)
{
	da->pipefd = (int **)malloc((da->pnum) * sizeof(int *));
	if (da->pipefd == NULL)
	{
		perror ("malloc");
		exit(EXIT_FAILURE);
	}
	da->i = 0;
	while (da->i < da->pnum)
	{
		da->pipefd[da->i] = (int *)malloc(2 * sizeof(int));
		if (da->pipefd[da->i] == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		if (pipe(da->pipefd[da->i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		da->i ++;
	}
}

void	free_pipe(t_data *da)
{
	da->i = 0;
	if (da->pipefd == NULL || da->pnum < 2)
		return ;
	while (da->i < da->pnum)
	{
		free(da->pipefd[da->i]);
		da->i++;
	}
	free(da->pipefd);
}
