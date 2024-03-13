/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:03:39 by lle-pier          #+#    #+#             */
/*   Updated: 2024/01/11 11:20:34 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

static char	*ft_new_line(char *str)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_charrchr(str, '\n');
	len = (ptr - str) + 1;
	line = ft_substr(str, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

static char	*ft_erase(char *memo)
{
	char	*new_storage;
	char	*ptr;
	int		len;

	ptr = ft_charrchr(memo, '\n');
	if (!ptr)
	{
		new_storage = NULL;
		return (ft_free(&memo));
	}
	else
		len = (ptr - memo) + 1;
	if (!memo[len])
		return (ft_free(&memo));
	new_storage = ft_substr(memo, len, ft_strlen(memo) - len);
	ft_free(&memo);
	if (!new_storage)
		return (NULL);
	return (new_storage);
}

static char	*ft_reader(int fd, char *memo)
{
	ssize_t		ret;
	char		*buffer;

	ret = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(&memo));
	buffer[0] = '\0';
	while (ret > 0 && !ft_charrchr(buffer, '\n'))
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret > 0)
		{
			buffer[ret] = '\0';
			memo = ft_strjoin(memo, buffer);
		}
	}
	free(buffer);
	if (ret == -1)
		return (ft_free(&memo));
	return (memo);
}

char	*get_next_line(int fd)
{
	static char	*memorized = {0};
	char		*line;

	if (fd < 0)
		return (free(memorized), NULL);
	if ((memorized && !ft_charrchr(memorized, '\n')) || !memorized)
		memorized = ft_reader(fd, memorized);
	if (!memorized)
		return (NULL);
	line = ft_new_line(memorized);
	if (!line)
		return (ft_free(&memorized));
	memorized = ft_erase(memorized);
	return (line);
}
