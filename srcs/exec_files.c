/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:03:01 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/23 18:56:02 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void read_until_delimiter(char *delimiters[], int fd, int index) {
    char buffer[MAX_INPUT_LENGTH];
    ssize_t bytes_read;
    
	fd = open("minishell_heredoc_tmpfile", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    // Lecture de l'entrée standard jusqu'à ce qu'un des délimiteurs soit rencontré
    while ((bytes_read = read(STDIN_FILENO, buffer, MAX_INPUT_LENGTH)) > 0) 
	{
		if (ft_strnstr(buffer, delimiters[index], bytes_read) != NULL)
		{
            return; // Si l'un des délimiteurs est trouvé, arrêter la lecture
        }
        // Écrire le buffer dans le fichier temporaire
        if (write(fd, buffer, bytes_read) == -1) {
            perror("Erreur lors de l'écriture dans le fichier temporaire");
            exit(EXIT_FAILURE);
        }
    }
    // Si la lecture échoue ou si nous avons atteint la fin de fichier, afficher une erreur
    if (bytes_read == -1) {
        perror("Erreur lors de la lecture de l'entrée standard");
        exit(EXIT_FAILURE);
    }
}

void heredoc(char *delimiters[], int num_delimiters, int fd, int index) 
{
    // Si nous avons atteint le dernier délimiteur, terminer
	if (index == num_delimiters)
		return ;
    read_until_delimiter(delimiters, fd, index);
	heredoc(delimiters, num_delimiters, fd, index + 1);
}

int	check_files(t_data *da, int index)
{
	int	i;
	int	fdelim;

	i = 0;
	fdelim = 0;
	da->fd_input = -1;
	da->fd_output = -1;
	if (da->in_tab[index][0] != NULL || da->delim_tab[index][0] != NULL)
	{
		while (da->in_tab[index][i] || da->delim_tab[index][i])
		{
			if (da->delim_tab[index][i] == NULL || \
			da->delim_tab[index][i][0] == '0')
				da->fd_input = open(da->in_tab[index][i], O_RDONLY);
			else
			{
				if (i == 1)
				    break ;
				heredoc(da->delim_tab[index], ft_tablen(da->delim_tab[index]), da->fd_input, 0);
				close(da->fd_input);
				da->fd_input = open("minishell_heredoc_tmpfile", O_RDONLY);
			}
			if (da->fd_input < 0)
				perror("Error opening input file");
			i++;
		}
	}
	if (da->fd_input != -1)
	{
		if (dup2(da->fd_input, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(da->fd_input);
	}
	if (da->out_tab[index][0] != NULL)
	{
		i = 0;
		while (da->out_tab[index][i])
		{
			if (da->append_tab[index][i] == NULL || \
			da->append_tab[index][i][0] == '0')
				da->fd_output = open(da->out_tab[index][i], O_WRONLY \
				| O_CREAT | O_TRUNC, 0644);
			else
				da->fd_output = open(da->out_tab[index][i], \
				O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (da->fd_output < 0)
			{
				close(da->fd_input);
				perror("Error opening output file");
			}
			i++;
		}
	}
	if (da->fd_output != -1)
	{
		if (dup2(da->fd_output, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(da->fd_output);
	}
	return (1);
}

void	close_fd(t_data *da, int index)
{
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
}
