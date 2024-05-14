/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:57:06 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/14 13:32:54 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define TMPFILE_NAME ".heredoc/minishell_heredoc_tmpfile"
#define MAX_RANDOM_BYTES 8

bool	stop_execution = false;

void	sigint_handler(int signum)
{
	(void) signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	stop_execution = true;
}

void	count_delim(t_data *da, int index)
{
	int	i;

	i = 0;
	da->mysignal.nb_delim = 0;
	while (da->in_tab[index][i])
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
    char    buffer[1024];
    int     fd;
    char    *tmpfile_name;
    ssize_t len;

    tmpfile_name = generate_tmpfile_name(0);
    da->mysignal.exit = 0;
    da->mysignal.endof = delimiter;
    fd = open(tmpfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	stop_execution = 0;
    while (1)
    {
        if (da->mysignal.exit == 1)
            return (tmpfile_name);
        // Utiliser read() à la place de readline()
        write(STDOUT_FILENO, "> ", 2); // Afficher le prompt
        len = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

        if (stop_execution == 1) {
            write(1, "ctrl+c\n", 7);
            return (tmpfile_name);
        }
        if (len <= 0) {
            // EOF or error
            if (len == 0) {
                printf("\nEnd of input. Exiting...\n");
            } else {
                perror("Error reading input");
            }
            return (NULL);
        }

        // Ajouter un NULL-terminator à la fin de la chaîne
        buffer[len] = '\0';

        // Supprimer le caractère de nouvelle ligne si présent
        if (buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';

        if (strcmp(buffer, delimiter) == 0)
            break;

        if (write(fd, buffer, strlen(buffer)) == -1)
        {
            perror("Erreur lors de l'écriture dans le fichier temporaire");
            return (NULL);
        }

        write(fd, "\n", 1);
    }

    close(fd);
    return tmpfile_name;
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
		printf("nb_delim = %d\n", nb_delim);
		while (j < nb_delim)
		{
			if (da->delim_tab[index][i][0] == '1')
			{
				tmpfile = read_until_delimiter(da->in_tab[index][i], da);
				if (tmpfile == NULL || stop_execution == 1)
					return (-1);
				free(da->in_tab[index][i]);
				da->in_tab[index][i] = ft_strdup(tmpfile);
				j++;
			}
			i++;
		}
		index++;
	}
	return (0);
}
