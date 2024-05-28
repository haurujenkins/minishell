/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_read.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:44:30 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/28 15:19:10 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	count_delim(t_data *da, int index)
{
	int	i;

	i = 0;
	da->mysignal.nb_delim = 0;
	while (da->in_tab[index][i] && da->delim_tab[index][i])
	{
		if (da->delim_tab[index][i][0] == '1')
			da->mysignal.nb_delim++;
		i++;
	}
}

int	handler_while(t_data *da, char *line, char *delimiter, int fd)
{
	if (line[0] == '\0')
		printf("> \n");
	if (strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	if (da->q_heredoc == 1)
		line = temp_without_dollar(da, line);
	if (write(fd, line, strlen(line)) == -1)
	{
		perror("Erreur lors de l'écriture dans le fichier temporaire");
		return (1);
	}
	write(fd, "\n", 1);
	free(line);
	return (0);
}

int	handler_callback(t_data *da, int fd, char *line)
{
	if (stop_execution == 1)
	{
		close(fd);
		free(line);
		da->exit_status = 130;
		return (1);
	}
	if (!line)
	{
		close(fd);
		sigquit_handler_doc(da);
		return (1);
	}
	return (0);
}
