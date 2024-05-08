/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:57:06 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/08 15:11:07 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define TMPFILE_NAME "minishell_heredoc_tmpfile"
#define MAX_RANDOM_BYTES 8

void	count_delim(t_data *da, int index)
{
	int	i;

	i = 0;
	while (da->in_tab[index][i])
	{
		if (da->delim_tab[index][i] != NULL && \
		da->delim_tab[index][i][0] != '0')
			da->mysignal.nb_delim++;
		i++;
	}
}

void	sigint_handler_doc()
{
	printf("\n");
	exit(1);
}

void	sigquit_handler_doc(t_data *da)
{
	da->mysignal.nb_delim--;
	printf("bash: warning: here-document delimited by end-of-file (wanted `%s')\n", da->mysignal.endof);
	if (da->mysignal.nb_delim == 0)
		exit(1);
	da->mysignal.exit = 1;
}

char *generate_tmpfile_name(int i)
{
	int			urandom_fd;
	char		random_bytes[MAX_RANDOM_BYTES];
	static char	hex_chars[] = "0123456789abcdef";
	char		*tmpfile_name;
	char		*ptr;

	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (read(urandom_fd, random_bytes, MAX_RANDOM_BYTES) != MAX_RANDOM_BYTES)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	close(urandom_fd);
	// Conversion des octets aléatoires en une chaîne hexadécimale
	tmpfile_name = (char *)malloc(sizeof(char) * \
	(strlen(TMPFILE_NAME) + 2 * MAX_RANDOM_BYTES + 1));
	if (tmpfile_name == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ptr = tmpfile_name;
	strcpy(ptr, TMPFILE_NAME);
	ptr += strlen(TMPFILE_NAME);
	while (i < MAX_RANDOM_BYTES)
	{
		*ptr++ = hex_chars[(random_bytes[i] >> 4) & 0xF];
		*ptr++ = hex_chars[random_bytes[i] & 0xF];
		i++;
	}
	*ptr = '\0';
	return (tmpfile_name);
}

char	*read_until_delimiter(char *delimiter, t_data *da)
{
	char	*line;
	int		fd;
	char	*tmpfile_name;

	tmpfile_name = generate_tmpfile_name(0);
	da->mysignal.exit = 0;
	da->mysignal.endof = delimiter;
	fd = open(tmpfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	while (1)
	{
		if (da->mysignal.exit == 1)
			return (NULL);
		line = readline("> ");
		if (!line)
		{
			sigquit_handler_doc(da);
			return (NULL);
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (write(fd, line, strlen(line)) == -1)
		{
			perror("Erreur lors de l'écriture dans le fichier temporaire");
			exit(EXIT_FAILURE);
		}
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (tmpfile_name);
}

void	heredoc_replace(t_data *da, int index)
{
	int			i;
	char		*tmpfile;

	while (da->in_tab[index])
	{
		count_delim(da, index);
		i = 0;
		while (da->in_tab[index][i])
		{
			if (da->delim_tab[index][i] == NULL || \
			da->delim_tab[index][i][0] == '0')
				i++ ;
			else
			{
				signal(SIGINT, sigint_handler_doc);
				signal(SIGQUIT, SIG_IGN);
				tmpfile = read_until_delimiter(da->delim_tab[index][i], da);
				free(da->in_tab[index][i]);
				da->in_tab[index][i] = ft_strdup(tmpfile);
				da->mysignal.nb_delim--;
			}
			i++;
		}
		index++;
	}
}
