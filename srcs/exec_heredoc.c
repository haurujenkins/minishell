/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:57:06 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/21 14:00:22 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define TMPFILE_NAME ".heredoc/minishell_heredoc_tmpfile"
#define MAX_RANDOM_BYTES 8

volatile sig_atomic_t stop_execution = 0;

void	sigint_handler(int signum)
{
	(void)signum;
	stop_execution = 1;
	rl_done = 1;
}

int	rl_hook_function(void)
{
	signal(SIGINT, sigint_handler);
	return (0);
}

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

void	sigquit_handler_doc(t_data *da)
{
	da->mysignal.nb_delim--;
	printf("bash: warning: here-document delimited by end-of-file (wanted `%s')\n", da->mysignal.endof);
	if (da->mysignal.nb_delim == 0)
		return ;
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


char *read_until_delimiter(char *delimiter, t_data *da)
{
	char	*line;
	int		fd;
	char	*tmpfile_name;

	tmpfile_name = generate_tmpfile_name(0);
	da->mysignal.exit = 0;
	da->mysignal.endof = delimiter;
	fd = open(tmpfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	rl_event_hook = rl_hook_function;
	while (1)
	{
		if (da->mysignal.exit == 1)
			return (tmpfile_name);
		rl_callback_handler_install("> ", NULL);
		line = readline(NULL);
		rl_callback_handler_remove();
		if (stop_execution == 1)
		{
			return (tmpfile_name);
		}
		if (!line)
		{
			sigquit_handler_doc(da);
			return (tmpfile_name);
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (da->q_heredoc == 1)
			line = temp_without_dollar(da, line);
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

int	heredoc_replace(t_data *da, int index)
{
	int			i;
	char		*tmpfile;
	int			nb_delim;
	int			j;

	while (index < da->pnum)
	{
		count_delim(da, index);
		i = 0;
		j = 0;
		nb_delim = da->mysignal.nb_delim;
		while (j < nb_delim)
		{
			if (da->delim_tab[index][i][0] == '1')
			{
				tmpfile = read_until_delimiter(da->in_tab[index][i], da);
				free(da->in_tab[index][i]);
				da->in_tab[index][i] = ft_strdup(tmpfile);
				if (stop_execution == 1)
					return (stop_execution = 0, -1);
				j++;
			}
			i++;
		}
		index++;
	}
	return (0);
}
