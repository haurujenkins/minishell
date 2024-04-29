/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:03:01 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/29 15:19:26 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	read_until_delimiter(char *delimiter, int fd) 
{
	char	buffer[MAX_INPUT_LENGTH];
	ssize_t	bytes_read;

	fd = open("minishell_heredoc_tmpfile", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	bytes_read = 1;
    // Lecture de l'entrée standard jusqu'à ce qu'un des délimiteurs soit rencontré
	while (bytes_read > 0)
	{
		bytes_read = read(STDIN_FILENO, buffer, MAX_INPUT_LENGTH);
		if (ft_strnstr(buffer, delimiter, bytes_read) != NULL)
		{
			return ; // Si l'un des délimiteurs est trouvé, arrêter la lecture
		}
		// Écrire le buffer dans le fichier temporaire
		if (write(fd, buffer, bytes_read) == -1)
		{
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

// void heredoc(char *check_tab[], char *delimiters[], int fd, int index) 
// {
// 	int	num_delimiters;

//     // Si nous avons atteint le dernier délimiteur, terminer
// 	num_delimiters = 0;
// 	while (check_tab[index] != NULL)
// 	{
// 		if (check_tab[index][0] == '1')
// 			num_delimiters++;
// 	}
// 	if (index == num_delimiters)
// 		return ;
//     read_until_delimiter(check_tab, delimiters, fd, index);
// 	heredoc(check_tab, delimiters, fd, index + 1);
// }

int	check_files(t_data *da, int index)
{
	int			i;
	int			fdelim;
	struct stat	filestat;

	i = 0;
	fdelim = 0;
	da->fd_input = -1;
	da->fd_output = -1;
	if (da->in_tab[index][0] != NULL)
	{
		while (da->in_tab[index][i])
		{
			if (da->delim_tab[index][i] == NULL || \
			da->delim_tab[index][i][0] == '0')
				da->fd_input = open(da->in_tab[index][i], O_RDONLY);
			else
			{
				read_until_delimiter(da->in_tab[index][i], da->fd_input);
				close(da->fd_input);
				da->fd_input = open("minishell_heredoc_tmpfile", O_RDONLY);
			}
			if (da->fd_input < 0)
			{
				if (stat(da->in_tab[index][i], &filestat) == -1)
				{
					write(2, "bash: ", 6);
					write(2, da->in_tab[index][i], ft_strlen(da->in_tab[index][i]));
					write(2, ": No such file or directory\n", 28);
					exit(1);
				}
				if (S_ISDIR(filestat.st_mode))
				{
					write(2, "bash: ", 6);
					write(2, da->in_tab[index][i], ft_strlen(da->in_tab[index][i]));
					write(2, ": Is a directory\n", 17);
					exit(1);
				}
				if (!(filestat.st_mode & S_IXUSR))
				{
					close(da->fd_input);
					write(2, "bash: ", 6);
					write(2, da->in_tab[index][i], ft_strlen(da->in_tab[index][i]));
					write(2, ": Permission denied\n", 21);
					exit(1);
				}
			}
			i++;
		}
	}
	if (da->fd_input != -1)
	{
		if (dup2(da->fd_input, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(127);
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
				if (stat(da->out_tab[index][i], &filestat) == -1)
				{
					write(2, "bash: ", 6);
					write(2, da->out_tab[index][i], ft_strlen(da->out_tab[index][i]));
					write(2, ": No such file or directory\n", 28);
					exit(1);
				}
				if (S_ISDIR(filestat.st_mode))
				{
					write(2, "bash: ", 6);
					write(2, da->out_tab[index][i], ft_strlen(da->out_tab[index][i]));
					write(2, ": Is a directory\n", 17);
					exit(1);
				}
				if (!(filestat.st_mode & S_IXUSR))
				{
					close(da->fd_input);
					write(2, "bash: ", 6);
					write(2, da->out_tab[index][i], ft_strlen(da->out_tab[index][i]));
					write(2, ": Permission denied\n", 21);
					exit(1);
				}
			}
			i++;
		}
	}
	if (da->fd_output != -1)
	{
		if (dup2(da->fd_output, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(127);
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
