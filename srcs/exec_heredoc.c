/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:57:06 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/30 13:40:57 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_stop_execution = 0;

int	rl_hook_function(void)
{
	signal(SIGINT, sigint_handler);
	return (0);
}

void	*tmpfile_hex(char *ptr, char *random_bytes, int i)
{
	static char	hex_chars[] = "0123456789abcdef";

	while (i < MAX_RANDOM_BYTES)
	{
		*ptr++ = hex_chars[(random_bytes[i] >> 4) & 0xF];
		*ptr++ = hex_chars[random_bytes[i] & 0xF];
		i++;
	}
	return (ptr);
}

char	*generate_tmpfile_name(int i)
{
	int			urandom_fd;
	char		random_bytes[MAX_RANDOM_BYTES];
	char		*tmpfile_name;
	char		*ptr;

	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd == -1)
		return (perror("open"), NULL);
	if (read(urandom_fd, random_bytes, MAX_RANDOM_BYTES) != MAX_RANDOM_BYTES)
		return (perror("read"), NULL);
	close(urandom_fd);
	tmpfile_name = (char *)malloc(sizeof(char) * \
	(strlen(TMPFILE_NAME) + 2 * MAX_RANDOM_BYTES + 1));
	if (tmpfile_name == NULL)
		return (perror("malloc"), NULL);
	ptr = tmpfile_name;
	strcpy(ptr, TMPFILE_NAME);
	ptr += strlen(TMPFILE_NAME);
	ptr = tmpfile_hex(ptr, random_bytes, i);
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
	if (fd == -1)
		return (perror("open"), NULL);
	rl_event_hook = rl_hook_function;
	while (1)
	{
		if (da->mysignal.exit == 1)
			return (rl_event_hook = NULL, tmpfile_name);
		rl_callback_handler_install("> ", NULL);
		line = readline(NULL);
		rl_callback_handler_remove();
		if (handler_callback(da, fd, line) == 1)
			return (rl_event_hook = NULL, tmpfile_name);
		if (handler_while(da, line, delimiter, fd) == 1)
			break ;
	}
	close(fd);
	return (rl_event_hook = NULL, tmpfile_name);
}

int	heredoc_replace(t_data *da, int index, int i)
{
	char		*tmpfile;
	int			nb_delim;
	int			j;

	while (index < da->pnum)
	{
		count_delim(da, index);
		j = -1;
		nb_delim = da->mysignal.nb_delim;
		while (++j < nb_delim)
		{
			if (da->delim_tab[index][i][0] == '1')
			{
				tmpfile = read_until_delimiter(da->in_tab[index][i], da);
				free(da->in_tab[index][i]);
				da->in_tab[index][i] = ft_strdup(tmpfile);
				free(tmpfile);
				if (g_stop_execution == 1)
					return (g_stop_execution = 0, -1);
			}
			i++;
		}
		index++;
	}
	return (0);
}
